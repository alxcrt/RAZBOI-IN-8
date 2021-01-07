
#include "GameHandler.hpp"

#include <iostream>

#include "Dictionary.hpp"
#include "Game.hpp"
#include "Utils.hpp"
#include "graphics.h"

void start() {
  //initwindow(1366, 768, "Razboi in 8", 0, 0);
  //settextjustify(CENTER_TEXT, CENTER_TEXT);
  //playSound("assets/theme_hospital2.wav");
  setResolution(1024, 640);
  // readimagefile("./assets/startingScreen.jpg", 0, 0, getmaxx(), getmaxy());
  // while (1) {
  //   if (ismouseclick(WM_LBUTTONDOWN)) {
  //     clearmouseclick(WM_LBUTTONDOWN);
  //     menu();
  //   }
  //   wait(50);
  // }

  menu();
}

void menu() {
  cleardevice();
  int kk = getmaxx() / 400;
  settextstyle(10, HORIZ_DIR, kk + 2);

  readimagefile("./assets/backgroundGame.jpg", 0, 0, getmaxx(), getmaxy());
  button startGameButton, exitGameButton, rulesGameButton, settingsGameButton;
  startGameButton = createButton(getmaxx() / 2, getmaxy() / 2 - 100, dict["Start Game"][LAN].c_str(), game, BLACK, WHITE, CYAN);
  rulesGameButton = createButton(getmaxx() / 2, getmaxy() / 2, dict["Rules"][LAN].c_str(), rules, BLACK, WHITE, CYAN);
  settingsGameButton = createButton(getmaxx() / 2, getmaxy() / 2 + 100, dict["Settings"][LAN].c_str(), settings, BLACK, WHITE, CYAN);
  exitGameButton = createButton(getmaxx() / 2, getmaxy() / 2 + 200, dict["Exit"][LAN].c_str(), exitGame, BLACK, WHITE, CYAN);

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
  outtextxy(getmaxx() / 100 * 45, getmaxy() / 2 + 5, (char*)dict["Music"][LAN].c_str());
  button languageGameButton, /* volumeGameButton, */ menuButton, volumeOnGameButton, volumeOffGameButton, resolutionButton;
  languageGameButton = createButton(getmaxx() / 2, getmaxy() / 2 - 100, dict["Language"][LAN].c_str(), language, BLACK, WHITE, CYAN);
  //volumeGameButton = createButton(getmaxx() / 2 - 70, getmaxy() / 2, "Volume:", volume, BLACK, WHITE, CYAN);
  volumeOnGameButton = createButton(getmaxx() / 100 * 60, getmaxy() / 2, dict["On"][LAN].c_str(), playyySound, BLACK, WHITE, CYAN);
  volumeOffGameButton = createButton(getmaxx() / 100 * 60, getmaxy() / 2 + 50, dict["Off"][LAN].c_str(), stopSound, BLACK, WHITE, CYAN);
  menuButton = createButton(getmaxx() / 2, getmaxy() / 2 + 200, dict["Menu"][LAN].c_str(), menu, BLACK, WHITE, CYAN);
  resolutionButton = createButton(getmaxx() / 2, getmaxy() / 2 + 100, dict["Resolution"][LAN].c_str(), gameResolution, BLACK, WHITE, CYAN);
  while (1) {
    drawButton(languageGameButton);
    drawButton(volumeOnGameButton);
    drawButton(volumeOffGameButton);
    //drawButton(volumeGameButton);
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
  menuButton = createButton(getmaxx() - 100, getmaxy() - 60, dict["Menu"][LAN].c_str(), menu, BLACK, WHITE, CYAN);
  rules2Button = createButton((getmaxx() / 100) * 75, (getmaxy() / 100) * 90, dict["Next page ->"][LAN].c_str(), rules2, WHITE, BLACK, CYAN);
  setbkcolor(WHITE);
  setcolor(BLACK);
  settextjustify(LEFT_TEXT, CENTER_TEXT);
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 20, (char*)"Jocul <Razboi in 8> (cu varianta sa <Razboi in 4>) este un joc");
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 24, (char*)"rational pentru toate varstele. El solicita atentia si spiritul de");
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 28, (char*)"observatie, favorizeaza analiza combinatorie a variantelor si dezvolta");
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 32, (char*)"obisnuinta de a duce lucrurile la bun sfarsit. Un joc asemanator -dar");
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 36, (char*)"mai simplu- care faciliteaza invatarea si practicarea jocului <Razboi");
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 40, (char*)"in 8> este <Cainii si vulpea>. Jocul ofera amatorilor un larg camp de");
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 44, (char*)"studiu si analiza -nu prea simpla- fiind perfect adaptat pentru");
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 48, (char*)"compunere si rezolvare de probleme, precum si pentru desfasurare");
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 52, (char*)"prin corespondenta.");
  settextjustify(CENTER_TEXT, CENTER_TEXT);
  while (1) {
    // settextstyle(10, HORIZ_DIR, kk + 2);
    drawButton(menuButton);
    // settextstyle(10, HORIZ_DIR, kk);
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
  readimagefile("./assets/board2.jpg", getmaxx() / 2 - 370 - 16, getmaxy() / 2 - 40 - 16, getmaxx() / 2 - 100, getmaxy() / 2 + 200);
  button menuButton, rulesButton, rules3Button;
  menuButton = createButton(getmaxx() - 100, getmaxy() - 60, "Menu", menu, BLACK, WHITE, CYAN);
  rulesButton = createButton((getmaxx() / 100) * 25, (getmaxy() / 100) * 90, dict["<- Previous page"][LAN].c_str(), rules, WHITE, BLACK, CYAN);
  rules3Button = createButton((getmaxx() / 100) * 75, (getmaxy() / 100) * 90, dict["Next page ->"][LAN].c_str(), rules3, WHITE, BLACK, CYAN);
  setbkcolor(WHITE);
  setcolor(BLACK);
  settextjustify(LEFT_TEXT, CENTER_TEXT);
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 18, (char*)"La joc iau parte doua persoane, care urmareste, fiecare, a scoate din");
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 22, (char*)"lupta <armata> adversa. Jocul se poate incheia cu victoria unuia dintre");
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 26, (char*)"jucatori, sau nedecis -remiza. Practicarea jocului reclama o tabla de");
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 30, (char*)"joc de 8x8 patratele (tabla de sah) si cate 8 piese (pioni) pentru");
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 34, (char*)"fiecare jucator - piese care vor fi de culori diferite. Sa numim cei");
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 38, (char*)"doi jucatori: A si B, iar piesele -respectiv culorile lor: alb si negru.");
  settextjustify(CENTER_TEXT, CENTER_TEXT);
  while (1) {
    // settextstyle(10, HORIZ_DIR, kk);
    drawButton(rulesButton);
    drawButton(rules3Button);
    // settextstyle(10, HORIZ_DIR, kk + 2);
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
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 20, (char*)"Piesele se pot muta doar pe diagonala, scopul fiind acela de a");
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 24, (char*)"inconjura piesa inamica pentru a o scoate de pe tabla. (img 1+2)");
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 28, (char*)"Castiga jocul cel care reuseste sa scoata din lupta mai multi soldati");
  outtextxy((getmaxx() / 100) * 10, (getmaxy() / 100) * 32, (char*)"adversi, deci cel care ramane cu mai multe piese pe tabla.");
  settextjustify(CENTER_TEXT, CENTER_TEXT);
  button menuButton, rules2Button;
  menuButton = createButton(getmaxx() - 100, getmaxy() - 60, dict["<- Back"][LAN].c_str(), menu, BLACK, WHITE, CYAN);
  rules2Button = createButton((getmaxx() / 100) * 25, (getmaxy() / 100) * 90, dict["<- Previous page"][LAN].c_str(), rules2, WHITE, BLACK, CYAN);
  while (1) {
    // settextstyle(10, HORIZ_DIR, kk);
    drawButton(rules2Button);
    // settextstyle(10, HORIZ_DIR, kk + 2);
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
  romanianLanguageButton = createButton(getmaxx() / 2 - 300, getmaxy() / 2 + 100, dict["Romanian"][LAN].c_str(), romanianLanguage, BLACK, WHITE, CYAN);
  franceLanguageButton = createButton(getmaxx() / 2 + 300, getmaxy() / 2 + 100, dict["France"][LAN].c_str(), franceLanguage, BLACK, WHITE, CYAN);
  englishLanguageButton = createButton(getmaxx() / 2, getmaxy() / 2 + 100, dict["English"][LAN].c_str(), englishLanguage, BLACK, WHITE, CYAN);
  menuButton = createButton(getmaxx() - 100, getmaxy() - 60, dict["Menu"][LAN].c_str(), menu, BLACK, WHITE, CYAN);
  settingsButton = createButton(130, getmaxy() - 60, dict["<- Back"][LAN].c_str(), settings, BLACK, WHITE, CYAN);
  while (1) {
    drawButton(romanianLanguageButton);
    drawButton(franceLanguageButton);
    drawButton(englishLanguageButton);
    drawButton(menuButton);
    drawButton(settingsButton);

    wait(50);
  }
}

void playyySound() {
  playSound("assets/theme_hospital2.wav");
}

void romanianLanguage() {
  LAN = RO;
  language();
}
void franceLanguage() {
  LAN = FR;
  language();
}
void englishLanguage() {
  LAN = EN;
  language();
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
  rezFullScreenButton = createButton(getmaxx() / 2, getmaxy() / 2 + 200, dict["Fullscreen"][LAN].c_str(), NULL, BLACK, WHITE, CYAN);
  menuButton = createButton(getmaxx() - 100, getmaxy() - 60, dict["Menu"][LAN].c_str(), menu, BLACK, WHITE, CYAN);
  settingsButton = createButton(130, getmaxy() - 60, dict["<- Back"][LAN].c_str(), settings, BLACK, WHITE, CYAN);
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