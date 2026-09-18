#include "MiniMax.hpp"

#include "graphics.h"

std::vector<Move> getValidMoves(GameBoard& gameBoard, int i, int j) {
  std::vector<Move> moves;

  if (contains(gameBoard, i + 1, j + 1) && gameBoard.board[i + 1][j + 1].type == EMPTY) {
    Move m = {i + 1, j + 1};
    moves.push_back(m);
  }
  if (contains(gameBoard, i + 1, j - 1) && gameBoard.board[i + 1][j - 1].type == EMPTY) {
    Move m = {i + 1, j - 1};
    moves.push_back(m);
  }
  if (contains(gameBoard, i - 1, j + 1) && gameBoard.board[i - 1][j + 1].type == EMPTY) {
    Move m = {i - 1, j + 1};
    moves.push_back(m);
  }
  if (contains(gameBoard, i - 1, j - 1) && gameBoard.board[i - 1][j - 1].type == EMPTY) {
    Move m = {i - 1, j - 1};
    moves.push_back(m);
  }

  return moves;
}

std::vector<std::pair<Move, Move>> getAllMoves(GameBoard& gameBoard, int player) {
  std::vector<std::pair<Move, Move>> moves;

  for (int i = 0; i < gameBoard.size; i++) {
    for (int j = 0; j < gameBoard.size; j++) {
      if (gameBoard.board[i][j].type == player) {
        for (Move& m : getValidMoves(gameBoard, i, j)) {
          moves.push_back({{i, j}, m});
        }
      }
    }
  }

  return moves;
}

void simulateMove(GameBoard& gameBoard, int _i, int _j, int _newI, int _newJ, int player) {
  gameBoard.board[_i][_j].type = EMPTY;
  gameBoard.board[_i][_j].moved = false;
  gameBoard.board[_newI][_newJ].type = player;
  gameBoard.board[_newI][_newJ].moved = true;

  if (player == PLAYER_1) {
    gameBoard.p1Moves++;
  } else if (player == PLAYER_2) {
    gameBoard.p2Moves++;
  }

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

  if (gameBoard.p2Moves >= MAX_MOVES) {
    for (int i = 0; i < gameBoard.size; i++) {
      for (int j = 0; j < gameBoard.size; j++) {
        if (gameBoard.board[i][j].type == EMPTY)
          gameBoard.board[i][j].moved = false;
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
          gameBoard.board[i][j].moved = false;
        }
      }
    }
  }
}

GameBoard copyGameBoard(GameBoard& gameBoard) {
  GameBoard newBoard = createBoard(getmaxx() / 2 - 200, getmaxy() / 2, 600, BOARD_SIZE);
  newBoard.p1Left = gameBoard.p1Left;
  newBoard.p2Left = gameBoard.p2Left;

  newBoard.p1Moves = gameBoard.p1Moves;
  newBoard.p2Moves = gameBoard.p2Moves;

  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      newBoard.board[i][j].type = gameBoard.board[i][j].type;
      newBoard.board[i][j].moved = gameBoard.board[i][j].moved;
    }
  }
  return newBoard;
}
