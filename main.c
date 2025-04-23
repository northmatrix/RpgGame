#include <SDL3/SDL_video.h>
#define SDL_MAIN_USE_CALLBACKS 1
#define SDL_WINDOW_WDITH 80U
#define SDL_WINDOW_HEIGHT 25U

#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  uint64_t last_step;
} AppState;

int LoadAndSetBMP(SDL_Window *window) {
  SDL_Surface *icon = SDL_LoadBMP("radiation.bmp");
  if (!icon) {
    SDL_Log("Couldn't get icon");
    return 1;
  }
  SDL_SetWindowIcon(window, icon);
  SDL_DestroySurface(icon);
  icon = NULL;
  return 0;
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  // initialized SDL VIDEO
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  // Create and allocate space  for the AppState
  AppState *as = (AppState *)SDL_calloc(1, sizeof(AppState));
  if (!as) {
    return SDL_APP_FAILURE;
  }
  *appstate = as;

  // Create the window and the renderer
  if (!SDL_CreateWindowAndRenderer("Day Zero", 640, 480, 0, &as->window,
                                   &as->renderer)) {
    SDL_Log("Couldn't initialize Window or Renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  // Set the last_step and load the window Icon
  as->last_step = SDL_GetTicks();
  LoadAndSetBMP(as->window);

  // Clear the screen and fill it with the color #262626
  SDL_SetRenderDrawColor(as->renderer, 25, 25, 25, 255);
  SDL_RenderClear(as->renderer);
  SDL_RenderPresent(as->renderer);
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) { return SDL_APP_CONTINUE; }

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  switch (event->type) {
  case SDL_EVENT_QUIT:
    return SDL_APP_SUCCESS;
  }
  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  /* SDL will clean up the window/renderer for us. */
}
