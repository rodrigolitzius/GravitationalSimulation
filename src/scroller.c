#include <SDL2/SDL.h>

#include "definitions.h"

SDL_FPoint position_modifiers = {0, 0};
SDL_FPoint mouse_click_position;

SDL_FPoint get_scroll() {
    return position_modifiers;
}

void scroll_mouse(SDL_MouseMotionEvent motion) {
    position_modifiers.x += motion.xrel;
    position_modifiers.y += motion.yrel;
}