// WinBGIm on a <canvas>: the graphics.h / mciSendStringA subset Razboi in 8 uses, with WinBGIm 6.0 semantics.
#include <emscripten.h>
#include <sys/stat.h>

#include "graphics.h"

// WinBGIm's palette (winbgi.cxx graphdefaults) and its BOLD_FONT metrics (text.cxx font_metrics: CreateFont(height, width) per charsize).
static const int palette[16] = {RGB(0, 0, 0), RGB(0, 0, 128), RGB(0, 128, 0), RGB(0, 128, 128), RGB(128, 0, 0), RGB(128, 0, 128), RGB(128, 128, 0), RGB(192, 192, 192),
                                RGB(128, 128, 128), RGB(128, 128, 255), RGB(128, 255, 128), RGB(128, 255, 255), RGB(255, 128, 128), RGB(255, 128, 255), RGB(255, 255, 0), RGB(255, 255, 255)};
static const int fontWidth[11] = {0, 11, 12, 14, 19, 25, 31, 38, 47, 57, 76};
static const int fontHeight[11] = {0, 19, 21, 24, 32, 42, 53, 64, 80, 96, 128};

static int width, height, color, bkcolor, fillcolor, thickness, charsize = 4, horiz, vert;
static int last[4];   // the last rectangle(), for floodfill()
static int mouse[5];  // pending left click, its x, y, then mousex, mousey; written by the canvas pointer handlers
static bool spun;     // ismouseclick came up empty since the last delay()

// saveSettings() exit(1)s when it can't open ./bin/release/settings.dat
static int dirs = mkdir("bin", 0777) + mkdir("bin/release", 0777);

static int rgb(int c) {
  return c >= 0 && c <= WHITE ? palette[c] : c & 0xFFFFFF;
}

EM_JS(void, bgi_open, (int w, int h, const char* title, int* mouse), {
  const cv = document.getElementById('canvas');
  cv.width = w * 2;
  cv.height = h * 2;
  cv.style.setProperty('--ar', w / h);
  cv.style.visibility = 'visible';
  document.title = UTF8ToString(title);
  Module.ctx = cv.getContext('2d');
  Module.ctx.setTransform(2, 0, 0, 2, 0, 0);
  Module.ctx.imageSmoothingEnabled = false;  // IPicture::Render's StretchBlt doesn't smooth either
  if (Module.bgi) return;

  const B = Module.bgi = {images: new Map(), sounds: new Map(), blocked: new Set()};
  B.css = (c) => 'rgb(' + (c & 255) + ',' + (c >> 8 & 255) + ',' + (c >> 16 & 255) + ')';
  const at = (e) => {
    // the window is always landscape, so a tall box means shell.html turned it 90deg for a phone held upright
    const r = cv.getBoundingClientRect(), m = mouse >> 2, up = r.height > r.width;
    HEAP32[m + 3] = Math.floor((up ? e.clientY - r.top : e.clientX - r.left) * cv.width / 2 / (up ? r.height : r.width));
    HEAP32[m + 4] = Math.floor((up ? r.right - e.clientX : e.clientY - r.top) * cv.height / 2 / (up ? r.width : r.height));
  };
  cv.addEventListener('pointermove', at);
  cv.addEventListener('pointerdown', (e) => {
    if (e.button) return;
    at(e);
    const m = mouse >> 2;
    HEAP32[m] = 1;
    HEAP32[m + 1] = HEAP32[m + 3];
    HEAP32[m + 2] = HEAP32[m + 4];
  });
  // browsers only start audio after a user gesture
  const unblock = () => {
    B.blocked.forEach((a) => a.play().catch(() => B.blocked.add(a)));
    B.blocked.clear();
  };
  addEventListener('pointerdown', unblock);
  addEventListener('keydown', unblock);
});

EM_JS(void, bgi_close, (), {
  const cv = document.getElementById('canvas');
  cv.style.visibility = 'hidden';
  // closing the .exe silenced it; setResolution() reopens the window straight away, exitGame() doesn't
  setTimeout(() => cv.style.visibility == 'hidden' && Module.bgi.sounds.forEach((a) => a.pause()));
});

EM_JS(void, bgi_fill, (int x, int y, int w, int h, int c), {
  Module.ctx.fillStyle = Module.bgi.css(c);
  Module.ctx.fillRect(x, y, w, h);
});

// TextOut on an OPAQUE DC: the w*n x h cell box in the bk colour, then the glyphs stretched to w px each like CreateFont(h, w) does.
EM_JS(void, bgi_text, (int x, int y, const char* s, int horiz, int vert, int w, int h, int fg, int bk), {
  const ctx = Module.ctx, t = UTF8ToString(s), tw = t.length * w, face = 'px "Courier New", Courier, monospace';
  ctx.font = 'bold 100' + face;
  const m = ctx.measureText('M'), px = 100 * h / (m.fontBoundingBoxAscent + m.fontBoundingBoxDescent), base = Math.round(m.fontBoundingBoxAscent * px / 100);
  x -= horiz == 1 ? tw >> 1 : horiz == 2 ? tw : 0;
  y -= vert == 0 ? h : vert == 1 ? base : 0;  // WinBGIm maps vertical CENTER_TEXT to TA_BASELINE
  ctx.fillStyle = Module.bgi.css(bk);
  ctx.fillRect(x, y, tw, h);
  ctx.save();
  ctx.translate(x, y + base);
  ctx.scale(w / (m.width * px / 100), 1);
  ctx.font = 'bold ' + px + face;
  ctx.fillStyle = Module.bgi.css(fg);
  ctx.fillText(t, 0, 0);
  ctx.restore();
});

EM_JS(int, bgi_image, (const char* path, int x, int y, int w, int h), {
  const img = Module.bgi.images.get(UTF8ToString(path));
  if (!img) return 0;
  if (img.naturalWidth) Module.ctx.drawImage(img, x, y, w, h);
  return 1;
});

EM_ASYNC_JS(void, bgi_load, (const char* path), {
  const p = UTF8ToString(path), img = new Image();
  img.src = p;
  await img.decode().catch(() => {});
  Module.bgi.images.set(p, img);
});

EM_JS(void, bgi_sound, (const char* command), {
  const [verb, ...file] = UTF8ToString(command).split(' '), B = Module.bgi, path = file.join(' ').replace('.wav', '.m4a');
  let a = B.sounds.get(path);
  if (!a) B.sounds.set(path, a = new Audio(path));
  if (verb == 'close') {
    a.pause();
    a.currentTime = 0;
    B.blocked.delete(a);
  } else if (verb == 'play' && a.paused) {  // like MCI, "play" on a playing file lets it play on
    a.play().catch(() => B.blocked.add(a));
  }
});

// landscape even on a phone held upright (shell.html turns the window sideways there)
// ponytail: scaled up to at least 1024x640 (the game's smallest layout) in the screen's shape, a phone has fewer CSS px than any 2021 screen
EM_JS(int, bgi_screen, (int h), {
  const s = Math.max(1, 640 / Math.min(innerWidth, innerHeight), 1024 / Math.max(innerWidth, innerHeight));
  return Math.round(s * (h ? Math.min(innerWidth, innerHeight) : Math.max(innerWidth, innerHeight)));
});

int initwindow(int w, int h, const char* title, int left, int top, bool dbflag, bool closeflag) {
  width = w;
  height = h;
  color = fillcolor = WHITE;
  bkcolor = BLACK;
  thickness = 1;
  for (int& m : mouse) m = 0;
  bgi_open(w, h, title, mouse);
  cleardevice();
  return 0;
}

void closegraph(int wid) {
  bgi_close();
}

void cleardevice() {
  bgi_fill(0, 0, width, height, rgb(bkcolor));
}

int getmaxx() {
  return width - 1;
}

int getmaxy() {
  return height - 1;
}

int getmaxwidth() {
  return bgi_screen(0);
}

int getmaxheight() {
  return bgi_screen(1);
}

void setcolor(int c) {
  color = c;
}

void setbkcolor(int c) {
  bkcolor = c;
}

void setfillstyle(int pattern, int c) {
  fillcolor = c;
}

void setlinestyle(int linestyle, unsigned upattern, int t) {
  thickness = t;
}

// Polyline with a t px pen, centred on the edges, as solid strips.
void rectangle(int left, int top, int right, int bottom) {
  int o = thickness / 2, c = rgb(color);
  bgi_fill(left - o, top - o, right - left + thickness, thickness, c);
  bgi_fill(left - o, bottom - o, right - left + thickness, thickness, c);
  bgi_fill(left - o, top - o, thickness, bottom - top + thickness, c);
  bgi_fill(right - o, top - o, thickness, bottom - top + thickness, c);
  last[0] = left, last[1] = top, last[2] = right, last[3] = bottom;
}

// ponytail: floodfill = fill the last rectangle's interior (all call sites follow rectangle()); real scanline fill if that changes
void floodfill(int x, int y, int border) {
  if (x > last[0] && x < last[2] && y > last[1] && y < last[3])
    bgi_fill(last[0] + 1, last[1] + 1, last[2] - last[0] - 1, last[3] - last[1] - 1, rgb(fillcolor));
}

void readimagefile(const char* filename, int left, int top, int right, int bottom) {
  if (!bgi_image(filename, left, top, right - left + 1, bottom - top + 1)) {
    bgi_load(filename);
    bgi_image(filename, left, top, right - left + 1, bottom - top + 1);
  }
}

// ponytail: every font is drawn as BOLD_FONT and HORIZ_DIR, the only ones the game uses
void settextstyle(int font, int direction, int size) {
  charsize = size < 1 ? 4 : size > 10 ? 10 : size;
}

void settextjustify(int h, int v) {
  horiz = h;
  vert = v;
}

void outtextxy(int x, int y, const char* s) {
  bgi_text(x, y, s, horiz, vert, fontWidth[charsize], fontHeight[charsize], rgb(color), rgb(bkcolor));
}

int textwidth(const char* s) {
  int n = 0;
  for (; *s; s++) n += (*s & 0xC0) != 0x80;
  return n * fontWidth[charsize];
}

int textheight(const char* s) {
  return fontHeight[charsize];
}

// The game busy-waits on this (Board.cpp movePlayer), so it has to let the browser run, but only from the
// second empty call: a tap during a yield inside a frame would move mousex/mousey after drawButton's hover test.
bool ismouseclick(int kind) {
  if (!mouse[0] && spun) emscripten_sleep(0);
  spun = !mouse[0];
  return kind == WM_LBUTTONDOWN && mouse[0];
}

void getmouseclick(int kind, int& x, int& y) {
  x = y = NO_CLICK;
  if (kind == WM_LBUTTONDOWN && mouse[0]) {
    x = mouse[1];
    y = mouse[2];
    mouse[0] = 0;
  }
}

void clearmouseclick(int kind) {
  if (kind == WM_LBUTTONDOWN) mouse[0] = 0;
}

int mousex() {
  return mouse[3];
}

int mousey() {
  return mouse[4];
}

void delay(int msec) {
  spun = false;
  emscripten_sleep(msec);
}

int mciSendStringA(const char* command, char* ret, int retLen, void* callback) {
  bgi_sound(command);
  return 0;
}
