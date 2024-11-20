#include <stdio.h>
#include <stdlib.h>

#include "logic.h"
#include "constants.h"



void render(int* grid, HWND hwnd) {

   Sleep(UPDATE_RATE_MS);

   int newGrid[GRID_X][GRID_Y];

   for (int y = 0; y < GRID_Y; ++y) {
      for (int x = 0; x < GRID_X; ++x) {

         int aliveNeighbors = 0;

         for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {

               if (i == 0 && j == 0) continue;

               int newX = x + j;
               int newY = y + i;

               if (newX >= 0 && newX < GRID_X && newY >= 0 && newY < GRID_Y) {
                  if (grid[newY * GRID_X + newX]) {
                     ++aliveNeighbors;
                  }
               }
            }
         }
         if (grid[y * GRID_X + x]) {
            if (aliveNeighbors == 2 || aliveNeighbors == 3) {
               newGrid[y][x] = 1;
            } else {
               newGrid[y][x] = 0;
            }
         }
         else {
            if (aliveNeighbors == 3) {
               newGrid[y][x] = 1;
            } else {
               newGrid[y][x] = 0;
            }
         }
      }
   }

   for (int y = 0; y < GRID_Y; ++y) {
      for (int x = 0; x < GRID_X; ++x) {
         grid[y * GRID_X + x] = newGrid[y][x];
      }
   }

   InvalidateRect(hwnd, NULL, FALSE);
}



void draw(const int* grid, const HWND* hwnd, const HBRUSH* hBrush) {

   PAINTSTRUCT ps;
   HDC hdc_l = BeginPaint(*hwnd, &ps);

   HBRUSH hBGBrush = CreateSolidBrush(RGB(0, 0, 0));
   RECT clientRect;

   GetClientRect(*hwnd, &clientRect);
   FillRect(hdc_l, &clientRect, hBGBrush);
   DeleteObject(hBGBrush);

   for(int y = 0; y < GRID_X; y++) {
      for(int x = 0; x < GRID_Y; x++) {
         if (grid[x * GRID_Y + y]) {
            RECT cellRect = { x * CELL_SIZE, y * CELL_SIZE, (x + 1) * CELL_SIZE, (y + 1) * CELL_SIZE };
            FillRect(hdc_l, &cellRect, *hBrush);
         }
      }
   }

   HPEN hPen = CreatePen(PS_SOLID, 1, RGB(69, 69, 69));
   HPEN hOldPen = (HPEN)SelectObject(hdc_l, hPen);

   for(int x = 0; x <= SCREEN_WIDTH; x += CELL_SIZE) {
      MoveToEx(hdc_l, x, 0, NULL);
      LineTo(hdc_l, x, SCREEN_HEIGHT);
   }

   for(int y = 0; y <= SCREEN_HEIGHT; y += CELL_SIZE) {
      MoveToEx(hdc_l, 0, y, NULL);
      LineTo(hdc_l, SCREEN_WIDTH, y);
   }

   SelectObject(hdc_l, hOldPen);
   DeleteObject(hPen);
   EndPaint(*hwnd, &ps);
}



void gameInput(game_state* g_state) {

   if (GetKeyState(VK_SPACE) == 1) {
      *g_state = RUNNING_MODE;
   }

   if (GetKeyState(VK_SPACE) == 0) {
      *g_state = INSERT_MODE;
   }
}



void leftButtonTrigger(int* grid, const HWND* hwnd, const LPARAM* lParam,const game_state* g_state) {

   if (*g_state != INSERT_MODE) {return;}

   int x = LOWORD(*lParam) / CELL_SIZE;
   int y = HIWORD(*lParam) / CELL_SIZE;

   if (x >= 0 && x < GRID_X && y >= 0 && y < GRID_Y) {
      grid[y + x*GRID_X] = !grid[y + x*GRID_X];
      InvalidateRect(*hwnd, NULL, FALSE);
   }
}



void clearGrid(int* grid) {
   for (int x = 0; x < GRID_X; x++) {
      for (int y = 0; y < GRID_Y; y++) {
         grid[x*GRID_X + y] = 0;
      }
   }
}



void saveGrid(int* grid, const char* filename) {

   FILE* file = fopen(filename, "w");

   if (file == NULL) {
      perror("Failed to open file");
      return;
   }

   for (int i = 0; i < GRID_X; i++) {
      for (int j = 0; j < GRID_Y; j++) {
         fprintf(file, "%d ", grid[j*GRID_X + i]);
      }
      fprintf(file, "\n");
   }

   fclose(file);
}



void loadGrid(int* grid, const char* filename) {

      FILE* file = fopen(filename, "r");

      if (file == NULL) {
         perror("Failed to open file");
         return;
      }

      for (int x = 0; x < GRID_X; x++) {
         for (int y = 0; y < GRID_Y; y++) {
            if (fscanf_s(file, "%d", &grid[y*GRID_X + x]) != 1) {
               fprintf(stderr, "Error reading grid value at position (%d, %d)\n", x, y);
               fclose(file);
               return;
            }
         }
      }

      fclose(file);
}



void keyFunctions(int* grid, const HWND* hWnd, const WPARAM *wParam, const game_state *g_state) {

   if (*g_state != INSERT_MODE) {return;}

   switch (*wParam) {
      case 'C': {
         clearGrid(grid);
         InvalidateRect(*hWnd, NULL, TRUE);
         break;
      }
      case 'S': {
         saveGrid(grid, "./game.txt");
         break;
      }
      case 'L': {
         loadGrid(grid, "./game.txt");
         InvalidateRect(*hWnd, NULL, TRUE);
         break;
      }
      default:
         break;
   }
}
