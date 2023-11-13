#include "definitions.h"
#include "functions.h"
#include "body.h"
#include <SDL2/SDL.h>

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

void update_bodies() {
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

void draw_bodies(SDL_Renderer* renderer) {
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