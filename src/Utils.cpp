#include "Utils.hpp"

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

  // Verify if the mouse is inside the area of the button
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
    // clearmouseclick(WM_LBUTTONDOWN);
    // if (ismouseclick(WM_LBUTTONDOWN))
  }

  setbkcolor(b.bkColor);
  // Draw the label text
  outtextxy(b.x, b.y + b.labelHeight / 4, (char*)b.label);
  // Reset Color
  // setcolor(WHITE);
}

void exitGame() {
  closegraph();
  exit(0);
}

void stopSound() {
  PlaySoundA(0, 0, 0);
}

void playSound(const char* path) {
  // Stops playback of a sound that is playing
  PlaySoundA(0, 0, 0);
  // Plays the sound
  // waveOutSetVolume(NULL, 0xFFFF);
  // PlaySoundA(path, NULL, SND_LOOP | SND_ASYNC);
  PlaySoundA(path, GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC | SND_LOOP);
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