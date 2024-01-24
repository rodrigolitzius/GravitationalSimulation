#ifndef SCROLLER
#define SCROLLER

#include "SDL2/SDL.h"

typedef struct {
    SDL_FPoint draw_offset; double scale;
} View;

View* get_view();
void view_set_draw_offset(SDL_FPoint draw_offset);
void view_set_scale(double scale);
void view_change_draw_offset(SDL_FPoint change);
void view_change_scale(double change);

#endif