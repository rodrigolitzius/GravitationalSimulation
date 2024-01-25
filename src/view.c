#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>

#include "definitions.h"
#include "view.h"

View view = {{0, 0}, 1};

View* get_view() {
    return &view;
}

void view_set_draw_offset(SDL_FPoint draw_offset) {
    view.draw_offset = draw_offset;
}

void view_set_scale(double scale) {
    view.scale = scale;
}

void view_change_draw_offset(SDL_FPoint change) {
    view.draw_offset.x += (change.x / view.scale) * SCROLL_SPEED;
    view.draw_offset.y += (change.y / view.scale) * SCROLL_SPEED;
}

void view_change_scale(double sign) {
    view.scale += (view.scale / 50) * sign;

    if (view.scale < 0) {
        view.scale = 0;
    }
}