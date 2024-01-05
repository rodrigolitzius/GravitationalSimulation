#ifndef SCROLLER
#define SCROLLER

#include "SDL2/SDL.h"

typedef struct {
    SDL_FPoint draw_offset; double scale;
} View;

View* get_view();
void move_view(SDL_MouseMotionEvent motion);
void change_view_scale(SDL_MouseWheelEvent wheel);

#endif