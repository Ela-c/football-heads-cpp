#ifndef PLAYER_H
#define PLAYER_H

#include "game_physics.h"

#define PLAYER_JUMP 10
#define PLAYER_SPEED 5

enum head_options
{
    SOUTH_KOREA,
    BRAZIL
};

/**
 * @brief  data structure to manage player's data
 *
 * @field id       id of the player
 * @field object   the object of the player used to manage the physics and sprite
 * @field head     The selected head option for the player
 * @field score    The player's score
 */
struct player_data
{
    unsigned short int id;
    object_data object;
    head_options head;
    unsigned int score;
};

/**
 * @brief  Creates a new player with initial values and returns its data
 *
 * @return player_data  new player
 */
player_data new_player(unsigned short int id);

/**
 * @brief Updates the position and behavior of the player based on its current state
 *
 * @param player_to_update  player to update
 */
void update_player(player_data &player_to_update);

/**
 * @brief Draws the player on the screen
 *
 * @param player player to draw
 */
void draw_player(player_data &player);

void move_player(player_data &player);

#endif