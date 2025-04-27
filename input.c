#include "input.h"
#define SPEED 50
SDL_AppResult handle_key_event(Camera *camera, float deltatime, int **tile,
                               SDL_Scancode key_code) {
  if (key_code == SDL_SCANCODE_W) {
    camera->y -= SPEED * deltatime;
  }
  if (key_code == SDL_SCANCODE_A) {
    camera->x -= SPEED * deltatime;
  }
  if (key_code == SDL_SCANCODE_S) {
    camera->y += SPEED * deltatime;
  }
  if (key_code == SDL_SCANCODE_D) {
    camera->x += SPEED * deltatime;
  }
  return SDL_APP_CONTINUE;
}
