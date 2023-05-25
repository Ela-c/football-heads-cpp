#include "game_physics.h"

void sprite_set_center(sprite &object, double x, double y)
{
    int width = sprite_width(object);
    int height = sprite_height(object);

    sprite_set_x(object, x - width/2);
    sprite_set_y(object, y - height/2);

    return;
}

bool in_the_air(const sprite &object)
{
    if(sprite_y(object) < screen_height() - sprite_height(object))
    {
        // sprite is in the air
        return true;
    }
    return false;
}

void keep_sprite_within_screen(sprite &object)
{
    if(sprite_x(object) < 0)
    {
        sprite_set_x(object, 0);
    }
    else if(sprite_x(object) > screen_width() - sprite_width(object))
    {
        sprite_set_x(object, screen_width() - sprite_width(object));
    }

    if(sprite_y(object) < 0)
    {
        sprite_set_y(object, 0);
    }
    else if(sprite_y(object) > screen_height() - sprite_height(object))
    {
        sprite_set_y(object, screen_height() - sprite_height(object));
    }
}



void handle_collisions(sprite s1, sprite s2) // S1 ES PLAYER Y S2 ES BALL
{
    
    if(sprite_collision(s1,s2))
    {
        float s1_mass, s2_mass;
        vector_2d normal_to_tangent, tangent, velocity_s1, velocity_s2;
        double dp_tangent_s1, dp_tangent_s2, dp_normal_s1, dp_normal_s2;
        
        s1_mass = PLAYER_MASS;
        s2_mass = BALL_MASS;
        
        // static collision
        float distance; //distance between the sprite centers
        float overlap;

        distance = point_point_distance(center_point(s1), center_point(s2));

        overlap = 0.5*(distance - sprite_width(s1)/2 - sprite_width(s2)/2);

        double move_x = overlap * (center_point(s1).x - center_point(s2).x)/distance;
        double move_y = overlap * (center_point(s1).y - center_point(s2).y)/distance;

        sprite_set_x(s1, sprite_x(s1) - move_x);
        sprite_set_y(s1, sprite_y(s1) - move_y);
        
        sprite_set_x(s2, sprite_x(s2) + move_x);
        sprite_set_y(s2, sprite_y(s2) + move_y);

        // Dynamic collision
        velocity_s1 = sprite_velocity(s1);
        velocity_s2 = sprite_velocity(s2);

        // Normal
        normal_to_tangent = unit_vector(vector_point_to_point(center_point(s1), center_point(s2)));

        // Tangent
        tangent.x = -normal_to_tangent.y;
        tangent.y = normal_to_tangent.x;

        // Dot Product Tangent
        dp_tangent_s1 = dot_product(tangent, velocity_s1);
        dp_tangent_s2 = dot_product(tangent, velocity_s2);

        // Dot Product Normal
        dp_normal_s1 = dot_product(normal_to_tangent, velocity_s1);
        dp_normal_s2 = dot_product(normal_to_tangent, velocity_s2);

        // Conservation of momentum in 1D
        float m1 = (dp_normal_s1 * (s1_mass - s2_mass) + 2.0f * s2_mass * dp_normal_s2) / (s1_mass + s2_mass);
        float m2 = (dp_normal_s2 * (s2_mass - s1_mass) + 2.0f * s1_mass * dp_normal_s1) / (s1_mass + s2_mass);

        // update velocity
        velocity_s1.x = tangent.x * dp_tangent_s1 + normal_to_tangent.x * m1;
        velocity_s1.y = tangent.y * dp_tangent_s1 + normal_to_tangent.y * m1;
        sprite_set_velocity(s1, velocity_s1);

        velocity_s2.x = tangent.x * dp_tangent_s2 + normal_to_tangent.x * m2;
        velocity_s2.y = tangent.y * dp_tangent_s2 + normal_to_tangent.y * m2;
        sprite_set_velocity(s2, velocity_s2);
    
    }   
}