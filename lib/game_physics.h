#ifndef GAME_PHYSICS_H
#define GAME_PHYSICS_H

#include "splashkit.h"
#include <math.h>

#define WIDTH 800 //window width
#define HEIGHT 600 // window height
#define BALL_SPEED 2
#define GRAVITY 0.3

#define BALL_MASS 2
#define PLAYER_MASS 200

// con un 10% de probabilidad, aplica aire a la bola, es decir aplicale una pequeña velocidad en x 
// elige izquierda or derecha aleatoriamente

enum elasticity_type
{

};

void sprite_set_center(sprite &object, double x, double y);

bool in_the_air(const sprite &object);

void keep_sprite_within_screen(sprite &object);

void handle_collisions(sprite s1, sprite s2);

#endif