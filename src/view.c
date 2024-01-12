#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>

#include "definitions.h"
#include "view.h"

View view = {{0, 0}, 1};

View* get_view() {
    return &view;
}

void set_view(SDL_FPoint draw_offset) {
    view.draw_offset = draw_offset;
}

void set_view_scale(double scale) {
    view.scale = scale;
}

void change_view(SDL_FPoint change) {
    view.draw_offset.x += (change.x / view.scale) * SCROLL_SPEED;
    view.draw_offset.y += (change.y / view.scale) * SCROLL_SPEED;
}

void change_view_scale(double change) {
    view.scale += change * 0.05;
    if (view.scale < 0) {
        view.scale = 0;
    }
}