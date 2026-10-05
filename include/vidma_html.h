// Auto-generated from Server.h by sprint1_extract.py
// HTML template for the Vidma main page. Do not edit by hand.
#ifndef VIDMA_HTML_H
#define VIDMA_HTML_H

constexpr const char* VIDMA_HTML = R"html(<!DOCTYPE html>
<html lang="ru">
<head>

    



    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no, viewport-fit=cover">
    <meta name="apple-mobile-web-app-capable" content="yes">
    <meta name="theme-color" content="#121212">
    <title>Vidma — Бесплатные видеозвонки без регистрации</title>
    <meta name="description" content="Vidma — видеозвонки без регистрации и ограничений по времени. Создайте комнату и общайтесь с друзьями или коллегами по видеосвязи прямо в браузере.">
    <meta name="keywords" content="видеозвонки, видеоконференции, бесплатные звонки, без регистрации, созвон, видеосвязь, комната, WebRTC">
    <link rel="canonical" href="https://vidma.online/">
    <meta property="og:title" content="Vidma — бесплатные видеозвонки без регистрации">
    <meta property="og:description" content="Видеозвонки в один клик. Конфиденциально, без ограничений по времени и регистрации.">
    <meta property="og:type" content="website">
    <meta property="og:url" content="https://vidma.online/">
    <meta property="og:image" content="https://vidma.online/favicon.ico">
    <meta name="twitter:card" content="summary">
    <meta name="twitter:title" content="Vidma — бесплатные видеозвонки без регистрации">
    <meta name="twitter:description" content="Видеозвонки в один клик. Конфиденциально, без ограничений и регистрации.">
    <link rel="icon" href="/favicon.ico">
    
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; }
        body {
            font-family: 'Inter', -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif;
            background: #121212;
            color: #e0e0e0;
            line-height: 1.5;
            -webkit-font-smoothing: antialiased;
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            min-height: 100vh;
            padding: 20px;
        }
        .container { max-width: 1200px; width: 100%; text-align: center; }
        header { margin-bottom: 40px; }
        .logo {
            font-size: 3.5rem;
            font-weight: 700;
            letter-spacing: -0.02em;
            color: #8b5cf6;
            margin-bottom: 10px;
        }
        .privacy-badge {
            display: inline-flex;
            align-items: center;
            gap: 8px;
            background: rgba(139,92,246,0.1);
            padding: 8px 24px;
            border-radius: 60px;
            margin-bottom: 16px;
            font-size: 0.95rem;
            font-weight: 500;
            color: #a78bfa;
            border: 1px solid rgba(139,92,246,0.2);
        }
        .subtitle { color: #888; font-size: 1.2rem; font-weight: 400; margin-top: 8px; }
        .cards { display: flex; flex-wrap: wrap; justify-content: center; gap: 30px; margin-top: 30px; }
        .card {
            background: #1e1e1e;
            border-radius: 28px;
            padding: 32px;
            width: 100%;
            max-width: 400px;
            box-shadow: 0 20px 35px -8px rgba(0,0,0,0.5);
            border: 1px solid #333;
            transition: transform 0.2s ease, box-shadow 0.2s ease;
            text-align: left;
        }
        .card:hover { transform: translateY(-4px); box-shadow: 0 30px 45px -12px rgba(139,92,246,0.3); }
        .card h2 { font-size: 1.8rem; font-weight: 600; margin-bottom: 20px; color: #fff; }
        .input-group { margin-bottom: 24px; }
        label { display: block; margin-bottom: 8px; font-weight: 500; color: #aaa; }
        input {
            width: 100%;
            padding: 14px 18px;
            background: #2a2a2a;
            border: 1.5px solid #444;
            border-radius: 18px;
            font-size: 1rem;
            color: #fff;
            outline: none;
            transition: border-color 0.2s, box-shadow 0.2s;
        }
        input:focus { border-color: #8b5cf6; box-shadow: 0 0 0 4px rgba(139,92,246,0.2); }
        .btn {
            width: 100%;
            padding: 14px;
            background: #333;
            color: white;
            border: none;
            border-radius: 40px;
            font-weight: 600;
            font-size: 1rem;
            cursor: pointer;
            transition: background 0.2s, transform 0.1s;
            box-shadow: 0 10px 20px -5px rgba(0,0,0,0.3);
        }
        .btn-primary { background: #7c3aed; }
        .btn-primary:hover { background: #6d28d9; }
        .btn-outline { background: transparent; border: 1.5px solid #555; color: #ccc; box-shadow: none; }
        .room-display { display: none; margin-top: 28px; padding: 20px; background: #1e1e1e; border-radius: 20px; text-align: center; }
        .room-id-display {
            font-size: 2.2rem;
            font-weight: 700;
            letter-spacing: 3px;
            margin: 16px 0;
            color: #a78bfa;
            background: rgba(139,92,246,0.1);
            padding: 8px 16px;
            border-radius: 60px;
            display: inline-block;
        }
        .footer-note { margin-top: 40px; font-size: 0.9rem; color: #666; }
        .support-link { margin-top: 8px; font-size: 0.85rem; color: #666; }
        .support-link span { color: #8b5cf6; }
        .legal-links { margin-top: 16px; font-size: 0.8rem; }
        .legal-links a { color: #888; text-decoration: none; margin: 0 10px; }
        .legal-links a:hover { color: #a78bfa; }

        #call-screen { display: none; position: fixed; top: 0; left: 0; width: 100%; height: 100%; background: #0b0b12; z-index: 1000; }
        .top-bar { position: fixed; top: 0; left: 0; right: 0; display: flex; flex-direction: column; align-items: center; padding: 10px 16px; z-index: 45; pointer-events: none; }
        .security-bar { background: rgba(20, 20, 30, 0.7); backdrop-filter: blur(12px); color: rgba(255, 255, 255, 0.8); padding: 6px 16px; border-radius: 20px; font-size: 0.75rem; font-weight: 500; display: none; align-items: center; gap: 6px; border: 1px solid rgba(255, 255, 255, 0.1); margin-bottom: 8px; pointer-events: auto; }
        .room-info-bar { background: rgba(20,20,30,0.7); backdrop-filter: blur(12px); color: white; padding: 10px 24px; border-radius: 60px; display: flex; align-items: center; gap: 20px; border: 1px solid rgba(255,255,255,0.1); pointer-events: auto; }
        .room-info-bar .room-code { font-weight: 700; letter-spacing: 2px; background: #2d2d4a; padding: 4px 14px; border-radius: 30px; }
        .share-btn { background: #4f52e0; border: none; color: white; padding: 8px 18px; border-radius: 30px; font-weight: 500; cursor: pointer; display: flex; align-items: center; gap: 4px; }
        #videos-container { position: absolute; top: 90px; left: 0; right: 0; bottom: 90px; overflow-y: auto; padding: 8px; }
        #remote-videos-grid { display: grid; grid-template-columns: repeat(auto-fit, minmax(300px, 1fr)); gap: 8px; min-height: 100%; align-items: center; justify-items: center; }
        .remote-video-wrapper, .remote-camera-wrapper { position: relative; background: #1a1a2a; border-radius: 24px; overflow: hidden; box-shadow: 0 20px 30px -10px black; width: 100%; max-width: 720px; aspect-ratio: 16/9; margin: auto; }
        .remote-camera-wrapper { width: 160px; max-width: none; aspect-ratio: 4/3; border-radius: 16px; box-shadow: 0 8px 16px rgba(0,0,0,0.6); border: 1px solid rgba(255,255,255,0.2); }
        .remote-camera-wrapper video, .remote-video-wrapper video { width: 100%; height: 100%; object-fit: contain; }
        .remote-camera-wrapper video { transform: scaleX(-1); }
        .video-label { position: absolute; bottom: 8px; left: 12px; background: rgba(0,0,0,0.5); backdrop-filter: blur(8px); color: white; padding: 4px 12px; border-radius: 20px; font-size: 0.8rem; z-index: 5; }
        .fullscreen-btn { position: absolute; top: 8px; left: 12px; background: rgba(0,0,0,0.5); backdrop-filter: blur(8px); color: white; border: none; width: 28px; height: 28px; border-radius: 50%; cursor: pointer; font-size: 0.9rem; display: flex; align-items: center; justify-content: center; z-index: 6; }
        .connection-status { position: absolute; top: 8px; right: 12px; background: rgba(0,0,0,0.6); color: #ffb347; padding: 4px 10px; border-radius: 20px; font-size: 0.7rem; z-index: 6; }
        .fullscreen-controls { display: none; position: absolute; bottom: 16px; left: 50%; transform: translateX(-50%); background: rgba(0,0,0,0.6); backdrop-filter: blur(10px); padding: 8px 16px; border-radius: 30px; gap: 12px; align-items: center; z-index: 10; }
        .remote-video-wrapper:fullscreen .fullscreen-controls, .remote-video-wrapper:-webkit-full-screen .fullscreen-controls { display: flex; }
        .fs-exit-btn { background: rgba(255,255,255,0.2); border: none; color: white; width: 28px; height: 28px; border-radius: 50%; cursor: pointer; font-size: 1rem; }
        .volume-slider { width: 80px; accent-color: #8b5cf6; }
        #local-video-container { position: fixed; bottom: 90px; right: 16px; width: 150px; aspect-ratio: 4/3; border-radius: 20px; overflow: hidden; box-shadow: 0 12px 28px rgba(0,0,0,0.5); border: 2px solid rgba(255,255,255,0.15); z-index: 20; background: #2d2d3a; }
        #local-video-container video { width: 100%; height: 100%; object-fit: cover; transform: scaleX(-1); }
        #local-video-container .video-label { bottom: 6px; left: 8px; padding: 2px 10px; font-size: 0.7rem; }
        #local-camera-container { display: none; position: fixed; bottom: 90px; right: 180px; width: 120px; aspect-ratio: 4/3; border-radius: 16px; overflow: hidden; box-shadow: 0 12px 28px rgba(0,0,0,0.5); border: 2px solid rgba(255,255,255,0.2); z-index: 21; background: #1a1a2a; }
        #local-camera-container video { width: 100%; height: 100%; object-fit: cover; transform: scaleX(-1); }
        #local-camera-container .video-label { position: absolute; bottom: 4px; left: 6px; background: rgba(0,0,0,0.5); backdrop-filter: blur(8px); color: white; padding: 2px 8px; border-radius: 20px; font-size: 0.65rem; }
        @media (orientation: landscape) and (max-height: 600px) {
            #videos-container { max-height: calc(100vh - 180px); overflow-y: auto; }
        }
        .controls { position: fixed; bottom: 16px; left: 50%; transform: translateX(-50%); height: 60px; background: rgba(20,20,30,0.7); backdrop-filter: blur(16px); display: flex; justify-content: center; align-items: center; gap: 12px; padding: 0 24px; border-radius: 30px; z-index: 40; border: 1px solid rgba(255,255,255,0.1); }
        .control-btn { width: 44px; height: 44px; border-radius: 22px; border: none; background: #3a3a55; color: white; cursor: pointer; display: flex; align-items: center; justify-content: center; transition: background 0.2s; }
        .control-btn svg { stroke: currentColor; fill: none; width: 20px; height: 20px; }
        .control-btn:hover { background: #50507a; }
        .control-btn.danger { background: #e11d48; }
        .control-btn.danger:hover { background: #be123c; }
        .control-btn.screen-share { background: #3a3a55; }
        .control-btn.screen-share:hover { background: #50507a; }
        .control-btn.screen-share.active { background: #2d6a4f; }
        .reconnect-btn { background: #f59e0b; border: none; color: white; padding: 4px 10px; border-radius: 20px; font-size: 0.7rem; cursor: pointer; margin-left: 8px; }
        .toast { position: fixed; bottom: 80px; left: 50%; transform: translateX(-50%); background: #333; color: #fff; padding: 10px 20px; border-radius: 30px; font-size: 0.85rem; opacity: 0; transition: opacity 0.3s; z-index: 100; pointer-events: none; }
        .toast.show { opacity: 1; }
        .modal-overlay { position: fixed; top: 0; left: 0; width: 100%; height: 100%; background: rgba(0,0,0,0.6); z-index: 200; display: none; justify-content: center; align-items: center; }
        .modal-overlay.active { display: flex; }
        .modal { background: #1e1e2f; color: white; padding: 30px; border-radius: 20px; text-align: center; max-width: 400px; width: 90%; }
        .modal h3 { margin-bottom: 20px; }
        .stars { font-size: 2rem; cursor: pointer; }
        .stars span { color: #555; transition: color 0.2s; }
        .stars span.active, .stars span:hover { color: #f59e0b; }
        .modal button { margin-top: 20px; padding: 10px 24px; border-radius: 30px; border: none; background: #7c3aed; color: white; font-weight: 600; cursor: pointer; }
    
/* === Sprint 3: chat === */
.control-btn.chat { position: relative; }
.control-btn.chat .badge {
    position: absolute; top: -4px; right: -4px;
    background: #e11d48; color: #fff;
    font-size: 0.7rem; font-weight: 700;
    min-width: 18px; height: 18px; line-height: 18px;
    border-radius: 9px; padding: 0 5px;
    display: none;
}
.control-btn.chat.has-unread .badge { display: block; }
.control-btn.chat.has-unread { animation: chat-pulse 1.6s ease-in-out infinite; }
@keyframes chat-pulse {
    0%, 100% { box-shadow: 0 0 0 0 rgba(225,29,72,0.55); }
    50%      { box-shadow: 0 0 0 6px rgba(225,29,72,0); }
}
.chat-time {
    display: block;
    font-size: 0.65rem;
    opacity: 0.7;
    margin-top: 3px;
    text-align: right;
    font-weight: 500;
}
.chat-msg.mine .chat-time { color: rgba(255,255,255,0.75); }
.chat-msg.theirs .chat-time { color: #888; }

#chat-panel {
    position: fixed; top: 0; right: 0; bottom: 0;
    width: 340px; max-width: 90vw;
    background: #16161f;
    border-left: 1px solid rgba(255,255,255,0.08);
    display: flex; flex-direction: column;
    z-index: 50;
    transform: translateX(100%);
    transition: transform 0.2s ease;
}
#chat-panel.open { transform: translateX(0); }

#chat-header {
    display: flex; align-items: center; justify-content: space-between;
    padding: 14px 16px; border-bottom: 1px solid rgba(255,255,255,0.08);
    font-weight: 600; color: #e0e0e0;
}
#chat-header .close-chat {
    background: none; border: none; color: #aaa;
    font-size: 1.2rem; cursor: pointer; padding: 4px 8px;
}
#chat-messages {
    flex: 1; overflow-y: auto; padding: 12px;
    display: flex; flex-direction: column; gap: 8px;
}
.chat-msg {
    max-width: 85%; padding: 8px 12px;
    border-radius: 14px;
    font-size: 0.9rem; line-height: 1.35;
    word-wrap: break-word; white-space: pre-wrap;
}
.chat-msg .chat-author {
    display: block; font-size: 0.72rem; color: #a78bfa;
    margin-bottom: 3px; font-weight: 600;
}
.chat-msg.mine {
    background: #7c3aed; color: #fff;
    align-self: flex-end; border-bottom-right-radius: 4px;
}
.chat-msg.mine .chat-author { color: #ddd6fe; }
.chat-msg.theirs {
    background: #2a2a3a; color: #e0e0e0;
    align-self: flex-start; border-bottom-left-radius: 4px;
}
.chat-msg.system {
    align-self: center; background: transparent;
    color: #888; font-style: italic; font-size: 0.8rem;
    max-width: 100%; text-align: center;
}
#chat-form {
    display: flex; gap: 8px; padding: 12px;
    border-top: 1px solid rgba(255,255,255,0.08);
    background: #1a1a24;
}
#chat-input {
    flex: 1; background: #23232f; border: 1px solid #333;
    color: #fff; padding: 10px 14px; border-radius: 22px;
    outline: none; font-size: 0.9rem; font-family: inherit;
}
#chat-input:focus { border-color: #7c3aed; }
#chat-send {
    background: #7c3aed; border: none; color: #fff;
    padding: 0 16px; border-radius: 22px;
    font-weight: 600; cursor: pointer;
}
#chat-send:disabled { background: #444; cursor: not-allowed; }
#chat-empty {
    color: #666; text-align: center; padding: 30px 16px;
    font-size: 0.85rem; font-style: italic;
}

</style>
    <script type="application/ld+json">
    {
      "@context": "https://schema.org",
      "@type": "WebApplication",
      "name": "Vidma",
      "url": "https://vidma.online",
      "description": "Бесплатные видеозвонки без регистрации. Создайте комнату и пригласите участников.",
      "applicationCategory": "CommunicationApplication",
      "operatingSystem": "All"
    }
    </script>
</head>
<body>
    <div class="container" id="main-screen">
        <header>
            <div class="logo">Vidma</div>
            <div class="privacy-badge">
                <svg width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><rect x="3" y="11" width="18" height="11" rx="2" ry="2"/><path d="M7 11V7a5 5 0 0 1 10 0v4"/></svg>
                Без регистрации. Ваш разговор конфиденциален.
            </div>
            <div class="privacy-badge" style="background:rgba(245,158,11,0.12);color:#fbbf24;border-color:rgba(245,158,11,0.3);margin-top:8px;">
                <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M12 2v6M12 18v4M4.93 4.93l4.24 4.24M14.83 14.83l4.24 4.24M2 12h6M18 12h4M4.93 19.07l4.24-4.24M14.83 9.17l4.24-4.24"/></svg>
                Тестовая версия. Пожалуйста, оставьте отзыв после звонка — это очень помогает!
            </div>
            <h1 style="position:absolute; opacity:0; pointer-events:none;">Бесплатные видеозвонки Vidma</h1>
            <div class="subtitle">Видеовстречи в один клик</div>
        </header>
        <div class="cards">
            <div class="card">
                <h2>Создать встречу</h2>
                <div class="input-group"><label>Ваше имя</label><input type="text" id="create-name" placeholder="Гость" value=""></div>
                <button class="btn btn-primary" onclick="createRoom()">Создать комнату</button>
                <div class="room-display" id="room-created">
                    <p>Код встречи:</p><div class="room-id-display" id="created-room-id"></div>
                    <button class="btn btn-outline" onclick="copyRoomLink()"><svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><rect x="9" y="9" width="13" height="13" rx="2" ry="2"/><path d="M5 15H4a2 2 0 0 1-2-2V4a2 2 0 0 1 2-2h9a2 2 0 0 1 2 2v1"/></svg> Копировать ссылку</button>
                    <button class="btn btn-primary" style="margin-top: 12px;" onclick="joinCreatedRoom()">Войти в комнату</button>
                </div>
            </div>
            <div class="card">
                <h2>Присоединиться</h2>
                <div class="input-group"><label>Ваше имя</label><input type="text" id="join-name" placeholder="Гость" value=""></div>
                <div class="input-group"><label>Код комнаты</label><input type="text" id="room-id" placeholder="XXX-XXX-XXX" maxlength="11"></div>
                <button class="btn btn-primary" onclick="joinRoom()">Присоединиться</button>
            </div>
        </div>
        <div class="footer-note">
            <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M12 22s8-4 8-10V5l-8-3-8 3v7c0 6 8 10 8 10z"/></svg>
            Мы не храним историю звонков и не требуем установки.
        </div>
        <div class="support-link">
            Support: <span>vidma.on@gmail.com</span>
        </div>
        <div class="legal-links">
            <a href="/privacy">Конфиденциальность</a>
            <a href="/terms">Условия использования</a>
        </div>
    </div>

    <div id="call-screen">
        <div class="top-bar">
            <div class="security-bar" id="beta-indicator" style="background:rgba(245,158,11,0.15);color:#fbbf24;border-color:rgba(245,158,11,0.3);display:flex;">
                <svg width="12" height="12" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><circle cx="12" cy="12" r="10"/><line x1="12" y1="8" x2="12" y2="12"/><line x1="12" y1="16" x2="12.01" y2="16"/></svg>
                Beta
            </div>
            <div class="security-bar" id="security-bar">
                <svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><rect x="3" y="11" width="18" height="11" rx="2" ry="2"/><path d="M7 11V7a5 5 0 0 1 10 0v4"/></svg>
                Connection is protected
            </div>
            <div class="room-info-bar" id="room-info-bar">
                <span>Комната</span><span class="room-code" id="current-room-code"></span>
                <button class="share-btn" onclick="shareRoomFromCall()"><svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><rect x="9" y="9" width="13" height="13" rx="2" ry="2"/><path d="M5 15H4a2 2 0 0 1-2-2V4a2 2 0 0 1 2-2h9a2 2 0 0 1 2 2v1"/></svg> Копировать ссылку</button>
            </div>
        </div>
        <div id="videos-container">
            <div id="remote-videos-grid"></div>
        </div>
        <div id="local-video-container">
            <div class="video-label" id="local-video-label">Вы</div>
            <video id="local-video" autoplay playsinline muted></video>
        </div>
        <div id="local-camera-container">
            <div class="video-label">Камера</div>
            <video id="local-camera-video" autoplay playsinline muted></video>
        </div>
        <div id="chat-panel">
        <div id="chat-header">
            <span>Чат комнаты</span>
            <button class="close-chat" onclick="toggleChatPanel()" title="Закрыть">✕</button>
        </div>
        <div id="chat-messages">
            <div id="chat-empty">История чата видна только вам и хранится в этом браузере.</div>
        </div>
        <form id="chat-form" onsubmit="handleChatSubmit(event)">
            <input type="text" id="chat-input" placeholder="Сообщение..." maxlength="500" autocomplete="off">
            <button type="submit" id="chat-send">→</button>
        </form>
    </div>
    
    <div class="controls">
            <button class="control-btn" id="toggle-mic" onclick="toggleMic()">
                <svg id="mic-icon-on" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M12 1a3 3 0 0 0-3 3v8a3 3 0 0 0 6 0V4a3 3 0 0 0-3-3z"/><path d="M19 10v2a7 7 0 0 1-14 0v-2"/><line x1="12" y1="19" x2="12" y2="23"/><line x1="8" y1="23" x2="16" y2="23"/></svg>
                <svg id="mic-icon-off" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" style="display: none;"><line x1="1" y1="1" x2="23" y2="23"/><path d="M9 9v3a3 3 0 0 0 5.12 2.12M15 9.34V4a3 3 0 0 0-5.94-.6"/><path d="M17 16.95A7 7 0 0 1 5 12v-2m14 0v2a7 7 0 0 1-.11 1.23"/><line x1="12" y1="19" x2="12" y2="23"/><line x1="8" y1="23" x2="16" y2="23"/></svg>
            </button>
            <button class="control-btn" id="toggle-cam" onclick="toggleCam()">
                <svg id="cam-icon-on" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><polygon points="23 7 16 12 23 17 23 7"/><rect x="1" y="5" width="15" height="14" rx="2" ry="2"/></svg>
                <svg id="cam-icon-off" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" style="display: none;"><line x1="1" y1="1" x2="23" y2="23"/><path d="M21 21H3a2 2 0 0 1-2-2V8a2 2 0 0 1 2-2h3m3-3h6l2 3h4a2 2 0 0 1 2 2v9.34m-7.72-2.06a4 4 0 1 1-5.56-5.56"/></svg>
            </button>
            <button class="control-btn screen-share" id="toggle-screen" onclick="toggleScreenShare()">
                <svg width="20" height="20" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><rect x="2" y="3" width="20" height="14" rx="2" ry="2"/><line x1="8" y1="21" x2="16" y2="21"/><line x1="12" y1="17" x2="12" y2="21"/></svg>
            </button>
            <button class="control-btn chat" id="toggle-chat" onclick="toggleChatPanel()" title="Чат">
                <svg width="20" height="20" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M21 15a2 2 0 0 1-2 2H7l-4 4V5a2 2 0 0 1 2-2h14a2 2 0 0 1 2 2z"/></svg>
                <span class="badge" id="chat-badge">0</span>
            </button>
            <button class="control-btn danger" onclick="leaveCall()">
                <svg width="20" height="20" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M22 16.92v3a2 2 0 0 1-2.18 2 19.79 19.79 0 0 1-8.63-3.07 19.5 19.5 0 0 1-6-6 19.79 19.79 0 0 1-3.07-8.67A2 2 0 0 1 4.11 2h3a2 2 0 0 1 2 1.72 12.84 12.84 0 0 0 .7 2.81 2 2 0 0 1-.45 2.11L8.09 9.91a16 16 0 0 0 6 6l1.27-1.27a2 2 0 0 1 2.11-.45 12.84 12.84 0 0 0 2.81.7A2 2 0 0 1 22 16.92z"/></svg>
            </button>
        </div>
    </div>

    <div class="toast" id="toast"></div>

    <div class="modal-overlay" id="rating-modal">
        <div class="modal">
            <h3>Оцените качество видеозвонка</h3>
            <div class="stars" id="stars">
                <span data-value="1">☆</span>
                <span data-value="2">☆</span>
                <span data-value="3">☆</span>
                <span data-value="4">☆</span>
                <span data-value="5">☆</span>
            </div>
            <p style="font-size:0.85rem;color:#bbb;margin:14px 0 8px;text-align:left;">
                Что понравилось или что сломалось? <span style="color:#888;">(необязательно)</span>
            </p>
            <textarea id="rating-comment" maxlength="500" placeholder="Например: звук отличный, но видео дёргается на телефоне"
                style="width:100%;min-height:70px;padding:10px 12px;border-radius:12px;background:#2a2a3a;color:#fff;border:1px solid #444;font-family:inherit;font-size:0.9rem;resize:vertical;outline:none;"></textarea>
            <button onclick="submitRating()">Отправить</button>
            <button onclick="closeRating()" style="background: transparent; border: 1px solid #555; margin-left: 10px;">Пропустить</button>
        </div>
    </div>

    <div class="modal-overlay" id="camera-choice-modal">
        <div class="modal">
            <h3>Доступ к камере</h3>
            <p style="margin-bottom: 20px; font-size: 0.9rem; color: #ccc;">Разрешите использование камеры или войдите без видео.</p>
            <button onclick="retryCamera()">Включить камеру</button>
            <button onclick="joinWithoutCamera()" style="background: transparent; border: 1px solid #555; margin-left: 10px;">Без видео</button>
        </div>
    </div>
    <script src="https://cdn.jsdelivr.net/npm/livekit-client@2.9.7/dist/livekit-client.umd.min.js"></script>
    <script src="/app.js"></script>
</body>
</html>)html";

#endif // VIDMA_HTML_H
