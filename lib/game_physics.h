#ifndef GAME_PHYSICS_H
#define GAME_PHYSICS_H

#include "splashkit.h"
#include <math.h>

#define WIDTH 800 //window width
#define HEIGHT 600 // window height
#define BALL_SPEED 2
#define GRAVITY 0.3

enum elasticity_type
{

};

void sprite_set_center(sprite &object, double x, double y);

bool in_the_air(const sprite &object);

void keep_sprite_within_screen(sprite &object);

#endif