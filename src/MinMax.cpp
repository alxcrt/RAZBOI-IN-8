#include "MinMax.hpp"

//TODO Find a better function
int evaluateBoard(GameBoard& gameBoard) {
  return gameBoard.p1Left - gameBoard.p2Left;
}

// vector