#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "functions.h"
#include "definitions.h"

bool running = true;
bool pause = false;

Uint64 frames_elapsed = 0;

Body body_list[] = {
    {
        {0, 0}, {0, 0},
        {WINDOW_CENTER}, 30, 10000000, {ORANGE}, 0
    }, // Sun

    {
        {0, 0}, {6, 0},
        {WINDOW_X_CENTER, 60}, 20, 1, {DARK_BLUE}, 0
    }, // Higher orbit

    {
        {0, 0}, {0, 11.5},
        {(WINDOW_X_CENTER + 70), WINDOW_Y_CENTER}, 10, 1, {BROWN}, 0
    }, // Lower orbit

    {
        {0, 0}, {-7, 0},
        {WINDOW_X_CENTER, 170}, 15, 1, {BLUE}, 0
    }, // Middle orbit
};

int body_count = sizeof(body_list) / sizeof(Body);

void update() {
    for (int primary=0; primary < body_count; primary++) {
        // If this body is marked as immovable, skip it
        if (body_list[primary].flags & IMMOVABLE) { continue; }

        // Stores the acceleration of primary body after it's calculation
        Vector2 calculated_accel = {0, 0};

        // Calculating the gravitaional attraction every other
        // body (Secondary bodies) exerts on primary body
        for (int secondary=0; secondary < body_count; secondary++) {
            // Do not let a body exert a force on itself
            if (primary == secondary) { continue; } 

            Vector2 temp_struct = gravity(body_list[primary], body_list[secondary]);

            calculated_accel.x += temp_struct.x;
            calculated_accel.y += temp_struct.y;
        }

        // Updating acceleration, velocity and position
        body_list[primary].accel = calculated_accel;

        body_list[primary].velocity.x += body_list[primary].accel.x;
        body_list[primary].velocity.y += body_list[primary].accel.y;

        body_list[primary].position.x += body_list[primary].velocity.x;
        body_list[primary].position.y += body_list[primary].velocity.y;
    }
}

void draw(SDL_Renderer* renderer) {
    // Drawing grid
    SDL_SetRenderDrawColor(renderer, GRID_COLOR);
    draw_background_grid(renderer);

    // Drawing Bodies
    for (int i=0; i < body_count; i++) {
        // If this body is marked as invisble, don't draw it
        if (body_list[i].flags & INVISIBLE) { continue; }

        SDL_SetRenderDrawColor(renderer, 
            body_list[i].color.r, body_list[i].color.g,
            body_list[i].color.b, body_list[i].color.a
        );

        draw_polygon(renderer, body_list[i].position, body_list[i].size, body_list[i].size);
    }
}

int main() {
    // Creating window and renderer
    SDL_Window* window;
    SDL_Renderer* renderer;

    initialize(&window, &renderer); 

    // Variables used within the game loop
    Uint64 frame_start=0, frame_end=0, current_frame_time=0;
    Uint64 frame_time_sum=0;
    Uint64 frequency = SDL_GetPerformanceFrequency();

    ///// Main Loop /////
    while (running) {
        frame_start = SDL_GetPerformanceCounter();

        handle_events();

        if (pause) { continue; }

        ///////////////////////////////////
        ///////////////////////////////////
        ///////////////////////////////////

        update();
        draw(renderer);

        // Updating window
		SDL_RenderPresent(renderer);

        // Clearing window
		SDL_SetRenderDrawColor(renderer, BACKGROUND_COLOR);
		SDL_RenderClear(renderer);

        ///////////////////////////////////
        ///////////////////////////////////
        ///////////////////////////////////

        frames_elapsed++;
        frame_end = SDL_GetPerformanceCounter();

        current_frame_time = frame_end - frame_start;
        current_frame_time += limit_fps(current_frame_time, frequency);

        frame_time_sum += current_frame_time;

        // Printing the average FPS over a period of PRINT_FPS_DELAY_FRAMES frames
        if (frames_elapsed % PRINT_FPS_DELAY_FRAMES == 0) {
            printf("%f\n", 1 / ((double) frame_time_sum / PRINT_FPS_DELAY_FRAMES / frequency));

            frame_time_sum = 0;
        }
    }

    // Quitting
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return EXIT_SUCCESS;
}