# Razboi in 8

### Prerequisites

- `Windows 10`
- `MinGW`
- `graphics.h`
- `GNU Make` Optional

# Instructions

1. Open a cmd inside `RAZBOI IN 8`
2. If you don't have have Make run :

   `g++ -o bin/release/main src/\*.cpp -std=c++17 -O3 -Wall -I include -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32 -lwinmm -lm && .\bin\release\main`

3. If you have have Make run :

   `make release`

## Overview

Razboi in 8 is a simple 2D game made in C++ using the graphics.h library.

Two people take part in the game, each of whom aimed to get the opposing armed fight out. The game can end with the victory of one of the players, or undecided - the draw.

This is the final project for the "Introduction to Programming" course (year I, semester I) from university.

## Authors

- Alexandru Cretu
- Razvan Iftimoaia

# Screenshots

<img src="https://raw.githubusercontent.com/Axellben/RAZBOI-IN-8/main/Screenshots/gameplay.png" width="98.5%">

<img src="https://raw.githubusercontent.com/Axellben/RAZBOI-IN-8/main/Screenshots/menu.png" width="49%"> <img src="https://raw.githubusercontent.com/Axellben/RAZBOI-IN-8/main/Screenshots/dokter_wins.png" width="49%">
