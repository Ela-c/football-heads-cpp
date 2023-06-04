#ifndef BUTTON_H
#define BUTTON_H

#include "splashkit.h"
#include "style.h"

struct button_data
{
    rectangle clickable_area;
    string text;
};

bool button_clicked(const button_data &button);
void draw_button(const button_data &button);
button_data new_button(const string &text, const rectangle &clickable_area);
button_data new_button(const string &text);

#endif