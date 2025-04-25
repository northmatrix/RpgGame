#include <SDL3/SDL_events.h>
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
#define UNIT 32
#define UNIT_WDITH SCREEN_WIDTH / UNIT
#define UNIT_HEIGHT SCREEN_HEIGHT / UNIT

typedef struct {
  float x;
  float y;
  int id;
} Tile;

typedef struct {
  Tile grid[UNIT_HEIGHT][256];
} TileMap;

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  TileMap tilemap;
  uint64_t last_step;
} AppState;

void map_init(TileMap *map) {
  for (int y = 0; y < UNIT_HEIGHT; y++) {
    for (int x = 0; x < UNIT_WDITH; x++) {
      Tile tile = {x * UNIT, y * UNIT, 0};
      map->grid[y][x] = tile;
    }
  }
}

int load_map(const char *filename, TileMap *map) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("Could not open file");
    return 1;
  }

  char line[512];
  int y = 0;

  while (fgets(line, sizeof(line), file) && y < UNIT_HEIGHT) {
    int x = 0;
    char *token = strtok(line, ",");

    while (token && x < UNIT_WDITH) {
      map->grid[y][x].id = atoi(token);
      token = strtok(NULL, ",");
      x++;
    }

    y++;
  }

  fclose(file);
  return 0;
}

void draw_map(TileMap *map, SDL_Renderer *renderer) {
  for (int y = 0; y < UNIT_HEIGHT; y++) {
    for (int x = 0; x < UNIT_WDITH; x++) {
      Tile tile = map->grid[y][x];
      if (tile.id == 1) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_FRect square = {tile.x, tile.y, UNIT, UNIT};
        SDL_RenderFillRect(renderer, &square);
      }
    }
  }
}

void draw_player(float x, float y, SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 25, 25, 255, 255);
  SDL_FRect square = {x, y, UNIT, UNIT * 2}; // x, y, width, height
  SDL_RenderFillRect(renderer, &square);
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

SDL_AppResult handle_key_event(TileMap *tilemap, SDL_Scancode key_code) {
  if (key_code == SDL_SCANCODE_W) {
  }
  if (key_code == SDL_SCANCODE_A) {
    for (int y = 0; y < UNIT_HEIGHT; y++) {
      for (int x = 0; x < UNIT_WDITH; x++) {
        tilemap->grid[y][x].x -= 16.0f;
      }
    }
  }
  if (key_code == SDL_SCANCODE_S) {
  }
  if (key_code == SDL_SCANCODE_D) {
    for (int y = 0; y < UNIT_HEIGHT; y++) {
      for (int x = 0; x < UNIT_WDITH; x++) {
        tilemap->grid[y][x].x += 16.0f;
      }
    }
  }
  return SDL_APP_CONTINUE;
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

  // load and set the tilemap
  map_init(&as->tilemap);
  load_map("map.csv", &as->tilemap);

  SDL_SetRenderDrawColor(as->renderer, 0, 0, 0, 255);
  SDL_RenderClear(as->renderer);
  SDL_RenderPresent(as->renderer);

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  AppState *as = appstate;
  SDL_SetRenderDrawColor(as->renderer, 0, 0, 0, 255);
  SDL_RenderClear(as->renderer);
  draw_map(&as->tilemap, as->renderer);
  SDL_RenderPresent(as->renderer);
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  AppState *as = appstate;
  switch (event->type) {
  case SDL_EVENT_QUIT:
    return SDL_APP_SUCCESS;
  case SDL_EVENT_KEY_DOWN:
    return handle_key_event(&as->tilemap, event->key.scancode);
  }
  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  /* SDL will clean up the window/renderer for us. */
}
