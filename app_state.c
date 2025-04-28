#include "app_state.h"
#include "constants.h"
#include "level.h"
#include "util.h"
#include <stdlib.h>

AppState *AppState_Init() {
  // initialized SDL VIDEO
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return NULL;
  }
  // Create and allocate space  for the AppState
  AppState *as = (AppState *)SDL_calloc(1, sizeof(AppState));
  if (!as) {
    return NULL;
  }
  // Create the window and the renderer
  if (!SDL_CreateWindowAndRenderer("Day Zero", SCREEN_WIDTH, SCREEN_HEIGHT, 0,
                                   &as->window, &as->renderer)) {
    SDL_Log("Couldn't initialize Window or Renderer: %s", SDL_GetError());
    return NULL;
  }
  set_icon(as->window);
  // Set the last_step and load the window Icon
  as->lastTick = SDL_GetTicks();
  as->rows = 0;
  as->cols = 0;
  as->map = load_csv("map.csv", &as->rows, &as->cols);
  as->camera = init_camera(as->cols, as->rows);
  KeyState key_state;
  key_state.down = 0;
  key_state.left = 0;
  key_state.right = 0;
  key_state.up = 0;
  as->key_state = key_state;
  return as;
}

void AppState_Free(AppState *as) {
  free(as->camera);
  for (int i = 0; i < as->rows; i++) {
    free(as->map[i]);
  }
  free(as->map);
}
