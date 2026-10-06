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
    <title data-i18n="app.title">Vidma — Free Video Calls</title>
    <meta name="description" content="Vidma — видеозвонки без регистрации и ограничений по времени. Создайте комнату и общайтесь с друзьями или коллегами по видеосвязи прямо в браузере.">
    <meta name="keywords" content="видеозвонки, видеоконференции, бесплатные звонки, без регистрации, созвон, видеосвязь, комната, WebRTC">
    <link rel="canonical" href="https://vidma.online/">
    <meta property="og:type" content="website">
    <meta property="og:url" content="https://vidma.online/">
    <meta property="og:title" content="Vidma — Free Video Calls">
    <meta property="og:description" content="Join my video call in one click. No registration, encrypted, works in browser.">
    <meta property="og:image" content="https://vidma.online/og-image.png">
    <meta property="og:image:width" content="1200">
    <meta property="og:image:height" content="630">
    <meta property="og:site_name" content="Vidma">
    <meta name="twitter:card" content="summary_large_image">
    <meta name="twitter:title" content="Vidma — Free Video Calls">
    <meta name="twitter:description" content="Join my video call in one click. No registration, encrypted, works in browser.">
    <meta name="twitter:image" content="https://vidma.online/og-image.png">
    
    
    
    
    
    
    
    
    <link rel="icon" type="image/x-icon" href="/favicon.ico">
    <link rel="icon" type="image/png" sizes="256x256" href="/logo.png">
    <link rel="apple-touch-icon" sizes="180x180" href="/apple-touch-icon.png">
    <meta name="msapplication-TileColor" content="#7c3aed">
    
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


/* === Lobby (preview before joining) === */
#lobby-screen {
    display: none;
    position: fixed; inset: 0;
    background: #0f0f16;
    z-index: 1500;
    align-items: center; justify-content: center;
    padding: 20px;
    overflow-y: auto;
}
#lobby-screen.active { display: flex; }
.lobby-wrap {
    max-width: 600px; width: 100%;
    background: #1a1a24; padding: 28px; border-radius: 20px;
    box-shadow: 0 20px 40px rgba(0,0,0,0.5);
}
.lobby-wrap h2 { margin: 0 0 6px; color: #fff; font-size: 1.4rem; text-align: center; }
.lobby-wrap .lobby-sub { color: #888; font-size: 0.9rem; text-align: center; margin-bottom: 20px; }
.lobby-preview {
    aspect-ratio: 4/3; background: #000; border-radius: 16px; overflow: hidden;
    margin-bottom: 16px; position: relative;
}
.lobby-preview video { width: 100%; height: 100%; object-fit: cover; transform: scaleX(-1); }
.lobby-preview .no-video {
    position: absolute; inset: 0; display: none;
    align-items: center; justify-content: center;
    background: #1a1a24; color: #666; font-size: 0.9rem;
}
.lobby-preview.no-video .no-video { display: flex; }
.lobby-preview.no-video video { visibility: hidden; }
.lobby-row {
    display: flex; align-items: center; gap: 10px; margin-bottom: 8px;
}
.lobby-row label { flex: 0 0 90px; color: #aaa; font-size: 0.85rem; }
.lobby-row select {
    flex: 1; min-width: 0;
    padding: 9px 12px; border-radius: 10px;
    background: #23232f; color: #fff;
    border: 1px solid #444; outline: none;
    font-family: inherit; font-size: 0.9rem;
}
.lobby-row select:focus { border-color: #7c3aed; }
.lobby-row .tog {
    flex: 0 0 40px; height: 40px; border-radius: 20px;
    background: #333; color: #fff; border: none; cursor: pointer;
    font-size: 1rem; display: flex; align-items: center; justify-content: center;
    transition: background 0.15s;
}
.lobby-row .tog.on { background: #7c3aed; }
.lobby-row .tog.off { background: #3a1f2a; }
.lobby-row .tog svg { pointer-events: none; }
.lobby-level {
    height: 6px; background: #23232f; border-radius: 3px; overflow: hidden;
    margin: 4px 0 16px 100px;
}
#lobby-level-bar {
    height: 100%; width: 0%;
    background: linear-gradient(90deg, #4ade80, #facc15 70%, #f97316);
    transition: width 0.08s linear;
}
.lobby-actions { display: flex; gap: 12px; margin-top: 22px; }
.lobby-actions button {
    flex: 1; padding: 14px; border-radius: 40px;
    font-weight: 600; font-size: 1rem; cursor: pointer;
    border: none; font-family: inherit;
}
.lobby-actions .btn-lobby-cancel { background: transparent; color: #aaa; border: 1px solid #555; }
.lobby-actions .btn-lobby-join { background: #7c3aed; color: #fff; }
.lobby-actions .btn-lobby-join:hover { background: #6d28d9; }
.lobby-actions .btn-lobby-cancel:hover { background: #2a2a3a; color: #ddd; }


.remote-video-wrapper.showing-screen { border: 2px solid #8b5cf6; }
.remote-video-wrapper.showing-screen video { object-fit: contain; }


/* === Active speaker glow === */
.remote-video-wrapper.speaking,
#local-video-container.speaking {
    box-shadow: 0 0 calc(14px + var(--speak-glow, 0) * 20px)
                rgba(139, 92, 246, calc(0.25 + var(--speak-glow, 0) * 0.55)),
                0 0 0 calc(1px + var(--speak-glow, 0) * 3px)
                rgba(167, 139, 250, calc(0.4 + var(--speak-glow, 0) * 0.6));
    transition: box-shadow 0.15s ease-out;
}
.remote-video-wrapper { transition: box-shadow 0.15s ease-out; }
#local-video-container { transition: box-shadow 0.15s ease-out; }

/* === Avatar overlay (camera off) === */
.video-avatar {
    position: absolute; inset: 0;
    display: none;
    align-items: center; justify-content: center;
    background: radial-gradient(ellipse at center, #26263a 0%, #15151f 100%);
    z-index: 3;
    pointer-events: none;
    opacity: 0;
    transition: opacity 0.25s ease;
}
.video-avatar.visible { display: flex; opacity: 1; }
.video-avatar .avatar-circle {
    width: 110px; height: 110px;
    border-radius: 50%;
    display: flex; align-items: center; justify-content: center;
    font-size: 3rem; font-weight: 700; color: #fff;
    letter-spacing: -0.02em;
    text-shadow: 0 2px 10px rgba(0,0,0,0.5);
    box-shadow:
        0 12px 32px rgba(0,0,0,0.45),
        0 0 0 3px rgba(255,255,255,0.12),
        inset 0 2px 8px rgba(255,255,255,0.15),
        inset 0 -6px 14px rgba(0,0,0,0.25);
    user-select: none;
    position: relative;
    overflow: hidden;
}
.video-avatar .avatar-circle::before {
    content: '';
    position: absolute; inset: 0;
    background: radial-gradient(circle at 30% 20%, rgba(255,255,255,0.22), transparent 55%);
    pointer-events: none;
}
.video-avatar .avatar-circle svg {
    width: 56px; height: 56px;
    stroke: rgba(255,255,255,0.92);
    filter: drop-shadow(0 2px 4px rgba(0,0,0,0.3));
}
/* Локальное превью — уменьшенная версия */
#local-video-container .video-avatar .avatar-circle {
    width: 68px; height: 68px; font-size: 1.9rem;
}
#local-video-container .video-avatar .avatar-circle svg {
    width: 34px; height: 34px;
}
#local-camera-container .video-avatar { display: none !important; }
@media (max-width: 600px) {
    .video-avatar .avatar-circle { width: 80px; height: 80px; font-size: 2.2rem; }
    .video-avatar .avatar-circle svg { width: 42px; height: 42px; }
}
    .video-avatar .avatar-circle svg { width: 40px; height: 40px; }
}


    .lang-switcher select { padding: 8px 34px 8px 36px; font-size: 0.85rem; }
}



    .lang-btn { padding: 7px 12px 7px 10px; font-size: 0.85rem; }
    .lang-menu { min-width: 150px; }
    .lang-item { padding: 8px 10px; font-size: 0.85rem; }
}



/* === Language switcher — FIXED top-right === */
#vidma-lang-root {
    position: fixed !important;
    top: 20px !important;
    right: 20px !important;
    left: auto !important;
    bottom: auto !important;
    z-index: 2147483647 !important;
    font-family: inherit;
    pointer-events: auto !important;
    display: block !important;
    margin: 0 !important;
    padding: 0 !important;
}
#vidma-lang-btn {
    display: flex !important;
    align-items: center;
    gap: 8px;
    background: rgba(30, 30, 45, 0.9);
    backdrop-filter: blur(14px);
    -webkit-backdrop-filter: blur(14px);
    color: #e0e0e0;
    border: 1px solid rgba(139, 92, 246, 0.35);
    border-radius: 100px;
    padding: 8px 14px 8px 12px;
    font-size: 0.9rem;
    font-weight: 500;
    font-family: inherit;
    cursor: pointer;
    outline: none;
    transition: border-color 0.2s, background 0.2s, box-shadow 0.2s;
    box-shadow: 0 4px 20px rgba(0, 0, 0, 0.3);
}
#vidma-lang-btn:hover {
    border-color: rgba(139, 92, 246, 0.8);
    background: rgba(40, 40, 60, 0.95);
    box-shadow: 0 6px 24px rgba(139, 92, 246, 0.35);
}
#vidma-lang-btn .vflag {
    display: inline-block;
    width: 22px; height: 15px;
    border-radius: 3px;
    overflow: hidden;
    flex-shrink: 0;
    box-shadow: 0 1px 3px rgba(0,0,0,0.3);
}
#vidma-lang-btn .vflag svg { display: block; width: 100%; height: 100%; }
#vidma-lang-btn .vchev {
    width: 12px; height: 12px;
    stroke: #a78bfa;
    transition: transform 0.2s;
    flex-shrink: 0;
}
#vidma-lang-root.open #vidma-lang-btn .vchev { transform: rotate(180deg); }

#vidma-lang-menu {
    position: absolute !important;
    top: calc(100% + 8px) !important;
    right: 0 !important;
    left: auto !important;
    background: rgba(30, 30, 45, 0.98);
    backdrop-filter: blur(20px);
    -webkit-backdrop-filter: blur(20px);
    border: 1px solid rgba(139, 92, 246, 0.35);
    border-radius: 14px;
    padding: 6px;
    min-width: 180px;
    box-shadow: 0 12px 40px rgba(0, 0, 0, 0.65);
    opacity: 0;
    visibility: hidden;
    transform: translateY(-6px);
    transition: opacity 0.18s, visibility 0.18s, transform 0.18s;
    z-index: 2147483647 !important;
    max-height: 80vh;
    overflow-y: auto;
}
#vidma-lang-root.open #vidma-lang-menu {
    opacity: 1 !important;
    visibility: visible !important;
    transform: translateY(0) !important;
}
.vlang-item {
    display: flex;
    align-items: center;
    gap: 10px;
    width: 100%;
    padding: 9px 12px;
    background: transparent;
    border: none;
    border-radius: 10px;
    color: #d0d0d0;
    font-family: inherit;
    font-size: 0.9rem;
    text-align: left;
    cursor: pointer;
    transition: background 0.15s;
}
.vlang-item:hover {
    background: rgba(139, 92, 246, 0.18);
    color: #fff;
}
.vlang-item.active {
    background: rgba(139, 92, 246, 0.28);
    color: #fff;
    font-weight: 600;
}
.vlang-item .vflag {
    display: inline-block;
    width: 22px; height: 15px;
    border-radius: 3px;
    overflow: hidden;
    flex-shrink: 0;
    box-shadow: 0 1px 3px rgba(0,0,0,0.3);
}
.vlang-item .vflag svg { display: block; width: 100%; height: 100%; }
.vlang-item .vname { flex: 1; }
.vlang-item .vcheck {
    width: 14px; height: 14px; stroke: #a78bfa; opacity: 0; flex-shrink: 0;
}
.vlang-item.active .vcheck { opacity: 1; }

@media (max-width: 600px) {
    #vidma-lang-root { top: 12px !important; right: 12px !important; }
    #vidma-lang-btn { padding: 7px 12px 7px 10px; font-size: 0.85rem; }
    #vidma-lang-menu { min-width: 160px; }
}


#cookie-banner {
    position: fixed; left: 20px; right: 20px; bottom: 20px;
    max-width: 720px; margin: 0 auto;
    background: rgba(26,26,36,0.97); backdrop-filter: blur(14px);
    border: 1px solid rgba(139,92,246,0.35); border-radius: 16px;
    padding: 18px 22px; z-index: 5000;
    display: none; align-items: center; gap: 16px;
    box-shadow: 0 12px 40px rgba(0,0,0,0.6);
    font-size: 0.92rem; color: #e0e0e0;
}
#cookie-banner.show { display: flex; }
#cookie-banner .cb-text { flex: 1; line-height: 1.5; }
#cookie-banner .cb-text a { color: #a78bfa; }
#cookie-banner .cb-btn {
    background: #7c3aed; color: #fff; border: none;
    padding: 10px 22px; border-radius: 40px; font-weight: 600;
    font-size: 0.9rem; cursor: pointer; white-space: nowrap;
    font-family: inherit;
}
#cookie-banner .cb-btn:hover { background: #6d28d9; }
#cookie-banner .cb-btn.secondary {
    background: transparent; border: 1px solid #555; color: #bbb;
    margin-left: 6px;
}
@media (max-width: 600px) {
    #cookie-banner { flex-direction: column; align-items: stretch; text-align: center; }
    #cookie-banner .cb-actions { display: flex; gap: 8px; }
    #cookie-banner .cb-actions .cb-btn { flex: 1; }
}


/* === Invite modal === */
#invite-modal {
    position: fixed; inset: 0;
    background: rgba(0,0,0,0.7); backdrop-filter: blur(6px);
    display: none; align-items: center; justify-content: center;
    z-index: 3000; padding: 20px;
}
#invite-modal.active { display: flex; }
#invite-modal .im-card {
    background: #1a1a24; border: 1px solid rgba(139,92,246,0.3);
    border-radius: 20px; padding: 28px;
    max-width: 440px; width: 100%;
    box-shadow: 0 20px 60px rgba(0,0,0,0.7);
}
#invite-modal h3 {
    margin: 0 0 6px; color: #fff; font-size: 1.3rem; text-align: center;
}
#invite-modal .im-sub {
    color: #888; font-size: 0.9rem; text-align: center; margin-bottom: 20px;
}
#invite-modal .im-link-box {
    display: flex; gap: 8px; margin-bottom: 20px;
}
#invite-modal .im-link {
    flex: 1; background: #23232f; border: 1px solid #333;
    color: #a78bfa; padding: 11px 14px; border-radius: 10px;
    font-size: 0.9rem; font-family: inherit;
    overflow: hidden; text-overflow: ellipsis; white-space: nowrap;
}
#invite-modal .im-copy {
    background: #7c3aed; color: #fff; border: none;
    padding: 0 16px; border-radius: 10px; font-weight: 600;
    cursor: pointer; white-space: nowrap; font-family: inherit;
    transition: background 0.15s;
}
#invite-modal .im-copy:hover { background: #6d28d9; }
#invite-modal .im-options {
    display: grid; grid-template-columns: 1fr 1fr; gap: 10px;
    margin-bottom: 20px;
}
#invite-modal .im-opt {
    display: flex; align-items: center; gap: 10px;
    padding: 14px 16px; border-radius: 12px;
    background: #23232f; border: 1px solid #333;
    color: #e0e0e0; font-family: inherit; font-size: 0.92rem;
    cursor: pointer; transition: all 0.15s; text-align: left;
}
#invite-modal .im-opt:hover {
    background: #2f2f3f; border-color: #8b5cf6;
    transform: translateY(-1px);
}
#invite-modal .im-opt svg {
    width: 22px; height: 22px; flex-shrink: 0;
}
#invite-modal .im-opt.tg svg { fill: #0088cc; }
#invite-modal .im-opt.wa svg { fill: #25D366; }
#invite-modal .im-opt.email svg { stroke: #a78bfa; fill: none; }
#invite-modal .im-close {
    width: 100%; background: transparent; color: #888;
    border: 1px solid #555; padding: 12px; border-radius: 10px;
    cursor: pointer; font-family: inherit; font-size: 0.9rem;
    transition: all 0.15s;
}
#invite-modal .im-close:hover { color: #ddd; border-color: #888; }


.lobby-name-row {
    margin-bottom: 16px;
}
.lobby-name-row label {
    display: block; color: #aaa; font-size: 0.85rem;
    margin-bottom: 6px;
}
.lobby-name-row input {
    width: 100%; padding: 12px 16px;
    background: #23232f; border: 1px solid #444;
    color: #fff; border-radius: 12px;
    font-family: inherit; font-size: 1rem;
    outline: none; transition: border-color 0.15s;
}
.lobby-name-row input:focus { border-color: #7c3aed; box-shadow: 0 0 0 3px rgba(139,92,246,0.2); }
.lobby-name-row input::placeholder { color: #666; }


/* === Landing sections === */
.landing-section {
    margin-top: 80px;
    text-align: center;
}
.landing-section h2 {
    font-size: 2rem;
    font-weight: 700;
    color: #fff;
    margin-bottom: 12px;
    letter-spacing: -0.02em;
}
.landing-section .section-sub {
    color: #888;
    font-size: 1rem;
    margin-bottom: 40px;
    max-width: 600px;
    margin-left: auto;
    margin-right: auto;
}
.features-grid {
    display: grid;
    grid-template-columns: repeat(2, 1fr);
    gap: 24px;
    max-width: 720px;
    margin: 0 auto;
    text-align: left;
}
.feature-card {
    background: #1a1a24;
    border: 1px solid #2a2a3a;
    border-radius: 20px;
    padding: 26px 22px;
    transition: all 0.25s ease;
}
.feature-card:hover {
    border-color: rgba(139,92,246,0.5);
    transform: translateY(-3px);
    box-shadow: 0 12px 30px -10px rgba(139,92,246,0.35);
}
.feature-card .fc-icon {
    width: 46px; height: 46px;
    border-radius: 14px;
    background: linear-gradient(135deg, rgba(139,92,246,0.2), rgba(167,139,250,0.1));
    display: flex; align-items: center; justify-content: center;
    margin-bottom: 16px;
    color: #a78bfa;
}
.feature-card .fc-icon svg { width: 24px; height: 24px; }
.feature-card h3 {
    font-size: 1.1rem;
    color: #fff;
    margin: 0 0 8px;
    font-weight: 600;
}
.feature-card p {
    color: #999;
    font-size: 0.92rem;
    line-height: 1.55;
    margin: 0;
}

.steps-grid {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(240px, 1fr));
    gap: 24px;
    max-width: 900px;
    margin: 0 auto;
    text-align: center;
}
.step {
    padding: 20px;
    position: relative;
}
.step .step-num {
    display: inline-flex;
    align-items: center;
    justify-content: center;
    width: 56px; height: 56px;
    border-radius: 50%;
    background: linear-gradient(135deg, #7c3aed, #a855f7);
    color: #fff;
    font-weight: 700;
    font-size: 1.4rem;
    margin-bottom: 16px;
    box-shadow: 0 10px 24px -6px rgba(139,92,246,0.5);
}
.step h3 {
    font-size: 1.05rem;
    color: #fff;
    margin: 0 0 6px;
    font-weight: 600;
}
.step p {
    color: #888;
    font-size: 0.9rem;
    line-height: 1.5;
    margin: 0;
}

.faq-list {
    max-width: 720px;
    margin: 0 auto;
    text-align: left;
}
.faq-item {
    background: #1a1a24;
    border: 1px solid #2a2a3a;
    border-radius: 14px;
    margin-bottom: 10px;
    overflow: hidden;
    transition: border-color 0.15s;
}
.faq-item:hover { border-color: rgba(139,92,246,0.4); }
.faq-item[open] { border-color: rgba(139,92,246,0.6); }
.faq-item summary {
    padding: 16px 20px;
    color: #e0e0e0;
    font-weight: 500;
    font-size: 0.98rem;
    cursor: pointer;
    list-style: none;
    position: relative;
    padding-right: 44px;
    user-select: none;
}
.faq-item summary::-webkit-details-marker { display: none; }
.faq-item summary::after {
    content: '+';
    position: absolute;
    right: 20px;
    top: 50%;
    transform: translateY(-50%);
    color: #a78bfa;
    font-size: 1.4rem;
    font-weight: 300;
    transition: transform 0.2s;
}
.faq-item[open] summary::after {
    content: '−';
    transform: translateY(-50%) rotate(0deg);
}
.faq-item .faq-answer {
    padding: 0 20px 18px;
    color: #999;
    font-size: 0.92rem;
    line-height: 1.6;
}

@media (max-width: 640px) {
    .features-grid { grid-template-columns: 1fr; }
    .landing-section { margin-top: 50px; }
    .landing-section h2 { font-size: 1.5rem; }
    .landing-section .section-sub { font-size: 0.92rem; margin-bottom: 28px; }
    .feature-card { padding: 20px 18px; }
    .step .step-num { width: 46px; height: 46px; font-size: 1.15rem; }
}


/* === Mobile UX (max-width: 640px) === */
@media (max-width: 640px) {
    body { padding: 12px 14px 100px; }

    /* Header / Logo */
    header { margin-bottom: 24px; }
    .logo {
        font-size: 2.2rem !important;
        gap: 10px !important;
    }
    .logo img { width: 52px !important; height: 52px !important; border-radius: 14px !important; }
    .subtitle { font-size: 1rem; margin-top: 4px; }

    /* Badges */
    .privacy-badge {
        padding: 6px 14px !important;
        font-size: 0.82rem !important;
        gap: 6px !important;
        margin-bottom: 10px !important;
        max-width: 100%;
        text-align: center;
        line-height: 1.35;
    }
    .privacy-badge svg { width: 14px; height: 14px; flex-shrink: 0; }

    /* Language switcher — фикс на мобильном */
    #vidma-lang-root { top: 12px !important; right: 12px !important; }
    #vidma-lang-btn { padding: 6px 10px 6px 8px !important; font-size: 0.8rem !important; gap: 6px !important; }
    #vidma-lang-btn .vflag { width: 18px !important; height: 13px !important; }
    #vidma-lang-btn #vidma-current-name { display: none; }  /* только флаг */
    #vidma-lang-menu { min-width: 160px !important; }

    /* Cards */
    .cards { gap: 16px; margin-top: 20px; }
    .card {
        padding: 22px 18px !important;
        border-radius: 22px !important;
    }
    .card h2 { font-size: 1.35rem !important; margin-bottom: 16px !important; }

    /* Inputs & buttons */
    input, textarea {
        padding: 14px 16px !important;
        font-size: 1rem !important;   /* 16px — нет зума в iOS */
        border-radius: 14px !important;
    }
    .btn {
        padding: 16px !important;
        font-size: 1rem !important;
        border-radius: 30px !important;
        min-height: 52px;
    }

    /* Room display */
    .room-id-display {
        font-size: 1.6rem !important;
        letter-spacing: 2px !important;
        padding: 6px 14px !important;
    }

    /* Footer / links */
    .footer-note { margin-top: 28px; font-size: 0.85rem; }
    .support-link { font-size: 0.8rem; }
    .legal-links { font-size: 0.78rem; }
    .legal-links a { margin: 0 6px; }

    /* Landing sections */
    .landing-section { margin-top: 44px !important; }
    .landing-section h2 { font-size: 1.45rem !important; }
    .feature-card { padding: 20px 18px !important; }
    .feature-card h3 { font-size: 1rem !important; }
    .feature-card p { font-size: 0.88rem !important; }
    .step h3 { font-size: 1rem; }
    .faq-item summary { padding: 14px 16px !important; padding-right: 44px !important; font-size: 0.92rem !important; }
    .faq-item .faq-answer { padding: 0 16px 16px !important; font-size: 0.88rem !important; }

    /* Cookie banner */
    #cookie-banner {
        left: 12px !important; right: 12px !important; bottom: 12px !important;
        padding: 14px 16px !important;
        flex-direction: column;
        align-items: stretch;
        font-size: 0.85rem;
    }
    #cookie-banner .cb-actions { display: flex; gap: 8px; }
    #cookie-banner .cb-btn { flex: 1; padding: 12px; font-size: 0.9rem; }
}

/* === Very small phones (max-width: 400px) === */
@media (max-width: 400px) {
    .logo { font-size: 1.9rem !important; }
    .logo img { width: 44px !important; height: 44px !important; }
    .card { padding: 18px 14px !important; }
    .card h2 { font-size: 1.2rem !important; }
    .room-id-display { font-size: 1.35rem !important; }
}

/* === Landscape phones (max-height: 500px) === */
@media (orientation: landscape) and (max-height: 500px) {
    header { margin-bottom: 12px; }
    .logo { font-size: 1.6rem !important; }
    .logo img { width: 40px !important; height: 40px !important; }
    .privacy-badge { display: none; }   /* скрываем на низкой высоте */
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
    <link rel="preload" as="image" href="/logo.png">
</head>
<body>
<div id="invite-modal">
    <div class="im-card">
        <h3 data-i18n="invite.title">Invite friends</h3>
        <p class="im-sub" data-i18n="invite.subtitle">Share this link with anyone you want to talk to</p>

        <div class="im-link-box">
            <div class="im-link" id="invite-link">https://vidma.online/</div>
            <button class="im-copy" onclick="inviteCopy()" data-i18n="invite.copy">Copy</button>
        </div>

        <div class="im-options">
            <button class="im-opt tg" onclick="inviteTelegram()">
                <svg viewBox="0 0 24 24"><path d="M9.78 18.65l.28-4.23 7.68-6.92c.34-.31-.07-.46-.52-.19L7.74 13.3 3.64 12c-.88-.25-.89-.86.2-1.3l15.97-6.16c.73-.33 1.43.18 1.15 1.3l-2.72 12.81c-.19.91-.74 1.13-1.5.71L12.6 16.3l-1.99 1.93c-.23.23-.42.42-.83.42z"/></svg>
                <span>Telegram</span>
            </button>
            <button class="im-opt wa" onclick="inviteWhatsApp()">
                <svg viewBox="0 0 24 24"><path d="M17.472 14.382c-.297-.149-1.758-.867-2.03-.967-.273-.099-.471-.148-.67.15-.197.297-.767.966-.94 1.164-.173.199-.347.223-.644.075-.297-.15-1.255-.463-2.39-1.475-.883-.788-1.48-1.761-1.653-2.059-.173-.297-.018-.458.13-.606.134-.133.298-.347.446-.52.149-.174.198-.298.298-.497.099-.198.05-.371-.025-.52-.075-.149-.669-1.612-.916-2.207-.242-.579-.487-.5-.669-.51-.173-.008-.371-.01-.57-.01-.198 0-.52.074-.792.372-.272.297-1.04 1.016-1.04 2.479 0 1.462 1.065 2.875 1.213 3.074.149.198 2.096 3.2 5.077 4.487.709.306 1.262.489 1.694.625.712.227 1.36.195 1.871.118.571-.085 1.758-.719 2.006-1.413.248-.694.248-1.289.173-1.413-.074-.124-.272-.198-.57-.347m-5.421 7.403h-.004a9.87 9.87 0 01-5.031-1.378l-.361-.214-3.741.982.998-3.648-.235-.374a9.86 9.86 0 01-1.51-5.26c.001-5.45 4.436-9.884 9.888-9.884 2.64 0 5.122 1.03 6.988 2.898a9.825 9.825 0 012.893 6.994c-.003 5.45-4.437 9.884-9.885 9.884m8.413-18.297A11.815 11.815 0 0012.05 0C5.495 0 .16 5.335.157 11.892c0 2.096.547 4.142 1.588 5.945L.057 24l6.305-1.654a11.882 11.882 0 005.683 1.448h.005c6.554 0 11.89-5.335 11.893-11.893a11.821 11.821 0 00-3.48-8.413z"/></svg>
                <span>WhatsApp</span>
            </button>
            <button class="im-opt email" onclick="inviteEmail()">
                <svg viewBox="0 0 24 24" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><rect x="2" y="4" width="20" height="16" rx="2"/><path d="M22 6l-10 7L2 6"/></svg>
                <span>Email</span>
            </button>
            <button class="im-opt" onclick="inviteCopy()">
                <svg viewBox="0 0 24 24" fill="none" stroke="#a78bfa" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><rect x="9" y="9" width="13" height="13" rx="2"/><path d="M5 15H4a2 2 0 0 1-2-2V4a2 2 0 0 1 2-2h9a2 2 0 0 1 2 2v1"/></svg>
                <span data-i18n="invite.copy">Copy</span>
            </button>
        </div>

        <button class="im-close" onclick="closeInviteModal()" data-i18n="invite.close">Close</button>
    </div>
</div>

<div id="cookie-banner">
    <div class="cb-text">
        <span data-i18n="cookie.text">We use only essential cookies and local storage for your language, chat history and consent. No tracking. Details in</span>
        <a href="/privacy" data-i18n="legal.privacy">Privacy</a>.
    </div>
    <div class="cb-actions">
        <button class="cb-btn" onclick="acceptCookies()" data-i18n="cookie.accept">Accept</button>
    </div>
</div>

<div id="vidma-lang-root" style="position:absolute;top:20px;right:20px;z-index:1000;font-family:inherit;">
    <button id="vidma-lang-btn" type="button" onclick="vidmaToggleLang(event)" aria-haspopup="listbox" aria-expanded="false" style="display:flex;align-items:center;gap:8px;background:rgba(30,30,45,0.9);backdrop-filter:blur(14px);color:#e0e0e0;border:1px solid rgba(139,92,246,0.35);border-radius:100px;padding:8px 14px 8px 12px;font-size:0.9rem;font-weight:500;cursor:pointer;outline:none;box-shadow:0 4px 20px rgba(0,0,0,0.3);">
        <span class="vflag" id="vidma-current-flag" style="display:inline-block;width:22px;height:15px;border-radius:3px;overflow:hidden;flex-shrink:0;"><svg viewBox="0 0 24 16" preserveAspectRatio="none"><rect width="24" height="16" fill="#012169"/><path d="M0,0 L24,16 M24,0 L0,16" stroke="#fff" stroke-width="3.2"/><path d="M0,0 L24,16 M24,0 L0,16" stroke="#C8102E" stroke-width="1.6"/><path d="M12,0 L12,16 M0,8 L24,8" stroke="#fff" stroke-width="5.3"/><path d="M12,0 L12,16 M0,8 L24,8" stroke="#C8102E" stroke-width="3.2"/></svg></span>
        <span id="vidma-current-name">English</span>
        <svg class="vchev" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.5" stroke-linecap="round" stroke-linejoin="round" style="width:12px;height:12px;stroke:#a78bfa;transition:transform 0.2s;"><polyline points="6 9 12 15 18 9"/></svg>
    </button>
    <div id="vidma-lang-menu" role="listbox" style="position:absolute;top:calc(100% + 8px);right:0;background:rgba(30,30,45,0.98);backdrop-filter:blur(20px);border:1px solid rgba(139,92,246,0.35);border-radius:14px;padding:6px;min-width:180px;box-shadow:0 12px 40px rgba(0,0,0,0.65);opacity:0;visibility:hidden;transform:translateY(-6px);transition:all 0.18s;max-height:80vh;overflow-y:auto;">
        <button class="vlang-item" data-lang="en" onclick="vidmaPickLang('en',event)" type="button" style="display:flex;align-items:center;gap:10px;width:100%;padding:9px 12px;background:transparent;border:none;border-radius:10px;color:#d0d0d0;font-size:0.9rem;text-align:left;cursor:pointer;"><span class="vflag" style="display:inline-block;width:22px;height:15px;border-radius:3px;overflow:hidden;"><svg viewBox="0 0 24 16" preserveAspectRatio="none"><rect width="24" height="16" fill="#012169"/><path d="M0,0 L24,16 M24,0 L0,16" stroke="#fff" stroke-width="3.2"/><path d="M0,0 L24,16 M24,0 L0,16" stroke="#C8102E" stroke-width="1.6"/><path d="M12,0 L12,16 M0,8 L24,8" stroke="#fff" stroke-width="5.3"/><path d="M12,0 L12,16 M0,8 L24,8" stroke="#C8102E" stroke-width="3.2"/></svg></span><span class="vname" style="flex:1;">English</span><svg class="vcheck" viewBox="0 0 24 24" fill="none" stroke="#a78bfa" stroke-width="3" stroke-linecap="round" stroke-linejoin="round" style="width:14px;height:14px;opacity:0;"><polyline points="20 6 9 17 4 12"/></svg></button>
        <button class="vlang-item" data-lang="ru" onclick="vidmaPickLang('ru',event)" type="button" style="display:flex;align-items:center;gap:10px;width:100%;padding:9px 12px;background:transparent;border:none;border-radius:10px;color:#d0d0d0;font-size:0.9rem;text-align:left;cursor:pointer;"><span class="vflag" style="display:inline-block;width:22px;height:15px;border-radius:3px;overflow:hidden;"><svg viewBox="0 0 24 16" preserveAspectRatio="none"><rect width="24" height="5.33" fill="#fff"/><rect y="5.33" width="24" height="5.33" fill="#0039A6"/><rect y="10.66" width="24" height="5.34" fill="#D52B1E"/></svg></span><span class="vname" style="flex:1;">Русский</span><svg class="vcheck" viewBox="0 0 24 24" fill="none" stroke="#a78bfa" stroke-width="3" stroke-linecap="round" stroke-linejoin="round" style="width:14px;height:14px;opacity:0;"><polyline points="20 6 9 17 4 12"/></svg></button>
        <button class="vlang-item" data-lang="es" onclick="vidmaPickLang('es',event)" type="button" style="display:flex;align-items:center;gap:10px;width:100%;padding:9px 12px;background:transparent;border:none;border-radius:10px;color:#d0d0d0;font-size:0.9rem;text-align:left;cursor:pointer;"><span class="vflag" style="display:inline-block;width:22px;height:15px;border-radius:3px;overflow:hidden;"><svg viewBox="0 0 24 16" preserveAspectRatio="none"><rect width="24" height="16" fill="#AA151B"/><rect y="4" width="24" height="8" fill="#F1BF00"/></svg></span><span class="vname" style="flex:1;">Español</span><svg class="vcheck" viewBox="0 0 24 24" fill="none" stroke="#a78bfa" stroke-width="3" stroke-linecap="round" stroke-linejoin="round" style="width:14px;height:14px;opacity:0;"><polyline points="20 6 9 17 4 12"/></svg></button>
        <button class="vlang-item" data-lang="de" onclick="vidmaPickLang('de',event)" type="button" style="display:flex;align-items:center;gap:10px;width:100%;padding:9px 12px;background:transparent;border:none;border-radius:10px;color:#d0d0d0;font-size:0.9rem;text-align:left;cursor:pointer;"><span class="vflag" style="display:inline-block;width:22px;height:15px;border-radius:3px;overflow:hidden;"><svg viewBox="0 0 24 16" preserveAspectRatio="none"><rect width="24" height="5.33" fill="#000"/><rect y="5.33" width="24" height="5.33" fill="#DD0000"/><rect y="10.66" width="24" height="5.34" fill="#FFCE00"/></svg></span><span class="vname" style="flex:1;">Deutsch</span><svg class="vcheck" viewBox="0 0 24 24" fill="none" stroke="#a78bfa" stroke-width="3" stroke-linecap="round" stroke-linejoin="round" style="width:14px;height:14px;opacity:0;"><polyline points="20 6 9 17 4 12"/></svg></button>
        <button class="vlang-item" data-lang="fr" onclick="vidmaPickLang('fr',event)" type="button" style="display:flex;align-items:center;gap:10px;width:100%;padding:9px 12px;background:transparent;border:none;border-radius:10px;color:#d0d0d0;font-size:0.9rem;text-align:left;cursor:pointer;"><span class="vflag" style="display:inline-block;width:22px;height:15px;border-radius:3px;overflow:hidden;"><svg viewBox="0 0 24 16" preserveAspectRatio="none"><rect width="8" height="16" fill="#002395"/><rect x="8" width="8" height="16" fill="#fff"/><rect x="16" width="8" height="16" fill="#ED2939"/></svg></span><span class="vname" style="flex:1;">Français</span><svg class="vcheck" viewBox="0 0 24 24" fill="none" stroke="#a78bfa" stroke-width="3" stroke-linecap="round" stroke-linejoin="round" style="width:14px;height:14px;opacity:0;"><polyline points="20 6 9 17 4 12"/></svg></button>
        <button class="vlang-item" data-lang="zh" onclick="vidmaPickLang('zh',event)" type="button" style="display:flex;align-items:center;gap:10px;width:100%;padding:9px 12px;background:transparent;border:none;border-radius:10px;color:#d0d0d0;font-size:0.9rem;text-align:left;cursor:pointer;"><span class="vflag" style="display:inline-block;width:22px;height:15px;border-radius:3px;overflow:hidden;"><svg viewBox="0 0 24 16" preserveAspectRatio="none"><rect width="24" height="16" fill="#DE2910"/><polygon points="4.5,2.5 5.6,5.6 2.6,3.4 6.4,3.4 3.4,5.6" fill="#FFDE00"/></svg></span><span class="vname" style="flex:1;">中文</span><svg class="vcheck" viewBox="0 0 24 24" fill="none" stroke="#a78bfa" stroke-width="3" stroke-linecap="round" stroke-linejoin="round" style="width:14px;height:14px;opacity:0;"><polyline points="20 6 9 17 4 12"/></svg></button>
        <button class="vlang-item" data-lang="ja" onclick="vidmaPickLang('ja',event)" type="button" style="display:flex;align-items:center;gap:10px;width:100%;padding:9px 12px;background:transparent;border:none;border-radius:10px;color:#d0d0d0;font-size:0.9rem;text-align:left;cursor:pointer;"><span class="vflag" style="display:inline-block;width:22px;height:15px;border-radius:3px;overflow:hidden;"><svg viewBox="0 0 24 16" preserveAspectRatio="none"><rect width="24" height="16" fill="#fff"/><circle cx="12" cy="8" r="4.4" fill="#BC002D"/></svg></span><span class="vname" style="flex:1;">日本語</span><svg class="vcheck" viewBox="0 0 24 24" fill="none" stroke="#a78bfa" stroke-width="3" stroke-linecap="round" stroke-linejoin="round" style="width:14px;height:14px;opacity:0;"><polyline points="20 6 9 17 4 12"/></svg></button>
        <button class="vlang-item" data-lang="pt" onclick="vidmaPickLang('pt',event)" type="button" style="display:flex;align-items:center;gap:10px;width:100%;padding:9px 12px;background:transparent;border:none;border-radius:10px;color:#d0d0d0;font-size:0.9rem;text-align:left;cursor:pointer;"><span class="vflag" style="display:inline-block;width:22px;height:15px;border-radius:3px;overflow:hidden;"><svg viewBox="0 0 24 16" preserveAspectRatio="none"><rect width="9.6" height="16" fill="#006600"/><rect x="9.6" width="14.4" height="16" fill="#FF0000"/><circle cx="9.6" cy="8" r="3.3" fill="#FFCC00" stroke="#fff" stroke-width="0.4"/></svg></span><span class="vname" style="flex:1;">Português</span><svg class="vcheck" viewBox="0 0 24 24" fill="none" stroke="#a78bfa" stroke-width="3" stroke-linecap="round" stroke-linejoin="round" style="width:14px;height:14px;opacity:0;"><polyline points="20 6 9 17 4 12"/></svg></button>
    </div>
</div>



<div class="container" id="main-screen">
        <header>
            <div class="logo" style="display:flex;align-items:center;justify-content:center;gap:14px;">
                <img src="/logo.png" alt="Vidma" width="72" height="72" style="border-radius:18px;" fetchpriority="high">
                <span>Vidma</span>
            </div>
            <div class="privacy-badge">
                <svg width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><rect x="3" y="11" width="18" height="11" rx="2" ry="2"/><path d="M7 11V7a5 5 0 0 1 10 0v4"/></svg>
                <span data-i18n="badge.privacy">No registration. Your conversation is private.</span>
            </div>
            <div class="privacy-badge" style="background:rgba(245,158,11,0.12);color:#fbbf24;border-color:rgba(245,158,11,0.3);margin-top:8px;">
                <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M12 2v6M12 18v4M4.93 4.93l4.24 4.24M14.83 14.83l4.24 4.24M2 12h6M18 12h4M4.93 19.07l4.24-4.24M14.83 9.17l4.24-4.24"/></svg>
                <span data-i18n="badge.beta">Beta version. Please leave feedback after the call!</span>
            </div>
            <h1 style="position:absolute; opacity:0; pointer-events:none;">Бесплатные видеозвонки Vidma</h1>
            <div class="subtitle" data-i18n="app.subtitle">Video meetings in one click</div>
        </header>
        <div class="cards">
            <div class="card">
                <h2 data-i18n="card.create">Create a meeting</h2>
                <div class="input-group"><label data-i18n="label.yourName">Your name</label><input type="text" id="create-name" placeholder="Guest" data-i18n-placeholder="placeholder.guest" value="" autocomplete="name" onkeydown="if(event.key==='Enter'){event.preventDefault();createRoom();}"></div>
                <button class="btn btn-primary" onclick="createRoom()" data-i18n="btn.createRoom">Create room</button>
                <div class="room-display" id="room-created">
                    <p data-i18n="room.code">Meeting code:</p><div class="room-id-display" id="created-room-id"></div>
                    <button class="btn btn-outline" onclick="openInviteModal()"><svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M16 21v-2a4 4 0 0 0-4-4H5a4 4 0 0 0-4 4v2"/><circle cx="8.5" cy="7" r="4"/><line x1="20" y1="8" x2="20" y2="14"/><line x1="23" y1="11" x2="17" y2="11"/></svg> <span data-i18n="invite.button">Invite</span></button>
                    <button class="btn btn-primary" style="margin-top: 12px;" onclick="joinCreatedRoom()" data-i18n="btn.enterRoom">Enter room</button>
                </div>
            </div>
            <div class="card">
                <h2 data-i18n="card.join">Join</h2>
                <div class="input-group"><label data-i18n="label.yourName">Your name</label><input type="text" id="join-name" placeholder="Guest" data-i18n-placeholder="placeholder.guest" value="" autocomplete="name" onkeydown="if(event.key==='Enter'){event.preventDefault();document.getElementById('room-id').focus();}"></div>
                <div class="input-group"><label data-i18n="label.roomCode">Room code</label><input type="text" id="room-id" placeholder="XXX-XXX-XXX" maxlength="11" inputmode="numeric" pattern="[0-9\-]*" autocomplete="off" onkeydown="if(event.key==='Enter'){event.preventDefault();joinRoom();}"></div>
                <button class="btn btn-primary" onclick="joinRoom()" data-i18n="btn.join">Join</button>
            </div>
        </div>
        
        <!-- === FEATURES === -->
        <section class="landing-section">
            <h2 data-i18n="landing.features.title">Why Vidma</h2>
            <p class="section-sub" data-i18n="landing.features.subtitle">Simple, private, and works right in your browser</p>
            <div class="features-grid">
                <div class="feature-card">
                    <div class="fc-icon">
                        <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><rect x="3" y="11" width="18" height="11" rx="2" ry="2"/><path d="M7 11V7a5 5 0 0 1 10 0v4"/></svg>
                    </div>
                    <h3 data-i18n="landing.features.encrypted.title">Encrypted end-to-end</h3>
                    <p data-i18n="landing.features.encrypted.text">TLS 1.3 for signalling, DTLS-SRTP for media, E2EE for chat. No recordings, no history.</p>
                </div>
                <div class="feature-card">
                    <div class="fc-icon">
                        <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M13 2L3 14h9l-1 8 10-12h-9l1-8z"/></svg>
                    </div>
                    <h3 data-i18n="landing.features.instant.title">Instant meetings</h3>
                    <p data-i18n="landing.features.instant.text">Create a room in one click and share the link. No registration, no download, no email.</p>
                </div>
                <div class="feature-card">
                    <div class="fc-icon">
                        <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M21 15a2 2 0 0 1-2 2H7l-4 4V5a2 2 0 0 1 2-2h14a2 2 0 0 1 2 2z"/></svg>
                    </div>
                    <h3 data-i18n="landing.features.chat.title">Chat + screen share</h3>
                    <p data-i18n="landing.features.chat.text">Message anyone in the call, share your screen, switch cameras. All from the same tab.</p>
                </div>
                <div class="feature-card">
                    <div class="fc-icon">
                        <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><circle cx="12" cy="12" r="10"/><line x1="2" y1="12" x2="22" y2="12"/><path d="M12 2a15.3 15.3 0 0 1 4 10 15.3 15.3 0 0 1-4 10 15.3 15.3 0 0 1-4-10 15.3 15.3 0 0 1 4-10z"/></svg>
                    </div>
                    <h3 data-i18n="landing.features.langs.title">8 languages</h3>
                    <p data-i18n="landing.features.langs.text">English, Русский, Español, Deutsch, Français, 中文, 日本語, Português — switch anytime.</p>
                </div>
            </div>
        </section>

        <!-- === HOW IT WORKS === -->
        <section class="landing-section">
            <h2 data-i18n="landing.how.title">How it works</h2>
            <p class="section-sub" data-i18n="landing.how.subtitle">Get on a call in under 10 seconds</p>
            <div class="steps-grid">
                <div class="step">
                    <div class="step-num">1</div>
                    <h3 data-i18n="landing.how.step1.title">Create a room</h3>
                    <p data-i18n="landing.how.step1.text">Enter your name and press Create. You get a link instantly.</p>
                </div>
                <div class="step">
                    <div class="step-num">2</div>
                    <h3 data-i18n="landing.how.step2.title">Share the link</h3>
                    <p data-i18n="landing.how.step2.text">Send it via Telegram, WhatsApp, email, or copy manually.</p>
                </div>
                <div class="step">
                    <div class="step-num">3</div>
                    <h3 data-i18n="landing.how.step3.title">Talk</h3>
                    <p data-i18n="landing.how.step3.text">Friends click the link, check their camera, and join the room.</p>
                </div>
            </div>
        </section>

        <!-- === FAQ === -->
        <section class="landing-section">
            <h2 data-i18n="landing.faq.title">Frequently asked questions</h2>
            <div class="faq-list">
                <details class="faq-item">
                    <summary data-i18n="landing.faq.q1">Do I need to register?</summary>
                    <div class="faq-answer" data-i18n="landing.faq.a1">No. Vidma is completely free and requires no account. Just enter a name (or leave it as Guest) and start a call.</div>
                </details>
                <details class="faq-item">
                    <summary data-i18n="landing.faq.q2">Are my calls private?</summary>
                    <div class="faq-answer" data-i18n="landing.faq.a2">Yes. Video and audio are encrypted end-to-end using DTLS-SRTP. We never record calls or store call history. Chat is E2EE via LiveKit DataChannel.</div>
                </details>
                <details class="faq-item">
                    <summary data-i18n="landing.faq.q3">How many people can join a room?</summary>
                    <div class="faq-answer" data-i18n="landing.faq.a3">Up to 20 participants per room. For larger meetings, contact us.</div>
                </details>
                <details class="faq-item">
                    <summary data-i18n="landing.faq.q4">Does it work on mobile?</summary>
                    <div class="faq-answer" data-i18n="landing.faq.a4">Yes. Vidma works on iPhone, iPad, Android phones and tablets through any modern browser. No app required.</div>
                </details>
                <details class="faq-item">
                    <summary data-i18n="landing.faq.q5">Is Vidma open source?</summary>
                    <div class="faq-answer" data-i18n="landing.faq.a5">Yes. The full source code is available on GitHub under AGPL-3.0 license. Self-host it, modify it, or contribute back.</div>
                </details>
            </div>
        </section>

        <div class="footer-note">
            <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M12 22s8-4 8-10V5l-8-3-8 3v7c0 6 8 10 8 10z"/></svg>
            <span data-i18n="footer.noHistory">We don't store call history and don't require installation.</span>
        </div>
        <div class="support-link">
            <span data-i18n="support">Support</span>: <span>vidma.on@gmail.com</span>
        </div>
        <div class="legal-links">
            <a href="/privacy" data-i18n="legal.privacy">Privacy</a>
            <a href="/terms" data-i18n="legal.terms">Terms</a>
        </div>
    </div>

    <div id="lobby-screen">
        <div class="lobby-wrap">
            <h2 data-i18n="lobby.title">Check camera and microphone</h2>
            <p class="lobby-sub" data-i18n="lobby.subtitle">Make sure you are seen and heard, then join the room</p>
            <div class="lobby-name-row">
                <label data-i18n="label.yourName">Your name</label>
                <input type="text" id="lobby-name-input" placeholder="Guest" data-i18n-placeholder="placeholder.guest" maxlength="50" autocomplete="name" onkeydown="if(event.key==='Enter'){event.preventDefault();confirmLobbyEntry();}">
            </div>

            <div class="lobby-preview" id="lobby-preview-box">
                <video id="lobby-video" autoplay playsinline muted></video>
                <div class="no-video">Камера выключена</div>
            </div>

            <div class="lobby-row">
                <label data-i18n="lobby.mic">Microphone</label>
                <select id="lobby-mic-select"></select>
                <button class="tog on" id="lobby-mic-toggle" onclick="lobbyToggleMic()" title="Вкл/выкл микрофон">
                    <svg id="lobby-mic-svg-on" width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M12 1a3 3 0 0 0-3 3v8a3 3 0 0 0 6 0V4a3 3 0 0 0-3-3z"/><path d="M19 10v2a7 7 0 0 1-14 0v-2"/><line x1="12" y1="19" x2="12" y2="23"/><line x1="8" y1="23" x2="16" y2="23"/></svg>
                    <svg id="lobby-mic-svg-off" width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" style="display:none;"><line x1="1" y1="1" x2="23" y2="23"/><path d="M9 9v3a3 3 0 0 0 5.12 2.12M15 9.34V4a3 3 0 0 0-5.94-.6"/><path d="M17 16.95A7 7 0 0 1 5 12v-2m14 0v2a7 7 0 0 1-.11 1.23"/><line x1="12" y1="19" x2="12" y2="23"/><line x1="8" y1="23" x2="16" y2="23"/></svg>
                </button>
            </div>
            <div class="lobby-level"><div id="lobby-level-bar"></div></div>

            <div class="lobby-row">
                <label data-i18n="lobby.camera">Camera</label>
                <select id="lobby-cam-select"></select>
                <button class="tog on" id="lobby-cam-toggle" onclick="lobbyToggleCam()" title="Вкл/выкл камеру">
                    <svg id="lobby-cam-svg-on" width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><polygon points="23 7 16 12 23 17 23 7"/><rect x="1" y="5" width="15" height="14" rx="2" ry="2"/></svg>
                    <svg id="lobby-cam-svg-off" width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" style="display:none;"><line x1="1" y1="1" x2="23" y2="23"/><path d="M21 21H3a2 2 0 0 1-2-2V8a2 2 0 0 1 2-2h3m3-3h6l2 3h4a2 2 0 0 1 2 2v9.34m-7.72-2.06a4 4 0 1 1-5.56-5.56"/></svg>
                </button>
            </div>

            <div class="lobby-actions">
                <button class="btn-lobby-cancel" onclick="cancelLobby()" data-i18n="lobby.cancel">Cancel</button>
                <button class="btn-lobby-join" id="lobby-join-btn" onclick="confirmLobbyEntry()"> <span data-i18n="lobby.join">Join room</span></button>
            </div>
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
                <span data-i18n="call.room">Room</span><span class="room-code" id="current-room-code"></span>
                <button class="share-btn" onclick="openInviteModal()"><svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M16 21v-2a4 4 0 0 0-4-4H5a4 4 0 0 0-4 4v2"/><circle cx="8.5" cy="7" r="4"/><line x1="20" y1="8" x2="20" y2="14"/><line x1="23" y1="11" x2="17" y2="11"/></svg> <span data-i18n="invite.button">Invite</span></button>
            </div>
        </div>
        <div id="videos-container">
            <div id="remote-videos-grid"></div>
        </div>
        <div id="local-video-container">
            <div class="video-label" id="local-video-label" data-i18n="call.you">You</div>
            <div class="video-avatar" id="local-video-avatar">
                <div class="avatar-circle" id="local-avatar-circle"></div>
            </div>
            <video id="local-video" autoplay playsinline muted></video>
        </div>
        <div id="local-camera-container">
            <div class="video-label" data-i18n="call.camera">Camera</div>
            <video id="local-camera-video" autoplay playsinline muted></video>
        </div>
        <div id="chat-panel">
        <div id="chat-header">
            <span data-i18n="chat.title">Room chat</span>
            <button class="close-chat" onclick="toggleChatPanel()" title="Закрыть">✕</button>
        </div>
        <div id="chat-messages">
            <div id="chat-empty">История чата видна только вам и хранится в этом браузере.</div>
        </div>
        <form id="chat-form" onsubmit="handleChatSubmit(event)">
            <input type="text" id="chat-input" placeholder="Message..." data-i18n-placeholder="chat.placeholder" data-i18n-placeholder="chat.placeholder" maxlength="500" autocomplete="off">
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
            <h3 data-i18n="rating.title">Rate the call quality</h3>
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
            <textarea id="rating-comment" maxlength="500" placeholder="For example: sound is great, but video stutters on phone" data-i18n-placeholder="rating.commentPlaceholder"
                style="width:100%;min-height:70px;padding:10px 12px;border-radius:12px;background:#2a2a3a;color:#fff;border:1px solid #444;font-family:inherit;font-size:0.9rem;resize:vertical;outline:none;"></textarea>
            <button onclick="submitRating()" data-i18n="rating.submit">Submit</button>
            <button onclick="closeRating()" style="background: transparent; border: 1px solid #555; margin-left: 10px;" data-i18n="rating.skip">Skip</button>
        </div>
    </div>

    <div class="modal-overlay" id="camera-choice-modal">
        <div class="modal">
            <h3 data-i18n="camera.title">Camera access</h3>
            <p style="margin-bottom: 20px; font-size: 0.9rem; color: #ccc;"><span data-i18n="camera.hint">Allow camera access or join without video.</span></p>
            <button onclick="retryCamera()" data-i18n="camera.allow">Enable camera</button>
            <button onclick="joinWithoutCamera()" style="background: transparent; border: 1px solid #555; margin-left: 10px;" data-i18n="camera.noVideo">Without video</button>
        </div>
    </div>
    <script src="https://cdn.jsdelivr.net/npm/livekit-client@2.9.7/dist/livekit-client.umd.min.js"></script>
    <script src="/app.js"></script>
</body>
</html>)html";

#endif // VIDMA_HTML_H
