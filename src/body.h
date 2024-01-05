#ifndef BODY
#define BODY

#include <SDL2/SDL.h>

#include "definitions.h"
#include "view.h"

typedef struct { Vector2 accel; Vector2 velocity; SDL_FPoint position; int size; double mass; SDL_Color color; unsigned int flags; } Body;

enum BodyFlags {
    IMMOVABLE = 1 << 0,
    INVISIBLE = 1 << 1,
};

// Return the acceleration exerted on body1 by body2
Vector2 gravity(Body body1, Body body2);

// Update all bodies
void update_bodies();

// Draw all bodies
void draw_bodies(SDL_Renderer* renderer, View* view);

#endif