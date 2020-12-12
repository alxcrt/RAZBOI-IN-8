#include "Game.hpp"

#include <cmath>

#include "GameHandler.hpp"
#include "Utils.hpp"
#include "graphics.h"

#define PLAYER_1 1
#define PLAYER_2 2

int currentPlayer;

void game() {
  cleardevice();
  button menuButton = createButton(getmaxx() / 2 + 300, getmaxy() / 4, "Menu", menu, WHITE, BLACK, CYAN);
  readimagefile("./assets/blur-hospital.jpg", 0, 0, getmaxx(), getmaxy());
  GameBoard gameBoard = createBoard(getmaxx() / 2 - 200, getmaxy() / 2, 600, 8);
  drawBoard(gameBoard);
  drawPlayers(gameBoard);

  currentPlayer = PLAYER_1;

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

      int k = gameBoard.width / gameBoard.lines;

      // std::cout << floor((x - (gameBoard.x - gameBoard.width / 2.)) / k) << "  " << floor((y - (gameBoard.y - gameBoard.width / 2.)) / k) << '\n';
      int j = floor((x - (gameBoard.x - gameBoard.width / 2.)) / k);
      int i = floor((y - (gameBoard.y - gameBoard.width / 2.)) / k);
      // std::cout << i << " " << j << "  " << k << '\n';

      if (i < 0 || i > gameBoard.lines - 1 || j < 0 || j > gameBoard.lines - 1 || gameBoard.board[i][j] == 0 || currentPlayer != gameBoard.board[i][j]) {
      } else {
        isValidMove(gameBoard, i + 1, j - 1);
        isValidMove(gameBoard, i + 1, j + 1);
        isValidMove(gameBoard, i - 1, j - 1);
        isValidMove(gameBoard, i - 1, j + 1);

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

        if ((newI < 0 || newI > gameBoard.lines - 1 || newJ < 0 || newJ > gameBoard.lines - 1 || gameBoard.board[newI][newJ] != 0) || !((i + 1 == newI && j - 1 == newJ) || (i + 1 == newI && j + 1 == newJ) || (i - 1 == newI && j - 1 == newJ) || (i - 1 == newI && j + 1 == newJ))) {
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

          // checkNeighbours(gameBoard);

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
  k = gameBoard.width / gameBoard.lines;

  // Draw the cells
  for (i = 0; i < gameBoard.lines; i++)
    for (j = 0; j < gameBoard.lines; j++) {
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

GameBoard createBoard(int x, int y, int width, int lines) {
  GameBoard gameBoard;
  gameBoard.x = x;
  gameBoard.y = y;
  gameBoard.width = width;
  gameBoard.lines = lines;

  int i;
  gameBoard.board = (int**)malloc(gameBoard.lines * sizeof(int*));
  for (i = 0; i < gameBoard.lines; i++)
    gameBoard.board[i] = (int*)malloc(gameBoard.lines * sizeof(int));

  for (i = 0; i < gameBoard.lines; i++)
    for (int j = 0; j < gameBoard.lines; j++)
      gameBoard.board[i][j] = 0;

  for (i = 1; i < gameBoard.lines; i += 2) {
    gameBoard.board[0][i] = PLAYER_1;
    gameBoard.board[1][i - 1] = PLAYER_1;
  }

  for (i = 1; i < gameBoard.lines; i += 2) {
    gameBoard.board[gameBoard.lines - 2][i] = PLAYER_2;
    gameBoard.board[gameBoard.lines - 1][i - 1] = PLAYER_2;
  }

  return gameBoard;
}

void drawPlayers(GameBoard& gameBoard) {
  int i,
      j, k;
  int cellX1, cellY1, cellX2, cellY2;
  k = gameBoard.width / gameBoard.lines;

  for (i = 0; i < gameBoard.lines; i++)
    for (j = 0; j < gameBoard.lines; j++) {
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
  if (i < 0 || i > gameBoard.lines - 1 || j < 0 || j > gameBoard.lines - 1 || gameBoard.board[j][i] != 0) {
    return;
  } else {
    // std::cout << i << " " << j << '\n';

    int k;
    int cellX1, cellY1, cellX2, cellY2;
    k = gameBoard.width / gameBoard.lines;
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
  k = gameBoard.width / gameBoard.lines;

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
  k = gameBoard.width / gameBoard.lines;

  cellX1 = gameBoard.x - (gameBoard.width / 2 - i * k);
  cellY1 = gameBoard.y - (gameBoard.width / 2 - j * k);
  cellX2 = gameBoard.x - (gameBoard.width / 2 - k - i * k);
  cellY2 = gameBoard.y - (gameBoard.width / 2 - k - j * k);

  setcolor(COLOR(42, 219, 68));
  rectangle(cellX1, cellY1, cellX2 - 1, cellY2 - 1);
  setfillstyle(SOLID_FILL, COLOR(42, 219, 68));
  floodfill(cellX1 + 10, cellY1 + 10, COLOR(42, 219, 68));
}

bool isValidMove(GameBoard& gameBoard, int i, int j) {
  if (i < 0 || i > gameBoard.lines - 1 || j < 0 || j > gameBoard.lines - 1) {
    return false;
  }

  // if (gameBoard.board[i][j] == 1 && currentPlayer == 2) {
  //   markValidMove(gameBoard, j, i);
  //   drawPlayer(gameBoard, j, i, 1);
  // }

  // if (gameBoard.board[i][j] == 2 && currentPlayer == 1) {
  //   markValidMove(gameBoard, j, i);
  //   drawPlayer(gameBoard, j, i, 2);
  // }

  if (gameBoard.board[i][j] != 0) {
    return false;
  }

  markValidMove(gameBoard, j, i);
  return true;
}

bool contains(GameBoard& gameBoard, int i, int j) {
  return !(i < 0 || i > gameBoard.lines - 1 || j < 0 || j > gameBoard.lines - 1);
}

// void checkNeighbours(GameBoard& gameBoard) {
//   for (int i = 0; i < 8; i++) {
//     for (int j = 0; j < 8; j++) {
//       int ok = true;
//       if (contains(gameBoard, i + 1, j - 1) && gameBoard.board[i][j] == currentPlayer) {
//         if (gameBoard.board[i + 1][j - 1] == currentPlayer)
//           ok = false;
//       } else if (contains(gameBoard, i + 1, j + 1) && gameBoard.board[i][j] == currentPlayer) {
//         if (gameBoard.board[i + 1][j + 1] == currentPlayer)
//           ok = false;
//       } else if (contains(gameBoard, i - 1, j - 1) && gameBoard.board[i][j] == currentPlayer) {
//         if (gameBoard.board[i - 1][j - 1] == currentPlayer)
//           ok = false;
//       } else if (contains(gameBoard, i - 1, j + 1) && gameBoard.board[i][j] == currentPlayer) {
//         if (gameBoard.board[i - 1][j + 1] == currentPlayer)
//           ok = false;
//       }

//       if (ok) {
//         gameBoard.board[i][j] = 0;
//         delelePiece(gameBoard, j, i);
//         return;
//       }
//     }
//   }
// }