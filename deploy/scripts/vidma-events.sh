#!/bin/bash

[ -f /etc/vidma.env ] && set -a && . /etc/vidma.env && set +a
# Watches vidma events + feedback logs, sends to Telegram on new entries.

CHAT_ID="${TG_CHAT_ID:-1415377874}"
PROXY="socks5h://127.0.0.1:1080"
EVENTS_LOG="/opt/vidma/vidma_events.log"
FEEDBACK_LOG="/var/log/vidma-feedback.jsonl"
STATE_DIR="/var/lib/vidma-events-state"
LOG="/var/log/vidma-events.log"

mkdir -p "$STATE_DIR"

# DEBUG: пишем всё в лог, чтобы видеть что происходит
dbg() { echo "[$(date '+%Y-%m-%d %H:%M:%S')] $1" >> "$LOG"; }

send_tg() {
    curl -s --max-time 15 --proxy "$PROXY" \
        -X POST "https://api.telegram.org/bot${BOT_TOKEN}/sendMessage" \
        -d "chat_id=${CHAT_ID}" \
        -d "parse_mode=HTML" \
        -d "text=$1" >/dev/null 2>&1
    return $?
}

# read_offset: если state нет — создаём его с текущим кол-вом строк
read_offset() {
    local name=$1
    local file=$2
    local state="$STATE_DIR/$name.offset"
    if [ -f "$state" ]; then
        cat "$state"
    else
        local n=0
        [ -f "$file" ] && n=$(wc -l < "$file")
        echo "$n" > "$state"
        echo "$n"
    fi
}

save_offset() { echo "$2" > "$STATE_DIR/$1.offset"; }

MESSAGES=""
COUNT=0

# === Events log ===
if [ -f "$EVENTS_LOG" ]; then
    OFFSET=$(read_offset "events" "$EVENTS_LOG")
    TOTAL=$(wc -l < "$EVENTS_LOG")
    dbg "events: offset=$OFFSET total=$TOTAL"
    if [ "$TOTAL" -gt "$OFFSET" ]; then
        NEW=$(tail -n +$((OFFSET + 1)) "$EVENTS_LOG")
        while IFS= read -r line; do
            [ -z "$line" ] && continue

            # Skip token_req (too noisy — duplicate of room_create)
            if echo "$line" | grep -q 'token_req'; then
                continue
            fi

            if echo "$line" | grep -q 'room_create id='; then
                RID=$(echo "$line" | sed -n 's/.*room_create id=\([^ ]*\).*/\1/p')
                [ -n "$RID" ] && MESSAGES="${MESSAGES}🎥 <b>Новая комната</b> ${RID}%0A" && COUNT=$((COUNT+1))

            elif echo "$line" | grep -q 'room_closed id='; then
                RID=$(echo "$line" | sed -n 's/.*room_closed id=\([^ ]*\).*/\1/p')
                LAST=$(echo "$line" | sed -n 's/.*last_user=\([^ ]*\).*/\1/p')
                LAST=${LAST//_/ }
                [ -z "$LAST" ] && LAST="Гость"
                MESSAGES="${MESSAGES}🏁 <b>Комната закрыта</b> ${RID} (последний: ${LAST})%0A" && COUNT=$((COUNT+1))

            elif echo "$line" | grep -q ' join room='; then
                RID=$(echo "$line" | sed -n 's/.*join room=\([^ ]*\).*/\1/p')
                NAME=$(echo "$line" | sed -n 's/.*name=\([^ ]*\).*/\1/p')
                CNT=$(echo "$line" | sed -n 's/.*count=\([0-9]*\).*/\1/p')
                NAME=${NAME//_/ }
                [ -z "$NAME" ] && NAME="Гость"
                [ -z "$CNT" ] && CNT="?"
                MESSAGES="${MESSAGES}👤 <b>${NAME}</b> вошёл в ${RID} (сейчас: ${CNT})%0A" && COUNT=$((COUNT+1))

            elif echo "$line" | grep -q ' leave room='; then
                RID=$(echo "$line" | sed -n 's/.*leave room=\([^ ]*\).*/\1/p')
                NAME=$(echo "$line" | sed -n 's/.*name=\([^ ]*\).*/\1/p')
                REM=$(echo "$line" | sed -n 's/.*remaining=\([0-9]*\).*/\1/p')
                NAME=${NAME//_/ }
                [ -z "$NAME" ] && NAME="Гость"
                if [ "$REM" = "0" ]; then
                    # Don't show "покинул" — will show "комната закрыта" на след. строке
                    :
                else
                    [ -z "$REM" ] && REM="?"
                    MESSAGES="${MESSAGES}🚪 <b>${NAME}</b> покинул ${RID} (осталось: ${REM})%0A" && COUNT=$((COUNT+1))
                fi
            fi
        done <<< "$NEW"
        save_offset "events" "$TOTAL"
    fi
else
    dbg "events: log not found at $EVENTS_LOG"
fi

# === Feedback log ===
if [ -f "$FEEDBACK_LOG" ]; then
    OFFSET=$(read_offset "feedback" "$FEEDBACK_LOG")
    TOTAL=$(wc -l < "$FEEDBACK_LOG")
    dbg "feedback: offset=$OFFSET total=$TOTAL"
    if [ "$TOTAL" -gt "$OFFSET" ]; then
        NEW=$(tail -n +$((OFFSET + 1)) "$FEEDBACK_LOG")
        while IFS= read -r line; do
            [ -z "$line" ] && continue
            PARSED=$(echo "$line" | python3 -c "
import sys, json
try:
    d = json.load(sys.stdin)
    r = d.get('rating', 0)
    c = (d.get('comment', '') or '').replace('&','&amp;').replace('<','&lt;').replace('>','&gt;')[:200]
    room = d.get('roomId', 'unknown')
    print(f'{r}|{c}|{room}')
except: pass
" 2>/dev/null)
            [ -z "$PARSED" ] && continue
            RATING=$(echo "$PARSED" | cut -d'|' -f1)
            COMMENT=$(echo "$PARSED" | cut -d'|' -f2)
            ROOM=$(echo "$PARSED" | cut -d'|' -f3)
            # Пропускаем пустые отзывы (rating=0 и без коммента)
            if [ "$RATING" = "0" ] && [ -z "$COMMENT" ]; then
                continue
            fi
            if [ "$RATING" != "0" ]; then
                STARS=""
                i=1
                while [ $i -le $RATING ]; do STARS="${STARS}★"; i=$((i+1)); done
                MSG="⭐ Оценка ${STARS} (${RATING}/5) · ${ROOM}%0A"
            else
                MSG="💬 Отзыв · ${ROOM}%0A"
            fi
            [ -n "$COMMENT" ] && MSG="${MSG}<i>${COMMENT}</i>%0A"
            MESSAGES="${MESSAGES}${MSG}"
            COUNT=$((COUNT+1))
        done <<< "$NEW"
        save_offset "feedback" "$TOTAL"
    fi
fi

# ROTATE: events log
if [ -f "$EVENTS_LOG" ]; then
    LINES=$(wc -l < "$EVENTS_LOG")
    if [ "$LINES" -gt 10000 ]; then
        tail -n 2000 "$EVENTS_LOG" > "$EVENTS_LOG.tmp" && mv "$EVENTS_LOG.tmp" "$EVENTS_LOG"
        # Сбрасываем offset до нового размера
        echo "$(wc -l < $EVENTS_LOG)" > "$STATE_DIR/events.offset"
        dbg "ROTATED events log to 2000 lines"
    fi
fi

if [ "$COUNT" -eq 0 ] || [ -z "$MESSAGES" ]; then
    dbg "nothing new, exit"
    exit 0
fi

TIME=$(date '+%d.%m.%Y %H:%M MSK')
FULL="📊 <b>Vidma — активность</b>%0A%0A${MESSAGES}%0A🕐 ${TIME}"

if send_tg "$FULL"; then
    dbg "sent $COUNT events OK"
else
    dbg "send_tg FAILED"
fi
