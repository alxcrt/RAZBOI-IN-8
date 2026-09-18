release:
	g++ -o bin/release/main src/*.cpp -std=c++17 -O3 -Wall -I include -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32 -lwinmm -lm && .\bin\release\main

# Browser build (Emscripten): the same game on a <canvas> through the WinBGIm shim in wasm/.
web:
	mkdir -p ../web/assets
	cp assets/*.jpg ../web/assets/
	for f in theme_hospital2 moving_piece winning losing; do afconvert -f m4af -d aac@48000 -b 96000 assets/$$f.wav ../web/assets/$$f.m4a; done
	em++ src/*.cpp wasm/bgi.cpp -std=c++17 -O2 -I include -I wasm -sASYNCIFY -sSTACK_SIZE=8MB -sASYNCIFY_STACK_SIZE=1048576 -sALLOW_MEMORY_GROWTH --shell-file wasm/shell.html -o ../web/index.html
