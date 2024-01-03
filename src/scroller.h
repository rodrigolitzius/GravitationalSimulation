#ifndef SCROLLER
#define SCROLLER

#include "SDL2/SDL.h"

SDL_FPoint get_scroll();
void scroll_mouse(SDL_MouseMotionEvent motion);

#endif