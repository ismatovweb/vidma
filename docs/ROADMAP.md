# Дорожная карта

## Sprint 0 — Фундамент
- [x] Репозиторий, лицензия AGPL-3.0
- [x] README, SECURITY, CONTRIBUTING, CODE_OF_CONDUCT
- [ ] GitHub, первый коммит

## Sprint 1 — P0 Безопасность
- [ ] nginx: TLS, WSS, rate limit, CSP
- [ ] Убрать Yandex.Metrika и рекламу
- [ ] Убрать захардкоженные TURN-креды
- [ ] /api/turn-credentials
- [ ] Серверные sessionId
- [ ] Проверка комнаты для target
- [ ] Fix lifetime WebSocket
- [ ] Валидация входных данных
- [ ] Лимиты: 10 участников, TTL комнат
- [ ] Анонимизация логов

## Sprint 2 — LiveKit
- [ ] LiveKit Cloud (пока)
- [ ] /api/room/create возвращает LiveKit-токен
- [ ] Клиент: livekit-client
- [ ] Тест на 10 участников

## Sprint 3 — Чат
- [ ] DataChannel
- [ ] UI: панель чата
- [ ] История в IndexedDB

## Sprint 4 — Глобализация
- [ ] i18n: en, ru
- [ ] Privacy Policy, Terms, Cookie Policy
- [ ] Cookie consent

## Sprint 5 — GDPR
- [ ] Retention логов
- [ ] Анонимизация IP
- [ ] /api/me/delete

## Sprint 6 — Пентест и запуск
- [ ] OWASP ZAP
- [ ] Нагрузочный тест
- [ ] Публичный запуск
