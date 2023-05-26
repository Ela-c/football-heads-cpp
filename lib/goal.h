#ifndef GOAL_H
#define GOAL_H

#include "game_physics.h"

struct goal_data
{
    rectangle goal_area;
    int status;
};


goal_data new_goal();

void update_goal(goal_data &goal);

void draw_goal(const goal_data &goal);

#endif