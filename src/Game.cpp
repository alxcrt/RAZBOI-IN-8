#include "Game.hpp"

#include <cmath>

#include "Board.hpp"
#include "GameHandler.hpp"
#include "Utils.hpp"
#include "graphics.h"

void game() {
  cleardevice();
  // readimagefile("./assets/startingimg.jpg", 0, 0, getmaxx(), getmaxy());
  button pvpButton = createButton(getmaxx() / 2, getmaxy() / 2 - 50, "Player vs Player", Pvp, BLACK, WHITE, CYAN);
  button pvcButton = createButton(getmaxx() / 2, getmaxy() / 2 + 50, "Player vs Computer Easy", PvcEasy, BLACK, WHITE, CYAN);
  button menuButton = createButton(getmaxx() / 2, getmaxy() / 2 + 200, "Menu", menu, BLACK, WHITE, CYAN);

  while (1) {
    drawButton(pvpButton);
    drawButton(pvcButton);
    drawButton(menuButton);

    delay(50);
  }
}

void Pvp() {
  cleardevice();
  button menuButton = createButton(getmaxx() / 2 + 300, getmaxy() / 4, "Menu", menu, WHITE, BLACK, CYAN);
  readimagefile("./assets/blur-hospital.jpg", 0, 0, getmaxx(), getmaxy());
  GameBoard gameBoard = createBoard(getmaxx() / 2 - 200, getmaxy() / 2, 600, BOARD_SIZE);
  drawBoard(gameBoard);

  while (1) {
    drawButton(menuButton);

    setcolor(BLACK);

    if (!winner(gameBoard)) {
      if (gameBoard.currentPlayer == PLAYER_1) {
        outtextxy(getmaxx() / 2 + 300, getmaxy() / 4 + 200, (char*)"P1 Turn");
      } else {
        outtextxy(getmaxx() / 2 + 300, getmaxy() / 4 + 200, (char*)"P2 Turn");
      }
    } else {
      if (winner(gameBoard) == PLAYER_1) {
        outtextxy(getmaxx() / 2 + 300, getmaxy() / 4 + 200, (char*)"P1 WINS");
      } else {
        outtextxy(getmaxx() / 2 + 300, getmaxy() / 4 + 200, (char*)"P2 WINS");
      }
      fillBoard(gameBoard, winner(gameBoard));
    }

    if (!winner(gameBoard))
      movePlayer(gameBoard);

    delay(50);
  }
}

void PvcEasy() {
  cleardevice();
  button menuButton = createButton(getmaxx() / 2 + 300, getmaxy() / 4, "Menu", menu, WHITE, BLACK, CYAN);
  readimagefile("./assets/blur-hospital.jpg", 0, 0, getmaxx(), getmaxy());
  GameBoard gameBoard = createBoard(getmaxx() / 2 - 200, getmaxy() / 2, 600, BOARD_SIZE);
  drawBoard(gameBoard);

  while (1) {
    drawButton(menuButton);

    setcolor(BLACK);

    if (!winner(gameBoard)) {
      if (gameBoard.currentPlayer == PLAYER_1) {
        outtextxy(getmaxx() / 2 + 300, getmaxy() / 4 + 200, (char*)"P1 Turn");
      } else {
        outtextxy(getmaxx() / 2 + 300, getmaxy() / 4 + 200, (char*)"P2 Turn");
      }
    } else {
      if (winner(gameBoard) == PLAYER_1) {
        outtextxy(getmaxx() / 2 + 300, getmaxy() / 4 + 200, (char*)"P1 WINS");
      } else {
        outtextxy(getmaxx() / 2 + 300, getmaxy() / 4 + 200, (char*)"P2 WINS");
      }
      fillBoard(gameBoard, winner(gameBoard));
    }

    if (!winner(gameBoard)) {
      if (gameBoard.currentPlayer == PLAYER_2) {
        movePlayer(gameBoard);
      } else {
        moveAiEasy(gameBoard);
      }
    }

    delay(50);
  }
}