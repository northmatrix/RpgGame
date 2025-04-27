#ifndef INCLUDE_INPUT
#define INCLUDE_INPUT
#include "camera.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_scancode.h>

SDL_AppResult handle_key_event(Camera *camera, float last_tick, int **tile,
                               SDL_Scancode scancode);
#endif // !INCLUDE_INPUT
