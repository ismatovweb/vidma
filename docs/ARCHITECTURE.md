# Архитектура Vidma

## Компоненты

- Vidma Server (C++) — control plane: REST API, WebSocket signaling, выдача токенов. Медиа не обрабатывает.
- LiveKit (SFU) — принимает один поток от клиента, раздаёт остальным. 10+ участников, E2EE, DataChannel.
- coturn — STUN + TURN fallback. REST-аутентификация.
- nginx — TLS, reverse proxy, rate limit, CSP, HSTS.
- Клиент — HTML/CSS/JS, livekit-client SDK. История чата только локально, в IndexedDB.

## Потоки

Создание комнаты:
Browser POST /api/room/create -> Vidma Server -> генерирует roomId (CSPRNG), подписывает LiveKit JWT -> возвращает {roomId, token}

Вход:
Browser WSS /ws (join) -> Vidma Server -> выдаёт livekitToken + turnCredentials
Browser WSS /rtc (LiveKit) -> LiveKit SFU -> публикует один поток

Чат:
Browser A DataChannel (E2EE) -> LiveKit -> Browser B -> сохраняет локально

## Безопасность

- TLS везде
- Медиа: DTLS-SRTP
- Signaling: WSS + проверка Origin
- sessionId генерирует сервер
- TURN-креды: REST auth, 5 минут
- Rate limit: nginx + token bucket
- CSP строгая, без внешних скриптов
- Логи анонимизированы, retention 30 дней
