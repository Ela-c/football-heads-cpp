#include "soccer_ball.h"
#include <math.h>

soccer_ball_data new_ball()
{
    soccer_ball_data result;


    result.ball_sprite = create_sprite("soccer_ball");

    result.radius = sprite_height(result.ball_sprite)/2;

    result.center.x = WIDTH / 2;
    result.center.y = 0;

    result.elasticity = 0.6;

    // set position
    sprite_set_x(result.ball_sprite, result.center.x - result.radius);
    sprite_set_y(result.ball_sprite, result.center.y - result.radius);

    // set collision area for the ball
    //sprite_set_collision_bitmap(result.ball_sprite, );
    //sprite_set_collision_kind(result.ball_sprite, AABB_COLLISIONS);

    // set velocity of the ball
    result.dx = 5;
    result.dy = 0;
    sprite_set_dx(result.ball_sprite, result.dx);
    sprite_set_dy(result.ball_sprite, result.dy);

    return result;
}

void bounce_ball_against_screen(soccer_ball_data &ball)
{
    if ( ball.center.x < ball.radius)
    {
        sprite_set_center(ball.ball_sprite, ball.radius, ball.center.y);
        ball.dx *= -1; 
    }
    else if ( ball.center.x + ball.radius > WIDTH)
    {
        sprite_set_center(ball.ball_sprite, WIDTH - ball.radius, ball.center.y);
        ball.dx *= -1;
    }

    if ( ball.center.y < ball.radius )
    {
        sprite_set_center(ball.ball_sprite, ball.center.x, ball.radius);
        ball.dy *= -1;
    }
    else if ( ball.center.y + ball.radius < HEIGHT)
    {
        ball.dy += GRAVITY;
    }
    else
    {
        sprite_set_center(ball.ball_sprite, ball.center.x, HEIGHT - ball.radius);   
        ball.dy *= -ball.elasticity;
        if ( fabsf(ball.dy) < 0.01)
        {
            ball.dy = 0;
        }
            
    }

    //cout << "AFTER: position of the sprite (" << sprite_x(ball.ball_sprite) << ", " << sprite_y(ball.ball_sprite) << ")" << endl;
    //cout << "velocity vector X: " << ball.dx << " Y: " << ball.dy << endl;
    sprite_set_dx(ball.ball_sprite, ball.dx);
    //write_line((float)ball.dy);
    sprite_set_dy(ball.ball_sprite, ball.dy); // Reverse the direction
}

void update_ball(soccer_ball_data &ball)
{   
    update_sprite(ball.ball_sprite);

    // calculate the new center
    ball.center.x = sprite_x(ball.ball_sprite) + ball.radius;
    ball.center.y = sprite_y(ball.ball_sprite) + ball.radius;

    //cout << " BEFORE: position of the sprite (" << sprite_x(ball.ball_sprite) << ", " << sprite_y(ball.ball_sprite) << ")" << endl;
    
    // CHECK IF INSIDE THE WINDOW AND COLLIDE
    bounce_ball_against_screen(ball);
    /*
    write("position X: ");
    write_line(ball.center.x);
    write("vY: ");
    write_line(ball.dy);
    */
    //apply gravity and bounce against the floor
}


void draw_ball(const soccer_ball_data &ball)
{
    draw_sprite(ball.ball_sprite);
}