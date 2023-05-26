#ifndef NERF_H
#define NERF_H

#include "game_physics.h"

// enumeration of all the kind of nerfs available
enum nerf_kind
{
    POISON
};

/**
 * @brief Data sctruct that keeps track of all the information related to a nerf object
 * 
 * @field object  the object of the nerf used to manage the physics and sprite
 * @field kind    Kind of nerf
 */
struct nerf_data
{
    object_data object;
    nerf_kind kind;
};

/**
 * @brief Creates a new nerf of the specified kind at a random location at the top of the screen
 * 
 * @param kind          kind of nerf to be created
 * @return nerf_data    the new nerf data
 */
nerf_data new_nerf(const nerf_kind &kind);

/**
 * @brief  Updates the nerf sprite and velocity variable
 * 
 * @param nerf  the nerf being updated
 */
void update_nerf(nerf_data &nerf);

/**
 * @brief  Draws the nerf to the screen
 * 
 * @param nerf  The nerf to be drawn
 */
void draw_nerf(const nerf_data &nerf);

#endif