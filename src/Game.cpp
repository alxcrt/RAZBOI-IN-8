#include "Game.hpp"

#include "GameHandler.hpp"
#include "Utils.hpp"
#include "graphics.h"

void game() {
  cleardevice();
  button menuButton = createButton(getmaxx() / 2, getmaxy() / 4, "Menu");

  while (1) {
    drawButton(menuButton);
    outtextxy(getmaxx() / 2, getmaxy() / 2 + 6, (char*)"Jocul este in constructie");

    if (menuButton.isPressed) {
      menu();
    }

    delay(50);
  }
}
