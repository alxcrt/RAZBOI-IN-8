#include "helper.hpp"

#include <iostream>

#include "graphics.h"

// Create a button
button createButton(int x, int y, const char* label) {
  button b;
  b.x = x;
  b.y = y;

  // Increase the font size
  settextstyle(0, HORIZ_DIR, 3);
  // Draw the label text
  outtextxy(x, y + 6, (char*)label);

  // Get the width and height in pixel of the desired label
  b.labelWidth = textwidth((char*)label);
  b.labelHeight = textheight((char*)label);

  return b;
}

void checkMousePressed(button& b) {
  rectangle(b.x - b.labelWidth / 2, b.y - b.labelHeight / 2, b.x + b.labelWidth / 2, b.y + b.labelHeight / 2);

  // Verify if the mouse is inside the area of the button
  if (mousex() > b.x - b.labelWidth / 2 && mousex() < b.x + b.labelWidth / 2 && mousey() > b.y - b.labelHeight / 2 && mousey() < b.y + b.labelHeight / 2 && ismouseclick(WM_LBUTTONDOWN)) {
    clearmouseclick(WM_LBUTTONDOWN);
    b.isPressed = true;
    setcolor(15);
  } else {
    setcolor(2);
    clearmouseclick(WM_LBUTTONDOWN);
  }
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
