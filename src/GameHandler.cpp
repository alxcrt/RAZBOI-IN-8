
#include "GameHandler.hpp"

#include "Game.hpp"
#include "Utils.hpp"
#include "graphics.h"

void start() {
  //initwindow(1366, 768, "Razboi in 8", 0, 0);
  //settextjustify(CENTER_TEXT, CENTER_TEXT);
  //playSound("assets/theme_hospital2.wav");
  setResolution(1200,800);

  menu();
}

void menu() {
  cleardevice();
  readimagefile("./assets/startingimg.jpg", 0, 0, getmaxx(), getmaxy());
  settextstyle(10, HORIZ_DIR, 5);
  button startGameButton, exitGameButton, rulesGameButton, settingsGameButton;
  startGameButton = createButton(getmaxx() / 2, getmaxy() / 2 - 100, "Start Game", game, BLACK, WHITE, CYAN);
  rulesGameButton = createButton(getmaxx() / 2, getmaxy() / 2, "Rules", rules, BLACK, WHITE, CYAN);
  settingsGameButton = createButton(getmaxx() / 2, getmaxy() / 2 + 100, "Settings", settings, BLACK, WHITE, CYAN);
  exitGameButton = createButton(getmaxx() / 2, getmaxy() / 2 + 200, "Exit", exitGame, BLACK, WHITE, CYAN);

  while (1) {
    drawButton(startGameButton);
    drawButton(exitGameButton);
    drawButton(rulesGameButton);
    drawButton(settingsGameButton);

    delay(50);
  }
}

void settings() {
  cleardevice();
  readimagefile("./assets/startingimg.jpg", 0, 0, getmaxx(), getmaxy());
  settextstyle(10, HORIZ_DIR, 5);
  setbkcolor(BLACK);
  setcolor(WHITE);
  settextstyle(10, HORIZ_DIR, 5);
  outtextxy(getmaxx() / 2 - 70, getmaxy() / 2 + 5, (char*)"Volume:");
  button languageGameButton, /* volumeGameButton, */ menuButton, volumeOnGameButton, volumeOffGameButton, resolutionButton;
  languageGameButton = createButton(getmaxx() / 2, getmaxy() / 2 - 100, "Language", language, BLACK, WHITE, CYAN);
  //volumeGameButton = createButton(getmaxx() / 2 - 70, getmaxy() / 2, "Volume:", volume, BLACK, WHITE, CYAN);
  volumeOnGameButton = createButton(getmaxx() / 2 + 50, getmaxy() / 2, "ON", playyySound, BLACK, WHITE, CYAN);
  volumeOffGameButton = createButton(getmaxx() / 2 + 130, getmaxy() / 2, "OFF", stopSound, BLACK, WHITE, CYAN);
  menuButton = createButton(getmaxx() / 2, getmaxy() / 2 + 200, "Menu", menu, BLACK, WHITE, CYAN);
  resolutionButton = createButton(getmaxx() / 2, getmaxy() / 2 + 100, "Resolution", gameResolution, BLACK, WHITE, CYAN);
  while (1) {
    drawButton(languageGameButton);
    drawButton(volumeOnGameButton);
    drawButton(volumeOffGameButton);
    //drawButton(volumeGameButton);
    drawButton(resolutionButton);
    drawButton(menuButton);
    
    delay(50);
  }
}

void rules() {
  cleardevice();
  readimagefile("./assets/rules.jpg", 0, 0, getmaxx(), getmaxy());
  button menuButton, rules2Button;
  menuButton = createButton(getmaxx() - 100, getmaxy() - 60, "Menu", menu, BLACK, WHITE, CYAN);
  rules2Button = createButton(getmaxx() - 250, getmaxy() - 100, "next page ->", rules2, WHITE, BLACK, CYAN);
  setbkcolor(WHITE);
  setcolor(BLACK);
  settextstyle(10, HORIZ_DIR, 2);
  outtextxy(520, 200, (char*)"Jocul <Razboi in 8> (cu varianta sa <Razboi in 4>) este un joc         ");
  outtextxy(520, 230, (char*)"rational pentru toate varstele. El solicita atentia si spiritul de     ");
  outtextxy(520, 260, (char*)"observatie, favorizeaza analiza combinatorie a variantelor si dezvolta ");
  outtextxy(520, 290, (char*)"obisnuinta de a duce lucrurile la bun sfarsit. Un joc asemanator -dar  ");
  outtextxy(520, 320, (char*)"mai simplu- care faciliteaza invatarea si practicarea jocului <Razboi  ");
  outtextxy(520, 350, (char*)"in 8> este <Cainii si vulpea>. Jocul ofera amatorilor un larg camp de  ");
  outtextxy(520, 380, (char*)"studiu si analiza -nu prea simpla- fiind perfect adaptat pentru        ");
  outtextxy(520, 410, (char*)"compunere si rezolvare de probleme, precum si pentru desfasurare       ");
  outtextxy(520, 440, (char*)"prin corespondenta.                                                    ");
  while (1) {
    settextstyle(10, HORIZ_DIR, 5);
    drawButton(menuButton);
    settextstyle(10, HORIZ_DIR, 3);
    drawButton(rules2Button);

    delay(50);
  }
}

void rules2() {
  cleardevice();
  readimagefile("./assets/rules.jpg", 0, 0, getmaxx(), getmaxy());
  readimagefile("./assets/board2.jpg", getmaxx() / 2 - 370, getmaxy() / 2 - 40, getmaxx() / 2 - 100, getmaxy() / 2 + 200);
  button menuButton, rulesButton, rules3Button;
  menuButton = createButton(getmaxx() - 100, getmaxy() - 60, "Menu", menu, BLACK, WHITE, CYAN);
  rulesButton = createButton(250, getmaxy() - 100, "<- previous page", rules, WHITE, BLACK, CYAN);
  rules3Button = createButton(getmaxx() - 250, getmaxy() - 100, "next page ->", rules3, WHITE, BLACK, CYAN);
  setbkcolor(WHITE);
  setcolor(BLACK);
  settextstyle(10, HORIZ_DIR, 2);
  outtextxy(520, 110, (char*)"La joc iau parte doua persoane, care urmarese, fiecare, a scoate din   ");
  outtextxy(520, 140, (char*)"lupta <armata> adversa. Jocul se poate incheia cu victoria unuia dintre");
  outtextxy(520, 170, (char*)"jucatori, sau nedecis -remiza. Practicarea jocului reclama o tabla de  ");
  outtextxy(520, 200, (char*)"joc de 8x8 patratele (tabla de sah) si cate 8 piese (pioni) pentru     ");
  outtextxy(520, 230, (char*)"fiecare jucator - piese care vor fi de culori diferite. Sa numim cei   ");
  outtextxy(520, 260, (char*)"doi jucatori: A si B, iar piesele -respectiv culorile lor: alb si negru.");
  while (1) {
    settextstyle(10, HORIZ_DIR, 3);
    drawButton(rulesButton);
    drawButton(rules3Button);
    settextstyle(10, HORIZ_DIR, 5);
    drawButton(menuButton);

    delay(50);
  }
}

void rules3() {
  cleardevice();
  readimagefile("./assets/rules.jpg", 0, 0, getmaxx(), getmaxy());
  readimagefile("./assets/board.jpg", getmaxx() / 2 - 370, getmaxy() / 2 - 40, getmaxx() / 2 - 100, getmaxy() / 2 + 200);
  readimagefile("./assets/board3.jpg", getmaxx() / 2, getmaxy() / 2 - 40, getmaxx() / 2 + 270, getmaxy() / 2 + 200);
  settextstyle(10, HORIZ_DIR, 2);
  outtextxy(520, 130, (char*)"Piesele se pot muta doar pe diagonala, scopul fiind acela de a         ");
  outtextxy(520, 160, (char*)"inconjura piesa inamica pentru a o scoate de pe tabla. (img 1+2)       ");
  outtextxy(520, 190, (char*)"Castiga jocul cel care reuseste sa scoata din lupta mai multi soldati  ");
  outtextxy(520, 220, (char*)"adversi, deci cel care ramane cu mai multe piese pe tabla.             ");
  button menuButton, rules2Button;
  menuButton = createButton(getmaxx() - 100, getmaxy() - 60, "Menu", menu, BLACK, WHITE, CYAN);
  rules2Button = createButton(250, getmaxy() - 100, "<- previous page", rules2, WHITE, BLACK, CYAN);
  settextstyle(10, HORIZ_DIR, 3);
  while (1) {
    settextstyle(10, HORIZ_DIR, 3);
    drawButton(rules2Button);
    settextstyle(10, HORIZ_DIR, 5);
    drawButton(menuButton);

    delay(50);
  }
}

void language() {
  cleardevice();
  readimagefile("./assets/romaniaFlag.jpg", getmaxx() / 2 - 400, getmaxy() / 2 - 60, getmaxx() / 2 - 200, getmaxy() / 2 + 60);
  readimagefile("./assets/ukFlag.jpg", getmaxx() / 2 - 100, getmaxy() / 2 - 60, getmaxx() / 2 + 100, getmaxy() / 2 + 60);
  readimagefile("./assets/franceFlag.jpg", getmaxx() / 2 + 200, getmaxy() / 2 - 60, getmaxx() / 2 + 400, getmaxy() / 2 + 60);
  button romanianLanguageButton, franceLanguageButton, englishLanguageButton, menuButton, settingsButton;
  romanianLanguageButton = createButton(getmaxx() / 2 - 300, getmaxy() / 2 + 100, "Romanian", romanianLanguage, BLACK, WHITE, CYAN);
  franceLanguageButton = createButton(getmaxx() / 2 + 300, getmaxy() / 2 + 100, "France", franceLanguage, BLACK, WHITE, CYAN);
  englishLanguageButton = createButton(getmaxx() / 2, getmaxy() / 2 + 100, "English", englishLanguage, BLACK, WHITE, CYAN);
  menuButton = createButton(getmaxx() - 100, getmaxy() - 60, "Menu", menu, BLACK, WHITE, CYAN);
  settingsButton = createButton(130, getmaxy() - 60, "<- Back", settings, BLACK, WHITE, CYAN);
  settextstyle(10, HORIZ_DIR, 5);
  while (1) {
    drawButton(romanianLanguageButton);
    drawButton(franceLanguageButton);
    drawButton(englishLanguageButton);
    drawButton(menuButton);
    drawButton(settingsButton);

    delay(50);
  }
}

void playyySound() {
  playSound("assets/theme_hospital2.wav");
}

void romanianLanguage() {
  return;
}
void franceLanguage() {
  return;
}
void englishLanguage() {
  return;
}

void gameResolution() {
  cleardevice();
  readimagefile("./assets/1200x800mini.jpg", getmaxx() / 2 - 400, getmaxy() / 2 - 60, getmaxx() / 2 - 200, getmaxy() / 2 + 60);
  readimagefile("./assets/1366x768mini.jpg", getmaxx() / 2 - 100, getmaxy() / 2 - 60, getmaxx() / 2 + 100, getmaxy() / 2 + 60);
  readimagefile("./assets/1024x640mini.jpg", getmaxx() / 2 + 200, getmaxy() / 2 - 60, getmaxx() / 2 + 400, getmaxy() / 2 + 60);
  button rez1200x800Button, rez1366x768Button, rez1024x640Button, settingsButton, menuButton;
  rez1200x800Button = createButton(getmaxx() / 2 - 300, getmaxy() / 2 + 100, "1200x800", NULL, BLACK, WHITE, CYAN);
  rez1366x768Button = createButton(getmaxx() / 2, getmaxy() / 2 + 100, "1366x768", NULL, BLACK, WHITE, CYAN);
  rez1024x640Button = createButton(getmaxx() / 2 + 300, getmaxy() / 2 + 100, "1024x640", NULL, BLACK, WHITE, CYAN);
  menuButton = createButton(getmaxx() - 100, getmaxy() - 60, "Menu", menu, BLACK, WHITE, CYAN);
  settingsButton = createButton(130, getmaxy() - 60, "<- Back", settings, BLACK, WHITE, CYAN);
  settextstyle(10, HORIZ_DIR, 5);
  while (1) {
    drawButton(rez1024x640Button);
    drawButton(rez1200x800Button);
    drawButton(rez1366x768Button);
    drawButton(menuButton);
    drawButton(settingsButton);

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

    delay(50);
  }
}