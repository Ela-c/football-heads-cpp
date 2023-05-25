#include "game.h"
#include <math.h>
#include <string>

using namespace std;

#define MAX_SCORE 100

void load_resources()
{
    load_resource_bundle("game_bundle", "football_heads.txt");
}

string make_score(const player_data &player)
{
    if (player.score >= 100)
    {
        return "00";
    }

    if(player.score < 10)
    {
        return "0" + to_string(player.score);
    }
    else
    {
        return to_string(player.score);
    }
}

void draw_score(const game_data &game)
{
    // has to be a rectangle with two smaller rectangles 1 to each of the sides representing the score of
    // player one and player two
    rectangle score_screen, score_player_1, score_player_2;
    int font_size=14, text_w, text_h;
    double score_player_w, score_player_h, offset_x, offset_y;
    string text_p1, text_p2;

    // set properties of the screen where the score will appear
    score_screen.height = 100;
    score_screen.width = 400;
    score_screen.x = screen_width()/2 - score_screen.width/2;
    score_screen.y = 10;

    score_player_h = score_screen.height * 0.8;
    score_player_w = score_screen.width/5;

    // set the properties of the rectangle where the score of PLAYER 1 will appear
    score_player_1.height = score_player_h;
    score_player_1.width = score_player_w;
    score_player_1.x = score_screen.x + score_player_1.width/2;
    score_player_1.y = score_screen.y + score_screen.height * 0.1;
    text_p1 = make_score(game.players[0]);

    // set the properties of the rectangle where the score of PLAYER 2 will appear
    score_player_2.height = score_player_h;
    score_player_2.width = score_player_w;
    score_player_2.x = score_screen.x + 3.5 * score_player_1.width;
    score_player_2.y = score_screen.y + score_screen.height * 0.1;
    text_p2 = make_score(game.players[1]);

    // set the font
    text_w = text_width("00", "roboto", font_size);
    text_h = text_height("00", "roboto", font_size);
    offset_x = (score_player_w - text_w)/2.0;
    offset_y = (score_player_h - text_h)/2.0;

    // draw score screen
    draw_rectangle(COLOR_AQUA, score_screen);
    fill_rectangle(COLOR_DARK_BLUE, score_screen);

    // draw score PLAYER 1
    draw_rectangle(COLOR_AQUA, score_player_1);
    fill_rectangle(COLOR_LIGHT_BLUE, score_player_1);
    draw_text(text_p1, COLOR_BLACK, "roboto", font_size, score_player_1.x + offset_x, score_player_1.y + offset_y);

    // draw score PLAYER 2
    draw_rectangle(COLOR_AQUA, score_player_2);
    fill_rectangle(COLOR_LIGHT_BLUE, score_player_2);
    draw_text(text_p2, COLOR_BLACK, "roboto", font_size, score_player_2.x +offset_x, score_player_2.y + offset_y);
}


game_data new_game()
{
    game_data result;
    result.ball = new_ball();
    result.players[0] = new_player(1);
    result.players[1] = new_player(2);

    return result;
}

void update_game(game_data &game)
{
    update_ball(game.ball);
    update_player(game.players[1]);
}

void draw_game(game_data &game)
{
    clear_screen(COLOR_WHITE);

    draw_score(game);

    draw_ball(game.ball);
    draw_player(game.players[1]);

    fill_rectangle(COLOR_GREEN, WIDTH/2 - 70/2, HEIGHT/2 - 70/2, 70, 70);
    refresh_screen(60);
}

void update_object_collisions(game_data game)
{
    player_data player_1, player_2;

    player_1 = game.players[0];
    player_2 = game.players[1];

    if(sprite_collision(player_1.player_sprite, player_2.player_sprite))
    {
        // do something
        
        // distance between the sprite centers
        //double distance = sqrt( pow(center_point(player_1.player_sprite).x - center_point(player_2.player_sprite).x, 2) + pow(center_point(player_1.player_sprite).y - center_point(player_2.player_sprite).y,2));
    }
    else if(sprite_collision(game.players[0].player_sprite, game.ball.ball_sprite))
    {
        // do something
    }

    if(sprite_collision(game.players[1].player_sprite, game.ball.ball_sprite))
    {
        // do something
    }
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
        sprite_set_dx(players[1].player_sprite, -1*PLAYER_SPEED);
    else if(key_released(LEFT_KEY))
        sprite_set_dx(players[1].player_sprite, 0);
    
    if(key_down(RIGHT_KEY))
        sprite_set_dx(players[1].player_sprite, PLAYER_SPEED);
    else if(key_released(RIGHT_KEY))
        sprite_set_dx(players[1].player_sprite, 0);
    
    // jump player 2
    if(key_down(UP_KEY) and not in_the_air(players[1].player_sprite))
        sprite_set_dy(players[1].player_sprite, -2*PLAYER_SPEED);
    
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