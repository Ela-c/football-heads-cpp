#include "game.h"

void load_resources()
{
    load_resource_bundle("game_bundle", "football_heads.txt");
}

void handle_input(player_data players[])
{
     // Allow player to move forward or backwards by holding the up/down keys - Movement happens only when the key is pressed
    
    // move player 1

    // move to the left
    if(key_down(A_KEY))
        sprite_set_dx(players[0].player_sprite, -1*PLAYER_SPEED);
    else if(key_released(A_KEY))
        sprite_set_dx(players[0].player_sprite, 0);
    // move to the right
    if(key_down(D_KEY))
        sprite_set_dx(players[0].player_sprite, PLAYER_SPEED);
    else if(key_released(D_KEY))
        sprite_set_dx(players[0].player_sprite, 0);

    // jump player 1
    if(key_down(W_KEY))
        sprite_set_dy(players[0].player_sprite, PLAYER_SPEED);
    // kick player 1
    if(key_down(K_KEY))
    {
        // kick
    }
    else if(key_released(K_KEY))
    {
        // RETURN foot to normal position
    }
    
    
    // move player 2
    if(key_down(LEFT_KEY))
        sprite_set_dx(players[1].player_sprite, PLAYER_SPEED);
    else if(key_released(LEFT_KEY))
        sprite_set_dx(players[1].player_sprite, 0);
    
    if(key_down(RIGHT_KEY))
        sprite_set_dx(players[1].player_sprite, -1*PLAYER_SPEED);
    else if(key_released(RIGHT_KEY))
        sprite_set_dx(players[1].player_sprite, 0);
    
    // jump player 2
    if(key_down(UP_KEY))
        sprite_set_dy(players[1].player_sprite, PLAYER_SPEED);
    
    // kick player 2
    if(key_down(K_KEY))
    {
        // kick
    }
    else if(key_released(K_KEY))
    {
        // RETURN foot to normal position
    }
    
}