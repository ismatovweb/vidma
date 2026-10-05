// Auto-generated from Server.h by sprint1_extract.py
// Client-side JavaScript for the Vidma app. Do not edit by hand.
#ifndef VIDMA_JS_H
#define VIDMA_JS_H

constexpr const char* VIDMA_JS = R"js(
console.log('=== Vidma WebRTC (Final) ===');

let localStream = null;
let peerConnections = new Map();
let peerNames = new Map();
let currentRoomId = null;
let currentSessionId = null;
let currentName = null;
let ws = null;
let isMicEnabled = true;
let isCamEnabled = true;
let pendingIce = new Map();
let remoteStreams = new Map();
let reconnectTimers = new Map();
let isMobile = /iPhone|iPad|iPod|Android/i.test(navigator.userAgent);
let audioContext = null;
let isScreenSharing = false;
let screenStream = null;
let originalVideoTrack = null;
let screenAudioTrackAdded = null;
let selectedRating = 0;

const iceServers = {
    iceServers: [
        { urls: 'stun:stun.l.google.com:19302' },
        { urls: 'stun:stun1.l.google.com:19302' }
    ],
    iceTransportPolicy: 'all',
    iceCandidatePoolSize: 10
};

async function loadTurnCredentials() {
    try {
        const res = await fetch('/api/turn-credentials', { cache: 'no-store' });
        if (!res.ok) return;
        const data = await res.json();
        if (data.urls && data.username && data.credential) {
            iceServers.iceServers.push({
                urls: data.urls,
                username: data.username,
                credential: data.credential
            });
            console.log('TURN credentials loaded');
        }
    } catch (e) {
        console.warn('TURN credentials fetch failed:', e);
    }
}

function generateSessionId() { return Math.random().toString(36).substring(2,10); }
function showSecureConnectionIndicator() {
    const bar = document.getElementById('security-bar');
    if(bar) bar.style.display = 'flex';
}

function showToast(text) {
    const toast = document.getElementById('toast');
    toast.textContent = text;
    toast.classList.add('show');
    setTimeout(() => toast.classList.remove('show'), 2000);
}

function resetButtons() {
    isMicEnabled = true;
    isCamEnabled = true;
    document.getElementById('mic-icon-on').style.display = '';
    document.getElementById('mic-icon-off').style.display = 'none';
    document.getElementById('cam-icon-on').style.display = '';
    document.getElementById('cam-icon-off').style.display = 'none';
}

document.addEventListener('DOMContentLoaded', function() {
    const roomInput = document.getElementById('room-id');
    if (roomInput) {
        roomInput.addEventListener('input', function(e) {
            const inputType = e.inputType || '';
            const isDeletion = inputType.startsWith('delete');
            if (isDeletion) return;
            let val = e.target.value;
            let digits = val.replace(/[^\d]/g, '');
            if (digits.length > 9) digits = digits.slice(0, 9);
            let formatted = digits;
            if (digits.length >= 7) formatted = digits.slice(0,3)+'-'+digits.slice(3,6)+'-'+digits.slice(6);
            else if (digits.length === 6) formatted = digits.slice(0,3)+'-'+digits.slice(3,6)+'-';
            else if (digits.length >= 4) formatted = digits.slice(0,3)+'-'+digits.slice(3);
            else if (digits.length === 3) formatted = digits+'-';
            e.target.value = formatted;
            e.target.setSelectionRange(formatted.length, formatted.length);
        });
        const urlParams = new URLSearchParams(window.location.search);
        const roomFromUrl = urlParams.get('room');
        if (roomFromUrl) {
            let digits = roomFromUrl.replace(/[^\d]/g, '');
            if (digits.length > 9) digits = digits.slice(0, 9);
            let formatted = digits;
            if (digits.length >= 7) formatted = digits.slice(0,3)+'-'+digits.slice(3,6)+'-'+digits.slice(6);
            else if (digits.length === 6) formatted = digits.slice(0,3)+'-'+digits.slice(3,6)+'-';
            else if (digits.length >= 4) formatted = digits.slice(0,3)+'-'+digits.slice(3);
            else if (digits.length === 3) formatted = digits+'-';
            roomInput.value = formatted;
            roomInput.setSelectionRange(formatted.length, formatted.length);
        }
    }
});

async function createRoom() {
    let name = document.getElementById('create-name').value.trim();
    if (!name) name = 'Гость';
    try {
        const res = await fetch('/api/room/create', { method: 'POST' });
        const data = await res.json();
        document.getElementById('created-room-id').textContent = data.roomId;
        document.getElementById('room-created').style.display = 'block';
        currentRoomId = data.roomId;
        currentName = name;
    } catch(e) { alert('Ошибка создания'); }
}

function copyRoomLink() {
    const link = location.origin + '?room=' + currentRoomId;
    const fullText = link + '\nVidma — Видеовстречи в один клик';
    navigator.clipboard.writeText(fullText).then(() => showToast('Ссылка скопирована!'));
}

function joinCreatedRoom() { joinRoomById(currentRoomId, currentName); }

async function joinRoom() {
    let name = document.getElementById('join-name').value.trim();
    if (!name) name = 'Гость';
    let roomId = document.getElementById('room-id').value.trim();
    const digits = roomId.replace(/[^\d]/g, '');
    if (digits.length !== 9) { alert('Введите полный код комнаты (9 цифр)'); return; }
    roomId = digits.slice(0,3)+'-'+digits.slice(3,6)+'-'+digits.slice(6,9);
    try {
        const res = await fetch(`/api/room/${roomId}/exists`);
        const data = await res.json();
        if (!data.exists) { alert('Комната не найдена'); return; }
        joinRoomById(roomId, name);
    } catch(e) { alert('Ошибка'); }
}

// === ИЗМЕНЁННЫЕ ФУНКЦИИ ДЛЯ ПОДДЕРЖКИ ОТСУТСТВИЯ КАМЕРЫ ===
async function tryGetUserMedia(constraints) {
    try {
        return await navigator.mediaDevices.getUserMedia(constraints);
    } catch (err) {
        // Показываем диалог с вариантами (повторить или без видео) при любой ошибке
        document.getElementById('camera-choice-modal').classList.add('active');
        throw err;
    }
}

async function retryCamera() {
    document.getElementById('camera-choice-modal').classList.remove('active');
    try {
        const stream = await navigator.mediaDevices.getUserMedia({video: true, audio: true});
        localStream = stream;
        isCamEnabled = true;
        isMicEnabled = true;
        document.getElementById('cam-icon-on').style.display = '';
        document.getElementById('cam-icon-off').style.display = 'none';
        document.getElementById('mic-icon-on').style.display = '';
        document.getElementById('mic-icon-off').style.display = 'none';
        setupLocalVideo();
        connectWebSocket();
    } catch (err) {
        // если снова ошибка, возвращаем модалку (кнопка "Без видео" всё ещё работает)
        document.getElementById('camera-choice-modal').classList.add('active');
        console.warn('Повторная попытка не удалась:', err);
    }
}

async function joinWithoutCamera() {
    document.getElementById('camera-choice-modal').classList.remove('active');
    try {
        const stream = await navigator.mediaDevices.getUserMedia({video: false, audio: true});
        localStream = stream;
        isCamEnabled = false;
        isMicEnabled = true;
        document.getElementById('cam-icon-on').style.display = 'none';
        document.getElementById('cam-icon-off').style.display = '';
        document.getElementById('mic-icon-on').style.display = '';
        document.getElementById('mic-icon-off').style.display = 'none';

        audioContext = new (window.AudioContext || window.webkitAudioContext)();
        const source = audioContext.createMediaStreamSource(localStream);
        const highpass = audioContext.createBiquadFilter();
        highpass.type = "highpass"; highpass.frequency = 80; highpass.Q = 0.5;
        const compressor = audioContext.createDynamicsCompressor();
        compressor.threshold = -24; compressor.knee = 30; compressor.ratio = 12;
        compressor.attack = 0.003; compressor.release = 0.25;
        const gain = audioContext.createGain(); gain.gain.value = 1.2;
        source.connect(highpass); highpass.connect(compressor); compressor.connect(gain);

        document.getElementById('main-screen').style.display = 'none';
        document.getElementById('call-screen').style.display = 'block';
        document.getElementById('local-video').srcObject = null;
        document.getElementById('local-video-label').textContent = currentName + ' (Вы)';
        connectWebSocket();
    } catch (err) {
        alert('Не удалось получить доступ к микрофону. Проверьте настройки браузера.');
    }
}

function setupLocalVideo() {
    const videoTrack = localStream ? localStream.getVideoTracks()[0] : null;
    if (videoTrack) {
        document.getElementById('local-video').srcObject = localStream;
    } else {
        document.getElementById('local-video').srcObject = null;
    }
}

async function joinRoomById(roomId, name) {
    currentRoomId = roomId;
    currentName = name;
    currentSessionId = generateSessionId();
    await loadTurnCredentials();
    document.getElementById('current-room-code').textContent = roomId;
    resetButtons();

    try {
        const constraints = { video: true, audio: true };
        localStream = await tryGetUserMedia(constraints);  // при ошибке покажет модалку и выбросит исключение
        isCamEnabled = true;
        isMicEnabled = true;
        audioContext = new (window.AudioContext || window.webkitAudioContext)();
        const source = audioContext.createMediaStreamSource(localStream);
        const highpass = audioContext.createBiquadFilter();
        highpass.type = "highpass"; highpass.frequency = 80; highpass.Q = 0.5;
        const compressor = audioContext.createDynamicsCompressor();
        compressor.threshold = -24; compressor.knee = 30; compressor.ratio = 12;
        compressor.attack = 0.003; compressor.release = 0.25;
        const gain = audioContext.createGain(); gain.gain.value = 1.2;
        source.connect(highpass); highpass.connect(compressor); compressor.connect(gain);
        document.getElementById('main-screen').style.display = 'none';
        document.getElementById('call-screen').style.display = 'block';
        document.getElementById('local-video').srcObject = localStream;
        document.getElementById('local-video-label').textContent = name + ' (Вы)';
        connectWebSocket();
    } catch (err) {
        // модалка уже показана, ничего не делаем; пользователь выберет действие
        return;
    }
}

// ====== ОСТАЛЬНЫЕ ФУНКЦИИ БЕЗ ИЗМЕНЕНИЙ (как в исходном коде) ======

function connectWebSocket() {
    const proto = location.protocol === 'https:' ? 'wss:' : 'ws:';
    ws = new WebSocket(proto + '//' + location.host + '/ws');
    ws.onopen = () => {
        showSecureConnectionIndicator();
        ws.send(JSON.stringify({ type: 'join', roomId: currentRoomId, name: currentName }));
    };
    ws.onmessage = (e) => {
        const msg = JSON.parse(e.data);
        console.log('WS:', msg.type, msg);
        if (msg.type === 'joined') { if (msg.sessionId) currentSessionId = msg.sessionId; return; }
        if (msg.type === 'new-peer' && msg.sessionId !== currentSessionId) {
            peerNames.set(msg.sessionId, msg.name);
            const isInitiator = (msg.existing === true);
            createPeerConnection(msg.sessionId, msg.name, isInitiator);
        } else if (msg.type === 'offer') {
            const peerName = peerNames.get(msg.sender) || 'Участник';
            handleOffer(msg.sender, msg.offer, peerName);
        } else if (msg.type === 'answer') {
            handleAnswer(msg.sender, msg.answer);
        } else if (msg.type === 'ice-candidate') {
            handleIceCandidate(msg.sender, msg.candidate);
        } else if (msg.type === 'peer-left') {
            closePeerConnection(msg.sessionId);
            peerNames.delete(msg.sessionId);
        }
    };
    ws.onclose = () => console.log('WS closed');
}

async function toggleScreenShare() {
    const btn = document.getElementById('toggle-screen');
    if (!isScreenSharing) {
        try {
            screenStream = await navigator.mediaDevices.getDisplayMedia({ video: true, audio: true });
            originalVideoTrack = localStream.getVideoTracks()[0] || null;
            const screenVideoTrack = screenStream.getVideoTracks()[0];

            for (let [id, pc] of peerConnections) {
                const senders = pc.getSenders();
                const videoSender = senders.find(s => s.track && s.track.kind === 'video');
                if (videoSender) await videoSender.replaceTrack(screenVideoTrack);
                if (originalVideoTrack) {
                    pc.addTrack(originalVideoTrack, localStream);
                }
            }

            const screenAudioTrack = screenStream.getAudioTracks()[0];
            if (screenAudioTrack) {
                for (let [id, pc] of peerConnections) {
                    pc.addTrack(screenAudioTrack, screenStream);
                }
                screenAudioTrackAdded = screenAudioTrack;
            }

            document.getElementById('local-video').srcObject = screenStream;
            document.getElementById('local-video-label').textContent = currentName + ' (Экран)';
            const camContainer = document.getElementById('local-camera-container');
            if (originalVideoTrack) {
                const camVideo = document.getElementById('local-camera-video');
                camVideo.srcObject = new MediaStream([originalVideoTrack]);
                camContainer.style.display = 'block';
            }

            screenVideoTrack.onended = () => stopScreenShare();
            isScreenSharing = true;
            btn.classList.add('active');
        } catch (err) { alert('Не удалось начать демонстрацию экрана'); }
    } else {
        stopScreenShare();
    }
}

function stopScreenShare() {
    if (!isScreenSharing) return;
    const btn = document.getElementById('toggle-screen');
    if (screenStream) { screenStream.getTracks().forEach(t => t.stop()); screenStream = null; }
    if (originalVideoTrack) {
        for (let [id, pc] of peerConnections) {
            const sender = pc.getSenders().find(s => s.track && s.track.id === originalVideoTrack.id);
            if (sender) pc.removeTrack(sender);
            const videoSender = pc.getSenders().find(s => s.track && s.track.kind === 'video');
            if (videoSender && originalVideoTrack) videoSender.replaceTrack(originalVideoTrack);
        }
        document.getElementById('local-video').srcObject = localStream;
        document.getElementById('local-video-label').textContent = currentName + ' (Вы)';
    }
    if (screenAudioTrackAdded) {
        for (let [id, pc] of peerConnections) {
            const sender = pc.getSenders().find(s => s.track && s.track.id === screenAudioTrackAdded.id);
            if (sender) pc.removeTrack(sender);
        }
        screenAudioTrackAdded = null;
    }
    document.getElementById('local-camera-container').style.display = 'none';
    document.getElementById('local-camera-video').srcObject = null;
    originalVideoTrack = null;
    isScreenSharing = false;
    btn.classList.remove('active');
}

function createPeerConnection(sessionId, peerName, isInitiator) {
    if (peerConnections.has(sessionId)) {
        const pc = peerConnections.get(sessionId);
        if (pc.connectionState === 'connected' || pc.connectionState === 'connecting') return pc;
        pc.close();
        peerConnections.delete(sessionId);
    }
    console.log(`Creating PC for ${sessionId}, initiator=${isInitiator}`);
    const pc = new RTCPeerConnection(iceServers);
    peerConnections.set(sessionId, pc);
    pendingIce.set(sessionId, []);

    if (localStream) {
        localStream.getTracks().forEach(track => {
            if (isScreenSharing && track.kind === 'video') return;
            const sender = pc.addTrack(track, localStream);
            if (track.kind === 'audio') {
                const params = sender.getParameters();
                if (!params.encodings) params.encodings = [{}];
                params.encodings[0].priority = 'high';
                params.encodings[0].networkPriority = 'high';
                sender.setParameters(params).catch(console.warn);
            }
        });
        if (isScreenSharing && screenStream) {
            pc.addTrack(screenStream.getVideoTracks()[0], screenStream);
            if (originalVideoTrack) pc.addTrack(originalVideoTrack, localStream);
            if (screenAudioTrackAdded) pc.addTrack(screenAudioTrackAdded, screenStream);
        }
    }

    pc.onicecandidate = (e) => {
        if (e.candidate && ws.readyState === WebSocket.OPEN) {
            ws.send(JSON.stringify({ type: 'ice-candidate', roomId: currentRoomId, target: sessionId, candidate: e.candidate }));
        }
    };

    pc.ontrack = (e) => {
        console.log(`Track from ${sessionId}: ${e.track.kind}`);
        if (!remoteStreams.has(sessionId)) {
            remoteStreams.set(sessionId, new MediaStream());
        }
        const stream = remoteStreams.get(sessionId);
        stream.addTrack(e.track);

        const videoTracks = stream.getVideoTracks();
        const hasMainVideo = !!document.getElementById('remote-' + sessionId);

        if (!hasMainVideo && videoTracks.length > 0) {
            addRemoteVideo(sessionId, stream, peerName);
        } else if (videoTracks.length >= 2 && !document.getElementById('remote-camera-' + sessionId)) {
            createRemoteCameraBlock(sessionId, e.track, peerName);
        }
    };

    pc.onconnectionstatechange = () => {
        console.log(`State ${sessionId}: ${pc.connectionState}`);
        updateStatus(sessionId, pc.connectionState);
        if (pc.connectionState === 'failed' || pc.connectionState === 'disconnected') {
            scheduleReconnect(sessionId, peerName);
        }
    };

    if (isInitiator) {
        pc.createOffer({ offerToReceiveAudio: true, offerToReceiveVideo: true })
            .then(offer => pc.setLocalDescription(offer))
            .then(() => ws.send(JSON.stringify({ type: 'offer', roomId: currentRoomId, target: sessionId, offer: pc.localDescription })))
            .catch(e => console.error('Offer error', e));
    }
    return pc;
}

function createRemoteCameraBlock(sessionId, track, label) {
    const grid = document.getElementById('remote-videos-grid');
    const wrapper = document.createElement('div');
    wrapper.id = 'remote-camera-' + sessionId;
    wrapper.className = 'remote-camera-wrapper';
    const video = document.createElement('video');
    video.autoplay = true; video.playsInline = true;
    video.srcObject = new MediaStream([track]);
    video.onloadedmetadata = () => video.play();
    const lbl = document.createElement('div');
    lbl.className = 'video-label';
    lbl.textContent = label + ' (Камера)';
    wrapper.appendChild(video);
    wrapper.appendChild(lbl);
    grid.appendChild(wrapper);
}

function addRemoteVideo(sessionId, stream, label) {
    const grid = document.getElementById('remote-videos-grid');
    let wrapper = document.getElementById('remote-' + sessionId);
    if (!wrapper) {
        wrapper = document.createElement('div');
        wrapper.id = 'remote-' + sessionId;
        wrapper.className = 'remote-video-wrapper';
        const video = document.createElement('video');
        video.autoplay = true; video.playsInline = true;
        video.srcObject = stream;
        video.onloadedmetadata = () => video.play();
        const lbl = document.createElement('div');
        lbl.className = 'video-label';
        lbl.textContent = label;
        const status = document.createElement('div');
        status.className = 'connection-status';
        status.id = 'status-' + sessionId;
        status.textContent = 'connecting...';
        const fullscreenBtn = document.createElement('button');
        fullscreenBtn.className = 'fullscreen-btn';
        fullscreenBtn.innerHTML = '⛶';
        fullscreenBtn.onclick = (e) => { e.stopPropagation(); toggleFullscreen(wrapper); };
        fullscreenBtn.ontouchend = (e) => { e.stopPropagation(); toggleFullscreen(wrapper); };

        const controlsDiv = document.createElement('div');
        controlsDiv.className = 'fullscreen-controls';
        const exitBtn = document.createElement('button');
        exitBtn.className = 'fs-exit-btn';
        exitBtn.innerHTML = '✕';
        exitBtn.onclick = (e) => { e.stopPropagation(); closeFullscreen(); };
        exitBtn.ontouchend = (e) => { e.stopPropagation(); closeFullscreen(); };
        const volumeSlider = document.createElement('input');
        volumeSlider.type = 'range';
        volumeSlider.className = 'volume-slider';
        volumeSlider.min = 0;
        volumeSlider.max = 1;
        volumeSlider.step = 0.01;
        volumeSlider.value = video.volume || 1;
        volumeSlider.oninput = (e) => { video.volume = e.target.value; };

        controlsDiv.appendChild(volumeSlider);
        controlsDiv.appendChild(exitBtn);
        wrapper.appendChild(controlsDiv);

        const reconnectBtn = document.createElement('button');
        reconnectBtn.className = 'reconnect-btn';
        reconnectBtn.textContent = '⟲';
        reconnectBtn.onclick = () => manualReconnect(sessionId, label);

        wrapper.appendChild(video);
        wrapper.appendChild(lbl);
        wrapper.appendChild(status);
        wrapper.appendChild(fullscreenBtn);
        wrapper.appendChild(reconnectBtn);
        grid.appendChild(wrapper);
    }
}

function toggleFullscreen(wrapper) {
    if (document.fullscreenElement || document.webkitFullscreenElement) {
        closeFullscreen();
    } else {
        if (wrapper.requestFullscreen) {
            wrapper.requestFullscreen();
        } else if (wrapper.webkitRequestFullscreen) {
            wrapper.webkitRequestFullscreen();
        }
    }
}

function closeFullscreen() {
    if (document.exitFullscreen) {
        document.exitFullscreen();
    } else if (document.webkitExitFullscreen) {
        document.webkitExitFullscreen();
    }
}

function updateStatus(sessionId, state) {
    const el = document.getElementById('status-' + sessionId);
    if (!el) return;
    if (state === 'connected') {
        el.textContent = 'connected';
        el.style.color = '#4ade80';
    } else if (state === 'failed') {
        el.textContent = 'failed';
        el.style.color = '#ef4444';
    } else if (state === 'connecting') {
        el.textContent = 'connecting...';
        el.style.color = '#ffb347';
    } else {
        el.textContent = state;
        el.style.color = '#ffb347';
    }
}

function scheduleReconnect(sessionId, peerName) {
    if (reconnectTimers.has(sessionId)) return;
    const timer = setTimeout(() => {
        reconnectTimers.delete(sessionId);
        closePeerConnection(sessionId);
        createPeerConnection(sessionId, peerName, true);
    }, 2000);
    reconnectTimers.set(sessionId, timer);
}

function manualReconnect(sessionId, peerName) {
    if (reconnectTimers.has(sessionId)) clearTimeout(reconnectTimers.get(sessionId));
    reconnectTimers.delete(sessionId);
    closePeerConnection(sessionId);
    createPeerConnection(sessionId, peerName, true);
}

function handleOffer(senderId, offer, peerName) {
    const pc = createPeerConnection(senderId, peerName, false);
    pc.setRemoteDescription(new RTCSessionDescription(offer))
        .then(() => pc.createAnswer({ offerToReceiveAudio: true, offerToReceiveVideo: true }))
        .then(answer => pc.setLocalDescription(answer))
        .then(() => ws.send(JSON.stringify({ type: 'answer', roomId: currentRoomId, target: senderId, answer: pc.localDescription })))
        .then(() => {
            const candidates = pendingIce.get(senderId) || [];
            candidates.forEach(c => pc.addIceCandidate(new RTCIceCandidate(c)).catch(console.warn));
            pendingIce.set(senderId, []);
        })
        .catch(e => console.error('Offer error', e));
}

function handleAnswer(senderId, answer) {
    const pc = peerConnections.get(senderId);
    if (!pc) return;
    pc.setRemoteDescription(new RTCSessionDescription(answer))
        .then(() => {
            const candidates = pendingIce.get(senderId) || [];
            candidates.forEach(c => pc.addIceCandidate(new RTCIceCandidate(c)).catch(console.warn));
            pendingIce.set(senderId, []);
        })
        .catch(e => console.error('Answer error', e));
}

function handleIceCandidate(senderId, candidate) {
    const pc = peerConnections.get(senderId);
    if (pc && pc.remoteDescription) {
        pc.addIceCandidate(new RTCIceCandidate(candidate)).catch(console.warn);
    } else {
        const arr = pendingIce.get(senderId) || [];
        arr.push(candidate);
        pendingIce.set(senderId, arr);
    }
}

function closePeerConnection(sessionId) {
    const pc = peerConnections.get(sessionId);
    if (pc) { pc.close(); peerConnections.delete(sessionId); }
    const mainEl = document.getElementById('remote-' + sessionId);
    if (mainEl) mainEl.remove();
    const camEl = document.getElementById('remote-camera-' + sessionId);
    if (camEl) camEl.remove();
    remoteStreams.delete(sessionId);
    pendingIce.delete(sessionId);
    if (reconnectTimers.has(sessionId)) {
        clearTimeout(reconnectTimers.get(sessionId));
        reconnectTimers.delete(sessionId);
    }
}

function shareRoomFromCall() {
    const link = location.origin + '?room=' + currentRoomId;
    const fullText = link + '\nVidma — Видеовстречи в один клик';
    navigator.clipboard.writeText(fullText).then(() => showToast('Ссылка скопирована!'));
}

function toggleMic() {
    if (localStream) {
        const audioTrack = localStream.getAudioTracks()[0];
        if (audioTrack) {
            audioTrack.enabled = !audioTrack.enabled;
            isMicEnabled = audioTrack.enabled;
            document.getElementById('mic-icon-on').style.display = isMicEnabled ? '' : 'none';
            document.getElementById('mic-icon-off').style.display = isMicEnabled ? 'none' : '';
        }
    }
}

function toggleCam() {
    if (localStream) {
        const videoTrack = localStream.getVideoTracks()[0];
        if (videoTrack) {
            videoTrack.enabled = !videoTrack.enabled;
            isCamEnabled = videoTrack.enabled;
            document.getElementById('cam-icon-on').style.display = isCamEnabled ? '' : 'none';
            document.getElementById('cam-icon-off').style.display = isCamEnabled ? 'none' : '';
        }
    }
}

function showRatingModal() {
    document.getElementById('rating-modal').classList.add('active');
    const stars = document.querySelectorAll('#stars span');
    stars.forEach(star => {
        star.addEventListener('click', () => {
            selectedRating = parseInt(star.dataset.value);
            stars.forEach(s => s.classList.remove('active'));
            for (let i = 0; i < selectedRating; i++) stars[i].classList.add('active');
        });
    });
}

function submitRating() {
    if (selectedRating > 0) {
        fetch('/api/feedback', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ roomId: currentRoomId, rating: selectedRating, comment: '' })
        }).catch(e => console.error);
    }
    closeRating();
}

function closeRating() {
    document.getElementById('rating-modal').classList.remove('active');
    selectedRating = 0;
    const stars = document.querySelectorAll('#stars span');
    stars.forEach(s => s.classList.remove('active'));
}

function leaveCall() {
    for (let [id, pc] of peerConnections) pc.close();
    peerConnections.clear();
    remoteStreams.clear();
    pendingIce.clear();
    peerNames.clear();
    if (localStream) localStream.getTracks().forEach(t => t.stop());
    if (screenStream) screenStream.getTracks().forEach(t => t.stop());
    if (ws) ws.close();
    if (audioContext) audioContext.close();
    document.getElementById('call-screen').style.display = 'none';
    document.getElementById('main-screen').style.display = 'block';
    document.getElementById('remote-videos-grid').innerHTML = '';
    document.getElementById('security-bar').style.display = 'none';
    document.getElementById('local-camera-container').style.display = 'none';
    reconnectTimers.forEach(t => clearTimeout(t));
    reconnectTimers.clear();
    isScreenSharing = false;
    screenStream = null;
    originalVideoTrack = null;
    screenAudioTrackAdded = null;
    showRatingModal();
}
)js";

#endif // VIDMA_JS_H
