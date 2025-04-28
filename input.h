#ifndef INCLUDE_INPUT
#define INCLUDE_INPUT
#include "app_state.h"
#include "camera.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_scancode.h>

SDL_AppResult handle_key_event(Camera *camera, float last_tick, int **tile,
                               KeyState *key_state);

void update_key_state(KeyState *key_state, SDL_Scancode key_code,
                      int is_pressed);
#endif // !INCLUDE_INPUT
