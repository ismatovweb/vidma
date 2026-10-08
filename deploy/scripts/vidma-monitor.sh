#!/bin/bash

[ -f /etc/vidma.env ] && set -a && . /etc/vidma.env && set +a
# Vidma health monitoring
# Проверяет /api/health каждую минуту (из cron), при падении шлёт в Telegram

CHAT_ID="${TG_CHAT_ID:-1415377874}"
PROXY="socks5h://127.0.0.1:1080"
URL="https://vidma.online/api/health"
STATE_FILE="/var/lib/vidma-monitor.state"
LOG_FILE="/var/log/vidma-monitor.log"
MAX_LOG_LINES=5000

# Создаём директорию для state
mkdir -p "$(dirname "$STATE_FILE")"

log() {
    echo "[$(date '+%Y-%m-%d %H:%M:%S')] $1" >> "$LOG_FILE"
    # Ротация
    if [ -f "$LOG_FILE" ]; then
        lines=$(wc -l < "$LOG_FILE")
        if [ "$lines" -gt "$MAX_LOG_LINES" ]; then
            tail -n 1000 "$LOG_FILE" > "$LOG_FILE.tmp" && mv "$LOG_FILE.tmp" "$LOG_FILE"
        fi
    fi
}

send_telegram() {
    curl -s --max-time 15 --proxy "$PROXY" \
        -X POST "https://api.telegram.org/bot${BOT_TOKEN}/sendMessage" \
        -d "chat_id=${CHAT_ID}" \
        -d "parse_mode=HTML" \
        -d "text=$1" > /dev/null 2>&1
}

# Проверка через прокси (API Telegram доступен только так, но health через прямой https должен работать)
# Проверяем health напрямую — vidma.online доступен из РФ
HTTP_CODE=$(curl -s --max-time 10 -o /dev/null -w "%{http_code}" "$URL" 2>/dev/null)
RESPONSE=$(curl -s --max-time 10 "$URL" 2>/dev/null)

# Прочитаем предыдущее состояние
PREV_STATE="unknown"
if [ -f "$STATE_FILE" ]; then
    PREV_STATE=$(cat "$STATE_FILE")
fi

# Определяем текущее состояние
if [ "$HTTP_CODE" = "200" ] && echo "$RESPONSE" | grep -q '"status":"ok"'; then
    CURRENT_STATE="up"
else
    CURRENT_STATE="down"
fi

# Логируем
log "HTTP $HTTP_CODE, state=$CURRENT_STATE (prev=$PREV_STATE)"

# Обрабатываем переходы
if [ "$CURRENT_STATE" = "down" ] && [ "$PREV_STATE" != "down" ]; then
    # Только что упал
    send_telegram "🚨 <b>Vidma DOWN</b>%0A%0AHTTP: $HTTP_CODE%0ATime: $(date '+%Y-%m-%d %H:%M:%S MSK')%0AURL: $URL"
    log "ALERT sent: DOWN"
elif [ "$CURRENT_STATE" = "up" ] && [ "$PREV_STATE" = "down" ]; then
    # Восстановлен
    send_telegram "✅ <b>Vidma is UP again</b>%0A%0ATime: $(date '+%Y-%m-%d %H:%M:%S MSK')"
    log "ALERT sent: RECOVERED"
fi

echo "$CURRENT_STATE" > "$STATE_FILE"

# ============ LiveKit container check ============
LK_STATE_FILE="/var/lib/vidma-monitor-lk.state"
LK_STATE=$(docker inspect --format='{{.State.Running}}' livekit-livekit-1 2>/dev/null || echo "false")
LK_PREV="unknown"
[ -f "$LK_STATE_FILE" ] && LK_PREV=$(cat "$LK_STATE_FILE")

if [ "$LK_STATE" = "true" ]; then
    LK_NOW="up"
else
    LK_NOW="down"
fi

if [ "$LK_NOW" = "down" ] && [ "$LK_PREV" != "down" ]; then
    send_telegram "🚨 <b>LiveKit DOWN</b>%0A%0ATime: $(date '+%Y-%m-%d %H:%M:%S MSK')%0AContainer: livekit-livekit-1"
    log "ALERT: LiveKit DOWN"
elif [ "$LK_NOW" = "up" ] && [ "$LK_PREV" = "down" ]; then
    send_telegram "✅ <b>LiveKit is UP again</b>%0A%0ATime: $(date '+%Y-%m-%d %H:%M:%S MSK')"
    log "ALERT: LiveKit RECOVERED"
fi
echo "$LK_NOW" > "$LK_STATE_FILE"

# ============ coturn check ============
TURN_STATE_FILE="/var/lib/vidma-monitor-turn.state"
TURN_ACTIVE=$(systemctl is-active coturn 2>/dev/null || echo "unknown")
TURN_PREV="unknown"
[ -f "$TURN_STATE_FILE" ] && TURN_PREV=$(cat "$TURN_STATE_FILE")

if [ "$TURN_ACTIVE" = "active" ]; then
    TURN_NOW="up"
else
    TURN_NOW="down"
fi

if [ "$TURN_NOW" = "down" ] && [ "$TURN_PREV" != "down" ]; then
    send_telegram "🚨 <b>coturn DOWN</b>%0A%0ATime: $(date '+%Y-%m-%d %H:%M:%S MSK')%0AState: $TURN_ACTIVE"
    log "ALERT: coturn DOWN ($TURN_ACTIVE)"
elif [ "$TURN_NOW" = "up" ] && [ "$TURN_PREV" = "down" ]; then
    send_telegram "✅ <b>coturn is UP again</b>%0A%0ATime: $(date '+%Y-%m-%d %H:%M:%S MSK')"
    log "ALERT: coturn RECOVERED"
fi
echo "$TURN_NOW" > "$TURN_STATE_FILE"

# ============ Plausible status check ============
PL_STATE_FILE="/var/lib/vidma-monitor-plausible.state"
PL_URL="https://status.vidma.online/api/health"
PL_CODE=$(curl -s --max-time 10 -o /dev/null -w "%{http_code}" "$PL_URL" 2>/dev/null)
PL_PREV="unknown"
[ -f "$PL_STATE_FILE" ] && PL_PREV=$(cat "$PL_STATE_FILE")

if [ "$PL_CODE" = "200" ]; then
    PL_NOW="up"
else
    PL_NOW="down"
fi

if [ "$PL_NOW" = "down" ] && [ "$PL_PREV" != "down" ]; then
    send_telegram "🚨 <b>Plausible DOWN</b>%0A%0AHTTP: $PL_CODE%0ATime: $(date '+%Y-%m-%d %H:%M:%S MSK')%0AURL: $PL_URL"
    log "ALERT: Plausible DOWN (HTTP $PL_CODE)"
elif [ "$PL_NOW" = "up" ] && [ "$PL_PREV" = "down" ]; then
    send_telegram "✅ <b>Plausible is UP again</b>%0A%0ATime: $(date '+%Y-%m-%d %H:%M:%S MSK')"
    log "ALERT: Plausible RECOVERED"
fi
echo "$PL_NOW" > "$PL_STATE_FILE"

# ============ Disk usage check ============
DISK_STATE="/var/lib/vidma-monitor-disk.state"
DISK_USE=$(df / | tail -1 | awk '{print $5}' | tr -d '%')
DISK_PREV="unknown"
[ -f "$DISK_STATE" ] && DISK_PREV=$(cat "$DISK_STATE")

if [ "$DISK_USE" -ge 90 ]; then
    DISK_NOW="alert"
else
    DISK_NOW="ok"
fi

if [ "$DISK_NOW" = "alert" ] && [ "$DISK_PREV" != "alert" ]; then
    send_telegram "⚠️ <b>Disk usage ${DISK_USE}%</b>%0A%0AServer: vidma.online%0ATime: $(date '+%Y-%m-%d %H:%M:%S MSK')"
    log "ALERT: disk ${DISK_USE}%"
elif [ "$DISK_NOW" = "ok" ] && [ "$DISK_PREV" = "alert" ]; then
    send_telegram "✅ <b>Disk usage OK (${DISK_USE}%)</b>%0A%0ATime: $(date '+%Y-%m-%d %H:%M:%S MSK')"
    log "RECOVERED: disk ${DISK_USE}%"
fi
echo "$DISK_NOW" > "$DISK_STATE"

# ============ RAM usage check ============
RAM_STATE="/var/lib/vidma-monitor-ram.state"
RAM_USE=$(free | awk '/^Mem:/ {printf "%.0f", $3/$2*100}')
RAM_PREV="unknown"
[ -f "$RAM_STATE" ] && RAM_PREV=$(cat "$RAM_STATE")

if [ "$RAM_USE" -ge 90 ]; then
    RAM_NOW="alert"
else
    RAM_NOW="ok"
fi

if [ "$RAM_NOW" = "alert" ] && [ "$RAM_PREV" != "alert" ]; then
    send_telegram "⚠️ <b>RAM usage ${RAM_USE}%</b>%0A%0AServer: vidma.online%0ATime: $(date '+%Y-%m-%d %H:%M:%S MSK')"
    log "ALERT: RAM ${RAM_USE}%"
elif [ "$RAM_NOW" = "ok" ] && [ "$RAM_PREV" = "alert" ]; then
    send_telegram "✅ <b>RAM usage OK (${RAM_USE}%)</b>%0A%0ATime: $(date '+%Y-%m-%d %H:%M:%S MSK')"
    log "RECOVERED: RAM ${RAM_USE}%"
fi
echo "$RAM_NOW" > "$RAM_STATE"

# ============ SSL certificates check (14 days threshold) ============
for DOMAIN in vidma.online status.vidma.online; do
    SSL_STATE="/var/lib/vidma-monitor-ssl-${DOMAIN}.state"
    SSL_PREV="unknown"
    [ -f "$SSL_STATE" ] && SSL_PREV=$(cat "$SSL_STATE")

    # Check if cert expires within 14 days (1209600 seconds)
    if echo | timeout 10 openssl s_client -servername "$DOMAIN" -connect "$DOMAIN:443" 2>/dev/null         | openssl x509 -checkend 1209600 -noout 2>/dev/null; then
        SSL_NOW="ok"
    else
        SSL_NOW="alert"
    fi

    if [ "$SSL_NOW" = "alert" ] && [ "$SSL_PREV" != "alert" ]; then
        EXPIRY=$(echo | timeout 10 openssl s_client -servername "$DOMAIN" -connect "$DOMAIN:443" 2>/dev/null             | openssl x509 -noout -enddate 2>/dev/null | cut -d= -f2)
        send_telegram "🔒 <b>SSL expiring soon: ${DOMAIN}</b>%0A%0AExpires: ${EXPIRY}%0ATime: $(date '+%Y-%m-%d %H:%M:%S MSK')"
        log "ALERT: SSL ${DOMAIN} expires ${EXPIRY}"
    elif [ "$SSL_NOW" = "ok" ] && [ "$SSL_PREV" = "alert" ]; then
        send_telegram "✅ <b>SSL renewed: ${DOMAIN}</b>%0A%0ATime: $(date '+%Y-%m-%d %H:%M:%S MSK')"
        log "RECOVERED: SSL ${DOMAIN}"
    fi
    echo "$SSL_NOW" > "$SSL_STATE"
done
