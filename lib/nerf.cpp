#include "nerf.h"

/* -------------- PRIVATE FUNCTIONS --------------*/

/**
 * @brief  Converts nerf kind into a bitmap
 * 
 * @param kind      The kind of nerf you want the bitmap of
 * @return bitmap   The bitmap matching the nerf kind
 */
bitmap nerf_bitmap(const nerf_kind &kind)
{
    switch (kind)
    {
    case POISON:
        return bitmap_named("poison");
    default:
        return bitmap_named("poison");
    }
}

/* -------------- END OF PRIVATE FUNCTIONS --------------*/

nerf_data new_nerf(const nerf_kind &kind)
{
    nerf_data result;

    bitmap n_bitmap = nerf_bitmap(kind); // nerf bitmap
    /* initialize nerf object */

    result.kind = kind;

    // create nerf sprite
    result.object._sprite = create_sprite(n_bitmap);
    
    result.object.elasticity = ELASTIC;
    result.object.friction_coefficient = HAS_FRICTION;
    result.object.mass = BALL_MASS/2;

    result.object.velocity.x = 0;
    result.object.velocity.y = 0;
    sprite_set_velocity(result.object._sprite, result.object.velocity);

    // set nerf kind
    result.kind = POISON;

    // set position of nerf
    sprite_set_y(result.object._sprite, 0);
    sprite_set_x(result.object._sprite, rnd(0, screen_width() - sprite_width(result.object._sprite)));

    return result;
}

void update_nerf(nerf_data &nerf)
{
    update_sprite(nerf.object._sprite);

    // update velocity variable
    nerf.object.velocity = sprite_velocity(nerf.object._sprite);

    //apply physics
    apply_physics(nerf.object);
}


void draw_nerf(const nerf_data &nerf)
{
    draw_sprite(nerf.object._sprite);
}