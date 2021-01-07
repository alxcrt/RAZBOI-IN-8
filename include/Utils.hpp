#pragma once

#define EN 0
#define FR 1
#define RO 2

extern int LAN;

// Structs
struct button {
  bool isPressed;
  char* label;
  void (*callFunction)();
  int x, y, labelWidth, labelHeight, bkColor, fontColor, hoverColor;
};

// Button
button createButton(int x, int y, const char* label, void (*callFunction)(), int bkColor, int fontColor, int hoverColor);

void drawButton(button& b);

// Others
void exitGame();
void playSound(const char* path);
void stopSound();
void setResolution(int width, int height);
void wait(int t);