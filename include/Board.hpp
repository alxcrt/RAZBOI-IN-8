#pragma once

#define PLAYER_1 1
#define PLAYER_2 2
#define EMPTY 0

#define BOARD_SIZE 8
#define MAX_MOVES BOARD_SIZE / 2
#define TOTAL_MOVES 25

struct Piece {
  float x1, y1, x2, y2;
  int type;
  bool moved;
};

struct GameBoard {
  int x, y, width, size;
  Piece** board;
  int currentPlayer;
  int p1Left, p2Left;
  int p1Moves, p2Moves;

  ~GameBoard() {
    for (int i = 0; i < size; ++i) {
      delete board[i];
    }

    delete[] board;
  }
};

struct Move {
  int i, j;
};

GameBoard createBoard(int x, int y, int width, int lines);
void drawBoard(GameBoard& gameBoard);
void drawValidMove(GameBoard& gameBoard, int i, int j);
void clearSideBar();

void remove(GameBoard& gameBoard, int x, int y);
void move(GameBoard& gameBoard, int i, int j, int player);
bool contains(GameBoard& gameBoard, int i, int j);
void checkNeighbours(GameBoard& gameBoard);
bool isValidMove(GameBoard& gameBoard, int i, int j, int newI, int newJ);
void changeTurn(GameBoard& gameBoard);
int winner(GameBoard& gameBoard);
void fillBoard(GameBoard& gameBoard, int player);

void movePlayer(GameBoard& gameBoard);
void moveAiEasy(GameBoard& gameBoard);
void moveAiHard(GameBoard& gameBoard);