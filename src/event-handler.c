#include <SDL2/SDL_events.h>
#include <stdio.h>
#include <stdlib.h>

#include "event-handler.h"
#include "definitions.h"
#include "view.h"

event_handler_callback* callbacks;
int callbacks_length = 0;

void register_callback(event_handler_callback handler) {
    printf("%d\n", callbacks_length+1);

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
    if (event.key.keysym.sym == SDLK_p) { pause = !pause; }
}

void on_mouseup(SDL_Event event, void* data) {
    SDL_SetRelativeMouseMode(SDL_FALSE);
}

void on_mousewheel(SDL_Event event, void* data) {
    change_view_scale(event.wheel);
}

void on_mouse_motion(SDL_Event event, void* data) {
    if (event.motion.state & SDL_BUTTON(3)) {
        SDL_SetRelativeMouseMode(SDL_TRUE);
        move_view(event.motion);
    }
}