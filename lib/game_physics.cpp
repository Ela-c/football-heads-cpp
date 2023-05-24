#include "game_physics.h"

void sprite_set_center(sprite &object, double x, double y)
{
    int width = sprite_width(object);
    int height = sprite_height(object);

    sprite_set_x(object, x - width/2);
    sprite_set_y(object, y - height/2);

    return;
}