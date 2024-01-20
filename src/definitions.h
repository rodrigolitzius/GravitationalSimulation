#ifndef DEFINITIONS
#define DEFINITIONS

#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <stdbool.h>

#define PROGRAM_NAME "Gravitational Simulation"
#define MAX_FPS 60

#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 700
#define WINDOW_X_CENTER WINDOW_WIDTH/2.0f
#define WINDOW_Y_CENTER WINDOW_HEIGHT/2.0f
#define WINDOW_CENTER WINDOW_X_CENTER,WINDOW_Y_CENTER

#define UNUSED(x) (void)(x)

#define PRINT_FPS_DELAY_FRAMES MAX_FPS
#define GRID_SPACING_PIXELS 20
#define SCROLL_SPEED 0.333333333

// CAREFUL. 
// If you set this value too high and zoom out too much
// the program will start to use too much memory to render 
// the lines and your computer might freeze.
// 150 is the recommended value
#define GRID_LINES_LIMIT 150

#define BACKGROUND_COLOR 0,0,0,255
#define GRID_COLOR 20,20,20,255

#define BIG_G 0.001
#define PI 3.14159265358979323846

#define WHITE 255,255,255,255
#define BLACK 0,0,0,255
#define RED 255,0,0,255
#define GREEN 0,255,0,255
#define BLUE 0,0,255,255

#define GRAY 50,50,50,255

#define ORANGE 253,213,0,255
#define BROWN 106,89,0,255
#define DARK_BLUE 0,33,113,255

typedef struct { double x, y; } Vector2;

extern bool running;
extern bool pause;

#endif