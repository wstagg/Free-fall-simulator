#include "Events.h"
#include "Freefall_object.h"
#include "Text.h"

#include <iostream>

Events::Events(Freefall_object * _menu_cube, Freefall_object * _menu_ball, int * _next_display,
            int*  _object_chosen, int * _text_input, User_input_text * _user_input_height,
            User_input_text * _user_input_mass, sf::RenderWindow* _window, Text* _menu_text, Text* _space,
            Text* _e_drop_ht, Text* _e_obj_mass, Text* _ff_ht, Text* _ff_time):
            menu_cube( _menu_cube),
            menu_ball( _menu_ball),
            next_display( _next_display),
            object_chosen(_object_chosen),
            text_input(_text_input),
            user_input_height(_user_input_height),
            user_input_mass(_user_input_mass),
            window(_window),
            Menu_text(_menu_text),
            space(_space),
            e_drop_ht(_e_drop_ht),
            e_obj_mass(_e_obj_mass),
            ff_ht(_ff_ht),
            ff_time(_ff_time)
{

}

void Events::events_init(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        space_key(event);
        right_key(event);
        left_key(event);
        backspace_key(event);
        
        /* Requires space bar input */ 
        text_entered(event); 
    }
    if (event.type == sf::Event::TextEntered)
    {
        text_entered(event);   
    }

    close_app(event);
}

void Events::space_key(sf::Event event)
{
    if (event.key.code == sf::Keyboard::Space)
    {
        /* This changes to the object selection menu */
        if (*next_display < 1) 
        {
            *next_display = 1;
        }
        /* Cube chosen */ 
        else if ((*object_chosen == static_cast<int>(Obj_choice::cube)) && (*next_display == 1))
        {
            //Text->cube_sel();                          
            menu_cube->set_outline_thickness(Obj_choice::No_choice);
            *next_display = 2;
        }
        /* Ball Chosen */
        else if ((*object_chosen == static_cast<int>(Obj_choice::ball)) && (*next_display == 1))
        {
            //Text->ball_sel();               
            menu_ball->set_outline_thickness(Obj_choice::No_choice);
            *next_display = 2;
        }
        else if ((*text_input == 1) && (user_input_mass->return_string_length() > 0))
        {
            if(*object_chosen == 0)
            {
                menu_cube->get_user_inputs(user_input_height->return_drop_ht(), user_input_mass->return_obj_mass());
            }
            if(*object_chosen == 1)
            {
                menu_ball->get_user_inputs(user_input_height->return_drop_ht(), user_input_mass->return_obj_mass());
            }
        }
    }
}

void Events::left_key(sf::Event event)
{
    if (event.key.code == sf::Keyboard::Left)
    {
        if (*next_display == 1)
        {
            menu_cube->set_outline_thickness(Obj_choice::cube);
            menu_ball->set_outline_thickness(Obj_choice::cube);
            Menu_text->cube();
            *object_chosen = static_cast<int>(Obj_choice::cube);
        }
    }
}

void Events::right_key(sf::Event event)
{
    if (event.key.code == sf::Keyboard::Right)
    {
        if (*next_display == 1)
        {
            menu_ball->set_outline_thickness(Obj_choice::ball);
            menu_cube->set_outline_thickness(Obj_choice::ball);
            Menu_text->ball();
            *object_chosen = static_cast<int>(Obj_choice::ball);
        }
    }
}

void Events::backspace_key(sf::Event event)
{
    if (event.key.code == sf::Keyboard::BackSpace)
    {
        if (*text_input == 0)
        { 
            user_input_height->erase_text();                     
        }
        else if (*text_input == 1)
        {
            user_input_mass->erase_text();
        }
    }
}

void Events::text_entered(sf::Event event)
{
    if(*next_display == 3)
    {
        if (*text_input == 0)
        {
            user_input_height->enter_text(event, text_input);
        }
        else if(*text_input == 1)
        {
            user_input_mass->enter_text(event, text_input);
        }
    }
}

 void Events::close_app(sf::Event event)
 {
    if (event.type == sf::Event::Closed)
    {
        window->close();
    }   
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        window->close();
    }
 }

void Events::display_events()
{
    Menu_text->welcome();
    space->press_space();
    e_drop_ht->enter_drop_ht();
    e_obj_mass->enter_obj_mass();

        /* Changes the y pos of object when it has been selected to make  */
        /* it drop from the screen                                        */
    if (*next_display == 1)
    {
        if (*object_chosen == 0)
        {
            Menu_text->cube();
        }
        else if (*object_chosen == 1)
        {
            Menu_text->ball();
        }
    }
    else if (*next_display == 2)
    {
        if (*object_chosen == 0)
        {
            menu_cube->menu_drop(window->getSize().y, *next_display);
            Menu_text->cube_sel();
        }
        else if (*object_chosen == 1)
        {
            menu_ball->menu_drop(window->getSize().y, *next_display);
            Menu_text->ball_sel();
        }
        
        user_input_height->start_text_cursor_clock();
    }
    else if (*next_display == 3)
    {        
        user_input_height->text_cursor();  
        user_input_mass->text_cursor();
        user_input_mass->delay_timer(*next_display);
    }
    
    else if (*next_display == 4)
    {       
        if(*object_chosen == static_cast<int>(Obj_choice::cube))
        {
            menu_cube->obj_fall_pos(window->getSize().y);
            ff_ht->obj_height(menu_cube->get_obj_height());
            ff_time->elapsed_time(menu_cube->get_elapsed_time());
        } 
            
        if(*object_chosen == static_cast<int>(Obj_choice::ball))
        {
            menu_ball->obj_fall_pos(window->getSize().y);
            ff_ht->obj_height(menu_ball->get_obj_height());
            ff_time->elapsed_time(menu_ball->get_elapsed_time());
        }
    }         
}

