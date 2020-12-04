#pragma once

// Structs
struct button {
  char* label;
  void (*callFunction)();
  int x, y, labelWidth, labelHeight, bkColor, fontColor, hoverColor;
};

// Button
button createButton(int x, int y, const char* label, void(*callFunction)(), int bkColor, int fontColor, int hoverColor);
void drawButton(button& b);

// Others
void exitGame();
void playSound(const char* path);