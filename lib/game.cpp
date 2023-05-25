#include "game.h"
#include <math.h>
#include <string>

using namespace std;

#define MAX_SCORE 100

void load_resources()
{
    load_resource_bundle("game_bundle", "football_heads.txt");
}

string make_score_text(const player_data &player)
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
    rectangle score_screen, score_player;
    int font_size=14, text_w, text_h;
    double score_player_w, score_player_h, offset_x, offset_y;
    string score_text;

    // set properties of the screen where the score will appear
    score_screen.height = 100;
    score_screen.width = 400;
    score_screen.x = screen_width()/2 - score_screen.width/2;
    score_screen.y = 10;

    score_player_h = score_screen.height * 0.8;
    score_player_w = score_screen.width/3;

    // set the properties of the rectangle where the score of PLAYER
    score_player.height = score_player_h;
    score_player.width = score_player_w;
    score_player.x = score_screen.x + score_player.width;
    score_player.y = score_screen.y + score_screen.height * 0.1;
    score_text = make_score_text(game.player);

    // set the font
    text_w = text_width("00", "roboto", font_size);
    text_h = text_height("00", "roboto", font_size);
    offset_x = (score_player_w - text_w)/2.0;
    offset_y = (score_player_h - text_h)/2.0;

    // draw score screen
    draw_rectangle(COLOR_AQUA, score_screen);
    fill_rectangle(COLOR_DARK_BLUE, score_screen);

    // draw score PLAYER
    draw_rectangle(COLOR_AQUA, score_player);
    fill_rectangle(COLOR_LIGHT_BLUE, score_player);
    draw_text(score_text, COLOR_BLACK, "roboto", font_size, score_player.x + offset_x, score_player.y + offset_y);
}


game_data new_game()
{
    game_data result;
    result.ball = new_ball();
    result.player = new_player();



    return result;
}

void handle_collisions(player_data player, soccer_ball_data ball)
{
    circle bounding_circle_player, bounding_circle_ball;

    bounding_circle_player = sprite_circle(player.player_sprite);
    bounding_circle_ball = sprite_circle(ball.ball_sprite);

    if(circles_intersect(bounding_circle_ball, bounding_circle_player))
    {
        // static collision
        float distance; //distance between the sprite centers
        float overlap;

        distance = point_point_distance(bounding_circle_ball.center, bounding_circle_player.center);

        overlap = 0.5*(distance - bounding_circle_ball.radius - bounding_circle_player.radius);

        double move_x = overlap * (bounding_circle_ball.center.x - bounding_circle_player.center.x)/distance;
        double move_y = overlap * (bounding_circle_ball.center.y - bounding_circle_player.center.y)/distance;

        sprite_set_x(ball.ball_sprite, sprite_x(ball.ball_sprite) - move_x);
        sprite_set_y(ball.ball_sprite, sprite_y(ball.ball_sprite) - move_y);
        
        sprite_set_x(player.player_sprite, sprite_x(player.player_sprite) + move_x);
        sprite_set_y(player.player_sprite, sprite_y(player.player_sprite) + move_y);

        vector_2d final_velocity;
        final_velocity.x = -1*sprite_dx(ball.ball_sprite);
        final_velocity.y = -1*sprite_dy(ball.ball_sprite); 
        sprite_set_velocity(ball.ball_sprite, final_velocity);

    }
}

void update_game(game_data &game)
{
    update_ball(game.ball);
    update_player(game.player);
    handle_collisions(game.player, game.ball);
}

void draw_game(game_data &game)
{
    clear_screen(COLOR_WHITE);
    draw_score(game);
    draw_player(game.player);
    //delay(2000);
    draw_ball(game.ball);
    refresh_screen(60);
}

void handle_input(player_data player)
{
    // Allow player to move forward or backwards by holding the up/down keys - Movement happens only when the key is pressed
    
    // move player
    if(key_down(LEFT_KEY))
        sprite_set_dx(player.player_sprite, -1*PLAYER_SPEED);
    else if(key_released(LEFT_KEY))
        sprite_set_dx(player.player_sprite, 0);
    
    if(key_down(RIGHT_KEY))
        sprite_set_dx(player.player_sprite, PLAYER_SPEED);
    else if(key_released(RIGHT_KEY))
        sprite_set_dx(player.player_sprite, 0);
    
    // jump player
    if(key_down(UP_KEY) and not in_the_air(player.player_sprite))
        sprite_set_dy(player.player_sprite, -2*PLAYER_SPEED);
}