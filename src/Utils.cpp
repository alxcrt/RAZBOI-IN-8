#include "Utils.hpp"

#include <cstring>

#include "graphics.h"

// Create a buttonz
button createButton(int x, int y, const char* label, void (*callFunction)(), int bkColor, int fontColor, int hoverColor) {
  button b;

  b.label = (char*)label;
  b.x = x;
  b.y = y;
  // Get the width and height in pixel of the desired label
  b.labelWidth = textwidth((char*)label);
  b.labelHeight = textheight((char*)label);
  b.bkColor = bkColor;
  b.fontColor = fontColor;
  b.hoverColor = hoverColor;
  b.callFunction = callFunction;
  b.isPressed = false;
  return b;
}

void drawButton(button& b) {
  // rectangle(b.x - b.labelWidth / 2, b.y - b.labelHeight / 2, b.x + b.labelWidth / 2, b.y + b.labelHeight / 2);

  // * Verify if the mouse is inside the area of the button
  if (mousex() > b.x - b.labelWidth / 2 && mousex() < b.x + b.labelWidth / 2 && mousey() > b.y - b.labelHeight / 2 && mousey() < b.y + b.labelHeight / 2) {
    if (ismouseclick(WM_LBUTTONDOWN)) {
      b.isPressed = true;
      if (b.callFunction != NULL) {
        clearmouseclick(WM_LBUTTONDOWN);
        b.callFunction();
      }
    }
    setcolor(b.hoverColor);
  } else {
    setcolor(b.fontColor);
  }

  setbkcolor(b.bkColor);
  // * Draw the label text
  outtextxy(b.x, b.y + b.labelHeight / 4, (char*)b.label);
  // * Reset Color
}

void exitGame() {
  closegraph();
  exit(0);
}

void stopSound(const std::string path) {
  mciSendStringA(("close " + path).c_str(), NULL, 0, NULL);
}

void playSound(const std::string path) {
  // * Stops playback of a sound that is playing
  // stopSound(path);

  // Plays the sound
  // waveOutSetVolume(NULL, 0xFFFF);
  // PlaySoundA(path, NULL, SND_LOOP | SND_ASYNC);
  // PlaySoundA(path, GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
  mciSendStringA(("play " + path).c_str(), NULL, 0, 0);

  // mciSendString("play mp3", NULL, 0, NULL);
}

void wait(int x) {
  clearmouseclick(WM_LBUTTONDOWN);
  delay(x);
}

void setResolution(int width, int height) {
  closegraph();

  if (width == 1200) {
    initwindow(width, height, "Razboi in 8", 0, 0);
    settextstyle(10, HORIZ_DIR, 5);
  } else if (width == 1366) {
    initwindow(width, height, "Razboi in 8", 0, 0);
    settextstyle(10, HORIZ_DIR, 5);
  } else if (width == 1024) {
    initwindow(width, height, "Razboi in 8", 0, 0);
    settextstyle(10, HORIZ_DIR, 4);
  } else {
    initwindow(getmaxwidth(), getmaxheight(), "Razboi in 8", 0, 0);
    settextstyle(10, HORIZ_DIR, 5);
  }
  settextjustify(CENTER_TEXT, CENTER_TEXT);
}

// * Manage the language
int LAN = EN;

// * Dictionary
std::unordered_map<std::string, std::array<std::string, 3>> dict{
    {"Start Game", {"Start Game", "Demarrer jeu", "Incepe jocul"}},
    {"Rules", {"Rules", "Regles", "Reguli"}},
    {"Settings", {"Settings", "Reglages", "Setari"}},

    {"Exit", {"Exit", "Sortie", "Iesire"}},
    {"Language", {"Language", "Langue", "Limba"}},
    {"Music", {"Music", "Musique", "Muzica"}},

    {"English", {"English", "Anglaise", "Engleza"}},
    {"France", {"France", "Francais", "Franceza"}},
    {"Romanian", {"Romanian", "Roumaine", "Romana"}},

    {"On", {"On", "Ouvrir", "Pornita"}},
    {"Off", {"Off", "Vide", "Inchisa"}},
    {"Resolution", {"Resolution", "La resolution", "Rezolutia"}},
    {"Menu", {"Menu", "Le menu", "Meniu"}},
    {"Fullscreen", {"Fullscreen", "Plein ecran", "Tot ecranul"}},
    {"<- Back", {"<- Back", "<- Retour", "<- Inapoi"}},
    {"Next page ->", {"Next page ->", "Page suivante ->", "Urmatoarea pagina ->"}},
    {"<- Previous page", {"<- Previous page", "<- Page precedente", "<- Pagina precedenta"}},

    {"Player vs Player", {"Player vs Player", "Joueur contre Joueur", "Jucator contra Jucator"}},
    {"Player vs Computer Easy", {"Player vs Computer Easy", "Joueur contre Ordinateur Facile", "Jucator contra Calculator Usor"}},
    {"Player vs Computer Hard", {"Player vs Computer Hard", "Joueur contre Ordinateur Dur", "Jucator contra Calculator Greu"}},
    {"Virus Moves", {"Virus Moves", "Virus Passe", "Virusul Muta"}},
    {"Dokter Moves", {"Dokter Moves", "Docteur Passe", "Doctorul Muta"}},
    {"Dokter Wins", {"Dokter Wins", "Docteur Gagne", "Doctorul Castiga"}},
    {"Virus Wins", {"Virus Wins", "Virus Gagne", "Virusul Castiga"}},

    {"Dokter", {"Dokter", "Docteur", "Doctor"}},
    {"Virus", {"Virus", "Virus", "Virus"}},
    {"moves", {"moves", "coups", "mutari"}},
    {"pieces", {"pieces", "pieces", "piese"}},

    {"The game <War in 8> (with its version <War in 4>) is a rational game", {"The game <War in 8> (with its version <War in 4>) is a rational game", "Le jeu <War in 8> (avec sa version <War in 4>) est un jeu rationnel", "Jocul <Razboi in 8> (cu varianta sa <Razboi in 4>) este un joc"}},
    {"for all ages. It demands attention and the spirit of observation,", {"for all ages. It demands attention and the spirit of observation,", "pour tous les ages. Il reclame attention et esprit d'observation,", "rational pentru toate varstele. El solicita atentia si spiritul de"}},
    {"favors the combinatorial analysis of the variants and develops the", {"favors the combinatorial analysis of the variants and develops the", "favorise l'analyse combinatoire des variantes et developpe", "observatie, favorizeaza analiza combinatorie a variantelor si dezvolta"}},
    {"habit of carrying things to the end. A similar game - but simpler -", {"habit of carrying things to the end. A similar game - but simpler -", "l'habitude de porter les choses jusqu'au bout. Un jeu similaire", "obisnuinta de a duce lucrurile la bun sfarsit. Un joc asemanator -dar"}},
    {"that facilitates learning and practicing the game <War in 8> is", {"that facilitates learning and practicing the game <War in 8> is", "- mais plus simple - qui facilite l'apprentissage et la pratique du", "mai simplu -care faciliteaza invatarea si practicarea jocului <Razboi"}},
    {"<Dogs and fox>. The game offers amateurs a wide field of study and", {"<Dogs and fox>. The game offers amateurs a wide field of study and", "jeu <War in 8> est <Dogs and fox>. Le jeu offre aux amateurs un large", "in 8> este <Cainii si vulpea>. Jocul ofera amatorilor un larg camp de"}},
    {"analysis - not too simple - being perfectly adapted for composing and", {"analysis - not too simple - being perfectly adapted for composing and", "champ d'etude et d'analyse - pas trop simple - parfaitement adapte", "studiu si analiza - nu prea simpla -fiind perfect adaptat pentru"}},
    {"solving problems, as well as for correspondence.", {"solving problems, as well as for correspondence.", "pour la composition et la resolution de problemes.", "compunere si rezolvare de probleme."}},

    {"Two people take part in the game, each of whom aimed to get the", {"Two people take part in the game, each of whom aimed to get the", "Deux personnes participent au jeu, chacune visant a faire sortir le", "La joc iau parte doua persoane, care urmarese, fiecare, a scoate din"}},
    {"opposing <armed> fight out. The game can end with the victory of one", {"opposing <armed> fight out. The game can end with the victory of one", "combat <arme> adverse. Le jeu peut se terminer par la victoire de", "lupta <armata> adversa. Jocul se poate incheia cu victoria unuia dintre"}},
    {"of the players, or undecided - the draw. Practicing the game requires", {"of the players, or undecided - the draw. Practicing the game requires", "l'un des joueurs, ou indecis - le tirage au sort. La pratique du jeu", "jucatori, sau nedecis -remiza. Practicarea jocului reclama o tabla de"}},
    {"a game board of 8x8 squares (chessboard) and 8 pieces (pawns) for ", {"a game board of 8x8 squares (chessboard) and 8 pieces (pawns) for ", "necessite un plateau de jeu de 8x8 carres (echiquier) et 8 pieces", "joc de 8x8 patratele (tabla de sah) si cate 8 piese (pioni) pentru"}},
    {"each player - pieces that will be different colors. Let's name the two", {"each player - pieces that will be different colors. Let's name the two", "(pions) pour chaque joueur - des pieces qui seront de couleurs", "fiecare jucator - piese care vor fi de culori diferite. Sa numim cei"}},
    {"players: A and B, and the pieces - respectively their colors: white", {"players: A and B, and the pieces - respectively their colors: white", "differentes. Nommons les deux joueurs: A et B, et les pieces", "doi jucatori: A si B, iar piesele -respectiv culorile lor: alb"}},
    {"and black.", {"and black.", "- respectivement leurs couleurs: blanc et noir.", "si negru"}},

    {"The pieces can only be moved diagonally, the goal being to surround", {"The pieces can only be moved diagonally, the goal being to surround", "Les pieces ne peuvent être deplacees qu'en diagonale, le but etant", "Piesele se pot muta doar pe diagonala, scopul fiind acela de a"}},
    {"the enemy piece to remove it from the board. (img 1&2)", {"the enemy piece to remove it from the board. (img 1&2)", "d'entourer la piece ennemie pour la retirer du plateau. (img 1&2)", "inconjura piesa inamica pentru a o scoate de pe tabla. (img 1&2)"}},
    {"The one who manages to get more soldiers out of the battle wins the game", {"The one who manages to get more soldiers out of the battle wins the game", "Celui qui parvient à faire sortir plus de soldats de la bataille", "Castiga jocul cel care reuseste sa scoata din lupta mai multi soldati"}},
    {"opponents, so the one who stays with more pieces on the board.", {"opponents, so the one who stays with more pieces on the board.", "remporte la partie adversaires.", "adversi, deci cel care ramane cu mai multe piese pe tabla."}},

};
