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
    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    rectangle(0, 0, 1200, 800);
    floodfill(100, 100, RED);
    drawTable(getmaxx() / 2, getmaxy() / 2, 600, 600);
    if (menuButton.isPressed) {
      menu();
    }

    delay(50);
  }
}

void drawTable(int x, int y, int width, int height) {
  int i, j, k;
  k = width / 8;
  setcolor(WHITE);
  setlinestyle(0,1,1);
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++) {
      //if (i % 2 == 0 && j % 2 == 0)
      //setcolor(WHITE);
      //else if (i % 2 == 1 && j % 2 == 1)
      //setcolor(WHITE);
      //else setcolor(BLACK);
      rectangle(x - (300 - i * k), y - (300 - j * k), x - (300 - k - i * k), y - (300 - k - j * k));
      if (i % 2 == 0 && j % 2 == 0) {
        setfillstyle(SOLID_FILL, WHITE);
        floodfill(x - (290 - i * k), y - (290 - j * k), WHITE);
      } else if (i % 2 == 1 && j % 2 == 1) {
        setfillstyle(SOLID_FILL, WHITE);
        floodfill(x - (290 - i * k), y - (290 - j * k), WHITE);
      } else {
        {
          setfillstyle(SOLID_FILL, BLACK);
          floodfill(x - (290 - i * k), y - (290 - j * k), WHITE);
        }
      }
    }
}

//culoare pt background
//tabla cu patratele ca la sah
//