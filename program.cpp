#include "splashkit.h"

#define WIDTH 800
#define HEIGHT 600

#define BALL_SPEED 5

struct soccer_ball_data
{
    sprite ball_sprite;
};

void load_resources()
{
    load_resource_bundle("game_bundle", "football_heads.txt");
}


soccer_ball_data new_ball()
{
    soccer_ball_data result;
    int width, height;
    result.ball_sprite = create_sprite("soccer_ball");

    width = sprite_width(result.ball_sprite);
    height = sprite_height(result.ball_sprite);

    // set position
    sprite_set_x(result.ball_sprite, WIDTH / 2 - width/2);
    sprite_set_y(result.ball_sprite, HEIGHT / 2 - height/2);

    // set movement of the ball to the right
    sprite_set_dx(result.ball_sprite, BALL_SPEED);
    return result;
}

void update_ball(soccer_ball_data &ball)
{
    int x, width, speed;
    
    update_sprite(ball.ball_sprite);

    x = sprite_x(ball.ball_sprite);
    width = sprite_width(ball.ball_sprite);
    speed = sprite_dx(ball.ball_sprite);

    // collide with the border
    if ( x <= 0 || x + width >= WIDTH)
    {
        sprite_set_dx(ball.ball_sprite, speed*-1); // Reverse the direction
    }
}

void draw_ball(const soccer_ball_data &ball)
{
    draw_sprite(ball.ball_sprite);
}

int main()
{
    open_window("Ball Collision", WIDTH, HEIGHT);
    load_resources();

    soccer_ball_data ball = new_ball();

    while (!quit_requested())
    {
        process_events(); // for the quit_requested thing
        clear_screen(COLOR_WHITE);

        update_ball(ball);

        draw_ball(ball);

        refresh_screen(60);
    }

    close_window("Ball Collision");
    return 0;
}
