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
    // Reallocates memory to hold another event handler callback function
    callbacks = realloc(callbacks, sizeof(event_handler_callback)*(callbacks_length+1));
    callbacks_length += 1;

    callbacks[callbacks_length-1] = handler;
}

void handle_events() {
    SDL_Event event;

    // Polling events and calling their associated callback functions
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

    // Pauses the game
    if (event.key.keysym.sym == SDLK_p) { pause = !pause; }

    // Center view
    if (event.key.keysym.sym == SDLK_c) {
        view_set_draw_offset((SDL_FPoint){VIEW_INITIAL_X_OFFSET, VIEW_INITIAL_Y_OFFSET});
        view_set_scale(VIEW_INITIAL_SCALE);
    }
}

void on_mouseup(SDL_Event event, void* data) {
    UNUSED(event);
    UNUSED(data);

    // Ungrabs mouse
    SDL_SetRelativeMouseMode(SDL_FALSE);
}

void on_mousewheel(SDL_Event event, void* data) {
    UNUSED(data);

    // Zooms/unzooms according to mouse wheel movement
    view_change_scale(event.wheel.y);
}

void on_mouse_motion(SDL_Event event, void* data) {
    UNUSED(data);

    if (event.motion.state & SDL_BUTTON(3)) {
        // Grabs mouse
        SDL_SetRelativeMouseMode(SDL_TRUE);

        // Changes the view according to mouse movement
        view_change_draw_offset((SDL_FPoint){event.motion.xrel, event.motion.yrel});
    }
}