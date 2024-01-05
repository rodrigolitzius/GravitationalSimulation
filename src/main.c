#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "functions.h"
#include "event-handler.h"
#include "definitions.h"
#include "body.h"
#include "view.h"

bool running = true;
bool pause = false;

Uint64 frames_elapsed = 0;

void update() {
    update_bodies();
}

void draw(SDL_Renderer* renderer, View* view) {
    SDL_SetRenderDrawColor(renderer, GRID_COLOR);
    draw_background_grid(renderer);

    draw_bodies(renderer, view);
}

int main() {
    // Creating window and renderer
    SDL_Window* window;
    SDL_Renderer* renderer;

    initialize(&window, &renderer);
    View* view = get_view();

    // Registering event callbacks
    register_callback((event_handler_callback){SDL_KEYDOWN, &on_keydown});
    register_callback((event_handler_callback){SDL_MOUSEMOTION, &on_mouse_motion});
    register_callback((event_handler_callback){SDL_MOUSEBUTTONUP, &on_mouseup});
    register_callback((event_handler_callback){SDL_MOUSEWHEEL, &on_mousewheel});

    // Variables used within the game loop
    Uint64 frame_start=0, frame_end=0, frame_time=0;
    Uint64 frame_time_sum=0;
    Uint64 frequency = SDL_GetPerformanceFrequency();

    ///// Main Loop /////
    while (running) {
        frame_start = SDL_GetPerformanceCounter();

        // Clearing window
        SDL_SetRenderDrawColor(renderer, BACKGROUND_COLOR);
        SDL_RenderClear(renderer);

        handle_events();

        ///////////////////////////////////
        ///////////////////////////////////
        ///////////////////////////////////

        if (!pause) {
            update();
        }

        draw(renderer, view);

        // Updating window
        SDL_RenderPresent(renderer);

        ///////////////////////////////////
        ///////////////////////////////////
        ///////////////////////////////////

        frames_elapsed++;
        frame_end = SDL_GetPerformanceCounter();

        frame_time = frame_end - frame_start;
        frame_time += limit_fps(frame_time, frequency);

        frame_time_sum += frame_time;

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