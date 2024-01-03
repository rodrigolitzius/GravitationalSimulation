#include <stdio.h>
#include <stdlib.h>

#include "event-handler.h"
#include "definitions.h"
#include "scroller.h"

event_handler_callback* callbacks;
int callbacks_length = 0;

void initialize_event_handler() {
    callbacks = malloc(callbacks_length);
}

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

void on_mouse_motion(SDL_Event event, void* data) {
    if (event.motion.state & SDL_BUTTON(1)) {
        scroll_mouse(event.motion);
    }
}