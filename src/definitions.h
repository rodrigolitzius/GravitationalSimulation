#ifndef DEFINITIONS
#define DEFINITIONS

#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <stdbool.h>

#define MAX_FPS 60
#define PRINT_FPS_DELAY_FRAMES 180
#define BIG_G 0.001

#define PI 3.14159265358979323846

#define WINDOW_CENTER window_width/2.0f,window_height/2.0f
#define WINDOW_X_CENTER window_width/2.0f
#define WINDOW_Y_CENTER window_height/2.0f

#define BACKGROUND_COLOR 0,0,0,255
#define GRID_COLOR 20,20,20,255

#define WHITE 255,255,255,255
#define BLACK 0,0,0,255
#define GRAY 50,50,50,255

#define ORANGE 253,213,0,255
#define BROWN 106,89,0,255
#define DARK_BLUE 0,33,113,255

#define RED 255,0,0,255
#define GREEN 0,255,0,255
#define BLUE 0,0,255,255

typedef struct { double x, y; } Vector2;
typedef struct { Vector2 velocity; Vector2 accel; SDL_FPoint position; int size; double mass; SDL_Color color; } Body;

extern int window_width;
extern int window_height;

extern Uint64 frames_elapsed;

extern bool running;
extern bool pause;

#endif