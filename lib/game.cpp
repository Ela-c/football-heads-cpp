#include "game.h"

using namespace std;

#define MAX_SCORE 100

/* --------------- PRIVATE FUNCTIONS --------------- */

/**
 * @brief  Makes the score text to be displayed based on the player's score
 * 
 * @param player     current player
 * @return string    formatted text representing the score
 */
string make_score_text(const player_data &player)
{
    if (player.score >= MAX_SCORE)
    {
        return "00"; // If the player's score has 3 digits, return "00"
    }

    // if the player's score has 1 digit, then complement it with a 0, otherwise write it as it is.
    if(player.score < 10)
    {
        return "0" + to_string(player.score);
    }
    else
    {
        return to_string(player.score);
    }
}

/**
 * @brief  Draw player's score to the screen
 * 
 * @param game  data structure that manages the game entities
 */
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


/**
 * @brief  Update the goal properties based on the current goal status
 * 
 * @param game  current game
 */

void update_goal(game_data &game)
{
    // check if the player has marked a goal
    if(sprite_rectangle_collision(game.ball.object._sprite, game.goal.goal_area))
    {
        game.goal = new_goal(); // if the player has scored a goal, then create a new goal.
        game.goal.status = 1;
    }
}

/**
 * @brief  Updates the player's score
 * 
 * @param game  data structure that manages the game entities
 */
void update_score(game_data &game)
{
    // check if the player has marked a goal
    if(game.goal.status == 1)
    {
        game.goal.status = 0;
        game.player.score++;
    }
}

/**
 * @brief This function is privite to the module. Creates new nerfs at a random position at the top of the screen
 * 
 * @param game   data structure that manages the game entities
 */
void add_nerf(game_data &game)
{
    if (rnd() < 0.01)
    {
        nerf_data result;

        // create a new power up at a random location
        result = new_nerf(POISON);
        game.nerf_list.push_back(result);    
    }
    return;
}

/**
 * @brief Remove nerf at the indicated index from the game's nerf_list vector.
 * 
 * @param game     data structure that manages the game entities
 * @param index    index of the nerf to remove
 */
void remove_nerf(game_data &game, int index)
{
    int last_index = 0;
    // remove the power up from the power ups vector of the game data struct
    last_index = game.nerf_list.size() - 1;
    game.nerf_list[index] = game.nerf_list[last_index];
    game.nerf_list.pop_back();
}

/**
 * @brief Apply the effect of a nerf object to the game's player sprite
 * 
 * @param game     variable that manages the player and power ups
 * @param index    index of nerf to apply
 */
void apply_nerf(game_data &game, int index)
{   
    // Depending on the type of nerf, modify the player sprite
    switch (game.nerf_list[index].kind)
    {
        case POISON:
            game.status = GAME_OVER;
    
            // play a sound effect to indicate game over
            play_sound_effect("game-over-sound");
            break;
        default:
            game.status = GAME_OVER;
                
            // play a sound effect to indicate game over
            play_sound_effect("game-over-sound");
            break;
    }
}

/**
 * @brief Check for collisions between the player sprite and nerf entities
 * 
 * @param game     variable that manages the player and nerfs
 */
void check_player_nerf_collisions(game_data &game, int index)
{
    if(sprite_collision(game.player.object._sprite, game.nerf_list[index].object._sprite))
    {
        // If there is a collision, apply the nerf effect to the player sprite and remove the nerf entity from the game
        apply_nerf(game, index);
        remove_nerf(game, index);
    }
}

/**
 * @brief Update the currently available list of nerfs on the game
 * 
 * @param game  current game data
 */
void update_nerf_list(game_data &game)
{
    for(int i=0; i<game.nerf_list.size(); i++)
    {
        // update nerfs position and velocity
        update_nerf(game.nerf_list[i]);

        // if nerf touches the ground, then remove it from the list
        if(not in_the_air(game.nerf_list[i].object._sprite))
        {
            remove_nerf(game, i);
        }
    }
}

/**
 * @brief Display a congratulations screen 
 * 
 */
void display_final_screen(string text)
{
    clear_screen(COLOR_WHITE);
    
    // set text message
    int font_size = BIG_FONT_SIZE; 
    int text_w = text_width(text, "roboto", font_size);
    int text_h = text_height(text, "roboto", font_size);

    draw_text(text, COLOR_BLACK, "roboto", font_size, screen_center().x - text_w/2, screen_center().y - text_h/2);

    refresh_screen(60);
}

/**
 * @brief  Handle the collisions of the player, the ball and all the nerf objects
 * 
 * @param game  current game data
 */
void handle_all_collisions(game_data &game)
{
    // handle collisions between the player and the ball
    handle_collisions(game.player.object, game.ball.object);

    // handle the collisions of each nerf entity against all the other entities on the screen
    for(int i=0; i<game.nerf_list.size(); i++)
    {
        check_player_nerf_collisions(game, i);
        handle_collisions(game.nerf_list[i].object, game.ball.object);

        for(int j=0; j<game.nerf_list.size(); j++)
        {
            // check for collisions only if the nerfs are not the same
            if(i != j)
                handle_collisions(game.nerf_list[i].object, game.nerf_list[j].object);
        }
    }
}

/**
 * @brief  Update the game status by checking if the player has won
 * 
 * @param game  current game data
 */
void update_game_status(game_data &game)
{
    // check if the player has won only if the player has not already won
    if(game.player.score >= WIN_SCORE and game.status != PLAYER_WIN)
    {
        // play a sound effect to indicate player has won the game
        play_sound_effect("win-player-sound");
        game.status = PLAYER_WIN;
    }

}
/* --------------- END OF PRIVATE FUNCTIONS --------------- */

void load_resources()
{
    load_resource_bundle("game_bundle", "football_heads.txt");
}

game_data new_game()
{
    game_data result;
    
    // initialize all the game objects
    result.ball = new_ball();
    result.player = new_player();
    result.goal = new_goal();

    // set status as ACTIVE
    result.status = ACTIVE;
    return result;
}

void update_game(game_data &game)
{
    // update the soccer ball
    update_ball(game.ball);

    // updates the current player
    update_player(game.player);
    
    // update all the list of nerfs
    update_nerf_list(game);

    // handle collisions of all game entities
    handle_all_collisions(game);
    
    // update goal position and status
    update_goal(game);

    // update player score
    update_score(game);

    // check if player has won
    update_game_status(game);

    // create nerfs periodically
    add_nerf(game);
}

void draw_game(game_data &game)
{
    clear_screen(COLOR_WHITE);

    // draw all game entities
    draw_score(game);
    draw_player(game.player);
    draw_ball(game.ball);
    draw_goal(game.goal);
    
    for(int i=0; i<game.nerf_list.size(); i++)
    {
        draw_nerf(game.nerf_list[i]);
    }

    refresh_screen(60);
}

void handle_game_outcome(const game_data &game)
{   
    if(game.status == PLAYER_WIN)
    {
        display_final_screen("YOU WON!");
    }
    else if(game.status == GAME_OVER)
    {
        display_final_screen("GAME OVER");
    }
}

void handle_input(player_data player)
{
    // Allow player to move forward or backwards by holding the left/right keys - Movement happens only when the key is held
    
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