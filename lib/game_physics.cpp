#include "game_physics.h"

void sprite_set_center(sprite &object, double x, double y)
{
    int width = sprite_width(object);
    int height = sprite_height(object);

    sprite_set_x(object, x - width/2);
    sprite_set_y(object, y - height/2);

    return;
}

bool in_the_air(const sprite &object)
{
    if(sprite_y(object) < screen_height() - sprite_height(object))
    {
        // sprite is in the air
        return true;
    }
    return false;
}

void keep_sprite_within_screen(sprite &object)
{
    if(sprite_x(object) < 0)
    {
        sprite_set_x(object, 0);
    }
    else if(sprite_x(object) > screen_width() - sprite_width(object))
    {
        sprite_set_x(object, screen_width() - sprite_width(object));
    }

    if(sprite_y(object) < 0)
    {
        sprite_set_y(object, 0);
    }
    else if(sprite_y(object) > screen_height() - sprite_height(object))
    {
        sprite_set_y(object, screen_height() - sprite_height(object));
    }
}
