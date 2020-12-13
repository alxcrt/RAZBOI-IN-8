#pragma once

#define PLAYER_1 1
#define PLAYER_2 2
#define EMPTY 0

#define BOARD_SIZE 8

struct Piece {
  float x1, y1, x2, y2;
  int type;
};

struct GameBoard {
  int x, y, width, size;
  Piece** board;
  int currentPlayer;
};

GameBoard createBoard(int x, int y, int width, int lines);
void drawBoard(GameBoard& gameBoard);
void drawValidMove(GameBoard& gameBoard, int i, int j);

void remove(GameBoard& gameBoard, int x, int y);
void move(GameBoard& gameBoard, int i, int j, int player);
bool contains(GameBoard& gameBoard, int i, int j);
void checkNeighbours(GameBoard& gameBoard);
bool isValidMove(GameBoard& gameBoard, int i, int j, int newI, int newJ);
void changeTurn(GameBoard& gameBoard);

void movePlayer(GameBoard& gameBoard);
void moveAiEasy(GameBoard& gameBoard);