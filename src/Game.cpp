#include "Game.hpp"

#include <cmath>
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
  GameBoard gameBoard = createBoard(getmaxx() / 2, getmaxy() / 2, 600);
  drawBoard(gameBoard);
  drawPlayers(gameBoard);

  while (1) {
    drawButton(menuButton);

    if (ismouseclick(WM_LBUTTONDOWN)) {
      // clearmouseclick(WM_LBUTTONDOWN);
      int x, y;
      getmouseclick(WM_LBUTTONDOWN, x, y);

      int k = gameBoard.width / 8;

      // std::cout << floor((x - (gameBoard.x - gameBoard.width / 2.)) / k) << "  " << floor((y - (gameBoard.y - gameBoard.width / 2.)) / k) << '\n';
      int j = floor((x - (gameBoard.x - gameBoard.width / 2.)) / k);
      int i = floor((y - (gameBoard.y - gameBoard.width / 2.)) / k);
      std::cout << i << " " << j << "  " << k << '\n';

      markValidMove(gameBoard, j - 1, i + 1);
      markValidMove(gameBoard, j + 1, i + 1);

      while (!ismouseclick(WM_LBUTTONDOWN)) {
        /* code */
      }
      getmouseclick(WM_LBUTTONDOWN, x, y);

      int newJ = floor((x - (gameBoard.x - gameBoard.width / 2.)) / k);
      int newI = floor((y - (gameBoard.y - gameBoard.width / 2.)) / k);
      // std::cout << "second mouse click" << '\n';
      std::cout << newI << " " << newJ << "  " << k << "\n\n";

      // std::cout << y / k - 6 << "  " << x / k - 3 << '\n';
      gameBoard.board[i][j] = 0;
      gameBoard.board[newI][newJ] = 1;
      // gameBoard.board[5][5] = -1;
      delelePiece(gameBoard, j, i);
      delelePiece(gameBoard, j - 1, i + 1);
      delelePiece(gameBoard, j + 1, i + 1);
      drawPlayer(gameBoard, newJ, newI, 1);
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
    }

  // Black border around table
  setcolor(BLACK);
  int borderWidth = gameBoard.width / 100;
  setlinestyle(0, 0, borderWidth);
  rectangle(gameBoard.x - gameBoard.width / 2 - borderWidth / 2, gameBoard.y - gameBoard.width / 2 - borderWidth / 2, gameBoard.x + gameBoard.width / 2 + borderWidth / 2, gameBoard.y + gameBoard.width / 2 + borderWidth / 2);
  setlinestyle(0, 0, 1);
}

GameBoard createBoard(int x, int y, int width) {
  GameBoard gameBoard;
  gameBoard.x = x;
  gameBoard.y = y;
  gameBoard.width = width;
  return gameBoard;
}

void drawPlayers(GameBoard& gameBoard) {
  int i,
      j, k;
  int cellX1, cellY1, cellX2, cellY2;
  k = gameBoard.width / 8;

  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++) {
      cellX1 = gameBoard.x - (gameBoard.width / 2 - i * k);
      cellY1 = gameBoard.y - (gameBoard.width / 2 - j * k);
      cellX2 = gameBoard.x - (gameBoard.width / 2 - k - i * k);
      cellY2 = gameBoard.y - (gameBoard.width / 2 - k - j * k);
      if (gameBoard.board[j][i] == 1) {
        readimagefile("./assets/virus_jpg.jpg", cellX1 + 10, cellY1 + 10, cellX2 - 10, cellY2 - 10);
      } else if (gameBoard.board[j][i] == 2) {
        readimagefile("./assets/dokter.jpg", cellX1 + 10, cellY1 + 10, cellX2 - 10, cellY2 - 10);
      }
    }
}

void delelePiece(GameBoard& gameBoard, int i, int j) {
  int k;
  int cellX1, cellY1, cellX2, cellY2;
  k = gameBoard.width / 8;
  cellX1 = gameBoard.x - (gameBoard.width / 2 - i * k);
  cellY1 = gameBoard.y - (gameBoard.width / 2 - j * k);
  cellX2 = gameBoard.x - (gameBoard.width / 2 - k - i * k);
  cellY2 = gameBoard.y - (gameBoard.width / 2 - k - j * k);
  setcolor(COLOR(125, 135, 150));
  rectangle(cellX1, cellY1, cellX2 - 1, cellY2 - 1);
  setfillstyle(SOLID_FILL, COLOR(125, 135, 150));
  floodfill(cellX1 + 10, cellY1 + 10, COLOR(125, 135, 150));
}

void drawPlayer(GameBoard& gameBoard, int i, int j, int player) {
  int k;
  int cellX1, cellY1, cellX2, cellY2;
  k = gameBoard.width / 8;

  cellX1 = gameBoard.x - (gameBoard.width / 2 - i * k);
  cellY1 = gameBoard.y - (gameBoard.width / 2 - j * k);
  cellX2 = gameBoard.x - (gameBoard.width / 2 - k - i * k);
  cellY2 = gameBoard.y - (gameBoard.width / 2 - k - j * k);
  if (player == 1) {
    readimagefile("./assets/virus_jpg.jpg", cellX1 + 10, cellY1 + 10, cellX2 - 10, cellY2 - 10);
  } else if (player == 2) {
    readimagefile("./assets/dokter.jpg", cellX1 + 10, cellY1 + 10, cellX2 - 10, cellY2 - 10);
  }
}

void markValidMove(GameBoard& gameBoard, int i, int j) {
  int k;
  int cellX1, cellY1, cellX2, cellY2;
  k = gameBoard.width / 8;

  cellX1 = gameBoard.x - (gameBoard.width / 2 - i * k);
  cellY1 = gameBoard.y - (gameBoard.width / 2 - j * k);
  cellX2 = gameBoard.x - (gameBoard.width / 2 - k - i * k);
  cellY2 = gameBoard.y - (gameBoard.width / 2 - k - j * k);

  setcolor(COLOR(42, 219, 68));
  rectangle(cellX1, cellY1, cellX2 - 1, cellY2 - 1);
  setfillstyle(SOLID_FILL, COLOR(42, 219, 68));
  floodfill(cellX1 + 10, cellY1 + 10, COLOR(42, 219, 68));
}

/*
doar daca cand apasa e ceva diferit de 0
*/
