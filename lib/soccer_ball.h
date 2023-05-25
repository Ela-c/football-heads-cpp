#ifndef SOCCER_BALL_H
#define SOCCER_BALL_H

#include "game_physics.h"
#include "player.h"

struct soccer_ball_data
{
    sprite ball_sprite;
    point_2d center;
    double radius;
    double dx;
    double dy;
    vector_2d acceleration;
    double elasticity;
    double kinetic_friction_coefficient;
    double static_friction_coefficient;
};

soccer_ball_data new_ball();

void update_ball(soccer_ball_data &ball);


void draw_ball(const soccer_ball_data &ball);

#endif