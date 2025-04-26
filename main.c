#define SDL_MAIN_USE_CALLBACKS 1

#include "app_state.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <stdlib.h>

SDL_AppResult handle_key_event(Camera *camera, int **tile,
                               SDL_Scancode key_code) {
  if (key_code == SDL_SCANCODE_W) {
  }
  if (key_code == SDL_SCANCODE_A) {
    camera->x -= 5.0f;
  }
  if (key_code == SDL_SCANCODE_S) {
  }
  if (key_code == SDL_SCANCODE_D) {
    camera->x += 5.0f;
  }
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppInit(void **appstate, int arg, char *argv[]) {
  AppState *as = AppState_Init();
  if (!as)
    return SDL_APP_FAILURE;
  *appstate = as;
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  AppState *as = appstate;
  SDL_SetRenderDrawColor(as->renderer, 25, 25, 25, 255);
  SDL_RenderClear(as->renderer);
  draw_world(as->camera, as->renderer, as->map);
  SDL_RenderPresent(as->renderer);
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  AppState *as = appstate;
  switch (event->type) {
  case SDL_EVENT_QUIT:
    return SDL_APP_SUCCESS;
  case SDL_EVENT_KEY_DOWN:
    return handle_key_event(as->camera, as->map, event->key.scancode);
  }
  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  AppState *as = appstate;
  free(as->camera);
  for (int i = 0; i < as->rows; i++) {
    free(as->map[i]);
  }
  free(as->map);
}
