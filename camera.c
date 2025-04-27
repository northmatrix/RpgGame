#include "camera.h"
#include "constants.h"
#include <SDL3/SDL_render.h>
#include <stdlib.h>

int toTrimetricX(int i, int j) {
  return (i - j) * UNIT / 2; // Skewing based on grid position
}

int toTrimetricY(int i, int j) {
  return (i + j) * UNIT / 4;
  // Skewing based on grid position (no height `k` involved)
}

Camera *init_camera(int screen_width, int screen_height) {
  Camera *camera = malloc(sizeof(Camera));
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
        int nx = 1 + x + camera->x;
        int ny = 1 + y + camera->y;
        int tnx = toTrimetricX(nx, ny);
        int tny = toTrimetricY(nx, ny);
        // Define the vertices of the rhombus
        // Define the size of the rhombus based on UNIT
        int halfWidth = UNIT / 2;
        int halfHeight = UNIT / 4;

        // Define the vertices of the rhombus (diamond)
        SDL_FPoint vertices[4] = {
            {tnx, tny - halfHeight}, // Top vertex
            {tnx + halfWidth, tny},  // Right vertex
            {tnx, tny + halfHeight}, // Bottom vertex
            {tnx - halfWidth, tny}   // Left vertex
        };

        // Set the draw color (e.g., red)
        SDL_SetRenderDrawColor(renderer, 255, 25, 25, 255);

        // Manually draw the polygon by connecting the vertices
        for (int i = 0; i < 4; i++) {
          int next = (i + 1) %
                     4; // To close the polygon (wrap around to the first point)
          SDL_RenderLine(renderer, vertices[i].x, vertices[i].y,
                         vertices[next].x, vertices[next].y);
        }
      } else if (map[y][x] == 2) {
        SDL_SetRenderDrawColor(renderer, 25, 25, 255, 255);
        int nx = x + camera->x;
        int ny = y + camera->y;
        int tnx = toTrimetricX(nx, ny);
        int tny = toTrimetricY(nx, ny);
        SDL_FRect square = {tnx, tny, UNIT, UNIT};
        SDL_RenderFillRect(renderer, &square);
      }
    }
  }
}
