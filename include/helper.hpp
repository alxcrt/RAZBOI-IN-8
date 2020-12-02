struct button {
  bool isPressed = false;
  int x, y, labelWidth, labelHeight;
};

button createButton(int x, int y, const char* label);
void checkMousePressed(button& b);
void exitGame();
void playSound(const char* path);