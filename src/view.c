#include <SDL2/SDL.h>

#include "definitions.h"
#include "view.h"

View view = {
    {VIEW_INITIAL_X_OFFSET, VIEW_INITIAL_Y_OFFSET},
    VIEW_INITIAL_SCALE
};

View* get_view() {
    return &view;
}

void view_set_draw_offset(SDL_FPoint draw_offset) {
    view.draw_offset = draw_offset;
}

void view_set_scale(double scale) {
    view.scale = scale;
}

void view_change_draw_offset(SDL_FPoint change) {
    view.draw_offset.x += (change.x / view.scale) * CAMERA_SPEED;
    view.draw_offset.y += (change.y / view.scale) * CAMERA_SPEED;
}

void view_change_scale(double sign) {
    view.scale += (view.scale * VIEW_SCALE_MULTIPLIER) * sign;

    if (view.scale < 0) {
        view.scale = 0;
    }
}

SDL_FPoint apply_view(SDL_FPoint position, View* view) {
    // The problem: When you zoomed out, the scale would get closer and closer to 0,
    // And since i was multiplying the position by the scale, the bodies positions would also 
    // get closer to 0. Since in SDL the origin (0, 0) is at the topleft corner, all bodies  
    // would approach the corner until they disappeared, which was quite annoying.

    // The fix: Set a limit to where the positions can be when the scale is 0. This is what this code does.
    // The behaviour this achieves is that, when the scale is 0, all the positions will be at the
    // center of the window. When it's 1 they will not change. If it's >1 they will get farther from their
    // original value going AWAY from the center. Since the scale is at all times >=0 this never allows
    // for the position to be at (0, 0) and makes the zoom center point the center of the screen.

    // Longest comment i've ever written
    position.x = WINDOW_X_CENTER + ((position.x + view->draw_offset.x) - WINDOW_X_CENTER) * view->scale;
    position.y = WINDOW_Y_CENTER + ((position.y + view->draw_offset.y) - WINDOW_Y_CENTER) * view->scale;
    
    return position;
}