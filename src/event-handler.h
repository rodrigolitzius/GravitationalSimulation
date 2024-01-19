#ifndef EVENT_HANDLER
#define EVENT_HANDLER

#include <SDL2/SDL.h>

// Information about how to handle an event, such as handler function pointer and event id
typedef void event_handler(SDL_Event event, void* data);
typedef struct {
    unsigned int event_id;
    event_handler* handler;
} event_handler_callback;

// Associates a handler function to an event
void register_callback(event_handler_callback handler);

// Calls every event's associated handler function
void handle_events();

void on_keydown(SDL_Event event, void* data);
void on_mouseup(SDL_Event event, void* data);
void on_mouse_motion(SDL_Event event, void* data);
void on_mousewheel(SDL_Event event, void* data);

#endif