
#include "GameHandler.hpp"

#include "Game.hpp"
#include "Utils.hpp"
#include "graphics.h"

void start() {
  initwindow(1200, 800, "Razboi in 8", 0, 0);
  settextstyle(10, HORIZ_DIR, 5);
  settextjustify(CENTER_TEXT, CENTER_TEXT);
  //playSound("assets/buttercup.wav");

  menu();
}

void menu() {
  cleardevice();
  readimagefile("./assets/startingimg.jpg", 0, 0, getmaxx(), getmaxy());
  button startGameButton, exitGameButton, rulesGameButton, settingsGameButton;
  startGameButton = createButton(getmaxx() / 2, getmaxy() / 2 - 100, "Start Game", game , BLACK, WHITE, CYAN);
  rulesGameButton = createButton(getmaxx() / 2, getmaxy() / 2, "Rules", rules , BLACK, WHITE, CYAN);
  settingsGameButton = createButton(getmaxx() / 2, getmaxy() / 2 + 100, "Settings", settings , BLACK, WHITE, CYAN);
  exitGameButton = createButton(getmaxx() / 2, getmaxy() / 2 + 200, "Exit", exitGame,  BLACK, WHITE, CYAN);

  while (1) {
    drawButton(startGameButton);
    drawButton(exitGameButton);
    drawButton(rulesGameButton);
    drawButton(settingsGameButton);

    delay(50);
  }
}

void settings(){
  cleardevice();
  readimagefile("./assets/startingimg.jpg", 0, 0, getmaxx(), getmaxy());
  button languageGameButton, volumeGameButton, menuButton;
  languageGameButton = createButton(getmaxx() / 2, getmaxy() / 2 - 100, "Language", language , BLACK, WHITE, CYAN);
  volumeGameButton = createButton(getmaxx() / 2, getmaxy() / 2 , "Volume", volume , BLACK, WHITE, CYAN);
  menuButton = createButton(getmaxx() / 2, getmaxy() / 2 + 100, "Menu",menu, BLACK, WHITE, CYAN);
  while(1){
    drawButton(languageGameButton);
    drawButton(volumeGameButton);
    drawButton(menuButton);

    delay(50);
  }
}

void rules(){
  cleardevice();
  readimagefile("./assets/rules.jpg", 0, 0, getmaxx(), getmaxy());
  button menuButton;
  menuButton = createButton(getmaxx() -100, getmaxy() - 100, "Menu",menu, BLACK, WHITE, CYAN);
  setbkcolor(WHITE);
  setcolor(BLACK);
  settextstyle(10, HORIZ_DIR, 5);
  outtextxy(100,100,(char*)"hatz gion text semnificativ");
  while(1){
    drawButton(menuButton);

    delay(50);
  }

}
void language(){
  return;
}

void volume(){
  return;
}