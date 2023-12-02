#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

#include "App.h"
#include "Freefall_object.h"
#include "User_input_text.h"
#include "Events.h"
#include "Text.h"
#include "Draw.h"


App::App()
= default;

App::~App()
= default;

void App::init()
{
    unsigned int x_res{ sf::VideoMode::getDesktopMode().width };
    unsigned int y_res{ sf::VideoMode::getDesktopMode().height };

    std::cout << "xres = " << x_res << " yres = " << y_res << std::endl; // debug 
    std::cout << "xres / 2 = " << x_res/2 << " yres/2 = " << y_res/2 << std::endl; // debug 

    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Free fall simulator");
    window.setFramerateLimit(60);
    //window.setVerticalSyncEnabled(true);

    /*------------------------------------*/
    /* Create text to display on screen   */
    /*------------------------------------*/
    sf::Font arial;
    if (!arial.loadFromFile("fonts//arial.ttf"))
    {
        std::cout << "Cannot load font file." << std::endl;
    }
    
    User_input_text user_input_height {arial, sf::Vector2f(400.f, 0.f),
                                       sf::String("|")};
    User_input_text user_input_mass {arial, sf::Vector2f(400.f, 300.f),
                                     sf::String("|")};

    Text m_text{ &arial, &next_display };
    Text obj_text{ &arial, &next_display };
    Text space{ &arial, &next_display };
    Text e_drop_ht{ &arial, &next_display };
    Text e_obj_mass{ &arial, &next_display };
    Text ff_ht {&arial, &next_display};
    Text ff_time {&arial, &next_display};

    
    /*----------------------------------*/
    /* Load in textures for objects     */
    /*----------------------------------*/
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    
    sf::Texture concrete;
    if (!concrete.loadFromFile("textures//concrete_texture.jpg"))
    {
        std::cout << "Cannot load concrete texture" << std::endl;
    }

    sf::Texture crate;
    if (!crate.loadFromFile("textures//crate_texture.jpg"))
    {
        std::cout << "Cannot load crate texture" << std::endl;
    }

    sf::Texture background_texture;
    if (!background_texture.loadFromFile("textures//sky_bg.png"))
    {
        std::cout << "Cannot load background texture" << std::endl;
    }

    sf::Texture cloud_texture;
    if (!cloud_texture.loadFromFile("textures//cloud.png"))
    {
        std::cout << "Cannot load cloud texture" << std::endl;
    }

    /*******************************/
    /*** Create freefall objects ***/
    /*******************************/
   
    Freefall_object menu_ball {concrete, Obj_choice::ball};

    Freefall_object menu_cube {crate, Obj_choice::cube};

    /* Initialise main events object */
    Events main_events{ &menu_cube, &menu_ball, &next_display, 
                        &object_chosen,&text_input, &user_input_height, 
                        &user_input_mass, &window, &obj_text, &space, 
                        &e_drop_ht, &e_obj_mass, &ff_ht, &ff_time};

    /* Initialise draw object */
    Draw draw{ &window, &next_display, &object_chosen, &text_input,
              &m_text, &space, &obj_text, &e_drop_ht, &e_obj_mass,
              &menu_ball, &menu_cube, &user_input_mass, &user_input_height,
              &ff_ht, &ff_time};
    
    sf::Event event{};
    
    /*---------------------*/
    /*   main event loop   */
    /*---------------------*/
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            main_events.events_init(event);
        }

        main_events.display_events();

        draw.main_draw(); 
    }
}