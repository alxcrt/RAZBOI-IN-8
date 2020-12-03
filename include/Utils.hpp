#pragma once

// Structs
struct button {
  bool isPressed = false;
  char* label;
  int x, y, labelWidth, labelHeight;
};

// Button
button createButton(int x, int y, const char* label);
void drawButton(button& b);

// Others
void exitGame();
void playSound(const char* path);