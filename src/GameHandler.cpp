
#include "GameHandler.hpp"

#include "Game.hpp"
#include "Utils.hpp"
#include "graphics.h"

void start() {
  setResolution(1920, 1000);

  // playSound("assets/theme_hospital1.wav");

  menu();
}

void menu() {
  cleardevice();
  readimagefile("./assets/startingimg.jpg", 0, 0, getmaxx(), getmaxy());
  button startGameButton, exitGameButton, rulesGameButton, settingsGameButton;
  startGameButton = createButton(getmaxx() / 2, getmaxy() / 2 - 100, "Start Game", game, BLACK, WHITE, CYAN);
  rulesGameButton = createButton(getmaxx() / 2, getmaxy() / 2, "Rules", rules, BLACK, WHITE, CYAN);
  settingsGameButton = createButton(getmaxx() / 2, getmaxy() / 2 + 100, "Settings", settings, BLACK, WHITE, CYAN);
  exitGameButton = createButton(getmaxx() / 2, getmaxy() / 2 + 200, "Exit", exitGame, BLACK, WHITE, CYAN);

  while (1) {
    drawButton(startGameButton);
    drawButton(exitGameButton);
    drawButton(rulesGameButton);
    drawButton(settingsGameButton);

    delay(50);
  }
}

void settings() {
  cleardevice();
  // readimagefile("./assets/startingimg.jpg", 0, 0, getmaxx(), getmaxy());
  button languageGameButton, volumeGameButton, menuButton;
  languageGameButton = createButton(getmaxx() / 8, getmaxy() / 2 - 100, "Language", language, BLACK, WHITE, CYAN);
  volumeGameButton = createButton(getmaxx() - getmaxx() / 8, getmaxy() / 2, "Volume", volume, BLACK, WHITE, CYAN);
  menuButton = createButton(getmaxx() / 2, getmaxy() / 2 + 200, "Menu", menu, BLACK, WHITE, CYAN);

  outtextxy(getmaxx() / 8, getmaxy() / 2 - 200, (char*)"Resolution");
  button highResolutionButton = createButton(getmaxx() / 8 + 400, getmaxy() / 2 - 200, "1920x1000", NULL, BLACK, WHITE, CYAN);
  button mediumResolutionButton = createButton(getmaxx() / 8 + 800, getmaxy() / 2 - 200, "1366x768", NULL, BLACK, WHITE, CYAN);
  button lowResolutionButton = createButton(getmaxx() / 8 + 1200, getmaxy() / 2 - 200, "1024x640", NULL, BLACK, WHITE, CYAN);
  while (1) {
    drawButton(languageGameButton);
    drawButton(volumeGameButton);
    drawButton(menuButton);
    drawButton(highResolutionButton);
    drawButton(mediumResolutionButton);
    drawButton(lowResolutionButton);

    if (highResolutionButton.isPressed) {
      highResolutionButton.isPressed = false;
      setResolution(1920, 1000);
      settings();
    }
    if (mediumResolutionButton.isPressed) {
      mediumResolutionButton.isPressed = false;
      setResolution(1366, 768);
      settings();
    }
    if (lowResolutionButton.isPressed) {
      lowResolutionButton.isPressed = false;
      setResolution(1024, 640);
      settings();
    }

    delay(50);
  }
}

void rules() {
  cleardevice();
  readimagefile("./assets/rules.jpg", 0, 0, getmaxx(), getmaxy());
  button menuButton;
  menuButton = createButton(getmaxx() - 100, getmaxy() - 100, "Menu", menu, BLACK, WHITE, CYAN);
  setbkcolor(WHITE);
  setcolor(BLACK);
  settextstyle(10, HORIZ_DIR, 5);
  outtextxy(100, 100, (char*)"hatz gion text semnificativ");
  while (1) {
    drawButton(menuButton);

    delay(50);
  }
}
void language() {
  return;
}

void volume() {
  return;
}