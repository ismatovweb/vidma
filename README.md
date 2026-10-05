# Vidma

> Бесплатные видеозвонки без регистрации. Открытый исходный код.

Vidma — сервис видеоконференций в браузере. Без установки, без регистрации, с шифрованием WebRTC (DTLS-SRTP) и E2EE.

## Возможности

- Видеозвонки в браузере — без плагинов
- До 10 участников (SFU LiveKit)
- Чат внутри звонка (E2EE)
- Демонстрация экрана
- Локализация: English, Русский
- Без регистрации — только имя
- Open source под AGPL-3.0

## Стек

- Backend: C++17, cpp-httplib, nlohmann/json
- Медиа: LiveKit (SFU)
- TURN/STUN: coturn
- Reverse proxy: nginx
- Контейнеризация: Docker + Docker Compose

## Сборка

    mkdir build && cd build
    cmake ..
    make -j
    ./videocall

## Документация

- [Архитектура](docs/ARCHITECTURE.md)
- [Дорожная карта](docs/ROADMAP.md)
- [Безопасность](SECURITY.md)

## Лицензия

AGPL-3.0. См. [LICENSE](LICENSE).
