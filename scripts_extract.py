#!/usr/bin/env python3
import sys
from pathlib import Path

ROOT = Path('/root/VideoCallServer')
SRC  = ROOT / 'Server.h'
OUT_HTML = ROOT / 'include' / 'vidma_html.h'
OUT_JS   = ROOT / 'include' / 'vidma_js.h'

def extract(src, tag):
    open_tag  = 'R"' + tag + '('
    close_tag = ')' + tag + '";'
    start = src.find(open_tag)
    if start < 0:
        print('ERROR: opening marker not found for tag ' + tag); sys.exit(1)
    start += len(open_tag)
    end = src.find(close_tag, start)
    if end < 0:
        print('ERROR: closing marker not found for tag ' + tag); sys.exit(1)
    return src[start:end]

def main():
    src = SRC.read_text(encoding='utf-8')

    html = extract(src, 'html')
    print('Extracted HTML: %d bytes' % len(html))

    js = extract(src, 'js')
    print('Extracted JS: %d bytes' % len(js))

    # --- HTML patches ---
    before = len(html)
    # Yandex.Metrika block
    a = html.find('<!-- Yandex.Metrika counter -->')
    b = html.find('<!-- /Yandex.Metrika counter -->')
    if a >= 0 and b > a:
        b += len('<!-- /Yandex.Metrika counter -->')
        html = html[:a] + html[b:]
        print('  removed Yandex.Metrika block: %d bytes' % (b - a))
    else:
        print('  WARN: Yandex.Metrika block not found')

    # Yandex Autoplacement + ads scripts
    ads_block = '''<!-- Yandex Autoplacement 20053801 -->
    <script src="https://yandex.ru/ads/system/context.js" async></script>
    <script data-page-id="20053801" src="https://yandex.ru/ads/system/ap-loader.js" async></script>'''
    if ads_block in html:
        html = html.replace(ads_block, '')
        print('  removed Yandex Ads block')
    else:
        # try tolerant removal line by line
        lines = html.split('\n')
        lines = [l for l in lines if 'yandex.ru/ads' not in l and 'Yandex Autoplacement' not in l]
        html = '\n'.join(lines)
        print('  removed Yandex Ads lines (tolerant)')

    print('  HTML size: %d -> %d' % (before, len(html)))

    # --- JS patches ---
    before = len(js)

    # 1. Replace iceServers block (drop hardcoded TURN creds, add loader)
    ice_start = js.find('const iceServers = {')
    if ice_start < 0:
        print('  ERROR: const iceServers not found'); sys.exit(1)
    ice_end = js.find('};', ice_start)
    if ice_end < 0:
        print('  ERROR: end of iceServers not found'); sys.exit(1)
    ice_end += 2
    new_ice = (
'const iceServers = {\n'
'    iceServers: [\n'
"        { urls: 'stun:stun.l.google.com:19302' },\n"
"        { urls: 'stun:stun1.l.google.com:19302' }\n"
'    ],\n'
"    iceTransportPolicy: 'all',\n"
'    iceCandidatePoolSize: 10\n'
'};\n'
'\n'
'async function loadTurnCredentials() {\n'
'    try {\n'
"        const res = await fetch('/api/turn-credentials', { cache: 'no-store' });\n"
'        if (!res.ok) return;\n'
'        const data = await res.json();\n'
'        if (data.urls && data.username && data.credential) {\n'
'            iceServers.iceServers.push({\n'
'                urls: data.urls,\n'
'                username: data.username,\n'
'                credential: data.credential\n'
'            });\n'
"            console.log('TURN credentials loaded');\n"
'        }\n'
'    } catch (e) {\n'
"        console.warn('TURN credentials fetch failed:', e);\n"
'    }\n'
'}'
    )
    js = js[:ice_start] + new_ice + js[ice_end:]
    print('  replaced iceServers block')

    # 2. Remove client-generated sessionId from join message
    old_join = "ws.send(JSON.stringify({ type: 'join', roomId: currentRoomId, sessionId: currentSessionId, name: currentName }));"
    new_join = "ws.send(JSON.stringify({ type: 'join', roomId: currentRoomId, name: currentName }));"
    if old_join in js:
        js = js.replace(old_join, new_join)
        print('  removed sessionId from join message')
    else:
        print('  WARN: join message pattern not found')

    # 3. Save server-issued sessionId on 'joined'
    old_joined = "if (msg.type === 'joined') return;"
    new_joined = "if (msg.type === 'joined') { if (msg.sessionId) currentSessionId = msg.sessionId; return; }"
    if old_joined in js:
        js = js.replace(old_joined, new_joined)
        print('  saving server-issued sessionId')
    else:
        print('  WARN: joined handler pattern not found')

    # 4. Load TURN credentials before connectWebSocket in joinRoomById
    anchor = "currentSessionId = generateSessionId();"
    inject = anchor + "\n    await loadTurnCredentials();"
    if anchor in js and "await loadTurnCredentials()" not in js:
        js = js.replace(anchor, inject, 1)
        print('  inserted loadTurnCredentials() call')
    else:
        print('  WARN: anchor for loadTurnCredentials not found')

    print('  JS size: %d -> %d' % (before, len(js)))

    # --- write outputs ---
    OUT_HTML.write_text(
        '// Auto-generated from Server.h by sprint1_extract.py\n'
        '// HTML template for the Vidma main page. Do not edit by hand.\n'
        '#ifndef VIDMA_HTML_H\n#define VIDMA_HTML_H\n\n'
        'constexpr const char* VIDMA_HTML = R"html(' + html + ')html";\n\n'
        '#endif // VIDMA_HTML_H\n',
        encoding='utf-8'
    )
    OUT_JS.write_text(
        '// Auto-generated from Server.h by sprint1_extract.py\n'
        '// Client-side JavaScript for the Vidma app. Do not edit by hand.\n'
        '#ifndef VIDMA_JS_H\n#define VIDMA_JS_H\n\n'
        'constexpr const char* VIDMA_JS = R"js(' + js + ')js";\n\n'
        '#endif // VIDMA_JS_H\n',
        encoding='utf-8'
    )
    print('Wrote: %s' % OUT_HTML)
    print('Wrote: %s' % OUT_JS)

if __name__ == '__main__':
    main()
