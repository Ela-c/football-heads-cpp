#ifndef PLAYER_H
#define PLAYER_H

#include "game_physics.h"
//#include "../boot/soccer_boot.h"

enum team_options
{
    BARCELONA,
    REAL
};


struct boot_data
{
    sprite boot_sprite;
    double rotation;
};

struct player_data
{
    int side;
    team_options team;
    int score;
    sprite player_sprite;
    vector_2d velocity;
    vector_2d acceleration;
    boot_data boot;
};

player_data new_player(int player_side);

boot_data new_boot(const player_data &player);

void draw_player(player_data &player);

#endif