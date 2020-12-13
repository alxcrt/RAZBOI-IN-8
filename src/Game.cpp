#include "Game.hpp"

#include <cmath>

#include "Board.hpp"
#include "GameHandler.hpp"
#include "Utils.hpp"
#include "graphics.h"

void game() {
  PvcEasy();
}

void Pvp() {
  cleardevice();
  button menuButton = createButton(getmaxx() / 2 + 300, getmaxy() / 4, "Menu", menu, WHITE, BLACK, CYAN);
  readimagefile("./assets/blur-hospital.jpg", 0, 0, getmaxx(), getmaxy());
  GameBoard gameBoard = createBoard(getmaxx() / 2 - 200, getmaxy() / 2, 600, 8);
  drawBoard(gameBoard);

  while (1) {
    drawButton(menuButton);

    setcolor(BLACK);
    if (gameBoard.currentPlayer == PLAYER_1) {
      outtextxy(getmaxx() / 2 + 300, getmaxy() / 4 + 200, (char*)"P1's Turn");
    } else {
      outtextxy(getmaxx() / 2 + 300, getmaxy() / 4 + 200, (char*)"P2's Turn");
    }

    movePlayer(gameBoard);

    delay(50);
  }
}

void PvcEasy() {
  cleardevice();
  button menuButton = createButton(getmaxx() / 2 + 300, getmaxy() / 4, "Menu", menu, WHITE, BLACK, CYAN);
  readimagefile("./assets/blur-hospital.jpg", 0, 0, getmaxx(), getmaxy());
  GameBoard gameBoard = createBoard(getmaxx() / 2 - 200, getmaxy() / 2, 600, 8);
  drawBoard(gameBoard);

  while (1) {
    drawButton(menuButton);

    setcolor(BLACK);
    if (gameBoard.currentPlayer == PLAYER_1) {
      outtextxy(getmaxx() / 2 + 300, getmaxy() / 4 + 200, (char*)"P1's Turn");
    } else {
      outtextxy(getmaxx() / 2 + 300, getmaxy() / 4 + 200, (char*)"P2's Turn");
    }

    if (gameBoard.currentPlayer == PLAYER_2) {
      movePlayer(gameBoard);
    } else {
      moveAiEasy(gameBoard);
    }

    delay(50);
  }
}