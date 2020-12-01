#include <graphics.h>
#include <math.h>
#include <mmsystem.h>
#include <windows.h>

#include "helper.hpp"

int main() {
  // int gd = DETECT, gm;

  // initgraph(&gd, &gm, NULL);
  initwindow(800, 800, "Razboi in 8", 0, 0);

  while (1) {
    createButton(getmaxx() / 2, getmaxy() / 2, 70, 20, "Exit", closeWindow);
    delay(10);
  }

  return 0;
}