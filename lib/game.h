#ifndef GAME_H
#define GAME_H

#include "soccer_ball.h"
#include "player.h"
#include "goal.h"
#include "nerf.h"

#define WIN_SCORE 5
#define BIG_FONT_SIZE 100

// Enumerates the posible game status
enum game_status
{
    PLAYER_WIN,
    GAME_OVER,
    ACTIVE
};


/**
 * @brief game data structure meant to keep track of the game entities
 * 
 * @field player        keeps track of player data
 * @field ball          keeps track of the soccer ball data
 * @field goal          keeps track of the goal
 * @field nerf_list     keeps track of all the nerf entities created in the game
 * @field status        keeps track of the current game status
 */
struct game_data
{
    player_data player;
    soccer_ball_data ball;
    goal_data goal;
    vector<nerf_data> nerf_list;
    game_status status;
};

/**
 * @brief Creates and initializes a new game_data object.
 * 
 * @return game_data  created game
 */
game_data new_game();

/**
 * @brief Updates the current game state and the properties of the player, soccer ball, and goal.
 * 
 * @param game  game to update
 */
void update_game(game_data &game);

/**
 * @brief  Draws the current game state to the screen based on the provided game_data object. Draws the player, soccer ball, and goal.
 * 
 * @param game  game to draw
 */
void draw_game(game_data &game);

/**
 * @brief Loads any required game resources, such as images, sounds, or other assets needed for the game
 * 
 */
void load_resources();

/**
 * @brief  Displays the corresponding screen based on the game outcome (i.e player wins or game over).
 * 
 * @param game  current game data structure
 */
void handle_game_outcome(const game_data &game);

/**
 * @brief Handles input for the player in the game. This function listens for keyboard events and updates the player's state accordingly.
 * 
 * @param player  player being handled
 */
void handle_input(player_data player);

#endif