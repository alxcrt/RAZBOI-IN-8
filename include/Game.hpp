#pragma once

#define PLAYER_1 1
#define PLAYER_2 2
#define EMPTY 0

struct Piece {
  int row, skin;
  float x1, y1, x2, y2;
  int type;
};

struct GameBoard {
  int x, y, width, size;
  Piece** board;
};

void game();
GameBoard createBoard(int x, int y, int width, int lines);
void drawBoard(GameBoard& gameBoard);
void remove(GameBoard& gameBoard, int x, int y);
void move(GameBoard& gameBoard, int i, int j, int player);
void drawValidMove(GameBoard& gameBoard, int i, int j);
bool contains(GameBoard& gameBoard, int i, int j);
void checkNeighbours(GameBoard& gameBoard);
