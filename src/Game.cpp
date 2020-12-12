#include "Game.hpp"

#include <time.h>

#include <cmath>
// #include <iostream>

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
      // std::cout << i << " " << j << "  " << k << '\n';

      // if (!contains(gameBoard, i, j) || currentPlayer != gameBoard.board[i][j]) {
      // }
      if (contains(gameBoard, i, j) && currentPlayer == gameBoard.board[i][j].type) {
        drawValidMove(gameBoard, i + 1, j - 1);
        drawValidMove(gameBoard, i + 1, j + 1);
        drawValidMove(gameBoard, i - 1, j - 1);
        drawValidMove(gameBoard, i - 1, j + 1);

        while (!ismouseclick(WM_LBUTTONDOWN)) {
          /* code */
        }
        getmouseclick(WM_LBUTTONDOWN, x, y);

        int newJ = floor((x - (gameBoard.x - gameBoard.width / 2.)) / k);
        int newI = floor((y - (gameBoard.y - gameBoard.width / 2.)) / k);

        if ((!contains(gameBoard, newI, newJ) || gameBoard.board[newI][newJ].type != 0) || !((i + 1 == newI && j - 1 == newJ) || (i + 1 == newI && j + 1 == newJ) || (i - 1 == newI && j - 1 == newJ) || (i - 1 == newI && j + 1 == newJ))) {
          remove(gameBoard, i + 1, j - 1);
          remove(gameBoard, i + 1, j + 1);
          remove(gameBoard, i - 1, j - 1);
          remove(gameBoard, i - 1, j + 1);
        } else {
          gameBoard.board[i][j].type = EMPTY;
          remove(gameBoard, i, j);
          remove(gameBoard, i + 1, j - 1);
          remove(gameBoard, i + 1, j + 1);
          remove(gameBoard, i - 1, j - 1);
          remove(gameBoard, i - 1, j + 1);

          move(gameBoard, newI, newJ, currentPlayer);

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
  int x1, x2, y1, y2;
  // Draw the cells
  for (int i = 0; i < gameBoard.size; i++)
    for (int j = 0; j < gameBoard.size; j++) {
      x1 = gameBoard.board[i][j].x1;
      y1 = gameBoard.board[i][j].y1;
      x2 = gameBoard.board[i][j].x2;
      y2 = gameBoard.board[i][j].y2;

      if ((i + j) % 2 == 0) {
        setcolor(COLOR(232, 235, 239));
        rectangle(x1, y1, x2 - 1, y2 - 1);
        setfillstyle(SOLID_FILL, COLOR(232, 235, 239));
        floodfill(x1 + 10, y1 + 10, COLOR(232, 235, 239));
      } else {
        setcolor(COLOR(125, 135, 150));
        rectangle(x1, y1, x2 - 1, y2 - 1);
        setfillstyle(SOLID_FILL, COLOR(125, 135, 150));
        floodfill(x1 + 10, y1 + 10, COLOR(125, 135, 150));
      }

      // Draw pieces
      if (gameBoard.board[i][j].type == PLAYER_1) {
        readimagefile("./assets/virus_jpg.jpg", x1 + 10, y1 + 10, x2 - 10, y2 - 10);
      } else if (gameBoard.board[i][j].type == PLAYER_2) {
        readimagefile("./assets/dokter.jpg", x1 + 10, y1 + 10, x2 - 10, y2 - 10);
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

  gameBoard.board = (Piece**)malloc(gameBoard.size * sizeof(Piece*));
  for (int i = 0; i < gameBoard.size; i++)
    gameBoard.board[i] = (Piece*)malloc(gameBoard.size * sizeof(Piece));

  for (int i = 0; i < gameBoard.size; i++)
    for (int j = 0; j < gameBoard.size; j++)
      gameBoard.board[i][j].type = EMPTY;

  for (int i = 0; i < gameBoard.size; i++) {
    if (i % 2 == 1) {
      gameBoard.board[0][i].type = PLAYER_1;
      gameBoard.board[gameBoard.size - 2][i].type = PLAYER_2;
    } else {
      gameBoard.board[1][i].type = PLAYER_1;
      gameBoard.board[gameBoard.size - 1][i].type = PLAYER_2;
    }
  }

  int k = gameBoard.width / gameBoard.size;
  for (int i = 0; i < gameBoard.size; i++) {
    for (int j = 0; j < gameBoard.size; j++) {
      gameBoard.board[i][j].x1 = gameBoard.x - (gameBoard.width / 2 - j * k);
      gameBoard.board[i][j].y1 = gameBoard.y - (gameBoard.width / 2 - i * k);
      gameBoard.board[i][j].x2 = gameBoard.x - (gameBoard.width / 2 - k - j * k);
      gameBoard.board[i][j].y2 = gameBoard.y - (gameBoard.width / 2 - k - i * k);
    }
  }

  return gameBoard;
}

void remove(GameBoard& gameBoard, int i, int j) {
  if (!contains(gameBoard, i, j) || gameBoard.board[i][j].type != EMPTY) {
    return;
  } else {
    int x1, y1, x2, y2;

    x1 = gameBoard.board[i][j].x1;
    y1 = gameBoard.board[i][j].y1;
    x2 = gameBoard.board[i][j].x2;
    y2 = gameBoard.board[i][j].y2;

    setcolor(COLOR(125, 135, 150));
    rectangle(x1, y1, x2 - 1, y2 - 1);
    setfillstyle(SOLID_FILL, COLOR(125, 135, 150));
    floodfill(x1 + 10, y1 + 10, COLOR(125, 135, 150));
  }
}

void move(GameBoard& gameBoard, int i, int j, int player) {
  int x1, y1, x2, y2;

  x1 = gameBoard.board[i][j].x1;
  y1 = gameBoard.board[i][j].y1;
  x2 = gameBoard.board[i][j].x2;
  y2 = gameBoard.board[i][j].y2;

  gameBoard.board[i][j].type = currentPlayer;

  if (player == PLAYER_1) {
    readimagefile("./assets/virus_jpg.jpg", x1 + 10, y1 + 10, x2 - 10, y2 - 10);
  } else if (player == PLAYER_2) {
    readimagefile("./assets/dokter.jpg", x1 + 10, y1 + 10, x2 - 10, y2 - 10);
  }
}

void drawValidMove(GameBoard& gameBoard, int i, int j) {
  if (!contains(gameBoard, i, j) || gameBoard.board[i][j].type != 0) {
    return;
  }
  int x1, y1, x2, y2;

  x1 = gameBoard.board[i][j].x1;
  y1 = gameBoard.board[i][j].y1;
  x2 = gameBoard.board[i][j].x2;
  y2 = gameBoard.board[i][j].y2;

  setcolor(COLOR(42, 219, 68));
  rectangle(x1, y1, x2 - 1, y2 - 1);
  setfillstyle(SOLID_FILL, COLOR(42, 219, 68));
  floodfill(x1 + 10, y1 + 10, COLOR(42, 219, 68));
}

bool contains(GameBoard& gameBoard, int i, int j) {
  return (i >= 0 && i < gameBoard.size && j >= 0 && j < gameBoard.size);
}

void checkNeighbours(GameBoard& gameBoard) {
  for (int i = 0; i < gameBoard.size; i++) {
    for (int j = 0; j < gameBoard.size; j++) {
      if (gameBoard.board[i][j].type != EMPTY) {
        int ok = true;
        if (contains(gameBoard, i + 1, j - 1) && (gameBoard.board[i][j].type == gameBoard.board[i + 1][j - 1].type || gameBoard.board[i + 1][j - 1].type == EMPTY)) {
          ok = false;
        }
        if (contains(gameBoard, i + 1, j + 1) && (gameBoard.board[i][j].type == gameBoard.board[i + 1][j + 1].type || gameBoard.board[i + 1][j + 1].type == EMPTY)) {
          ok = false;
        }
        if (contains(gameBoard, i - 1, j - 1) && (gameBoard.board[i][j].type == gameBoard.board[i - 1][j - 1].type || gameBoard.board[i - 1][j - 1].type == EMPTY)) {
          ok = false;
        }
        if (contains(gameBoard, i - 1, j + 1) && (gameBoard.board[i][j].type == gameBoard.board[i - 1][j + 1].type || gameBoard.board[i - 1][j + 1].type == EMPTY)) {
          ok = false;
        }

        if (ok) {
          gameBoard.board[i][j].type = EMPTY;
          remove(gameBoard, i, j);
        }
      }
    }
  }
}