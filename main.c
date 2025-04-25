#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 640
#define PIXEL 32
#define PIXEL_P_WIDTH SCREEN_WIDTH / PIXEL
#define PIXEL_P_HEIGHT SCREEN_HEIGHT / PIXEL

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  uint64_t last_step;
} AppState;

typedef struct {
  int grid[PIXEL_P_HEIGHT][PIXEL_P_WIDTH];
} Map;

void map_init(Map *map) {
  for (int y = 0; y < PIXEL_P_HEIGHT; y++) {
    for (int x = 0; x < PIXEL_P_WIDTH; x++) {
      map->grid[y][x] = 0;
    }
  }
}

int load_map_from_csv(const char *filename, Map *map) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("Could not open file");
    return 0;
  }

  char line[512]; // Increase buffer for wide maps
  int y = 0;

  while (fgets(line, sizeof(line), file) && y < PIXEL_P_HEIGHT) {
    int x = 0;
    char *token = strtok(line, ",");

    while (token && x < PIXEL_P_WIDTH) {
      map->grid[y][x] = atoi(token);
      token = strtok(NULL, ",");
      x++;
    }

    y++;
  }

  fclose(file);
  return 1;
}

void draw_map(Map *map, SDL_Renderer *renderer) {
  for (int y = 0; y < PIXEL_P_HEIGHT; y++) {
    for (int x = 0; x < PIXEL_P_WIDTH; x++) {
      if (map->grid[y][x] == 1) {
        SDL_SetRenderDrawColor(renderer, 255, 25, 25, 255); // RED
        SDL_FRect square = {x * PIXEL, y * PIXEL, PIXEL,
                            PIXEL}; // x, y, width, height
        SDL_RenderFillRect(renderer, &square);
      }
    }
  }
}

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
  if (!SDL_CreateWindowAndRenderer("Day Zero", SCREEN_WIDTH, SCREEN_HEIGHT, 0,
                                   &as->window, &as->renderer)) {
    SDL_Log("Couldn't initialize Window or Renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  // Set the last_step and load the window Icon
  as->last_step = SDL_GetTicks();
  LoadAndSetBMP(as->window);

  Map map;
  map_init(&map);
  load_map_from_csv("map.csv", &map);
  draw_map(&map, as->renderer);
  printf("%d", PIXEL_P_HEIGHT);
  printf("%d", PIXEL_P_WIDTH);
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
