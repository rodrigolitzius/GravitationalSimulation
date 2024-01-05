#ifndef SCROLLER
#define SCROLLER

#include "SDL2/SDL.h"

typedef struct {
    SDL_FPoint draw_offset; double scale;
} View;

View* get_view();
void set_view(SDL_FPoint draw_offset);
void set_view_scale(double scale);
void change_view(SDL_FPoint change);
void change_view_scale(double change);

#endif