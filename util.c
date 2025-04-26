#include <SDL3/SDL.h>

int set_icon(SDL_Window *window) {
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
