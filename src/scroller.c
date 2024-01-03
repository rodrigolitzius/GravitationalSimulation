#include <SDL2/SDL.h>

#include "definitions.h"

double scroll_speed = 8;
SDL_FPoint position_modifiers = {0, 0};
SDL_FPoint mouse_click_position;

SDL_FPoint get_scrolling() {
    return position_modifiers;
}

void scroll_right() {
    position_modifiers.x -= scroll_speed;
}

void scroll_left() {
    position_modifiers.x += scroll_speed;
}

void scroll_up() {
    position_modifiers.y += scroll_speed;
}

void scroll_down() {
    position_modifiers.y -= scroll_speed;
}