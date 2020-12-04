#include "Game.hpp"

#include "GameHandler.hpp"
#include "Utils.hpp"
#include "graphics.h"

void game() {
  cleardevice();
  button menuButton = createButton(getmaxx() / 2, getmaxy() / 4, "Menu");

  while (1) {
    //drawButton(menuButton);
    // outtextxy(getmaxx() / 2, getmaxy() / 2 + 6, (char*)"Jocul este in constructie");
    drawTable(getmaxx() / 2, getmaxy() / 2, 600, 600);
    if (menuButton.isPressed) {
      menu();
    }

    delay(100);
  }
}

void drawTable(int x, int y, int width, int height) {
  int i, j, k;
  setcolor(RED);
  setfillstyle(SOLID_FILL, RED);
  rectangle(0, 0, getmaxx(), getmaxy());
  floodfill(100, 100, RED);
  k = width / 8;
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++) {
      if ((i + j) % 2 == 0) {
        setcolor(WHITE);
        rectangle(x - (width / 2 - i * k), y - (width / 2 - j * k), x - (width / 2 - k - i * k) - 1, y - (width / 2 - k - j * k) - 1);
        setfillstyle(SOLID_FILL, WHITE);
        floodfill(x - ((width / 2 - 10) - i * k), y - ((width / 2 - 10) - j * k), WHITE);
      } else {
        setcolor(BLACK);
        rectangle(x - (width / 2 - i * k), y - (width / 2 - j * k), x - (width / 2 - k - i * k) - 1, y - (width / 2 - k - j * k) - 1);
        setfillstyle(SOLID_FILL, BLACK);
        floodfill(x - ((width / 2 - 10) - i * k), y - ((width / 2 - 10) - j * k), BLACK);
      }
    }
}