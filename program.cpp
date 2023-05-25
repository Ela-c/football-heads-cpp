#include "splashkit.h"
#include "lib/game.h"
#include <iostream>

using namespace std;

// next step, handle collisions between different sprites
int main()
{
    open_window("Ball Collision", WIDTH, HEIGHT);
    load_resources();

    game_data game = new_game();

    while (!quit_requested())
    {
        process_events(); // for the quit_requested thing
        handle_input(game.player);
        update_game(game);
        draw_game(game);
    }

    close_window("Ball Collision");
    return 0;
}
