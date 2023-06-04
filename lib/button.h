#ifndef BUTTON_H
#define BUTTON_H

#include "splashkit.h"
#include "style.h"

/**
 * @brief Button data structure used to abstract the idea of button
 * 
 * @field text             The text that is going to be shown in the button
 * @field clickable_space  The space of the button that when clicked triggers the functionality
 */
struct button_data
{
    rectangle clickable_area;
    string text;
};

/**
 * @brief Check if the player clicked the button or not
 * 
 * @param button        Button data
 * @return true         If the button's clickable space was clicked
 * @return false        If the button's clickable space has not been clicked
 */
bool button_clicked(const button_data &button);


/**
 * @brief Draw a button on screen according to button's data
 * 
 * @param button  The button to be drawn
 */
void draw_button(const button_data &button);

/**
 * @brief  Create a new button according to the parameters
 * 
 * @param clickable_area Button's clickable area
 * @param text           Button's inner text
 * @return               button_data struct
 */
button_data new_button(const string &text, const rectangle &clickable_area);

/**
 * @brief Create a new button at the bottom of the screen with the text of paragraph size and centered in the button
 * 
 * @param text            Text to be drawn on the button
 * @return button_data    Button object
 */
button_data new_button(const string &text);

#endif