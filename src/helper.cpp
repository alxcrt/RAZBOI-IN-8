#include "helper.hpp"

#include <iostream>

#include "graphics.h"

// Create a button
void createButton(int x, int y, const char* label, void (*f)()) {
  // Get the width and height in pixel of the desired label
  int labelWidth = textwidth((char*)label);
  int labelHeight = textheight((char*)label);

  // rectangle(x - labelWidth / 2, y - labelHeight / 2, x + labelWidth / 2, y + labelHeight / 2);

  // Verify if the mouse is inside the area of the button
  if (mousex() > x - labelWidth / 2 && mousex() < x + labelWidth / 2 && mousey() > y - labelHeight / 2 && mousey() < y + labelHeight / 2) {
    if (ismouseclick(WM_LBUTTONDOWN)) {
      clearmouseclick(WM_LBUTTONDOWN);
      f();
    }
    setcolor(3);
  } else {
    setcolor(14);
  }

  settextstyle(0, HORIZ_DIR, 3);
  // Draw the label text
  outtextxy(x, y + 6, (char*)label);
}

void closeWindow() {
  closegraph();
  exit(0);
}

void playSound(const char* path) {
  // Stops playback of a sound that is playing
  PlaySoundA(0, 0, 0);
  // Plays the sound
  PlaySoundA(path, NULL, SND_ASYNC);
}

void game() {
  cleardevice();

  outtextxy(getmaxx() / 2, getmaxy() / 2 + 6, (char*)"Jocul este in constrctie");
}
