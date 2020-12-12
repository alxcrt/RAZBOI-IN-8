#include "Game.hpp"

#include <time.h>

#include <cmath>
#include <iostream>

#include "GameHandler.hpp"
#include "Utils.hpp"
#include "graphics.h"

int currentPlayer;

void game() {
  cleardevice();
  button menuButton = createButton(getmaxx() / 2 + 300, getmaxy() / 4, "Menu", menu, WHITE, BLACK, CYAN);
  readimagefile("./assets/blur-hospital.jpg", 0, 0, getmaxx(), getmaxy());
  GameBoard gameBoard = createBoard(getmaxx() / 2 - 200, getmaxy() / 2, 600, 8);
  drawBoard(gameBoard);
  drawPlayers(gameBoard);

  srand(time(NULL));
  currentPlayer = rand() % 2 + 1;

  while (1) {
    drawButton(menuButton);

    setcolor(BLACK);
    if (currentPlayer == PLAYER_1) {
      outtextxy(getmaxx() / 2 + 300, getmaxy() / 4 + 200, (char*)"P1's Turn");
    } else {
      outtextxy(getmaxx() / 2 + 300, getmaxy() / 4 + 200, (char*)"P2's Turn");
    }

    if (ismouseclick(WM_LBUTTONDOWN)) {
      // clearmouseclick(WM_LBUTTONDOWN);
      int x, y;
      getmouseclick(WM_LBUTTONDOWN, x, y);

      int k = gameBoard.width / gameBoard.size;

      // std::cout << floor((x - (gameBoard.x - gameBoard.width / 2.)) / k) << "  " << floor((y - (gameBoard.y - gameBoard.width / 2.)) / k) << '\n';
      int j = floor((x - (gameBoard.x - gameBoard.width / 2.)) / k);
      int i = floor((y - (gameBoard.y - gameBoard.width / 2.)) / k);
      std::cout << i << " " << j << "  " << k << '\n';

      // if (!contains(gameBoard, i, j) || currentPlayer != gameBoard.board[i][j]) {
      // }
      if (contains(gameBoard, i, j) && currentPlayer == gameBoard.board[i][j]) {
        markValidMove(gameBoard, i + 1, j - 1);
        markValidMove(gameBoard, i + 1, j + 1);
        markValidMove(gameBoard, i - 1, j - 1);
        markValidMove(gameBoard, i - 1, j + 1);

        while (!ismouseclick(WM_LBUTTONDOWN)) {
          /* code */
        }
        getmouseclick(WM_LBUTTONDOWN, x, y);

        int newJ = floor((x - (gameBoard.x - gameBoard.width / 2.)) / k);
        int newI = floor((y - (gameBoard.y - gameBoard.width / 2.)) / k);
        // std::cout << "second mouse click" << '\n';
        // std::cout << newI << " " << newJ << "  " << k << "\n\n";

        // std::cout << y / k - 6 << "  " << x / k - 3 << '\n';

        // if ((i + 1 == newI && j - 1 == newJ) || (i + 1 == newI && j + 1 == newJ) || (i - 1 == newI && j - 1 == newJ) || (i - 1 == newI && j + 1 == newJ))

        if ((!contains(gameBoard, newI, newJ) || gameBoard.board[newI][newJ] != 0) || !((i + 1 == newI && j - 1 == newJ) || (i + 1 == newI && j + 1 == newJ) || (i - 1 == newI && j - 1 == newJ) || (i - 1 == newI && j + 1 == newJ))) {
          delelePiece(gameBoard, j - 1, i + 1);
          delelePiece(gameBoard, j + 1, i + 1);
          delelePiece(gameBoard, j - 1, i - 1);
          delelePiece(gameBoard, j + 1, i - 1);
        } else {
          // gameBoard.board[5][5] = -1
          gameBoard.board[i][j] = 0;
          delelePiece(gameBoard, j, i);
          delelePiece(gameBoard, j - 1, i + 1);
          delelePiece(gameBoard, j + 1, i + 1);
          delelePiece(gameBoard, j - 1, i - 1);
          delelePiece(gameBoard, j + 1, i - 1);

          gameBoard.board[newI][newJ] = currentPlayer;
          drawPlayer(gameBoard, newJ, newI, currentPlayer);

          checkNeighbours(gameBoard);

          if (currentPlayer == PLAYER_1) {
            currentPlayer = PLAYER_2;
          } else {
            currentPlayer = PLAYER_1;
          }
        }
      }
    }

    delay(50);
  }
}

void drawBoard(GameBoard& gameBoard) {
  int i,
      j, k;
  int cellX1, cellY1, cellX2, cellY2;
  k = gameBoard.width / gameBoard.size;

  // Draw the cells
  for (i = 0; i < gameBoard.size; i++)
    for (j = 0; j < gameBoard.size; j++) {
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

GameBoard createBoard(int x, int y, int width, int size) {
  GameBoard gameBoard;
  gameBoard.x = x;
  gameBoard.y = y;
  gameBoard.width = width;
  gameBoard.size = size;

  int i;
  gameBoard.board = (int**)malloc(gameBoard.size * sizeof(int*));
  for (i = 0; i < gameBoard.size; i++)
    gameBoard.board[i] = (int*)malloc(gameBoard.size * sizeof(int));

  for (i = 0; i < gameBoard.size; i++)
    for (int j = 0; j < gameBoard.size; j++)
      gameBoard.board[i][j] = 0;

  for (i = 0; i < gameBoard.size; i++) {
    if (i % 2 == 1) {
      gameBoard.board[0][i] = PLAYER_1;
      gameBoard.board[gameBoard.size - 2][i] = PLAYER_2;
    } else {
      gameBoard.board[1][i] = PLAYER_1;
      gameBoard.board[gameBoard.size - 1][i] = PLAYER_2;
    }
  }

  for (i = 0; i < gameBoard.size; i++) {
    for (int j = 0; j < gameBoard.size; j++) {
      std::cout << gameBoard.board[i][j] << ' ';
    }
    std::cout << '\n';
  }

  return gameBoard;
}

void drawPlayers(GameBoard& gameBoard) {
  int i,
      j, k;
  int cellX1, cellY1, cellX2, cellY2;
  k = gameBoard.width / gameBoard.size;

  for (i = 0; i < gameBoard.size; i++)
    for (j = 0; j < gameBoard.size; j++) {
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
  if (!contains(gameBoard, i, j) || gameBoard.board[j][i] != 0) {
    return;
  } else {
    // std::cout << i << " " << j << '\n';
    int k;
    int cellX1, cellY1, cellX2, cellY2;
    k = gameBoard.width / gameBoard.size;
    cellX1 = gameBoard.x - (gameBoard.width / 2 - i * k);
    cellY1 = gameBoard.y - (gameBoard.width / 2 - j * k);
    cellX2 = gameBoard.x - (gameBoard.width / 2 - k - i * k);
    cellY2 = gameBoard.y - (gameBoard.width / 2 - k - j * k);
    setcolor(COLOR(125, 135, 150));
    rectangle(cellX1, cellY1, cellX2 - 1, cellY2 - 1);
    setfillstyle(SOLID_FILL, COLOR(125, 135, 150));
    floodfill(cellX1 + 10, cellY1 + 10, COLOR(125, 135, 150));
  }
}

void drawPlayer(GameBoard& gameBoard, int i, int j, int player) {
  int k;
  int cellX1, cellY1, cellX2, cellY2;
  k = gameBoard.width / gameBoard.size;

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

void markValidMove(GameBoard& gameBoard, int j, int i) {
  if (!contains(gameBoard, i, j) || gameBoard.board[j][i] != 0) {
    return;
  }

  int k;
  int cellX1, cellY1, cellX2, cellY2;
  k = gameBoard.width / gameBoard.size;

  cellX1 = gameBoard.x - (gameBoard.width / 2 - i * k);
  cellY1 = gameBoard.y - (gameBoard.width / 2 - j * k);
  cellX2 = gameBoard.x - (gameBoard.width / 2 - k - i * k);
  cellY2 = gameBoard.y - (gameBoard.width / 2 - k - j * k);

  setcolor(COLOR(42, 219, 68));
  rectangle(cellX1, cellY1, cellX2 - 1, cellY2 - 1);
  setfillstyle(SOLID_FILL, COLOR(42, 219, 68));
  floodfill(cellX1 + 10, cellY1 + 10, COLOR(42, 219, 68));
}

bool contains(GameBoard& gameBoard, int i, int j) {
  return (i >= 0 && i < gameBoard.size && j >= 0 && j < gameBoard.size);
}

void checkNeighbours(GameBoard& gameBoard) {
  for (int i = 0; i < gameBoard.size; i++) {
    for (int j = 0; j < gameBoard.size; j++) {
      if (gameBoard.board[i][j] != 0) {
        int ok = true;
        if (contains(gameBoard, i + 1, j - 1) && (gameBoard.board[i][j] == gameBoard.board[i + 1][j - 1] || gameBoard.board[i + 1][j - 1] == 0)) {
          ok = false;
        }
        if (contains(gameBoard, i + 1, j + 1) && (gameBoard.board[i][j] == gameBoard.board[i + 1][j + 1] || gameBoard.board[i + 1][j + 1] == 0)) {
          ok = false;
        }
        if (contains(gameBoard, i - 1, j - 1) && (gameBoard.board[i][j] == gameBoard.board[i - 1][j - 1] || gameBoard.board[i - 1][j - 1] == 0)) {
          ok = false;
        }
        if (contains(gameBoard, i - 1, j + 1) && (gameBoard.board[i][j] == gameBoard.board[i - 1][j + 1] || gameBoard.board[i - 1][j + 1] == 0)) {
          ok = false;
        }

        if (ok) {
          gameBoard.board[i][j] = 0;
          delelePiece(gameBoard, j, i);
        }
      }
    }
  }
}