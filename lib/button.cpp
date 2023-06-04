
#include "button.h"

bool button_clicked(const button_data &button)
{
    // if mouse was clicked and its cursor is inside button, then button was clicked
    return point_in_rectangle(mouse_position(), button.clickable_area);
}

void draw_button(const button_data &button)
{
    // Set all the inner text characteristics
    int font_size = PARAGRAPH_FONT_SIZE; 
    int text_w = text_width(button.text, "roboto", font_size);
    int text_h = text_height(button.text, "roboto", font_size);
    double offset_x = (button.clickable_area.width - text_w)/2.0;
    double offset_y = (button.clickable_area.height - text_h)/2.0;

    // Draw button's clickable space and inner text
    draw_rectangle(COLOR_BLACK, button.clickable_area);
    fill_rectangle(COLOR_LIGHT_BLUE, button.clickable_area);
    draw_text(button.text, COLOR_BLACK, "roboto", font_size, button.clickable_area.x+offset_x, button.clickable_area.y+offset_y);
    return;
}

button_data new_button(const string &text, const rectangle &clickable_area)
{
    // initialize new button
    button_data result;
    result.clickable_area = rectangle_from(clickable_area.x, clickable_area.y, clickable_area.width, clickable_area.height);
    result.text = text;
    return result;
}

button_data new_button(const string &text)
{
    // initialize new button
    button_data result;
    
    double width = 20 + text_width(text, "roboto", PARAGRAPH_FONT_SIZE) + 20;
    double height = 20 + text_height(text, "roboto", PARAGRAPH_FONT_SIZE) + 20;
    double x = screen_width()/2 - width/2;
    double y = screen_height() - screen_height()/3;
    
    result.clickable_area = rectangle_from(x, y, width, height);
    result.text = text;
    return result;
}