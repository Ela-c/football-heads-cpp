#include "player.h"

#define DEFAULT_TEAM BARCELONA

bitmap team_bitmap(team_options team)
{
    switch (team)
    {
    case BARCELONA:
        return bitmap_named("south_korea_head");
    default:
        return bitmap_named("south_korea_head");
    }
}

player_data new_player(unsigned short int player_side)
{
    player_data result;

    // set the side of the player
    result.side = player_side;

    // set team to default option
    result.team = DEFAULT_TEAM;
    // create sprite according to selected team
    result.player_sprite = create_sprite(team_bitmap(result.team));

    // Position in the center of the screen
    sprite_set_x(result.player_sprite, (screen_width() - sprite_width(result.player_sprite))/2.0);
    sprite_set_y(result.player_sprite, (screen_height() - sprite_height(result.player_sprite))/2.0);

    // set the foot of the player depending in which side is the player
    result.boot = new_boot(result);

    // each player begins with zero score
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
    draw_sprite(player.boot.boot_sprite);
    draw_sprite(player.player_sprite);
    return;
}

boot_data new_boot(const player_data &player)
{
    boot_data result;
    point_2d anchor_point;
    if(player.side == 1) // left side
        result.boot_sprite = create_sprite(bitmap_named("boot_player_1"));
    else if (player.side == 2) // right side
        result.boot_sprite = create_sprite(bitmap_named("boot_player_2"));

    // set roation to zero
    result.rotation = 0;

    // anchor the boot to the player
    anchor_point = center_point(player.player_sprite);
    sprite_set_anchor_point(result.boot_sprite, anchor_point);

    // set position of the boot
    sprite_set_y(result.boot_sprite, sprite_y(player.player_sprite)+ sprite_width(player.player_sprite) - 8);
    sprite_set_center(result.boot_sprite, center_point(player.player_sprite).x, center_point(result.boot_sprite).y);

    return result;
}