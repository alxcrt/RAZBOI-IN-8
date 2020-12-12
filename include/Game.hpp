#pragma once

#define PLAYER_1 1
#define PLAYER_2 2

struct GameBoard {
  int x, y, width, size;
  int** board;
};

void game();
GameBoard createBoard(int x, int y, int width, int lines);
void drawBoard(GameBoard& gameBoard);
void drawPlayers(GameBoard& gameBoard);
// void coordonatesToIndices();
void delelePiece(GameBoard& gameBoard, int x, int y);
void drawPlayer(GameBoard& gameBoard, int i, int j, int player);
void markValidMove(GameBoard& gameBoard, int i, int j);
// bool isValidMove(GameBoard& gameboard, int i, int j);
bool contains(GameBoard& gameBoard, int i, int j);
void checkNeighbours(GameBoard& gameBoard);
