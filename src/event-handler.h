#ifndef EVENT_HANDLER
#define EVENT_HANDLER

#include <SDL2/SDL.h>

typedef void event_handler(SDL_Event event, void* data);
typedef struct {
    unsigned int event_id;
    event_handler* handler;
} event_handler_callback;

void initialize_event_handler();
void register_callback(event_handler_callback handler);
void handle_events();

void on_keydown(SDL_Event event, void* data);
void on_mouse_motion(SDL_Event event, void* data);

#endif