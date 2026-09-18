// windows.h, just the part Razboi in 8 uses (see bgi.cpp).
#pragma once

#include <limits.h>
#include <stddef.h>

#define RGB(r, g, b) ((r) | ((g) << 8) | ((b) << 16))
#define WM_LBUTTONDOWN 0x0201

// Only "play <file>" and "close <file>".
int mciSendStringA(const char* command, char* ret, int retLen, void* callback);
