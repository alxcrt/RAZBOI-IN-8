
#include "Board.hpp"

#include <time.h>
#include <windows.h>

#include <cmath>

#include "MiniMax.hpp"
#include "Utils.hpp"
#include "graphics.h"

// * Draw
void drawBoard(GameBoard& gameBoard) {
  int x1, x2, y1, y2;
  // Draw the cells
  for (int j = 0; j < gameBoard.size; j++) {
    for (int i = 0; i < gameBoard.size; i++) {
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
  gameBoard.p1Left = gameBoard.p2Left = gameBoard.size;
  gameBoard.p1Moves = gameBoard.p2Moves = 0;

  srand(time(NULL));
  gameBoard.currentPlayer = rand() % 2 + 1;

  gameBoard.board = (Piece**)malloc(gameBoard.size * sizeof(Piece*));
  for (int i = 0; i < gameBoard.size; i++)
    gameBoard.board[i] = (Piece*)malloc(gameBoard.size * sizeof(Piece));

  for (int i = 0; i < gameBoard.size; i++)
    for (int j = 0; j < gameBoard.size; j++) {
      gameBoard.board[i][j].type = EMPTY;
      gameBoard.board[i][j].moved = false;
    }

  for (int i = 0; i < gameBoard.size; i++) {
    if (i % 2 == 1) {
      gameBoard.board[0][i].type = PLAYER_1;
      if (BOARD_SIZE % 2 == 1) {
        gameBoard.board[gameBoard.size - 1][i].type = PLAYER_2;
      } else {
        gameBoard.board[gameBoard.size - 2][i].type = PLAYER_2;
      }
    } else {
      gameBoard.board[1][i].type = PLAYER_1;
      if (BOARD_SIZE % 2 == 1) {
        gameBoard.board[gameBoard.size - 2][i].type = PLAYER_2;
      } else {
        gameBoard.board[gameBoard.size - 1][i].type = PLAYER_2;
      }
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

    gameBoard.board[i][j].moved = false;

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

  gameBoard.board[i][j].type = gameBoard.currentPlayer;
  gameBoard.board[i][j].moved = true;

  if (player == PLAYER_1) {
    gameBoard.p1Moves++;
  } else if (player == PLAYER_2) {
    gameBoard.p2Moves++;
  }

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
  return (i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE);
}

void checkNeighbours(GameBoard& gameBoard) {
  if (gameBoard.p1Moves >= MAX_MOVES) {
    for (int i = 0; i < gameBoard.size; i++) {
      for (int j = 0; j < gameBoard.size; j++) {
        if (gameBoard.board[i][j].type == PLAYER_1)
          gameBoard.board[i][j].moved = true;
      }
    }
  }

  if (gameBoard.p2Moves >= MAX_MOVES) {
    for (int i = 0; i < gameBoard.size; i++) {
      for (int j = 0; j < gameBoard.size; j++) {
        if (gameBoard.board[i][j].type == PLAYER_2)
          gameBoard.board[i][j].moved = true;
      }
    }
  }

  for (int i = 0; i < gameBoard.size; i++) {
    for (int j = 0; j < gameBoard.size; j++) {
      if (gameBoard.board[i][j].type != EMPTY && gameBoard.board[i][j].moved == true) {
        int ok = true;
        if (contains(gameBoard, i + 1, j - 1) && gameBoard.board[i + 1][j - 1].type == EMPTY) {
          ok = false;
        }
        if (contains(gameBoard, i + 1, j + 1) && gameBoard.board[i + 1][j + 1].type == EMPTY) {
          ok = false;
        }
        if (contains(gameBoard, i - 1, j - 1) && gameBoard.board[i - 1][j - 1].type == EMPTY) {
          ok = false;
        }
        if (contains(gameBoard, i - 1, j + 1) && gameBoard.board[i - 1][j + 1].type == EMPTY) {
          ok = false;
        }

        if (ok) {
          if (gameBoard.board[i][j].type == PLAYER_1) {
            gameBoard.p1Left--;
          } else if (gameBoard.board[i][j].type == PLAYER_2) {
            gameBoard.p2Left--;
          }
          gameBoard.board[i][j].type = EMPTY;
          remove(gameBoard, i, j);
        }
      }
    }
  }
}

bool isValidMove(GameBoard& gameBoard, int i, int j, int newI, int newJ) {
  return !((!contains(gameBoard, newI, newJ) || gameBoard.board[newI][newJ].type != 0) || !((i + 1 == newI && j - 1 == newJ) || (i + 1 == newI && j + 1 == newJ) || (i - 1 == newI && j - 1 == newJ) || (i - 1 == newI && j + 1 == newJ)));
}

void changeTurn(GameBoard& gameBoard) {
  if (gameBoard.currentPlayer == PLAYER_1) {
    gameBoard.currentPlayer = PLAYER_2;
  } else {
    gameBoard.currentPlayer = PLAYER_1;
  }
  clearSideBar();
}

int winner(GameBoard& gameBoard) {
  if (gameBoard.p1Moves >= TOTAL_MOVES && gameBoard.p2Moves >= TOTAL_MOVES) {
    if (gameBoard.p1Left < gameBoard.p2Left) {
      return PLAYER_2;
    } else if (gameBoard.p2Left < gameBoard.p1Left) {
      return PLAYER_1;
    }
  }

  if (gameBoard.p1Left <= 0) {
    return PLAYER_2;
  } else if (gameBoard.p2Left <= 0) {
    return PLAYER_1;
  }

  return 0;
}

void fillBoard(GameBoard& gameBoard, int player) {
  int x1, x2, y1, y2;
  // Draw the cells
  for (int j = 0; j < gameBoard.size; j++) {
    for (int i = 0; i < gameBoard.size; i++) {
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
      if (player == PLAYER_1) {
        readimagefile("./assets/virus_jpg.jpg", x1 + 10, y1 + 10, x2 - 10, y2 - 10);
      } else if (player == PLAYER_2) {
        readimagefile("./assets/dokter.jpg", x1 + 10, y1 + 10, x2 - 10, y2 - 10);
      }
    }
  }
}

void movePlayer(GameBoard& gameBoard) {
  if (ismouseclick(WM_LBUTTONDOWN) && !winner(gameBoard)) {
    int x, y;
    getmouseclick(WM_LBUTTONDOWN, x, y);

    int k = gameBoard.width / gameBoard.size;

    int j = floor((x - (gameBoard.x - gameBoard.width / 2.)) / k);
    int i = floor((y - (gameBoard.y - gameBoard.width / 2.)) / k);

    if (contains(gameBoard, i, j) && gameBoard.board[i][j].type == gameBoard.currentPlayer) {
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

      if (!isValidMove(gameBoard, i, j, newI, newJ)) {
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

        move(gameBoard, newI, newJ, gameBoard.currentPlayer);

        checkNeighbours(gameBoard);
        changeTurn(gameBoard);
        playSound("assets/moving_piece.wav");
      }
    }
  }
}

void moveAiEasy(GameBoard& gameBoard) {
  if (!winner(gameBoard)) {
    bool foundMove = false;
    int newI = 0, newJ = 0, i = 0, j = 0;

    while (!foundMove) {
      i = rand() % gameBoard.size;
      j = rand() % gameBoard.size;
      if (gameBoard.board[i][j].type == gameBoard.currentPlayer) {
        if (isValidMove(gameBoard, i, j, i + 1, j - 1)) {
          foundMove = true;
          newI = i + 1;
          newJ = j - 1;
          gameBoard.board[i][j].type = EMPTY;
          remove(gameBoard, i, j);
        } else if (isValidMove(gameBoard, i, j, i + 1, j + 1)) {
          foundMove = true;
          newI = i + 1;
          newJ = j + 1;
          gameBoard.board[i][j].type = EMPTY;
          remove(gameBoard, i, j);
        } else if (isValidMove(gameBoard, i, j, i - 1, j - 1)) {
          foundMove = true;
          newI = i - 1;
          newJ = j - 1;
          gameBoard.board[i][j].type = EMPTY;
          remove(gameBoard, i, j);
        } else if (isValidMove(gameBoard, i, j, i - 1, j + 1)) {
          foundMove = true;
          newI = i - 1;
          newJ = j + 1;
          gameBoard.board[i][j].type = EMPTY;
          remove(gameBoard, i, j);
        }
      }
    }

    move(gameBoard, newI, newJ, gameBoard.currentPlayer);

    checkNeighbours(gameBoard);
    changeTurn(gameBoard);
    playSound("assets/moving_piece.wav");
  }
}

void moveAiHard(GameBoard& gameBoard) {
  if (!winner(gameBoard)) {
    // Move bestMove = minimax(gameBoard, 3, false);
    Move initMove = {0, 0};
    Move nextMove = {0, 0};
    int bestScore = INT_MIN;

    int alpha = INT_MIN;
    int beta = INT_MAX;
    for (int i = 0; i < gameBoard.size; i++) {
      for (int j = 0; j < gameBoard.size; j++) {
        if (gameBoard.board[i][j].type == PLAYER_1) {
          std::vector<Move> validMoves = getValidMoves(gameBoard, i, j);
          if (!validMoves.empty()) {
            for (Move& m : validMoves) {
              GameBoard tmpBoard = copyGameBoard(gameBoard);
              simulateMove(tmpBoard, i, j, m.i, m.j, PLAYER_1);
              int score = minimax(tmpBoard, 4, alpha, beta, false);

              if (score > bestScore) {
                bestScore = score;
                initMove.i = i;
                initMove.j = j;
                nextMove.i = m.i;
                nextMove.j = m.j;
              }
            }
          }
        }
      }
    }
    gameBoard.board[initMove.i][initMove.j].type = EMPTY;
    remove(gameBoard, initMove.i, initMove.j);

    move(gameBoard, nextMove.i, nextMove.j, gameBoard.currentPlayer);
    checkNeighbours(gameBoard);
    changeTurn(gameBoard);
  }
  playSound("assets/moving_piece.wav");
}

void clearSideBar() {
  setcolor(COLOR(0, 0, 1));
  rectangle(getmaxx() / 2 + 150, 0, getmaxx() - 1, getmaxy() - 1);
  setfillstyle(SOLID_FILL, COLOR(232, 235, 239));
  floodfill(getmaxx() / 2 + 150 + 10, 10, COLOR(0, 0, 1));
}