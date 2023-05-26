#include "game_physics.h"

void sprite_set_center(sprite &object, double x, double y)
{
    int width = sprite_width(object);
    int height = sprite_height(object);

    // Set the position of the sprite based on the given center coordinates
    sprite_set_x(object, x - width/2);
    sprite_set_y(object, y - height/2);

    return;
}

bool in_the_air(const sprite &object)
{
    if(sprite_y(object) < screen_height() - sprite_height(object))
    {
        // Check if the sprite's y position is above the ground level
        // If so, the sprite is in the air
        return true;
    }
    return false;
}

void keep_sprite_within_screen(sprite &object)
{
    if(sprite_x(object) < 0)
    {
        // If the sprite's x position is less than 0, set it to 0 to keep it within the screen
        sprite_set_x(object, 0);
    }
    else if(sprite_x(object) > screen_width() - sprite_width(object))
    {
        // If the sprite's x position is greater than the screen width minus the sprite's width,
        // set it to the maximum allowed x position to keep it within the screen
        sprite_set_x(object, screen_width() - sprite_width(object));
    }

    if(sprite_y(object) < 0)
    {
        // If the sprite's y position is less than 0, set it to 0 to keep it within the screen
        sprite_set_y(object, 0);
    }
    else if(sprite_y(object) > screen_height() - sprite_height(object))
    {
        // If the sprite's y position is greater than the screen height minus the sprite's height,
        // set it to the maximum allowed y position to keep it within the screen
        sprite_set_y(object, screen_height() - sprite_height(object));
    }
}

void apply_gravity(object_data &object)
{
    // apply gravity to the object when it is on the air
    if (in_the_air(object._sprite))
    {
        object.velocity.y += GRAVITY;
    }
    // if the object is on the floor, then make it bounce and apply friction for the Vx component.
    else
    {
        sprite_set_y(object._sprite, screen_height() - sprite_height(object._sprite));
        
        // bounce according to elasticity
        object.velocity.y *= -object.elasticity;
        
        if ( fabsf(object.velocity.y) < 0.7)
        {
            object.velocity.y = 0;
        }
    }
    // update object velocity
    sprite_set_velocity(object._sprite, object.velocity);
}

void apply_friction(object_data &object)
{
    if(not in_the_air(object._sprite))
    {
        // apply friction when it moves
        if (object.velocity.x > 0) // it moves to the right
            object.velocity.x -= object.friction_coefficient*GRAVITY;
        else if (object.velocity.x < 0)
            object.velocity.x += object.friction_coefficient*GRAVITY;
        
        if ( fabsf(object.velocity.x) < 0.7)
        {
            object.velocity.x = 0;
        }
    }
    // update object velocity
    sprite_set_velocity(object._sprite, object.velocity);
}

void handle_collisions(object_data ob1, object_data ob2)
{
    // get the bounding circles from the sprites to make the equations more readable
    circle bounding_circle_ob1, bounding_circle_ob2;

    bounding_circle_ob1 = sprite_circle(ob1._sprite);
    bounding_circle_ob2 = sprite_circle(ob2._sprite);

    if(circles_intersect(bounding_circle_ob2, bounding_circle_ob1)) // check for collisions
    {
        // static collision
        float distance; //distance between the sprite centers
        float overlap; // distance of overlap between the two sprites
        double move_x, move_y; // components of the movement vector needed to not overlap
        float factor_ob1, factor_ob2;

        distance = point_point_distance(bounding_circle_ob2.center, bounding_circle_ob1.center);

        overlap = (distance - bounding_circle_ob2.radius - bounding_circle_ob1.radius);

        move_x = overlap * (bounding_circle_ob2.center.x - bounding_circle_ob1.center.x)/distance;
        move_y = overlap * (bounding_circle_ob2.center.y - bounding_circle_ob1.center.y)/distance;

        // compute movement factor to determine how much each object will move for the collision
        if(ob1.mass > ob2.mass)
        {
            factor_ob1 = ob2.mass / ob1.mass;
            factor_ob2 = 1 - factor_ob1;
        }
        else
        {
            factor_ob2 = ob1.mass/ob2.mass;
            factor_ob1 = 1 - factor_ob2;
        }

        // update position of object 1 and 2
        sprite_set_x(ob2._sprite, sprite_x(ob2._sprite) - factor_ob2 * move_x);
        sprite_set_y(ob2._sprite, sprite_y(ob2._sprite) - factor_ob2 * move_y);

        sprite_set_x(ob1._sprite, sprite_x(ob1._sprite) + factor_ob1 * move_x);
        sprite_set_y(ob1._sprite, sprite_y(ob1._sprite) + factor_ob1 * move_y);

        // Dynamic collision
        //float ob1.mass, ob2.mass;
        vector_2d normal_to_tangent, tangent;
        double dp_tangent_ob1, dp_tangent_ball, dp_normal_ob1, dp_normal_ball;

        // Normal
        normal_to_tangent = unit_vector(vector_point_to_point(bounding_circle_ob2.center, bounding_circle_ob1.center));

        // Tangent
        tangent.x = -normal_to_tangent.y;
        tangent.y = normal_to_tangent.x;

        // Dot Product Tangent
        dp_tangent_ob1 = dot_product(tangent, ob1.velocity);
        dp_tangent_ball = dot_product(tangent, ob2.velocity);

        // Dot Product Normal
        dp_normal_ob1 = dot_product(normal_to_tangent, ob1.velocity);
        dp_normal_ball = dot_product(normal_to_tangent, ob2.velocity);

        // Conservation of momentum in 1D
        float m1 = (dp_normal_ob1 * (ob1.mass - ob2.mass) + 2.0f * ob2.mass * dp_normal_ball) / (ob1.mass + ob2.mass);
        float m2 = (dp_normal_ball * (ob2.mass - ob1.mass) + 2.0f * ob1.mass * dp_normal_ob1) / (ob1.mass + ob2.mass);

        // update object.velocity
        ob1.velocity.x = tangent.x * dp_tangent_ob1 + normal_to_tangent.x * m1;
        ob1.velocity.y = tangent.y * dp_tangent_ob1 + normal_to_tangent.y * m1;
        sprite_set_velocity(ob1._sprite, ob1.velocity);

        ob2.velocity.x = tangent.x * dp_tangent_ball + normal_to_tangent.x * m2;
        ob2.velocity.y = tangent.y * dp_tangent_ball + normal_to_tangent.y * m2;
        sprite_set_velocity(ob2._sprite, ob2.velocity);
    }
}

void apply_physics(object_data &object)
{
    apply_gravity(object);
    apply_friction(object);
}