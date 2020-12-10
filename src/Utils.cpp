#include "Utils.hpp"

#include <iostream>

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
      clearmouseclick(WM_LBUTTONDOWN);
      b.isPressed = true;
      if (b.callFunction)
        b.callFunction();
    }
    setcolor(b.hoverColor);
  } else {
    setcolor(b.fontColor);
    // clearmouseclick(WM_LBUTTONDOWN);
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
  PlaySoundA(path, NULL, SND_LOOP | SND_ASYNC);
}

void setResolution(int width, int height) {
  closegraph();
  initwindow(width, height, "Razboi in 8", 0, 0);
  if (width == 1920) {
    settextstyle(10, HORIZ_DIR, 5);
  } else if (width == 1366) {
    settextstyle(10, HORIZ_DIR, 3);
  } else {
    settextstyle(10, HORIZ_DIR, 2);
  }
  settextjustify(CENTER_TEXT, CENTER_TEXT);
}