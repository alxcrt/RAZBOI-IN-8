#include "Jev.hpp"

#include <algorithm>
#include <cstdlib>
#include <sstream>

#include "MiniMax.hpp"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

JevJournal jevJournal = {-1};

// "c7-d6": column letter + rank, row 0 is rank 8 (the Virus side)
static std::string moveName(std::pair<Move, Move>& m) {
  return std::string(1, 'a' + m.first.j) + std::to_string(BOARD_SIZE - m.first.i) + "-" + std::string(1, 'a' + m.second.j) + std::to_string(BOARD_SIZE - m.second.i);
}

static int piecesLeft(GameBoard& gameBoard, int player) {
  return player == PLAYER_1 ? gameBoard.p1Left : gameBoard.p2Left;
}

// Most `victim` pieces a single move of `player` removes from this position
static int mostRemoved(GameBoard& gameBoard, int player, int victim) {
  int most = 0;
  for (auto& m : getAllMoves(gameBoard, player)) {
    GameBoard tmpBoard = copyGameBoard(gameBoard);
    simulateMove(tmpBoard, m.first.i, m.first.j, m.second.i, m.second.j, player);
    most = std::max(most, piecesLeft(gameBoard, victim) - piecesLeft(tmpBoard, victim));
  }
  return most;
}

// The gateway request body. Every string in it is ours, so nothing needs escaping.
std::string jevRequest(GameBoard& gameBoard, std::vector<int>& kinds) {
  std::string board = "";
  for (int i = 0; i < BOARD_SIZE; i++) {
    board += "\"" + std::to_string(BOARD_SIZE - i) + " ";
    for (int j = 0; j < BOARD_SIZE; j++) {
      board += gameBoard.board[i][j].type == PLAYER_1 ? 'V' : gameBoard.board[i][j].type == PLAYER_2 ? 'D' : '.';
    }
    board += "\",";
  }
  board += "\"  abcdefgh\"";

  std::string criteria = "";
  for (auto& m : getAllMoves(gameBoard, PLAYER_1)) {
    GameBoard tmpBoard = copyGameBoard(gameBoard);
    simulateMove(tmpBoard, m.first.i, m.first.j, m.second.i, m.second.j, PLAYER_1);
    int removeNow = gameBoard.p2Left - tmpBoard.p2Left, lostNow = gameBoard.p1Left - tmpBoard.p1Left;
    int dokterNext = mostRemoved(tmpBoard, PLAYER_2, PLAYER_1), virusNext = mostRemoved(tmpBoard, PLAYER_1, PLAYER_2);
    kinds.push_back(removeNow ? JEV_TAKE : lostNow || dokterNext ? JEV_RISKY : virusNext ? JEV_TRAP : JEV_SAFE);
    if (criteria != "") {
      criteria += ",";
    }
    criteria += "\"" + moveName(m) + "\":{" +
                "\"enemy pieces you remove now\":" + std::to_string(removeNow) + "," +
                "\"your pieces removed now\":" + std::to_string(lostNow) + "," +
                "\"most of your pieces Dokter can remove next turn\":" + std::to_string(dokterNext) + "," +
                "\"most Dokter pieces you could remove with your next move\":" + std::to_string(virusNext) + "," +
                "\"your legal moves after\":" + std::to_string(getAllMoves(tmpBoard, PLAYER_1).size()) + "," +
                "\"Dokter legal moves after\":" + std::to_string(getAllMoves(tmpBoard, PLAYER_2).size()) + "}";
  }

  return "{\"state\":{\"game\":\"Razboi in 8\","
         "\"rules\":\"Two players on an 8x8 board. Each turn a player moves one of their pieces one square diagonally onto an empty square. "
         "A piece becomes vulnerable once it has moved, and all of a player's pieces become vulnerable after that player's 4th move. "
         "After every move, each vulnerable piece with no empty diagonal neighbour is removed (neighbours of either colour and the board edge block). "
         "You win by removing all enemy pieces, or by having more pieces when both sides have made 25 moves. Equal pieces then is a draw.\","
         "\"you\":\"Virus (V)\",\"opponent\":\"Dokter (D)\","
         "\"board\":[" + board + "],"
         "\"yourPieces\":" + std::to_string(gameBoard.p1Left) + ","
         "\"opponentPieces\":" + std::to_string(gameBoard.p2Left) + ","
         "\"yourMovesMade\":" + std::to_string(gameBoard.p1Moves) + ","
         "\"opponentMovesMade\":" + std::to_string(gameBoard.p2Moves) + ","
         "\"movesLeftUntilLimit\":" + std::to_string(std::max(0, TOTAL_MOVES - gameBoard.p1Moves)) + "},"
         "\"questions\":{\"move\":{\"type\":\"choice\","
         "\"instructions\":\"You are Virus and it is your turn. Which move gives Virus the best chance to win this game?\","
         "\"criteria\":{" + criteria + "}}},"
         "\"providerOptions\":{\"gateway\":{\"noTraining\":true}}}";
}

#ifdef __EMSCRIPTEN__
EM_JS_DEPS(jev, "$UTF8ToString,$stringToNewUTF8");

// POSTs the request to /api/jev (web/api/jev.js adds the key) and returns (malloc'd) "choice confidence ms"
// then a "move probability" line per option, or 0
EM_ASYNC_JS(char*, jevAsk, (const char* body), {
  try {
    var start = performance.now();
    var res = await fetch("api/jev", {
      method: "POST",
      headers: {"Content-Type": "application/json"},
      body: UTF8ToString(body),
      signal: AbortSignal.timeout(8000)
    });
    if (!res.ok) {
      throw new Error("HTTP " + res.status);
    }
    var json = await res.json(), move = json.answers.move;
    var text = move.choice + " " + json.providerMetadata.typesafe.confidence.move + " " + Math.round(performance.now() - start);
    for (var k in move.probabilities) {
      text += "\n" + k + " " + move.probabilities[k];
    }
    return stringToNewUTF8(text);
  } catch (e) {
    console.warn("Jev: " + e);
    return 0;
  }
});

bool jevMove(GameBoard& gameBoard, Move& from, Move& to) {
  jevJournal = {-1};
  std::vector<std::pair<Move, Move>> moves = getAllMoves(gameBoard, PLAYER_1);
  if (moves.empty()) {
    return false;
  }
  std::vector<int> kinds;
  std::string request = jevRequest(gameBoard, kinds);
  for (int k = 0; k < 4; k++) {
    jevJournal.want[k] = std::count(kinds.begin(), kinds.end(), k) ? 0 : -1;
  }

  // Nothing to judge: play the only move
  if (moves.size() == 1) {
    from = moves[0].first;
    to = moves[0].second;
    jevJournal.kind = kinds[0];
    jevJournal.want[kinds[0]] = jevJournal.confidence = 1;
    return true;
  }

  char* answer = jevAsk(request.c_str());
  if (answer == NULL) {
    return false;
  }
  std::istringstream in(answer);
  free(answer);
  std::string choice, key;
  float p;
  in >> choice >> jevJournal.confidence >> jevJournal.ms;
  while (in >> key >> p) {
    for (size_t k = 0; k < moves.size(); k++) {
      if (moveName(moves[k]) == key) {
        jevJournal.want[kinds[k]] += p;
      }
    }
  }

  for (size_t k = 0; k < moves.size(); k++) {
    if (moveName(moves[k]) == choice) {
      from = moves[k].first;
      to = moves[k].second;
      jevJournal.kind = kinds[k];
      return true;
    }
  }
  return false;
}
#else
// ponytail: no Jev on the desktop build, Virus falls back to random moves
bool jevMove(GameBoard&, Move&, Move&) {
  jevJournal = {-1};
  return false;
}
#endif
