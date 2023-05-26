#ifndef GAME_PHYSICS_H
#define GAME_PHYSICS_H

#include "splashkit.h"
#include <math.h>

#define GRAVITY 0.3

#define BALL_MASS 2
#define PLAYER_MASS BALL_MASS*50
#define ELASTIC 0.8
#define NO_ELASTIC 0


struct object_data
{
    sprite _sprite;
    vector_2d velocity;
    float elasticity;
    float mass;
    float friction_coefficient;
};

/**
 * @brief  Sets the center of a given sprite to X,Y
 * 
 * @param object  sprite to modify
 * @param x       x - coordinate
 * @param y       y - coordinate
 */
void sprite_set_center(sprite &object, double x, double y);

/**
 * @brief  Checks if the sprite is in the air (above the ground level)
 * 
 * @param object   Object to analyse
 * @return true    Object not touching the floor
 * @return false   Object touching the floor
 */
bool in_the_air(const sprite &object);

/**
 * @brief  Keeps the given sprite inside the window boundaries
 * 
 * @param object  sprite to analyse
 */
void keep_sprite_within_screen(sprite &object);

/**
 * @brief  Apply physics to any object in the game
 * 
 * @param object  object to apply gravity
 */
void apply_physics(object_data &object);

/**
 * @brief  Handle collisions between two objects
 * 
 * @param ob1   object 1
 * @param ob2   object 2
 */
void handle_collisions(object_data ob1, object_data ob2);
#endif