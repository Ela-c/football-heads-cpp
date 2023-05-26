#include "game.h"

using namespace std;

#define MAX_SCORE 100

/* --------------- PRIVATE FUNCTIONS --------------- */

string make_score_text(const player_data &player)
{
    if (player.score >= MAX_SCORE)
    {
        return "00"; // If the player's score has 3 digits, return "00"
    }

    if(player.score < 10)
    {
        return "0" + to_string(player.score);
    }
    else
    {
        return to_string(player.score);
    }
    // if the player's score has 1 digit, then complement it with a 0, otherwise write it as it is.
}

void draw_score(const game_data &game)
{
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

    // set the properties of the rectangle where the score of PLAYER will be displayed
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

void update_score(game_data &game)
{
    if(sprite_rectangle_collision(game.ball.object._sprite, game.goal.goal_area))
    {
        game.goal.status = 1;
        game.player.score ++;
    }
    update_goal(game.goal);
}

/* --------------- END OF PRIVATE FUNCTIONS --------------- */

void load_resources()
{
    load_resource_bundle("game_bundle", "football_heads.txt");
}

game_data new_game()
{
    game_data result;
    result.ball = new_ball();
    result.player = new_player();
    result.goal = new_goal();

    return result;
}

void update_game(game_data &game)
{
    update_ball(game.ball);
    update_player(game.player);
    handle_collisions(game.player.object, game.ball.object);
    update_score(game);
}

void draw_game(game_data &game)
{
    clear_screen(COLOR_WHITE);
    draw_score(game);
    draw_player(game.player);
    draw_ball(game.ball);
    draw_goal(game.goal);
    refresh_screen(60);
}

void handle_input(player_data player)
{
    // Allow player to move forward or backwards by holding the up/down keys - Movement happens only when the key is pressed
    
    // move player to the left
    if(key_down(LEFT_KEY))
        sprite_set_dx(player.object._sprite, -1*PLAYER_SPEED);
    else if(key_released(LEFT_KEY))
        sprite_set_dx(player.object._sprite, 0);
    
    // move player to the right
    if(key_down(RIGHT_KEY))
        sprite_set_dx(player.object._sprite, PLAYER_SPEED);
    else if(key_released(RIGHT_KEY))
        sprite_set_dx(player.object._sprite, 0);
    
    // make player jump
    if(key_down(UP_KEY) and not in_the_air(player.object._sprite))
        sprite_set_dy(player.object._sprite, -PLAYER_JUMP);
}