# Razboi in 8

### Prerequisites

- `Windows 10`
- `MinGW`
- `graphics.h`
- `GNU Make` Optional

# Instructions

1. Open a cmd inside `RAZBOI IN 8`
2. If you don't have have Make run :

   `g++ -o bin/release/main src/\*.cpp -std=c++17 -O3 -Wall -I include -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32 -lwinmm -lm && .\bin\release\main`

3. If you have have Make run :

   `make release`

# Play in the browser

The same C++ game compiled to WebAssembly with Emscripten. A small `graphics.h` shim (`RAZBOI IN 8/wasm/`) draws the original BGI calls on a canvas, so the menus, board and sounds are the originals.

The computer opponent is now **Jev** ([TypeSafe](https://typesafe.ai)) through Vercel AI Gateway instead of minimax, and the Easy mode is gone. `src/Jev.cpp` describes every legal Virus move and Jev picks one. The API key stays on the server (`web/api/jev.js`).

1. Build (Emscripten is pinned in `mise.toml`):

   `cd "RAZBOI IN 8" && mise exec -- make web`

2. Play locally:

   `AI_GATEWAY_API_KEY=... node web/dev.mjs` and open http://localhost:8765

3. Deploy with [Coolify](https://coolify.io) (or any Docker host): create a resource from this repo with the **Dockerfile** build pack, port **3000**, and set the `AI_GATEWAY_API_KEY` environment variable. The image serves the prebuilt `web/` folder, so no Emscripten is needed on the server. Test it locally with:

   `docker build -t razboi-in-8 . && docker run -p 3000:3000 -e AI_GATEWAY_API_KEY razboi-in-8`

   It also deploys on Vercel as is: `web` as the root directory, plus the same environment variable. Either way, set a spend limit on your AI Gateway key.

On a phone held upright, the game turns sideways to fill the screen. Turn the phone and play with taps.

On the Windows build, Player vs Jev plays random moves (no Jev there).

## How it works

```
RAZBOI IN 8/src/*.cpp      the game (same code as the Windows version)
RAZBOI IN 8/wasm/          a browser version of graphics.h + windows.h
        │  make web → em++ (Emscripten)
        ▼
web/index.wasm             the game compiled to WebAssembly instead of a Windows .exe
web/index.js               loader: fetches the .wasm, connects it to the canvas, mouse and audio
web/index.html             a black page with one <canvas> as the game window
web/api/jev.js             server function the game calls for Jev's moves
```

- **C++17 and the WinBGIm API**: the original game code. The only changes are the Jev opponent and two rule fixes: a draw when both sides reach 25 moves with equal pieces, and a player with no legal move passes.
- **Emscripten → WebAssembly**: `em++` compiles the C++ into `web/index.wasm` plus a small JS loader, `web/index.js`. The Emscripten version is pinned in `mise.toml`.
- **A `graphics.h` for the browser** (`RAZBOI IN 8/wasm/`): it implements the ~26 WinBGIm functions the game calls, on an HTML `<canvas>`:
  - rectangles and fills
  - text in bold Courier, at WinBGIm's own font sizes, on a solid background box like on Windows
  - `readimagefile` images
  - mouse clicks, with one pending click at a time like WinBGIm
  - WinBGIm's colour palette

  The `mciSendString` call from `windows.h` plays the sounds with HTML audio. `make web` converts the big `.wav` files to small `.m4a` ones.
- **Asyncify**: every screen of the original is an endless `while (1)` loop with `delay(50)`, which would freeze a browser tab. Emscripten's Asyncify pauses the C++ inside `delay()`, lets the browser draw and handle clicks, then resumes exactly where it stopped. That's why the original loops run unchanged.
- **`EM_JS` / `EM_ASYNC_JS`**: small pieces of JavaScript written inside the C++ files. The shim uses them to draw on the canvas. `Jev.cpp` uses one for the `fetch()` call, and Asyncify makes the C++ wait for the answer as if it were a normal function call.
- **In-memory filesystem**: `settings.dat` still works through `fopen`/`fwrite`. It resets when the page reloads.
- **Jev ([TypeSafe](https://docs.typesafe.ai) System One model) via [Vercel AI Gateway](https://vercel.com/ai-gateway)**: replaces minimax.
  - For every legal Virus move, `Jev.cpp` uses the original `simulateMove` to compute plain facts: how many Dokters it takes now, how many Virus pieces Dokter could take back, how many moves each side has left, and so on.
  - It sends those facts to Jev as one `Choice` question, and Jev answers with the move it picked.
  - The rules stay in C++; Jev only makes the judgement.
- **Responsive page** (`RAZBOI IN 8/wasm/shell.html`): the window is scaled to fit and centred. On a portrait screen, one CSS rule turns it 90°, and the shim maps taps back through the rotation.
- **Vercel Function** (`web/api/jev.js`): keeps the API key on the server and forwards only Jev requests. `web/dev.mjs` does the same locally.

## Overview

Razboi in 8 is a simple 2D game made in C++ using the graphics.h library.

Two people take part in the game, each of whom aimed to get the opposing armed fight out. The game can end with the victory of one of the players, or undecided - the draw.

This is the final project for the "Introduction to Programming" course (year I, semester I) from university.

## Authors

- Alexandru Cretu
- Razvan Iftimoaia

# Screenshots

<img src="https://raw.githubusercontent.com/Axellben/RAZBOI-IN-8/main/Screenshots/gameplay.png" width="98.5%">

<img src="https://raw.githubusercontent.com/Axellben/RAZBOI-IN-8/main/Screenshots/menu.png" width="49%"> <img src="https://raw.githubusercontent.com/Axellben/RAZBOI-IN-8/main/Screenshots/dokter_wins.png" width="49%">
