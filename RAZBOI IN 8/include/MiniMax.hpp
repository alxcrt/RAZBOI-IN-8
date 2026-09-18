#pragma once

#include <utility>
#include <vector>

#include "Board.hpp"

std::vector<Move> getValidMoves(GameBoard& gameBoard, int i, int j);
// Every legal move of `player` as {from, to}
std::vector<std::pair<Move, Move>> getAllMoves(GameBoard& gameBoard, int player);

void simulateMove(GameBoard& gameBoard, int i, int j, int newI, int newJ, int player);

GameBoard copyGameBoard(GameBoard& gameBoard);