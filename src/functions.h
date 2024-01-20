#ifndef FUNCTIONS
#define FUNCTIONS

#include "stdbool.h"
#include "definitions.h"
#include "view.h"

// Initializes essential SDL stuff, like a window and a renderer
void initialize(SDL_Window** window, SDL_Renderer** renderer);

// Handles SDL events
void handle_events();

// Limits the FPS to a maximum of MAX_FPS.
// Returns how much the function waited (in frequency units) in order to perform exactly that
Uint64 limit_fps(Uint64 frame_time, Uint64 frequency);

// Draws polygons with any number of sides
void draw_polygon(SDL_Renderer* renderer, SDL_FPoint pos, int radius, int sides);

// Get the distance between pos1 and pos2
double get_distance(SDL_FPoint pos1, SDL_FPoint pos2);

// Returns whether two circles are colliding
bool collision_circle(SDL_FPoint pos1, SDL_FPoint pos2, int radius1, int radius2);

// Draws the background grid
void draw_background_grid(SDL_Renderer* renderer, View* view);

#endif