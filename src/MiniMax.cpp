#include "MiniMax.hpp"

#include <climits>
#include <iostream>

#include "graphics.h"

int minimax(GameBoard& gameBoard, int depth, bool maxPlayer) {
  if (depth == 0 || winner(gameBoard)) {
    // std::cout << evaluateBoard(gameBoard) << '\n';
    return evaluateBoard(gameBoard);
  }

  if (maxPlayer) {
    int maxEval = INT_MIN;
    for (int i = 0; i < gameBoard.size; i++) {
      for (int j = 0; j < gameBoard.size; j++) {
        if (gameBoard.board[i][j].type == PLAYER_1) {
          std::vector<Move> validMoves = getValidMoves(gameBoard, i, j);

          if (!validMoves.empty()) {
            for (Move& m : validMoves) {
              // std::cout << m.i << ' ' << m.j << '\n';

              // gameBoard.board[i][j].type = EMPTY;
              // gameBoard.board[m.i][m.j].type = PLAYER_1;
              GameBoard tmpBoard = copyGameBoard(gameBoard);
              simulateMove(tmpBoard, i, j, m.i, m.j, PLAYER_1);
              int eval = minimax(tmpBoard, depth - 1, false);
              // gameBoard.board[m.i][m.j].type = EMPTY;
              // gameBoard.board[i][j].type = PLAYER_1;

              if (eval > maxEval) {
                maxEval = eval;
              }
            }
          }
        }
      }
    }
    return maxEval;
    /*
    best_move = None
    for move in getAllMoves(gameBoard,PLAYER_1):
      eval = minimax(gameBoard, depth -1,false)[0]
      maxEval = max(eval,maxEval)
      if maxEval == eval:
        best_move = move
    return maxEval, best_move
    */

  } else {
    int minEval = INT_MAX;
    for (int i = 0; i < gameBoard.size; i++) {
      for (int j = 0; j < gameBoard.size; j++) {
        if (gameBoard.board[i][j].type == PLAYER_2) {
          std::vector<Move> validMoves = getValidMoves(gameBoard, i, j);
          if (!validMoves.empty()) {
            for (Move& m : validMoves) {
              // std::cout << m.i << ' ' << m.j << '\n';
              GameBoard tmpBoard = copyGameBoard(gameBoard);
              simulateMove(tmpBoard, i, j, m.i, m.j, PLAYER_2);
              int eval = minimax(tmpBoard, depth - 1, true);
              // gameBoard.board[m.i][m.j].type = EMPTY;
              // gameBoard.board[i][j].type = PLAYER_2;

              if (eval < minEval) {
                minEval = eval;
              }
            }
          }
        }
      }
    }
    return minEval;
    /*
    best_move = None
    for move in getAllMoves(gameBoard,PLAYER_2):
      eval = minimax(gameBoard, depth -1,true)[0]
      minEval = min(eval,minEval)
      if minEval == eval:
        best_move = move
    return minEval, best_move
    */
  }
}

//TODO Find a better function
int evaluateBoard(GameBoard& gameBoard) {
  // Cate piese virus inconjura un doctor
  int c1 = 1;
  int c2 = 1;

  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (gameBoard.board[i][j].type == PLAYER_2) {
        if (contains(gameBoard, i + 1, j - 1) && gameBoard.board[i + 1][j - 1].type == PLAYER_1) {
          c1 *= 2;
        }
        if (contains(gameBoard, i + 1, j + 1) && gameBoard.board[i + 1][j + 1].type == PLAYER_1) {
          c1 *= 2;
        }
        if (contains(gameBoard, i - 1, j - 1) && gameBoard.board[i - 1][j - 1].type == PLAYER_1) {
          c1 *= 2;
        }
        if (contains(gameBoard, i - 1, j + 1) && gameBoard.board[i - 1][j + 1].type == PLAYER_1) {
          c1 *= 2;
        }
      } else if (gameBoard.board[i][j].type == PLAYER_1) {
        if (contains(gameBoard, i + 1, j - 1) && gameBoard.board[i + 1][j - 1].type == PLAYER_2) {
          c2 *= 2;
        }
        if (contains(gameBoard, i + 1, j + 1) && gameBoard.board[i + 1][j + 1].type == PLAYER_2) {
          c2 *= 2;
        }
        if (contains(gameBoard, i - 1, j - 1) && gameBoard.board[i - 1][j - 1].type == PLAYER_2) {
          c2 *= 2;
        }
        if (contains(gameBoard, i - 1, j + 1) && gameBoard.board[i - 1][j + 1].type == PLAYER_2) {
          c2 *= 2;
        }
      }
    }
  }
  // if (c1 != 0)
  //   std::cout << c1 << '\n';
  // return c1 - c2;

  return (gameBoard.p1Left - gameBoard.p2Left) * 10 + c1;
}

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

void simulateMove(GameBoard& gameBoard, int _i, int _j, int _newI, int _newJ, int player) {
  gameBoard.board[_i][_j].type = EMPTY;
  gameBoard.board[_newI][_newJ].type = player;
  gameBoard.board[_newI][_newJ].moved = true;

  for (int i = 0; i < gameBoard.size; i++) {
    for (int j = 0; j < gameBoard.size; j++) {
      // O piesa nemutata dar ea u m=ai are locuri de mutare
      if (gameBoard.board[i][j].type != EMPTY && gameBoard.board[i][j].moved == false) {
        int ok = true;
        if (contains(gameBoard, i + 1, j - 1) && (gameBoard.board[i][j].type == gameBoard.board[i + 1][j - 1].type || gameBoard.board[i + 1][j - 1].type == EMPTY)) {
          ok = false;
        }
        if (contains(gameBoard, i + 1, j + 1) && (gameBoard.board[i][j].type == gameBoard.board[i + 1][j + 1].type || gameBoard.board[i + 1][j + 1].type == EMPTY)) {
          ok = false;
        }
        if (contains(gameBoard, i - 1, j - 1) && (gameBoard.board[i][j].type == gameBoard.board[i - 1][j - 1].type || gameBoard.board[i - 1][j - 1].type == EMPTY)) {
          ok = false;
        }
        if (contains(gameBoard, i - 1, j + 1) && (gameBoard.board[i][j].type == gameBoard.board[i - 1][j + 1].type || gameBoard.board[i - 1][j + 1].type == EMPTY)) {
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
      } else if (gameBoard.board[i][j].type != EMPTY && gameBoard.board[i][j].moved == true) {
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

  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      newBoard.board[i][j].type = gameBoard.board[i][j].type;
    }
  }
  return newBoard;
}