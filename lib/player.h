#ifndef PLAYER_H
#define PLAYER_H

#include "game_physics.h"
//#include "../boot/soccer_boot.h"

enum head_options
{
    BARCELONA,
    REAL
};

struct player_data
{
    unsigned short int side;
    head_options head;
    unsigned int score;
    sprite player_sprite;
    vector_2d velocity;
    vector_2d acceleration;
};

player_data new_player();

void update_player(player_data &player_to_update);

void draw_player(player_data &player);

#endif