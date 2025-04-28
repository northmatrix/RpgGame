#include "input.h"
#include "app_state.h"
#define SPEED 1
SDL_AppResult handle_key_event(Camera *camera, float deltatime, int **tile,
                               KeyState *key_state) {
  if (key_state->up) {
    camera->y += SPEED * deltatime;
  }
  if (key_state->left) {
    camera->x += SPEED * deltatime;
  }
  if (key_state->down) {
    camera->y -= SPEED * deltatime;
  }
  if (key_state->right) {
    camera->x -= SPEED * deltatime;
  }
  return SDL_APP_CONTINUE;
}

void update_key_state(KeyState *key_state, SDL_Scancode key_code,
                      int is_pressed) {
  if (key_code == SDL_SCANCODE_W) {
    SDL_Log("setting up key %d", is_pressed);
    key_state->up =
        is_pressed; // Set key state (whether it's being pressed or not)
  }
  if (key_code == SDL_SCANCODE_A) {
    key_state->left = is_pressed;
  }
  if (key_code == SDL_SCANCODE_S) {
    key_state->down = is_pressed;
  }
  if (key_code == SDL_SCANCODE_D) {
    key_state->right = is_pressed;
  }
}
