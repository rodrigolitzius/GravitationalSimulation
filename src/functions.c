#include <math.h>
#include <SDL2/SDL.h>
#include <stdio.h>

#include "definitions.h"

void initialize(SDL_Window** window, SDL_Renderer** renderer) {
	SDL_SetHint(SDL_HINT_VIDEODRIVER, "wayland,x11");

	// Initializing SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	// Creating window
	*window = SDL_CreateWindow(
		"Game",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		window_width,            window_height,
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

void handle_events() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) { running = false; }

		if (event.type == SDL_WINDOWEVENT) {
			if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
				window_width = event.window.data1;
				window_height = event.window.data2;
			}
		}

		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_p) {
				pause = !pause;
			}
		}
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

	for (int i=0; i < sides; i++) {
		SDL_Vertex point1 = {
			{
				pos.x, 
				pos.y
			}, color, {1, 1}
		};

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

		SDL_Vertex points[] = {point1, point2, point3};

		SDL_RenderGeometry(renderer, NULL, points, 3, NULL, 0);

		angle += angle_add;
	}

}

Vector2 gravity(Body body1, Body body2) {
	// Phytagorean theorem to get the distance from body1 to body2
	double x_distance = body2.position.x - body1.position.x;
	double y_distance = body2.position.y - body1.position.y;

	double distance = sqrt((x_distance * x_distance) + (y_distance * y_distance));

	// Newton's laws to get the acceleration
	double force = BIG_G * (body1.mass * body2.mass) / (distance*distance);
	double accel = force / body1.mass;

	// Triangle similarity to convert accel into accel_x and accel_y
	double accel_x = x_distance * accel / distance;
	double accel_y = y_distance * accel / distance;

	return (Vector2){accel_x, accel_y};
}

double get_distance(SDL_FPoint pos1, SDL_FPoint pos2) {
	return sqrt(
		pow((pos2.x - pos1.x), 2) + pow(pos2.y - pos1.y, 2)
	);
}

bool collision_circle(SDL_FPoint pos1, SDL_FPoint pos2, int radius1, int radius2) {
	return get_distance(pos1, pos2) <= radius1 + radius2;
}

void draw_background_grid(SDL_Renderer* renderer) {
	for (int i=0; i < window_width; i+=20) {
        SDL_RenderDrawLine(renderer, i, 0, i, window_height);
    }

	for (int i=0; i < window_width; i+=20) {
		SDL_RenderDrawLine(renderer, 0, i, window_width, i);
	}
}