#include "goal.h"


goal_data new_goal()
{
    goal_data result;
    result.goal_area.height = 70;
    result.goal_area.width = 10;
    result.goal_area.x = (rnd() < 0.5) ? 0 : (screen_width() - result.goal_area.width); // set the goal on the left or right of the screen with a 50% of probability
    result.goal_area.y = rnd(0, screen_height() - result.goal_area.height);  // set the goal in a random position of the screen walls

    // set initial status of goal to zero
    result.status = 0;
    return result;
}

void draw_goal(const goal_data &goal)
{
    draw_rectangle(COLOR_RED, goal.goal_area);
    fill_rectangle(COLOR_RED, goal.goal_area);
}

void update_goal(goal_data &goal)
{
    goal = new_goal(); // if the player has scored a goal, then create a new goal.
}