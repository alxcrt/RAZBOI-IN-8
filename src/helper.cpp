#include "helper.hpp"

#include <iostream>

#include "graphics.h"

void createButton(int x, int y, int w, int h, const char* label, void (*f)()) {
  settextstyle(0, HORIZ_DIR, 3);
  settextjustify(CENTER_TEXT, CENTER_TEXT);

  int labelWidth = textwidth((char*)label);
  int labelHeight = textheight((char*)label);

  outtextxy(x, y + 6, (char*)label);

  rectangle(x - labelWidth / 2, y - labelHeight / 2, x + labelWidth / 2, y + labelHeight / 2);

  if (mousex() > x - labelWidth / 2 && mousex() < x + labelWidth / 2 && mousey() > y - labelHeight / 2 && mousey() < y + labelHeight / 2) {
    if (ismouseclick(WM_LBUTTONDOWN)) {
      clearmouseclick(WM_LBUTTONDOWN);
      f();
    }
    setcolor(3);
  } else {
    setcolor(14);
  }
}

void closeWindow() {
  closegraph();
  exit(0);
}
