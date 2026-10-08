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
