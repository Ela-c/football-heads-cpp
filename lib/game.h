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
    player_data player[NUMBER_OF_PLAYERS];
    soccer_ball_data ball;
};

void load_resources();

void handle_input();

#endif