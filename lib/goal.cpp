#include "goal.h"


goal_data new_goal()
{
    goal_data result;
    result.goal_area.height = 70;
    result.goal_area.width = 10;
    result.goal_area.x = rnd(0,1) ? 0 : (screen_width() - result.goal_area.width);
    result.goal_area.y = rnd(0, screen_height() - result.goal_area.height);
    result.status = 0;
    return result;
}

void draw_goal(const goal_data &goal)
{
    if(goal.status)
    {
        draw_rectangle(COLOR_LIGHT_GREEN, goal.goal_area);
        fill_rectangle(COLOR_LIGHT_GREEN, goal.goal_area);
    }
    else
    {
        draw_rectangle(COLOR_RED, goal.goal_area);
        fill_rectangle(COLOR_RED, goal.goal_area);
    }
}

void update_goal(goal_data &goal)
{
    if(goal.status)
    {
        goal = new_goal();
    }
}