
#include "GameHandler.hpp"

#include <windows.h>

#include "Game.hpp"
#include "Utils.hpp"
#include "graphics.h"

extern _SETTINGS SETTINGS;

void start() {
  loadSettings();
  setResolution(SETTINGS.WIDTH, SETTINGS.HEIGHT);
  playSound("assets/theme_hospital2.wav");

  menu();
}

void menu() {
  cleardevice();
  int kk = getmaxx() / 400;
  settextstyle(10, HORIZ_DIR, kk + 2);

  readimagefile("./assets/backgroundGame.jpg", 0, 0, getmaxx(), getmaxy());
  button startGameButton, exitGameButton, rulesGameButton, settingsGameButton;
  startGameButton = createButton(getmaxx() / 2, getmaxy() / 2 - 100, dict["Start Game"][SETTINGS.LAN].c_str(), game, BLACK, WHITE, CYAN);
  rulesGameButton = createButton(getmaxx() / 2, getmaxy() / 2, dict["Rules"][SETTINGS.LAN].c_str(), rules, BLACK, WHITE, CYAN);
  settingsGameButton = createButton(getmaxx() / 2, getmaxy() / 2 + 100, dict["Settings"][SETTINGS.LAN].c_str(), settings, BLACK, WHITE, CYAN);
  exitGameButton = createButton(getmaxx() / 2, getmaxy() / 2 + 200, dict["Exit"][SETTINGS.LAN].c_str(), exitGame, BLACK, WHITE, CYAN);

  while (1) {
    drawButton(startGameButton);
    drawButton(exitGameButton);
    drawButton(rulesGameButton);
    drawButton(settingsGameButton);

    wait(50);
  }
}

void settings() {
  cleardevice();
  int kk = getmaxx() / 400;
  settextstyle(10, HORIZ_DIR, kk + 2);
  readimagefile("./assets/backgroundGame.jpg", 0, 0, getmaxx(), getmaxy());
  setbkcolor(BLACK);
  setcolor(WHITE);
  outtextxy(getmaxx() / 100 * 46, getmaxy() / 2 + 5, (char*)dict["Music"][SETTINGS.LAN].c_str());
  button languageGameButton, menuButton, volumeOnGameButton, volumeOffGameButton, resolutionButton;
  languageGameButton = createButton(getmaxx() / 2, getmaxy() / 2 - 100, dict["Language"][SETTINGS.LAN].c_str(), language, BLACK, WHITE, CYAN);
  volumeOnGameButton = createButton(getmaxx() / 100 * 59, getmaxy() * 47 / 100, dict["On"][SETTINGS.LAN].c_str(), playSoundTrack, BLACK, WHITE, CYAN);
  volumeOffGameButton = createButton(getmaxx() / 100 * 59, getmaxy() * 53 / 100, dict["Off"][SETTINGS.LAN].c_str(), stopSoundTrack, BLACK, WHITE, CYAN);
  menuButton = createButton(getmaxx() / 2, getmaxy() / 2 + 200, dict["Menu"][SETTINGS.LAN].c_str(), menu, BLACK, WHITE, CYAN);
  resolutionButton = createButton(getmaxx() / 2, getmaxy() / 2 + 100, dict["Resolution"][SETTINGS.LAN].c_str(), gameResolution, BLACK, WHITE, CYAN);
  while (1) {
    drawButton(languageGameButton);
    drawButton(volumeOnGameButton);
    drawButton(volumeOffGameButton);
    drawButton(resolutionButton);
    drawButton(menuButton);

    wait(50);
  }
}

void rules() {
  int kk = 0;
  cleardevice();
  kk = getmaxx() / 400;
  settextstyle(10, HORIZ_DIR, kk);
  readimagefile("./assets/rules.jpg", 0, 0, getmaxx(), getmaxy());
  button menuButton, rules2Button;
  menuButton = createButton(getmaxx() - 100, getmaxy() - 60, dict["Menu"][SETTINGS.LAN].c_str(), menu, BLACK, WHITE, CYAN);
  rules2Button = createButton((getmaxx() / 100) * 75, (getmaxy() / 100) * 90, dict["Next page ->"][SETTINGS.LAN].c_str(), rules2, WHITE, BLACK, CYAN);
  setbkcolor(WHITE);
  setcolor(BLACK);
  settextjustify(LEFT_TEXT, CENTER_TEXT);
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 20, (char*)dict["The game <War in 8> (with its version <War in 4>) is a rational game"][SETTINGS.LAN].c_str());
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 24, (char*)dict["for all ages. It demands attention and the spirit of observation,"][SETTINGS.LAN].c_str());
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 28, (char*)dict["favors the combinatorial analysis of the variants and develops the"][SETTINGS.LAN].c_str());
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 32, (char*)dict["habit of carrying things to the end. A similar game - but simpler -"][SETTINGS.LAN].c_str());
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 36, (char*)dict["that facilitates learning and practicing the game <War in 8> is"][SETTINGS.LAN].c_str());
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 40, (char*)dict["<Dogs and fox>. The game offers amateurs a wide field of study and"][SETTINGS.LAN].c_str());
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 44, (char*)dict["analysis - not too simple - being perfectly adapted for composing and"][SETTINGS.LAN].c_str());
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 48, (char*)dict["solving problems, as well as for correspondence."][SETTINGS.LAN].c_str());
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 52, (char*)dict["Jocul <Razboi in 8> (cu varianta sa <Razboi in 4>) este un joc"][SETTINGS.LAN].c_str());
  settextjustify(CENTER_TEXT, CENTER_TEXT);
  while (1) {
    drawButton(menuButton);
    drawButton(rules2Button);

    wait(50);
  }
}

void rules2() {
  int kk = 0;
  cleardevice();
  kk = getmaxx() / 400;
  settextstyle(10, HORIZ_DIR, kk);
  readimagefile("./assets/rules.jpg", 0, 0, getmaxx(), getmaxy());
  readimagefile("./assets/board2.jpg", getmaxx() / 2 - 370, getmaxy() / 2 - 40, getmaxx() / 2 - 100, getmaxy() / 2 + 200);
  button menuButton, rulesButton, rules3Button;
  menuButton = createButton(getmaxx() - 100, getmaxy() - 60, "Menu", menu, BLACK, WHITE, CYAN);
  rulesButton = createButton((getmaxx() / 100) * 25, (getmaxy() / 100) * 90, dict["<- Previous page"][SETTINGS.LAN].c_str(), rules, WHITE, BLACK, CYAN);
  rules3Button = createButton((getmaxx() / 100) * 75, (getmaxy() / 100) * 90, dict["Next page ->"][SETTINGS.LAN].c_str(), rules3, WHITE, BLACK, CYAN);
  setbkcolor(WHITE);
  setcolor(BLACK);
  settextjustify(LEFT_TEXT, CENTER_TEXT);
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 18, (char*)dict["Two people take part in the game, each of whom aimed to get the"][SETTINGS.LAN].c_str());
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 22, (char*)dict["opposing <armed> fight out. The game can end with the victory of one"][SETTINGS.LAN].c_str());
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 26, (char*)dict["of the players, or undecided - the draw. Practicing the game requires"][SETTINGS.LAN].c_str());
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 30, (char*)dict["a game board of 8x8 squares (chessboard) and 8 pieces (pawns) for "][SETTINGS.LAN].c_str());
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 34, (char*)dict["each player - pieces that will be different colors. Let's name the two"][SETTINGS.LAN].c_str());
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 38, (char*)dict["players: A and B, and the pieces - respectively their colors: white"][SETTINGS.LAN].c_str());
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 42, (char*)dict["and black."][SETTINGS.LAN].c_str());

  settextjustify(CENTER_TEXT, CENTER_TEXT);
  while (1) {
    drawButton(rulesButton);
    drawButton(rules3Button);
    drawButton(menuButton);

    wait(50);
  }
}

void rules3() {
  int kk = 0;
  cleardevice();
  kk = getmaxx() / 400;
  settextstyle(10, HORIZ_DIR, kk);
  readimagefile("./assets/rules.jpg", 0, 0, getmaxx(), getmaxy());
  readimagefile("./assets/board.jpg", getmaxx() / 2 - 370 - 16, getmaxy() / 2 - 40 - 16, getmaxx() / 2 - 100, getmaxy() / 2 + 200);
  readimagefile("./assets/board3.jpg", getmaxx() / 2, getmaxy() / 2 - 40 - 16, getmaxx() / 2 + 270 + 16, getmaxy() / 2 + 200);
  settextjustify(LEFT_TEXT, CENTER_TEXT);
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 20, (char*)dict["The pieces can only be moved diagonally, the goal being to surround"][SETTINGS.LAN].c_str());
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 24, (char*)dict["the enemy piece to remove it from the board. (img 1&2)"][SETTINGS.LAN].c_str());
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 28, (char*)dict["The one who manages to get more soldiers out of the battle wins the game"][SETTINGS.LAN].c_str());
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 32, (char*)dict["opponents, so the one who stays with more pieces on the board."][SETTINGS.LAN].c_str());
  settextjustify(CENTER_TEXT, CENTER_TEXT);
  button menuButton, rules2Button;
  menuButton = createButton(getmaxx() - 100, getmaxy() - 60, dict["Menu"][SETTINGS.LAN].c_str(), menu, BLACK, WHITE, CYAN);
  rules2Button = createButton((getmaxx() / 100) * 25, (getmaxy() / 100) * 90, dict["<- Previous page"][SETTINGS.LAN].c_str(), rules2, WHITE, BLACK, CYAN);
  while (1) {
    drawButton(rules2Button);
    drawButton(menuButton);

    wait(50);
  }
}

void language() {
  cleardevice();
  int kk = getmaxx() / 400;
  settextstyle(10, HORIZ_DIR, kk + 2);
  readimagefile("./assets/romaniaFlag.jpg", getmaxx() / 2 - 400, getmaxy() / 2 - 60, getmaxx() / 2 - 200, getmaxy() / 2 + 60);
  readimagefile("./assets/ukFlag.jpg", getmaxx() / 2 - 100, getmaxy() / 2 - 60, getmaxx() / 2 + 100, getmaxy() / 2 + 60);
  readimagefile("./assets/franceFlag.jpg", getmaxx() / 2 + 200, getmaxy() / 2 - 60, getmaxx() / 2 + 400, getmaxy() / 2 + 60);
  button romanianLanguageButton, franceLanguageButton, englishLanguageButton, menuButton, settingsButton;
  romanianLanguageButton = createButton(getmaxx() / 2 - 300, getmaxy() / 2 + 100, dict["Romanian"][SETTINGS.LAN].c_str(), romanianLanguage, BLACK, WHITE, CYAN);
  franceLanguageButton = createButton(getmaxx() / 2 + 300, getmaxy() / 2 + 100, dict["France"][SETTINGS.LAN].c_str(), franceLanguage, BLACK, WHITE, CYAN);
  englishLanguageButton = createButton(getmaxx() / 2, getmaxy() / 2 + 100, dict["English"][SETTINGS.LAN].c_str(), englishLanguage, BLACK, WHITE, CYAN);
  menuButton = createButton(getmaxx() * 93 / 100, getmaxy() - 60, dict["Menu"][SETTINGS.LAN].c_str(), menu, BLACK, WHITE, CYAN);
  settingsButton = createButton(getmaxx() * 8 / 100, getmaxy() - 60, dict["<- Back"][SETTINGS.LAN].c_str(), settings, BLACK, WHITE, CYAN);
  while (1) {
    drawButton(romanianLanguageButton);
    drawButton(franceLanguageButton);
    drawButton(englishLanguageButton);
    drawButton(menuButton);
    drawButton(settingsButton);

    wait(50);
  }
}

void gameResolution() {
  cleardevice();
  readimagefile("./assets/1200x800mini.jpg", getmaxx() / 2 - 400, getmaxy() / 2 - 60, getmaxx() / 2 - 200, getmaxy() / 2 + 60);
  readimagefile("./assets/1366x768mini.jpg", getmaxx() / 2 - 100, getmaxy() / 2 - 60, getmaxx() / 2 + 100, getmaxy() / 2 + 60);
  readimagefile("./assets/1024x640mini.jpg", getmaxx() / 2 + 200, getmaxy() / 2 - 60, getmaxx() / 2 + 400, getmaxy() / 2 + 60);
  button rez1200x800Button, rez1366x768Button, rez1024x640Button, settingsButton, menuButton, rezFullScreenButton;
  rez1200x800Button = createButton(getmaxx() / 2 - 300, getmaxy() / 2 + 100, "1200x800", NULL, BLACK, WHITE, CYAN);
  rez1366x768Button = createButton(getmaxx() / 2, getmaxy() / 2 + 100, "1366x768", NULL, BLACK, WHITE, CYAN);
  rez1024x640Button = createButton(getmaxx() / 2 + 300, getmaxy() / 2 + 100, "1024x640", NULL, BLACK, WHITE, CYAN);
  rezFullScreenButton = createButton(getmaxx() / 2, getmaxy() / 2 + 200, dict["Fullscreen"][SETTINGS.LAN].c_str(), NULL, BLACK, WHITE, CYAN);
  menuButton = createButton(getmaxx() - 100, getmaxy() - 60, dict["Menu"][SETTINGS.LAN].c_str(), menu, BLACK, WHITE, CYAN);
  settingsButton = createButton(130, getmaxy() - 60, dict["<- Back"][SETTINGS.LAN].c_str(), settings, BLACK, WHITE, CYAN);
  while (1) {
    drawButton(rez1024x640Button);
    drawButton(rez1200x800Button);
    drawButton(rez1366x768Button);
    drawButton(menuButton);
    drawButton(settingsButton);
    drawButton(rezFullScreenButton);

    if (rez1200x800Button.isPressed) {
      rez1200x800Button.isPressed = false;
      setResolution(1200, 800);
      gameResolution();
    }
    if (rez1366x768Button.isPressed) {
      rez1366x768Button.isPressed = false;
      setResolution(1366, 768);
      gameResolution();
    }
    if (rez1024x640Button.isPressed) {
      rez1024x640Button.isPressed = false;
      setResolution(1024, 640);
      gameResolution();
    }

    if (rezFullScreenButton.isPressed) {
      rezFullScreenButton.isPressed = false;
      // Fullscreen
      setResolution(0, 0);
      gameResolution();
    }

    wait(50);
  }
}

void playSoundTrack() {
  playSound("assets/theme_hospital2.wav");
}

void stopSoundTrack() {
  stopSound("assets/theme_hospital2.wav");
}

void romanianLanguage() {
  SETTINGS.LAN = RO;
  saveSettings();
  language();
}
void franceLanguage() {
  SETTINGS.LAN = FR;
  saveSettings();
  language();
}
void englishLanguage() {
  SETTINGS.LAN = EN;
  saveSettings();
  language();
}