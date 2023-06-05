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
    case BRAZIL:
        return bitmap_named("brazil_head");
    default:
        return bitmap_named("south_korea_head");
    }
}

/* --------------- END OF PRIVATE FUNCTIONS --------------- */

player_data new_player(unsigned short int id)
{
    player_data result;
    double player_x;

    // set player's id
    result.id = id;

    // set team and x coordinate of the player
    if (result.id == 1)
    {
        result.head = SOUTH_KOREA;
        player_x = screen_width() * 0.2;
    }
    else
    {
        result.head = BRAZIL;
        player_x = screen_width() * 0.8;
    }

    // create sprite according to selected character
    result.object._sprite = create_sprite(character_bitmap(result.head));

    // Position in the center of the screen
    sprite_set_x(result.object._sprite, player_x);
    sprite_set_y(result.object._sprite, screen_height());

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

void move_player(player_data &player)
{
    /* PLAYER 1 ------------------------ */
    if (player.id == 1)
    {
        // move player to the left
        if (key_down(A_KEY))
            sprite_set_dx(player.object._sprite, -1 * PLAYER_SPEED);
        else if (key_released(A_KEY))
            sprite_set_dx(player.object._sprite, 0);

        // move player to the right
        if (key_down(D_KEY))
            sprite_set_dx(player.object._sprite, PLAYER_SPEED);
        else if (key_released(D_KEY))
            sprite_set_dx(player.object._sprite, 0);

        // make player jump
        if (key_down(W_KEY) and not in_the_air(player.object._sprite))
            sprite_set_dy(player.object._sprite, -PLAYER_JUMP);
    }

    /* PLAYER 2 ------------------------ */
    if (player.id == 2)
    {
        // move player to the left
        if (key_down(LEFT_KEY))
            sprite_set_dx(player.object._sprite, -1 * PLAYER_SPEED);
        else if (key_released(LEFT_KEY))
            sprite_set_dx(player.object._sprite, 0);

        // move player to the right
        if (key_down(RIGHT_KEY))
            sprite_set_dx(player.object._sprite, PLAYER_SPEED);
        else if (key_released(RIGHT_KEY))
            sprite_set_dx(player.object._sprite, 0);

        // make player jump
        if (key_down(UP_KEY) and not in_the_air(player.object._sprite))
            sprite_set_dy(player.object._sprite, -PLAYER_JUMP);
    }
}