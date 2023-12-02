#include "Text.h"
#include<iostream>

Text::Text(sf::Font* _font, int* _next_display):
    font(_font),
    next_display(_next_display)
{
    text.setFont(*font);
}

void Text::welcome()
{
    if (*next_display == 0)
    {
        set_text(0);
        text.setPosition((centreScreen_x - halfScreen_x) - 300, centreScreen_y - halfScreen_y);
        text.setCharacterSize(150);
    }
    else if (*next_display == 1)
    {
        choose_obj();
    }
}

void Text::press_space()
{
    text.setPosition((centreScreen_x - halfScreen_x) + 200, centreScreen_y + halfScreen_y);
    set_text(2);
    text.setCharacterSize(100);
}

void Text::choose_obj()
{
    set_text(1);
    text.setPosition((centreScreen_x - halfScreen_x) - 300 , 0);
    text.setCharacterSize(100);
}

void Text::cube_sel()
{
    text.setPosition(165, 0);
    set_text(3);
    text.setCharacterSize(75);
}

void Text::ball_sel()
{
    text.setPosition(165, 0);
    set_text(4);
    text.setCharacterSize(75);
}

void Text::cube()
{
    text.setPosition(230, 500);
    set_text(5);
}

void Text::ball()
{
    text.setPosition(640, 500);
    set_text(6);
}

void Text::enter_drop_ht()
{
    set_text(7);
    text.setPosition(0, 0);
}

void Text::enter_obj_mass()
{
    set_text(8);
    text.setPosition(0, 300);
}

void Text::draw(sf::RenderWindow& window)
{
    window.draw(text);
}

void Text::set_text(int text_choice)
{
    text.setString(text_options[text_choice]);
}

void Text::obj_height(const std::string& obj_ht)
{
    std::string meters {"Meters: "};
    text.setString(meters + obj_ht);
}

void Text::elapsed_time(const std::string& elapsed_time)
{
    std::string seconds {"Seconds: "};
    text.setString(seconds + elapsed_time);
    text.setPosition(0, 300);
}
