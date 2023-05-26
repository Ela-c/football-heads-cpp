#include "soccer_ball.h"
#include <math.h>

soccer_ball_data new_ball()
{
    soccer_ball_data result;

    // create ball sprite
    result.object._sprite = create_sprite("soccer_ball");

    // calculate ball radius
    result.radius = sprite_height(result.object._sprite)/2;

    // set elasticity of the ball
    result.object.elasticity = 0.6;

    // set friction for the ball
    result.object.friction_coefficient = ELASTIC;

    // set position of the ball
    result.center.x = screen_center().x;
    result.center.y = 0;
    sprite_set_center(result.object._sprite, result.center.x, result.center.y);

    // set velocity of the ball
    result.object.velocity.x = 0;
    result.object.velocity.y = 0;
    sprite_set_velocity(result.object._sprite, result.object.velocity);

    return result;
}

void keep_ball_within_screen(soccer_ball_data &ball)
{
    // if the ball is trying to scape from the right side of the screen, make it bounce
    if ( ball.center.x < ball.radius)
    {
        sprite_set_center(ball.object._sprite, ball.radius, ball.center.y);
        ball.object.velocity.x *= -1; 
    }
    // if the ball is trying to scape from the left side of the screen, make it bounce
    else if ( ball.center.x + ball.radius > screen_width())
    {
        sprite_set_center(ball.object._sprite, screen_width() - ball.radius, ball.center.y);
        ball.object.velocity.x *= -1;
    }

    // if the ball is trying to scape from the top of the screen, make it bounce
    if ( ball.center.y < ball.radius )
    {
        sprite_set_center(ball.object._sprite, ball.center.x, ball.radius);
        ball.object.velocity.y *= -1;
    }
    
    sprite_set_dx(ball.object._sprite, ball.object.velocity.x);
    sprite_set_dy(ball.object._sprite, ball.object.velocity.y); // Reverse the direction
}

void update_ball(soccer_ball_data &ball)
{   
    update_sprite(ball.object._sprite);

    // calculate the new center
    ball.center.x = sprite_x(ball.object._sprite) + ball.radius;
    ball.center.y = sprite_y(ball.object._sprite) + ball.radius;

    // update velocity variables
    ball.object.velocity.x = sprite_dx(ball.object._sprite);
    ball.object.velocity.y = sprite_dy(ball.object._sprite);
    
    // keep the ball inside the window
    keep_ball_within_screen(ball);

    // apply physics to the ball
    //apply_physics(ball.object);
    apply_physics(ball.object);
}

void draw_ball(const soccer_ball_data &ball)
{
    draw_sprite(ball.object._sprite);
}