#include "helper.hpp"

#include <iostream>

#include "graphics.h"

// Create a buttonz
button createButton(int x, int y, const char* label) {
  // Get the width and height in pixel of the desired label
  int labelWidth = textwidth((char*)label);
  int labelHeight = textheight((char*)label);

  // rectangle(x - labelWidth / 2, y - labelHeight / 2, x + labelWidth / 2, y + labelHeight / 2);

  button b;

  // Verify if the mouse is inside the area of the button
  if (mousex() > x - labelWidth / 2 && mousex() < x + labelWidth / 2 && mousey() > y - labelHeight / 2 && mousey() < y + labelHeight / 2) {
    if (ismouseclick(WM_LBUTTONDOWN)) {
      clearmouseclick(WM_LBUTTONDOWN);
      b.isPressed = true;
    }
    setcolor(3);
  } else {
    setcolor(WHITE);
  }

  settextstyle(10, HORIZ_DIR, 5);
  // Draw the label text
  outtextxy(x, y + 6, (char*)label);
  // Reset Color
  setcolor(WHITE);
  return b;
}

void exitGame() {
  closegraph();
  exit(0);
}

void playSound(const char* path) {
  // Stops playback of a sound that is playing
  PlaySoundA(0, 0, 0);
  // Plays the sound
  PlaySoundA(path, NULL, SND_ASYNC);
}
