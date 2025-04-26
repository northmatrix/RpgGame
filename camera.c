#include "camera.h"
#include "constants.h"
#include <stdlib.h>

Camera *init_camera(int screen_width, int screen_height) {
  Camera *camera = malloc(sizeof(Camera *));
  camera->x = 0;
  camera->y = 0;
  camera->w = screen_width;
  camera->h = screen_height;
  return camera;
}

void draw_world(Camera *camera, SDL_Renderer *renderer, int **map) {
  for (int y = 0; y < camera->h; y++) {
    for (int x = 0; x < camera->w; x++) {
      if (map[y][x] == 1) {
        SDL_SetRenderDrawColor(renderer, 255, 25, 25, 255);
        SDL_FRect square = {(x * UNIT) + camera->x, (y * UNIT) + camera->y,
                            UNIT, UNIT};
        SDL_RenderFillRect(renderer, &square);
      }
    }
  }
}
