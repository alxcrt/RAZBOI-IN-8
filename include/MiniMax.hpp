#pragma once

#include <vector>

#include "Board.hpp"

int minimax(GameBoard& gameBoard, int depth, bool maxPlayer);
int evaluateBoard(GameBoard& gameBoard);
std::vector<Move> getValidMoves(GameBoard& gameBoard, int i, int j);

void simulateMove(GameBoard& gameBoard, int i, int j, int newI, int newJ, int player);

GameBoard copyGameBoard(GameBoard& gameBoard);