#pragma once

#include <windows.h>

typedef enum {
   DEAD = 0,
   ALIVE = 1
} Cell;

typedef enum {
   END_PLS = 0,
   INSERT_MODE = 1,
   RUNNING_MODE = 2
} game_state;

void render(int* grid, HWND hwnd);

void draw(const int* grid, const HWND* hwnd, const HBRUSH* hBrush);

void game_input(game_state* g_state);

void leftButtonTrigger(int* grid, const HWND* hwnd, const LPARAM* lParam,const  game_state* g_state);

void clearGrid(int* grid,const  game_state* g_state);