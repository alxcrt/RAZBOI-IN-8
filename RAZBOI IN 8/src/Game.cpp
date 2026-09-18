#include "Game.hpp"

#include <algorithm>
#include <cmath>
#include <cstring>

#include "Board.hpp"
#include "GameHandler.hpp"
#include "Jev.hpp"
#include "Utils.hpp"
#include "graphics.h"

extern _SETTINGS SETTINGS;

void game() {
  cleardevice();
  button pvpButton = createButton(getmaxx() / 2, getmaxy() / 2 - 100, dict["Player vs Player"][SETTINGS.LAN].c_str(), Pvp, BLACK, WHITE, CYAN);
  button pvcHardButton = createButton(getmaxx() / 2, getmaxy() / 2, dict["Player vs Jev"][SETTINGS.LAN].c_str(), PvcHard, BLACK, WHITE, CYAN);
  button menuButton = createButton(getmaxx() / 2, getmaxy() / 2 + 100, dict["Menu"][SETTINGS.LAN].c_str(), menu, BLACK, WHITE, CYAN);

  while (1) {
    drawButton(pvpButton);
    drawButton(pvcHardButton);
    drawButton(menuButton);

    wait(50);
  }
}

void Pvp() {
  cleardevice();
  int xSideBar = getmaxx() / 2 + (getmaxx() - getmaxx() / 2 + 150) / 2;
  button menuButton = createButton(xSideBar, getmaxy() - 100, dict["Menu"][SETTINGS.LAN].c_str(), menu, COLOR(232, 235, 239), BLACK, CYAN);
  readimagefile("./assets/blur-hospital.jpg", 0, 0, getmaxx(), getmaxy());

  GameBoard gameBoard = createBoard(getmaxx() / 2 - 200, getmaxy() / 2, 600, BOARD_SIZE);
  drawBoard(gameBoard);
  clearSideBar();

  bool b = false;

  while (1) {
    drawButton(menuButton);

    setcolor(BLACK);
    if (!winner(gameBoard)) {
      if (gameBoard.currentPlayer == PLAYER_1) {
        outtextxy(xSideBar, getmaxy() / 4 + 200, (char*)dict["Virus Moves"][SETTINGS.LAN].c_str());
      } else {
        outtextxy(xSideBar, getmaxy() / 4 + 200, (char*)dict["Dokter Moves"][SETTINGS.LAN].c_str());
      }

    } else if (winner(gameBoard) && !b) {
      stopSoundTrack();

      if (winner(gameBoard) == PLAYER_1) {
        outtextxy(xSideBar, getmaxy() / 4 + 200, (char*)dict["Virus Wins"][SETTINGS.LAN].c_str());
      } else if (winner(gameBoard) == PLAYER_2) {
        outtextxy(xSideBar, getmaxy() / 4 + 200, (char*)dict["Dokter Wins"][SETTINGS.LAN].c_str());
      } else {
        outtextxy(xSideBar, getmaxy() / 4 + 200, (char*)dict["Draw"][SETTINGS.LAN].c_str());
      }
      fillBoard(gameBoard, winner(gameBoard));
      b = true;
      playSound("assets/winning.wav");
    }

    std::string m = dict["Virus"][SETTINGS.LAN] + " " + std::to_string(gameBoard.p1Moves) + " " + dict["moves"][SETTINGS.LAN] + " " + std::to_string(gameBoard.p1Left) + " " + dict["pieces"][SETTINGS.LAN];
    settextstyle(10, HORIZ_DIR, 3);

    outtextxy(xSideBar, getmaxy() / 4 - 100, (char*)m.c_str());
    m = dict["Dokter"][SETTINGS.LAN] + " " + std::to_string(gameBoard.p2Moves) + " " + dict["moves"][SETTINGS.LAN] + " " + std::to_string(gameBoard.p2Left) + " " + dict["pieces"][SETTINGS.LAN];
    outtextxy(xSideBar, getmaxy() / 4 - 50, (char*)m.c_str());
    settextstyle(10, HORIZ_DIR, 4);

    if (!winner(gameBoard))
      movePlayer(gameBoard);

    wait(50);
  }
}

void PvcHard() {
  cleardevice();
  int xSideBar = getmaxx() / 2 + (getmaxx() - getmaxx() / 2 + 150) / 2;

  button menuButton = createButton(xSideBar, getmaxy() - 100, dict["Menu"][SETTINGS.LAN].c_str(), menu, COLOR(232, 235, 239), BLACK, CYAN);
  readimagefile("./assets/blur-hospital.jpg", 0, 0, getmaxx(), getmaxy());
  GameBoard gameBoard = createBoard(getmaxx() / 2 - 200, getmaxy() / 2, 600, BOARD_SIZE);
  drawBoard(gameBoard);
  clearSideBar();
  jevJournal = {-1};

  bool b = false;

  while (1) {
    drawButton(menuButton);

    setcolor(BLACK);
    if (!winner(gameBoard)) {
      if (gameBoard.currentPlayer == PLAYER_1) {
        outtextxy(xSideBar, getmaxy() / 4 + 200, (char*)dict["Virus Moves"][SETTINGS.LAN].c_str());
      } else {
        outtextxy(xSideBar, getmaxy() / 4 + 200, (char*)dict["Dokter Moves"][SETTINGS.LAN].c_str());
      }

    } else if (winner(gameBoard) && !b) {
      stopSoundTrack();

      if (winner(gameBoard) == PLAYER_1) {
        outtextxy(xSideBar, getmaxy() / 4 + 200, (char*)dict["Virus Wins"][SETTINGS.LAN].c_str());
        playSound("assets/losing.wav");

      } else if (winner(gameBoard) == PLAYER_2) {
        outtextxy(xSideBar, getmaxy() / 4 + 200, (char*)dict["Dokter Wins"][SETTINGS.LAN].c_str());
        playSound("assets/winning.wav");
      } else {
        outtextxy(xSideBar, getmaxy() / 4 + 200, (char*)dict["Draw"][SETTINGS.LAN].c_str());
        playSound("assets/winning.wav");
      }
      fillBoard(gameBoard, winner(gameBoard));
      b = true;
    }

    std::string m = dict["Virus"][SETTINGS.LAN] + " " + std::to_string(gameBoard.p1Moves) + " " + dict["moves"][SETTINGS.LAN] + " " + std::to_string(gameBoard.p1Left) + " " + dict["pieces"][SETTINGS.LAN];
    settextstyle(10, HORIZ_DIR, 3);

    outtextxy(xSideBar, getmaxy() / 4 - 100, (char*)m.c_str());
    m = dict["Dokter"][SETTINGS.LAN] + " " + std::to_string(gameBoard.p2Moves) + " " + dict["moves"][SETTINGS.LAN] + " " + std::to_string(gameBoard.p2Left) + " " + dict["pieces"][SETTINGS.LAN];
    outtextxy(xSideBar, getmaxy() / 4 - 50, (char*)m.c_str());

    // Jev's journal: the kind of move Jev just played, and how much it wanted each kind
    const char* headlines[4] = {"Jev took a Dokter!", "Jev set a trap", "Jev played safe", "Jev took a risk"};
    const char* kinds[4] = {"take", "trap", "safe", "risky"};
    int y = getmaxy() / 4;
    if (!winner(gameBoard) && gameBoard.currentPlayer == PLAYER_1) {
      outtextxy(xSideBar, y, (char*)dict["Jev is thinking..."][SETTINGS.LAN].c_str());
    } else if (jevJournal.offline) {
      outtextxy(xSideBar, y, (char*)dict["Jev is offline"][SETTINGS.LAN].c_str());
      settextstyle(10, HORIZ_DIR, 2);
      outtextxy(xSideBar, y + 30, (char*)dict["random move"][SETTINGS.LAN].c_str());
    } else if (jevJournal.kind >= 0) {
      outtextxy(xSideBar, y, (char*)dict[headlines[jevJournal.kind]][SETTINGS.LAN].c_str());
      settextstyle(10, HORIZ_DIR, 2);
      int t = (jevJournal.ms + 50) / 100;
      // ponytail: 0.5 is a display-only threshold
      m = dict[jevJournal.confidence >= 0.5 ? "Jev was sure" : "Jev hesitated"][SETTINGS.LAN] + " (" + std::to_string(t / 10) + "." + std::to_string(t % 10) + "s)";
      outtextxy(xSideBar, y + 30, (char*)m.c_str());

      // A row per kind of move Jev could play: label, bar, percentage
      int left = xSideBar - 150, right = xSideBar + 150, barLeft = left, barRight = right - textwidth((char*)"100%") - 8;
      for (int k = 0; k < 4; k++) {
        barLeft = std::max(barLeft, left + textwidth((char*)dict[kinds[k]][SETTINGS.LAN].c_str()) + 8);
      }
      settextjustify(LEFT_TEXT, CENTER_TEXT);
      y += 64;
      for (int k = 0; k < 4; k++) {
        if (jevJournal.want[k] < 0) {
          continue;
        }
        int percent = lround(jevJournal.want[k] * 100);
        outtextxy(left, y, (char*)dict[kinds[k]][SETTINGS.LAN].c_str());
        setfillstyle(SOLID_FILL, COLOR(200, 205, 212));
        bar(barLeft, y - 11, barRight, y);
        setfillstyle(SOLID_FILL, k == jevJournal.kind ? COLOR(42, 219, 68) : COLOR(125, 135, 150));
        if (percent > 0) {
          bar(barLeft, y - 11, barLeft + percent * (barRight - barLeft) / 100, y);
        }
        m = std::to_string(percent) + "%";
        outtextxy(right - textwidth((char*)m.c_str()), y, (char*)m.c_str());
        y += 26;
      }
      settextjustify(CENTER_TEXT, CENTER_TEXT);
    }
    settextstyle(10, HORIZ_DIR, 4);

    if (!winner(gameBoard)) {
      if (gameBoard.currentPlayer == PLAYER_2) {
        movePlayer(gameBoard);
      } else {
        moveAiHard(gameBoard);
      }
    }

    wait(50);
  }
}
