#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <stdio.h>
#include <stdlib.h>

#include "event-handler.h"
#include "definitions.h"
#include "view.h"

event_handler_callback* callbacks;
int callbacks_length = 0;

void register_callback(event_handler_callback handler) {
    callbacks = realloc(callbacks, sizeof(event_handler_callback)*(callbacks_length+1));
    callbacks_length += 1;

    callbacks[callbacks_length-1] = handler;
}

void handle_events() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) { running = false; }

        for (int i = 0; i < callbacks_length; i++) {
            if (callbacks[i].event_id == event.type) {
                callbacks[i].handler(event, NULL);
            }
        }
    }
}

////// On event //////
void on_keydown(SDL_Event event, void* data) {
    UNUSED(data);
    if (event.key.keysym.sym == SDLK_p) { pause = !pause; }

    if (event.key.keysym.sym == SDLK_c) {
        set_view((SDL_FPoint){0, 0});
        set_view_scale(1);
    }
}

void on_mouseup(SDL_Event event, void* data) {
    UNUSED(event);
    UNUSED(data);
    SDL_SetRelativeMouseMode(SDL_FALSE);
}

void on_mousewheel(SDL_Event event, void* data) {
    UNUSED(data);
    change_view_scale(event.wheel.y);
}

void on_mouse_motion(SDL_Event event, void* data) {
    UNUSED(data);
    if (event.motion.state & SDL_BUTTON(3)) {
        SDL_SetRelativeMouseMode(SDL_TRUE);
        change_view((SDL_FPoint){event.motion.xrel, event.motion.yrel});
    }
}