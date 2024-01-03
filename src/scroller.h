#ifndef SCROLLER
#define SCROLLER

#include "SDL2/SDL.h"

SDL_FPoint get_scrolling();
void scroll_right();
void scroll_left();
void scroll_up();
void scroll_down();

#endif