debug:
	g++ -c src/*.cpp  -std=c++17 -g -Wall -I include && g++ *.o -o bin/debug/main -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32 && .\bin\debug\main
release:
	g++ -c src/*.cpp -std=c++17 -O3 -Wall -I include && g++ *.o -o bin/release/main -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32 -lwinmm && .\bin\release\main