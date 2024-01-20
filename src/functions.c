#include <SDL2/SDL_render.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <stdio.h>

#include "definitions.h"
#include "view.h"

void initialize(SDL_Window** window, SDL_Renderer** renderer) {
    SDL_SetHint(SDL_HINT_VIDEODRIVER, "wayland,x11");

    // Initializing SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Creating window
    *window = SDL_CreateWindow(
        PROGRAM_NAME,
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH,            WINDOW_HEIGHT,
        0
    );

    // Checking if the window was created correctly
    if (!*window) {
        fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Creating renderer
    *renderer = SDL_CreateRenderer(*window, -1, 0);

    if (!*renderer) {
        fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

Uint64 limit_fps(Uint64 frame_time, Uint64 frequency) {
    double target_framerate = (double) frequency / MAX_FPS;
    double wait_time = target_framerate - frame_time;
    double wait_time_ms = wait_time / frequency * 1000;

    if (frame_time < target_framerate) {
        SDL_Delay(wait_time_ms);
    }

    if (wait_time <= 0) {
        return 0;
    }

    return wait_time;
}

void draw_polygon(SDL_Renderer* renderer, SDL_FPoint pos, int radius, int sides) {
    SDL_Color color;
    SDL_GetRenderDrawColor(renderer, &color.r, &color.g, &color.b, &color.a);

    double angle = 0;
    double angle_add = (2*PI)/sides;

    SDL_Vertex center_point = {
        {
            pos.x, 
            pos.y
        }, color, {1, 1}
    };

    for (int i=0; i < sides; i++) {
        SDL_Vertex point2 = {
            {
                (cos(angle)*radius)+pos.x, 
                (sin(angle)*radius)+pos.y
            }, color, {1,1}
        };

        SDL_Vertex point3 = {
            {
                (cos(angle+angle_add)*radius)+pos.x,
                (sin(angle+angle_add)*radius)+pos.y
            }, color, {1,1}
        };

        SDL_Vertex points[] = {center_point, point2, point3};

        SDL_RenderGeometry(renderer, NULL, points, 3, NULL, 0);

        angle += angle_add;
    }

}

double get_distance(SDL_FPoint pos1, SDL_FPoint pos2) {
    return sqrt(
        pow((pos2.x - pos1.x), 2) + pow(pos2.y - pos1.y, 2)
    );
}

bool collision_circle(SDL_FPoint pos1, SDL_FPoint pos2, int radius1, int radius2) {
    return get_distance(pos1, pos2) <= radius1 + radius2;
}

void draw_background_grid(SDL_Renderer* renderer, View* view) {
    const int lines_limit = 150;

    double spacing = (double) GRID_SPACING_PIXELS * view->scale;
    double horizontal_limit = (WINDOW_HEIGHT + spacing);
    double vertical_limit = (WINDOW_WIDTH + spacing);
    double x_draw_offset = (view->draw_offset.x * view->scale);
    double y_draw_offset = (view->draw_offset.y * view->scale);

    ///// Prevents crash /////
    if ((vertical_limit / spacing) >= lines_limit) {
        spacing = vertical_limit / lines_limit;
    }

    if ((horizontal_limit / spacing) >= lines_limit) {
        spacing = vertical_limit / lines_limit;
    }

    double line_draw_offset;

    ///// Vertical Lines /////
    line_draw_offset = fmod(x_draw_offset, spacing);

    for (int i=0; i < vertical_limit; i += spacing) {
        for (int k=0; k < WINDOW_HEIGHT; k++) {
            SDL_RenderDrawPoint(renderer, line_draw_offset+i, k);
        }
    }

    SDL_SetRenderDrawColor(renderer, RED);
    ///// Horizontal Lines /////
    line_draw_offset = fmod(y_draw_offset, spacing);

    for (int i=0; i < horizontal_limit; i += spacing) {
        for (int k=0; k < WINDOW_WIDTH; k++) {
            SDL_RenderDrawPoint(renderer, k, line_draw_offset+i);
        }
    }
}