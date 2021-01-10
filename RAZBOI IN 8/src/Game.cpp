#include "Game.hpp"

#include <cmath>
#include <cstring>

#include "Board.hpp"
#include "GameHandler.hpp"
#include "Utils.hpp"
#include "graphics.h"

extern _SETTINGS SETTINGS;

void game() {
  cleardevice();
  button pvpButton = createButton(getmaxx() / 2, getmaxy() / 2 - 100, dict["Player vs Player"][SETTINGS.LAN].c_str(), Pvp, BLACK, WHITE, CYAN);
  button pvcEasyButton = createButton(getmaxx() / 2, getmaxy() / 2, dict["Player vs Computer Easy"][SETTINGS.LAN].c_str(), PvcEasy, BLACK, WHITE, CYAN);
  button pvcHardButton = createButton(getmaxx() / 2, getmaxy() / 2 + 100, dict["Player vs Computer Hard"][SETTINGS.LAN].c_str(), PvcHard, BLACK, WHITE, CYAN);
  button menuButton = createButton(getmaxx() / 2, getmaxy() / 2 + 200, dict["Menu"][SETTINGS.LAN].c_str(), menu, BLACK, WHITE, CYAN);

  while (1) {
    drawButton(pvpButton);
    drawButton(pvcEasyButton);
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
      } else {
        outtextxy(xSideBar, getmaxy() / 4 + 200, (char*)dict["Dokter Wins"][SETTINGS.LAN].c_str());
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

void PvcEasy() {
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
        playSound("assets/losing.wav");

      } else {
        outtextxy(xSideBar, getmaxy() / 4 + 200, (char*)dict["Dokter Wins"][SETTINGS.LAN].c_str());
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
    settextstyle(10, HORIZ_DIR, 4);

    if (!winner(gameBoard)) {
      if (gameBoard.currentPlayer == PLAYER_2) {
        movePlayer(gameBoard);
      } else {
        moveAiEasy(gameBoard);
      }
    }

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

      } else {
        outtextxy(xSideBar, getmaxy() / 4 + 200, (char*)dict["Dokter Wins"][SETTINGS.LAN].c_str());
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
