#ifndef INCLUDE_APP_STATE
#define INCLUDE_APP_STATE
#include "camera.h"
#include <SDL3/SDL.h>

typedef struct {
  int up, down, left, right;
} KeyState;

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  int **map;
  int rows;
  int cols;
  Camera *camera;
  float lastTick;
  float deltaTime;
  float player_x;
  float player_y;
  KeyState key_state;
} AppState;

AppState *AppState_Init(void);
void AppState_Free(AppState *as);

#endif // !APP_STATE
