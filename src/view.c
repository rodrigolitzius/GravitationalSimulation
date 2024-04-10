#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>

#include "definitions.h"
#include "view.h"

View view = {
    {VIEW_INITIAL_X_OFFSET, VIEW_INITIAL_Y_OFFSET},
    VIEW_INITIAL_SCALE
};

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
    view.draw_offset.x += (change.x / view.scale) * CAMERA_SPEED;
    view.draw_offset.y += (change.y / view.scale) * CAMERA_SPEED;
}

void view_change_scale(double sign) {
    view.scale += (view.scale * VIEW_SCALE_MULTIPLIER) * sign;

    if (view.scale < 0) {
        view.scale = 0;
    }
}