#include <graphics.h>
#include <math.h>
#include <mmsystem.h>
#include <windows.h>

int main() {
  int gd = DETECT, gm;

  initgraph(&gd, &gm, NULL);

  readimagefile("./assets/bpatrut.jpg", 100, 100, 300, 300);
  // sndPlaySound("./assets/smile.mp3", SND_ASYNC);
  PlaySound(TEXT("./assets/smile.wav"), NULL, SND_FILENAME);

  getch();
  closegraph();
  return (0);
}