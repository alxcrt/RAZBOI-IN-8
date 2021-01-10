#pragma once

#include <array>
#include <cstring>
#include <unordered_map>

// Structs
struct _SETTINGS {
  int LAN, WIDTH, HEIGHT;
};

struct button {
  bool isPressed;
  char* label;
  void (*callFunction)();
  int x, y, labelWidth, labelHeight, bkColor, fontColor, hoverColor;
};

#define EN 0
#define FR 1
#define RO 2

extern std::unordered_map<std::string, std::array<std::string, 3>>
    dict;

const char* const SAVE_FILE_NAME = "./bin/release/settings.dat";

// Button
button createButton(int x, int y, const char* label, void (*callFunction)(), int bkColor, int fontColor, int hoverColor);

void drawButton(button& b);

// Others
void exitGame();
void playSound(const std::string path);
void stopSound(const std::string path);
void setResolution(int width, int height);
void wait(int t);

void loadSettings();
void saveSettings();