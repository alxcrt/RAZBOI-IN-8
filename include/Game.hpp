#pragma once

struct GameBoard {
  int x, y, width;
  int board[8][8] = {{0, 1, 0, 1, 0, 1, 0, 1},
                     {1, 0, 1, 0, 1, 0, 1, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 2, 0, 0, 0, 0, 0},
                     {0, 2, 0, 2, 0, 2, 0, 2},
                     {2, 0, 2, 0, 2, 0, 2, 0}};
};

void game();
GameBoard createBoard(int x, int y, int width);
void drawBoard(GameBoard& gameBoard);