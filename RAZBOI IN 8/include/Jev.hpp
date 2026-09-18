#pragma once

#include "Board.hpp"

// Kinds of Virus move, for the sidebar journal
#define JEV_TAKE 0
#define JEV_TRAP 1
#define JEV_SAFE 2
#define JEV_RISKY 3

struct JevJournal {
  int kind;         // JEV_* of Jev's last move, -1 before Jev's first move
  bool offline;     // Jev didn't answer and the move was random
  float want[4];    // Jev's probability for its favourite move of each kind, -1 if no legal move is of that kind
  float confidence;
  int ms;           // Jev's answer time
};
extern JevJournal jevJournal;

bool jevMove(GameBoard& gameBoard, Move& from, Move& to);
