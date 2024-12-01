#pragma once

#include <windows.h>

typedef enum {
   DEAD = 0,
   ALIVE = 1
} Cell;

typedef enum {
   FIRST = 0,
   SECOND = 1,
   THIRD = 2
} config_file;

typedef enum {
   END_PLS = 0,
   INSERT_MODE = 1,
   RUNNING_MODE = 2
} game_state;

void render(int* grid, HWND hwnd);

void draw(const int* grid, const HWND* hwnd, const HBRUSH* hBrush);

void leftButtonTrigger(int* grid, const HWND* hwnd, const LPARAM* lParam,const  game_state* g_state);

void clearGrid(int* grid);

void saveGrid(int* grid, const char* filename);

void loadGrid(int* grid, const char* filename);

void keyFunctions(int* grid, const HWND* hWnd, const WPARAM* wParam, game_state* g_state, config_file* config);