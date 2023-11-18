#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include "Freefall_object.h"
#include "User_input_text.h"
#include "Text.h"



class Events
{
public:
    Events(Freefall_object* _menu_cube, Freefall_object* _menu_ball, int* _next_display,
        int* _object_chosen, int* _text_input, User_input_text* _user_input_height,
        User_input_text* _user_input_mass, sf::RenderWindow* _window, Text* _menu_text, Text* _space,
        Text* _e_drop_ht, Text* _e_obj_mass, Text* _ff_ht, Text* _ff_time);

    void events_init(sf::Event event);
    void display_events();

private:
    void space_key     (sf::Event event);
    void left_key      (sf::Event event);
    void right_key     (sf::Event event);
    void backspace_key (sf::Event event);
    void text_entered  (sf::Event event);
    void close_app     (sf::Event event);
    
    Text* space;
    Text* obj_text;
    Text* e_drop_ht;
    Text* e_obj_mass;
    Text* ff_ht;
    Text* ff_time;


    Freefall_object* menu_cube;
    Freefall_object* menu_ball;
    User_input_text* user_input_height;
    User_input_text* user_input_mass;
    Text* Menu_text;
    int* next_display;
    int* object_chosen;
    int* text_input; // changes input selection
    sf::RenderWindow* window;

};