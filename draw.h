#pragma once
#include <windows.h>

PAINTSTRUCT ps;
HBRUSH hBGBrush = CreateSolidBrush(RGB(0, 0, 0));
RECT clientRect;

HPEN hPen = CreatePen(PS_SOLID, 1, RGB(69, 69, 69));
HBRUSH hBrush = CreateSolidBrush(RGB(138, 43, 226));