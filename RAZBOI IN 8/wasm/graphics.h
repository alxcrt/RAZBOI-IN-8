// WinBGIm graphics.h, just the part Razboi in 8 uses, drawn on a <canvas> (see bgi.cpp).
#pragma once

#include <limits.h>
#include <windows.h>

#include <sstream>  // WinBGIm's graphics.h has it too; the game gets std::string from here

enum colors { BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY, DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE };
#define COLOR(r, g, b) (0x03000000 | RGB(r, g, b))

#define SOLID_FILL 1
#define HORIZ_DIR 0
#define LEFT_TEXT 0
#define CENTER_TEXT 1
#define RIGHT_TEXT 2
#define BOTTOM_TEXT 0
#define TOP_TEXT 2
#define NO_CLICK -1

int initwindow(int width, int height, const char* title = "Windows BGI", int left = 0, int top = 0, bool dbflag = false, bool closeflag = true);
void closegraph(int wid = -1);
void cleardevice();
int getmaxx();
int getmaxy();
int getmaxwidth();
int getmaxheight();

void setcolor(int color);
void setbkcolor(int color);
void setfillstyle(int pattern, int color);
void setlinestyle(int linestyle, unsigned upattern, int thickness);
void rectangle(int left, int top, int right, int bottom);
void floodfill(int x, int y, int border);
void readimagefile(const char* filename = NULL, int left = 0, int top = 0, int right = INT_MAX, int bottom = INT_MAX);

void settextstyle(int font, int direction, int charsize);
void settextjustify(int horiz, int vert);
void outtextxy(int x, int y, const char* textstring);
int textwidth(const char* textstring);
int textheight(const char* textstring);

bool ismouseclick(int kind);
void getmouseclick(int kind, int& x, int& y);
void clearmouseclick(int kind);
int mousex();
int mousey();
void delay(int msec);
