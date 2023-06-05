#include "soccer_ball.h"

soccer_ball_data new_ball()
{
    soccer_ball_data result;

    // create ball sprite
    result.object._sprite = create_sprite("soccer_ball");

    // set initial position
    sprite_set_x(result.object._sprite, screen_width() / 2 - sprite_width(result.object._sprite));
    sprite_set_y(result.object._sprite, 0);

    // set ball mass
    result.object.mass = BALL_MASS;

    // set elasticity of the ball
    result.object.elasticity = ELASTIC;

    // set friction for the ball
    result.object.friction_coefficient = HAS_FRICTION;

    // set velocity of the ball
    result.object.velocity.x = 0;
    result.object.velocity.y = 0;
    sprite_set_velocity(result.object._sprite, result.object.velocity);

    return result;
}

void update_ball(soccer_ball_data &ball)
{
    update_sprite(ball.object._sprite);

    // update velocity variables
    ball.object.velocity = sprite_velocity(ball.object._sprite);

    // apply physics to the ball
    apply_physics(ball.object);
}

void draw_ball(const soccer_ball_data &ball)
{
    draw_sprite(ball.object._sprite);
}