#ifndef GOAL_H
#define GOAL_H

#include "game_physics.h"

/**
 * @brief  data structure to manage the goal data
 * 
 * @field goal_area  The rectangle object representing the goal  
 * @field status     value can be either 1 or 0. If the ball collides with the goal, the status is 1, otherwise is 0
 */
struct goal_data
{
    rectangle goal_area;
    unsigned short int status;
};

/**
 * @brief  create and initialize a new soccer goal
 * 
 * @return goal_data  the new soccer goal
 */
goal_data new_goal();

/**
 * @brief  Update the goal properties based on the current goal status
 * 
 * @param goal  goal to update
 */
void update_goal(goal_data &goal);

/**
 * @brief  Draw goal on the screen
 * 
 * @param goal  goal to be drawn
 */
void draw_goal(const goal_data &goal);

#endif