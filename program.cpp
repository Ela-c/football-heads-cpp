#include "splashkit.h"
#include "lib/game.h"
#include <iostream>

using namespace std;

// next step, handle collisions between different sprites
int main()
{
    open_window("Ball Collision", WIDTH, HEIGHT);
    load_resources();

    soccer_ball_data ball = new_ball();

    int size = 70;

    while (!quit_requested())
    {
        process_events(); // for the quit_requested thing
        clear_screen(COLOR_WHITE);

        update_ball(ball);
        fill_rectangle(COLOR_GREEN, WIDTH/2 - size/2, HEIGHT/2 - size/2, size, size);
        draw_ball(ball);

        refresh_screen(60);
    }

    close_window("Ball Collision");
    return 0;
}
