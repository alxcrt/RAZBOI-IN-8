#include "Game.hpp"

#include <iostream>

#include "GameHandler.hpp"
#include "Utils.hpp"
#include "graphics.h"

#define PLAYER_1 1
#define PLAYER_2 2
#define VALID_MOVE -1

void game() {
  cleardevice();
  button menuButton = createButton(getmaxx() / 2 + 400, getmaxy() / 4, "Menu", menu, WHITE, BLACK, CYAN);
  readimagefile("./assets/blur-hospital.jpg", 0, 0, getmaxx(), getmaxy());
  GameBoard gameBoard = createBoard(getmaxx() / 2 - 200, getmaxy() / 2, 600);
  drawBoard(gameBoard);

  while (1) {
    drawButton(menuButton);

    if (ismouseclick(WM_LBUTTONDOWN)) {
      clearmouseclick(WM_LBUTTONDOWN);
      gameBoard.board[4][4] = 2;
      gameBoard.board[0][1] = 0;
      gameBoard.board[5][5] = -1;
      drawBoard(gameBoard);
    }

    delay(50);
  }
}

void drawBoard(GameBoard& gameBoard) {
  int i,
      j, k;
  int cellX1, cellY1, cellX2, cellY2;
  k = gameBoard.width / 8;

  // Draw the cells
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++) {
      cellX1 = gameBoard.x - (gameBoard.width / 2 - i * k);
      cellY1 = gameBoard.y - (gameBoard.width / 2 - j * k);
      cellX2 = gameBoard.x - (gameBoard.width / 2 - k - i * k);
      cellY2 = gameBoard.y - (gameBoard.width / 2 - k - j * k);

      if ((i + j) % 2 == 0) {
        setcolor(COLOR(232, 235, 239));
        rectangle(cellX1, cellY1, cellX2 - 1, cellY2 - 1);
        setfillstyle(SOLID_FILL, COLOR(232, 235, 239));
        floodfill(cellX1 + 10, cellY1 + 10, COLOR(232, 235, 239));
      } else {
        setcolor(COLOR(125, 135, 150));
        rectangle(cellX1, cellY1, cellX2 - 1, cellY2 - 1);
        setfillstyle(SOLID_FILL, COLOR(125, 135, 150));
        floodfill(cellX1 + 10, cellY1 + 10, COLOR(125, 135, 150));
      }

      if (gameBoard.board[j][i] == -1) {
        setcolor(GREEN);
        rectangle(cellX1, cellY1, cellX2 - 1, cellY2 - 1);
        setfillstyle(SOLID_FILL, GREEN);
        floodfill(cellX1 + 10, cellY1 + 10, GREEN);
      }

      // Draw the players
      if (gameBoard.board[j][i] == 1) {
        readimagefile("./assets/virus_jpg.jpg", cellX1 + 10, cellY1 + 10, cellX2 - 10, cellY2 - 10);
      } else if (gameBoard.board[j][i] == 2) {
        readimagefile("./assets/dokter.jpg", cellX1 + 10, cellY1 + 10, cellX2 - 10, cellY2 - 10);
      }
    }

  // Black border around table
  setcolor(BLACK);
  setlinestyle(0, 0, 6);
  rectangle(gameBoard.x - gameBoard.width / 2 - 3, gameBoard.y - gameBoard.width / 2 - 3, gameBoard.x + gameBoard.width / 2 + 3, gameBoard.x + gameBoard.width / 2 + 3);
  setlinestyle(0, 0, 1);
}

GameBoard createBoard(int x, int y, int width) {
  GameBoard gameBoard;
  gameBoard.x = x;
  gameBoard.y = y;
  gameBoard.width = width;
  return gameBoard;
}