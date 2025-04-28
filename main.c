#include <stdint.h>
#define SDL_MAIN_USE_CALLBACKS 1

#include "app_state.h"
#include "input.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>

SDL_AppResult SDL_AppInit(void **appstate, int arg, char *argv[]) {
  AppState *as = AppState_Init();
  if (!as)
    return SDL_APP_FAILURE;
  *appstate = as;
  SDL_Log("Init Finished");
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  AppState *as = appstate;
  uint32_t currenttick = SDL_GetTicks();
  as->deltaTime = (currenttick - as->lastTick) / 1000.0f;
  if (as->deltaTime < 0.016f) {
    as->deltaTime = 0.016f; // 60 FPS (approximately)
  }
  as->lastTick = currenttick;
  SDL_SetRenderDrawColor(as->renderer, 25, 25, 25, 255);
  SDL_RenderClear(as->renderer);
  handle_key_event(as->camera, as->deltaTime, as->map, &as->key_state);
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
    update_key_state(&as->key_state, event->key.scancode, 1);
    break;
  case SDL_EVENT_KEY_UP:
    update_key_state(&as->key_state, event->key.scancode, 0);
    break;
  }
  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  AppState *as = appstate;
  AppState_Free(as);
}
