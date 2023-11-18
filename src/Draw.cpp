#include "Draw.h"
#include "Text.h"
#include <iostream>

Draw::Draw(sf::RenderWindow* _window, int* _next_display, int* _object_chosen, 
	int* _text_input, Text* _m_text, Text* _space, Text* _obj_text, 
	Text* _e_drop_ht, Text* _e_obj_mass,  Freefall_object* _menu_ball, 
	Freefall_object* _menu_cube, User_input_text* _user_input_mass, 
	User_input_text* _user_input_height, Text* _ff_ht, Text* _ff_time):
	
	window(_window),
	next_display(_next_display),
	object_chosen(_object_chosen),
    text_input(_text_input),
	m_text(_m_text),
	space(_space),
	obj_text(_obj_text),
	e_drop_ht(_e_drop_ht),
	e_obj_mass(_e_obj_mass),
	menu_cube(_menu_cube),
	menu_ball(_menu_ball),
	user_input_height(_user_input_height),
	user_input_mass(_user_input_mass),
    ff_ht(_ff_ht),
    ff_time(_ff_time)
{
}

void Draw::main_draw()
{
    /* Sets text postion and parameters */
    m_text->welcome();
    space->press_space();
    e_drop_ht->enter_drop_ht();
    e_obj_mass->enter_obj_mass();
    
    /*---------------------*/
    /*   Main draw block   */
    /*---------------------*/
    window->clear();
    //window->draw(background_image);

    /* Application welcome page */
    if (*next_display == 0)
    {
        //window.draw(cloud);
        m_text->draw(*window);
        space->draw(*window);
    }
    /* Object selection page */ 
    else if (*next_display == 1)
    {
        m_text->draw(*window);
        obj_text->draw(*window);

        menu_ball->draw(*window);
        menu_cube->draw(*window);
        space->draw(*window);
    }
    /* Object selected page */
    else if (*next_display == 2)
    {
        obj_text->draw(*window);

        if (*object_chosen == 0)
        {
            menu_cube->draw(*window);
        }
        else if (*object_chosen == 1)
        {
            menu_ball->draw(*window);
        }
    }
    /* User input page */
    else if (*next_display == 3)
    {
        space->draw(*window);
        e_drop_ht->draw(*window);
        e_obj_mass->draw(*window);

        if (*text_input == 0)
        {
            user_input_height->draw(*window);
        }
        else if (*text_input == 1)
        {
            user_input_height->draw(*window);
            user_input_mass->draw(*window);
        }
    }
    /* Object freefall page */
    else if (*next_display == 4)
    {
        //window->draw(background_image);
        if (*object_chosen == 0)
        {
            menu_cube->draw(*window);
            ff_ht->draw(*window);
            ff_time->draw(*window);
        }
        else if (*object_chosen == 1)
        {
            menu_ball->draw(*window);
            ff_ht->draw(*window);
            ff_time->draw(*window);
        }
    }
    window->display();

    /* debug cout */

    //std::cout << "next text: " << next_text << std::endl;
    //std::cout << drop_ht << std::endl;
    //std::cout << obj_mass << std::endl;

}
