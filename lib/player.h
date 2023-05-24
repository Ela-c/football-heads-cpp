#ifndef PLAYER_H
#define PLAYER_H

#include "game_physics.h"

enum team_options
{
    BARCELONA,
    REAL
};

struct player_data
{
    int id;
    team_options team;
    int score;
    sprite player_sprite;
    vector_2d velocity;
    vector_2d acceleration;
};

#endif