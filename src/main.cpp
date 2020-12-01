#include <graphics.h>
#include <math.h>

int main() {
  int gd = DETECT, gm;

  initgraph(&gd, &gm, NULL);

  readimagefile("./assets/bpatrut.jpg", 100, 100, 300, 300);

  getch();
  closegraph();
  return (0);
}