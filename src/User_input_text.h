#pragma once 

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Clock.h"
class User_input_text
{
public:
    
    User_input_text(sf::Font _font, sf::Vector2f _text_position, sf::String _string);
    void draw(sf::RenderWindow& window);
    void get_user_input(sf::Event event, int* next_text);
    std::string return_string();
    void text_cursor();
    void erase_text();
    void start_text_cursor_clock();
    void stop_text_cursor_clock();
    int return_string_length();
    double return_drop_ht();
    double return_obj_mass();
    void enter_text(sf::Event event, int *text_input);
    void delay_timer (int &next_display);

private:
    sf::Text text;
    sf::Font font;
    sf::Vector2f text_position;
    sf::String string;
    std::string input;
    sf::Color text_colour;
    double drop_ht;
    double obj_mass;
    sf::Clock text_cursor_clock;
    bool text_cursor_clock_start{ false };
    int switch_text_cursor_colour{ 0 };
    Clock mass_input_clock;
    bool obj_mass_input_clock_start{ false };

    enum class text_curosr_clock {start, stop};
    

};