
#include "game_manager.hpp"

#include "graphics.h"
#include "helper.hpp"

bool IN_MENU = true, IN_GAME = false;

void start() {
  initwindow(800, 800, "Razboi in 8", 0, 0);

  settextjustify(CENTER_TEXT, CENTER_TEXT);
  playSound("assets/buttercup.wav");

  menu();
}

void menu() {
  cleardevice();
  readimagefile("./assets/bpatrut.jpg", 0, 0, getmaxx(), getmaxy());
  button startGameButton, exitGameButton;

  while (IN_MENU) {
    startGameButton = createButton(getmaxx() / 2, getmaxy() / 3, "Start Game");
    exitGameButton = createButton(getmaxx() / 2, getmaxy() / 2, "Exit");

    if (startGameButton.isPressed || exitGameButton.isPressed) {
      IN_MENU = !IN_MENU;
    }
    delay(50);
  }

  if (startGameButton.isPressed) {
    IN_GAME = !IN_GAME;
    game();
  } else if (exitGameButton.isPressed) {
    exitGame();
  }
}

void game() {
  cleardevice();
  button menuButton;

  while (IN_GAME) {
    menuButton = createButton(getmaxx() / 2, getmaxy() / 4, "Menu");
    outtextxy(getmaxx() / 2, getmaxy() / 2 + 6, (char*)"Jocul este in constructie");

    if (menuButton.isPressed) {
      IN_GAME = !IN_GAME;
    }

    delay(50);
  }

  if (menuButton.isPressed) {
    IN_MENU = !IN_MENU;
    menu();
  }
}
