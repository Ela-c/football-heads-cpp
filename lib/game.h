#ifndef GAME_H
#define GAME_H

#include "soccer_ball.h"
//#include "boot/soccer_boot.h"
#include "player.h"

#define NUMBER_OF_PLAYERS 2
#define PLAYER_SPEED 5

enum state_option
{
    PLAYER_1_WIN,
    PLAYER_2_WIN,
    DRAW,
    ACTIVE
};

struct game_data
{
    player_data players[NUMBER_OF_PLAYERS];
    soccer_ball_data ball;
};

game_data new_game();

void update_game(game_data &game);

void draw_game(game_data &game);

void load_resources();

void handle_input(player_data players[]);



#endif