// Local play: serves the game and /api/jev on http://localhost:8765 (needs AI_GATEWAY_API_KEY).
import { createServer } from 'node:http';
import { readFile } from 'node:fs/promises';
import { extname, join } from 'node:path';
import { fileURLToPath } from 'node:url';
import { POST } from './api/jev.js';

const root = fileURLToPath(new URL('.', import.meta.url));
const types = { '.html': 'text/html', '.js': 'text/javascript', '.wasm': 'application/wasm', '.jpg': 'image/jpeg', '.m4a': 'audio/mp4' };

createServer(async (req, res) => {
  const path = decodeURIComponent(new URL(req.url, 'http://localhost').pathname);
  if (path === '/api/jev' && req.method === 'POST') {
    const r = await POST(new Request('http://localhost/api/jev', { method: 'POST', body: req, duplex: 'half' })).catch((e) => new Response(`{"error":"${e.name}"}`, { status: 502 }));
    res.writeHead(r.status, { 'Content-Type': 'application/json' }).end(await r.text());
    return;
  }
  const file = join(root, path.endsWith('/') ? path + 'index.html' : path);
  try {
    if (!file.startsWith(root)) throw new Error('outside web/');
    res.writeHead(200, { 'Content-Type': types[extname(file)] ?? 'application/octet-stream' }).end(await readFile(file));
  } catch {
    res.writeHead(404).end();
  }
}).listen(process.env.PORT ?? 8765, process.env.HOST ?? '127.0.0.1', () => console.log(`http://localhost:${process.env.PORT ?? 8765}`));
