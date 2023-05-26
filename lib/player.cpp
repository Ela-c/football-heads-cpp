#include "player.h"

#define DEFAULT_HEAD SOUTH_KOREA


/* --------------- PRIVATE FUNCTIONS --------------- */

/**
 * @brief Converts head options into their respective bitmaps
 * 
 * @param head       Head of the choosen character
 * @return bitmap    bitmap that matches the type of character
 */
bitmap character_bitmap(head_options head)
{
    switch (head)
    {
    case SOUTH_KOREA:
        return bitmap_named("south_korea_head");
    default:
        return bitmap_named("south_korea_head");
    }
}

/* --------------- END OF PRIVATE FUNCTIONS --------------- */

player_data new_player()
{
    player_data result;

    // set team to default option
    result.head = DEFAULT_HEAD;
    // create sprite according to selected character
    result.object._sprite = create_sprite(character_bitmap(result.head));

    // Position in the center of the screen
    sprite_set_x(result.object._sprite, (screen_width() - sprite_width(result.object._sprite))/2.0);
    sprite_set_y(result.object._sprite, (screen_height()));

    // player begins with zero score
    result.score = 0;
    
    // set object.velocity
    result.object.velocity.x = 0;
    result.object.velocity.y = 0;

    // set object elasticity
    result.object.elasticity = NO_ELASTIC;

    // set object mass
    result.object.mass = PLAYER_MASS;

    // set object friction
    result.object.friction_coefficient = NO_FRICTION; // no friction is applied to the player

    return result;
}

void update_player(player_data &player_to_update)
{
    // move the player
    update_sprite(player_to_update.object._sprite);
    
    // update velocity variable 
    player_to_update.object.velocity = sprite_velocity(player_to_update.object._sprite);
    
    // apply gravity to the player when jumping
    apply_physics(player_to_update.object);
}

void draw_player(player_data &player)
{
    draw_sprite(player.object._sprite);
    return;
}