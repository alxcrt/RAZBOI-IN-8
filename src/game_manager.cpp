
#include "game_manager.hpp"

#include "graphics.h"
#include "helper.hpp"

bool IN_MENU = true, IN_GAME = false;

void start() {
  int gd = DETECT, gm;
  initgraph(&gd, &gm, (char*)"test");
  initwindow(800, 800, "Razboi in 8", 0, 0);
  // setmousequeuestatus(WM_LBUTTONDOWN, false);

  settextjustify(CENTER_TEXT, CENTER_TEXT);
  menu();
}

void menu() {
  cleardevice();
  playSound("assets/buttercup.wav");
  readimagefile("./assets/bpatrut.jpg", 0, 0, getmaxx(), getmaxy());
  button startGameButton, exitGameButton;
  startGameButton = createButton(getmaxx() / 2, getmaxy() / 3, "Start Game");
  exitGameButton = createButton(getmaxx() / 2, getmaxy() / 2, "Exit");
  while (1) {
    checkMousePressed(startGameButton);
    checkMousePressed(exitGameButton);

    if (startGameButton.isPressed) {
      game();
    } else if (exitGameButton.isPressed) {
      exitGame();
    }

    // delay(500);
  }
}

void game() {
  cleardevice();

  outtextxy(getmaxx() / 2, getmaxy() / 2 + 6, (char*)"Jocul este in constrctie");
  // button b = createButton(getmaxx() / 2, getmaxy() / 3, "Jocul este in constructie");

  //   // if (b.isPressed) {
  //   //   exitGame();
  //   // }
  getch();
}
