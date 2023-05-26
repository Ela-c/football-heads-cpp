#include "splashkit.h"
#include "lib/game.h"
#include <iostream>

#define WIDTH 800 // Window width
#define HEIGHT 600 // Window height

using namespace std;

int main()
{
    open_window("Ball Collision", WIDTH, HEIGHT);
    load_resources(); // Loads any required game resources

    game_data game = new_game(); // Creates a new game_data object

    while (!quit_requested())
    {
        process_events(); // Processes any pending events
        handle_input(game.player); // Handles input for the player in the game
        update_game(game); // Updates the game state based on the current input and logic
        draw_game(game); // Draws the current game state to the screen
    }

    close_window("Ball Collision");
    return 0; // Indicates successful program execution
}
