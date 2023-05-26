#ifndef SOCCER_BALL_H
#define SOCCER_BALL_H

#include "game_physics.h"
#include "player.h"

#define BALL_SPEED 2

/**
 * @brief  Data structure representing the abstraction of the soccer ball
 * 
 * @field object                           The object of the ball used to manage the physics and sprite
 * @field center                           The center position of the soccer ball
 * @field radius                           The radius of the soccer ball
 */
struct soccer_ball_data
{                     
    object_data object;
    point_2d center;                         
    double radius;                            
};

/**
 * @brief Creates a new soccer ball with initial values and returns its data.
 * 
 * @return soccer_ball_data   initialized ball
 */
soccer_ball_data new_ball();

/**
 * @brief Updates the position and behavior of the soccer ball based on its current state
 * 
 * @param ball  ball to be updated
 */
void update_ball(soccer_ball_data &ball);

/**
 * @brief Draws the soccer ball on the screen
 * 
 * @param ball  ball to be drawn
 */
void draw_ball(const soccer_ball_data &ball);

#endif
