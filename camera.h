#ifndef INCLUDE_CAMERA

#include <SDL3/SDL.h>

typedef struct {
  float x, y;
  int w, h;
} Camera;

Camera *init_camera(int screen_width, int screen_height);
void draw_world(Camera *camera, SDL_Renderer *renderer, int **map);

#endif // !INCLUDE_CAMERA
