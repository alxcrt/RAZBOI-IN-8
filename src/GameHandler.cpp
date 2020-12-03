
#include "GameHandler.hpp"

#include "Game.hpp"
#include "Utils.hpp"
#include "graphics.h"

void start() {
  initwindow(800, 800, "Razboi in 8", 0, 0);
  settextstyle(10, HORIZ_DIR, 5);
  settextjustify(CENTER_TEXT, CENTER_TEXT);
  playSound("assets/buttercup.wav");

  menu();
}

void menu() {
  cleardevice();
  readimagefile("./assets/bpatrut.jpg", 0, 0, getmaxx(), getmaxy());
  button startGameButton, exitGameButton;
  startGameButton = createButton(getmaxx() / 2, getmaxy() / 3, "Start Game");
  exitGameButton = createButton(getmaxx() / 2, getmaxy() / 2, "Exit");

  while (1) {
    drawButton(startGameButton);
    drawButton(exitGameButton);

    if (startGameButton.isPressed) {
      game();
    } else if (exitGameButton.isPressed) {
      exitGame();
    }

    delay(50);
  }
}
