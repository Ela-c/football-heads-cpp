#include "goal.h"

goal_data new_goal(unsigned short int id)
{
    goal_data result;
    result.goal_area.height = 70;
    result.goal_area.width = 10;
    if (id == 1)
    {
        result._color = COLOR_BROWN;
        result.goal_area.x = 0;                                                 // set the goal on the left or right of the screen with a 50% of probability
        result.goal_area.y = rnd(0, screen_height() - result.goal_area.height); // set the goal in a random position of the screen walls
    }
    else if (id == 2)
    {
        result._color = COLOR_DARK_BLUE;
        result.goal_area.x = screen_width() - result.goal_area.width;           // set the goal on the left or right of the screen with a 50% of probability
        result.goal_area.y = rnd(0, screen_height() - result.goal_area.height); // set the goal in a random position of the screen walls
    }

    // set initial status of goal to zero
    result.status = 0;
    return result;
}

void draw_goal(const goal_data &goal)
{
    draw_rectangle(COLOR_BLACK, goal.goal_area);
    fill_rectangle(goal._color, goal.goal_area);
}
