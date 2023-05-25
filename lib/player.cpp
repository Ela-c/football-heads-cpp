#include "player.h"

#define DEFAULT_HEAD BARCELONA

bitmap team_bitmap(head_options team)
{
    switch (team)
    {
    case BARCELONA:
        return bitmap_named("south_korea_head");
    default:
        return bitmap_named("south_korea_head");
    }
}

player_data new_player()
{
    player_data result;

    // set team to default option
    result.head = DEFAULT_HEAD;
    // create sprite according to selected team
    result.player_sprite = create_sprite(team_bitmap(result.head));

    // Position in the center of the screen
    sprite_set_x(result.player_sprite, (screen_width() - sprite_width(result.player_sprite))/2.0);
    sprite_set_y(result.player_sprite, (screen_height()));

    // player begins with zero score
    result.score = 0;
    
    // set velocity
    result.velocity.x = 0;
    result.velocity.y = 0;

    // set acceleration
    result.acceleration.x = 0;
    result.acceleration.y = 0;

    return result;
}

void apply_gravity_to_player(player_data &player)
{
    if (in_the_air(player.player_sprite))
    {
        player.velocity.y += GRAVITY;
    }
    // if the player is on the floor.
    else
    {
        sprite_set_y(player.player_sprite, HEIGHT - sprite_height(player.player_sprite));
        player.velocity.y = 0;
    }
    sprite_set_dy(player.player_sprite, player.velocity.y);
}

void update_player(player_data &player_to_update)
{
    // move the player
    update_sprite(player_to_update.player_sprite);
    
    player_to_update.velocity.x = sprite_dx(player_to_update.player_sprite);
    player_to_update.velocity.y = sprite_dy(player_to_update.player_sprite);

    keep_sprite_within_screen(player_to_update.player_sprite);

    // apply gravity to the player when jumping
    apply_gravity_to_player(player_to_update);
}

void draw_player(player_data &player)
{
    draw_sprite(player.player_sprite);
    return;
}