#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

#include "definitions.h"
#include "view.h"

View view = {{0, 0}, 1};

View* get_view() {
    return &view;
}

void move_view(SDL_MouseMotionEvent motion) {
    view.draw_offset.x += motion.xrel / view.scale;
    view.draw_offset.y += motion.yrel / view.scale;
}

void change_view_scale(SDL_MouseWheelEvent wheel) {
    view.scale += wheel.y * 0.05;
    if (view.scale < 0) {
        view.scale = 0;
    }
}