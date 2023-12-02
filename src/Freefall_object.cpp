#include "Freefall_object.h"


/* Freefall_object class constructor */
Freefall_object::Freefall_object(const sf::Texture& _texture, Obj_choice _choice):
texture(_texture),
object_chosen(_choice)
{
    if(_choice == Obj_choice::ball)
    {
        sf::Vector2f ball_position{ static_cast<float>(halfScreen_xRight), static_cast<float>(halfScreen_y) };

        object_position = ball_position;
        ball.setRadius(radius);
        ball.setPosition(ball_position);
        ball.setTexture(&texture); 
        drag_coefficient = k_sphere; 
    }
    else if (_choice == Obj_choice::cube)
    {
        sf::Vector2f cube_position{ static_cast<float>(halfScreen_xLeft),  static_cast<float>(halfScreen_y) };
        
        object_position = cube_position;
        cube.setSize(cube_size);
        cube.setPosition(cube_position);
        cube.setOutlineThickness(outline_thickness);
        cube.setTexture(&texture);
        drag_coefficient = k_cube;
    }  
}

void Freefall_object::draw(sf::RenderWindow& window)
{
    if (object_chosen == Obj_choice::cube)
    {
        window.draw(cube);
    }
    else
    {
        window.draw(ball);
    }
}

void Freefall_object::set_outline_thickness (Obj_choice choice)
{
    if (choice == Obj_choice::cube)
    {
        cube.setOutlineThickness(outline_thickness);
        ball.setOutlineThickness(!outline_thickness);
    }
    else if (choice == Obj_choice::ball) 
    {
        ball.setOutlineThickness(outline_thickness);
        cube.setOutlineThickness(!outline_thickness);
    }
    else if (choice == Obj_choice::No_choice) 
    {
        ball.setOutlineThickness(!outline_thickness);
        cube.setOutlineThickness(!outline_thickness);
    }
}

void Freefall_object::setPosition(sf::Vector2f pos)
{
    if (object_chosen == Obj_choice::cube)
    {
        cube.setPosition(pos);
    }
    else if (object_chosen == Obj_choice::ball)
    {
        ball.setPosition(pos);
    }
}

void Freefall_object::menu_drop(float y_res, int &next_display)
{
    float velocity {10.f};
    object_position.y += velocity;
    setPosition(object_position);

    if (object_position.y > y_res)
    {
        next_display = 3;
    }
}

void Freefall_object::get_user_inputs(double drop_ht, double object_mass)
{
    in_drop_ht = drop_ht;
    std::cout << "drop height is: "<< in_drop_ht << std::endl;
    in_obj_mass = object_mass;
    std::cout << "obj mass is: " << in_obj_mass << std::endl;

}

/* Calculate free fall time */
double Freefall_object::calculate_free_fall_time(double mass, double height)
{
    double freefall_time{ (sqrt(mass / (g * drag_coefficient))) * (acosh(pow(e,(height * drag_coefficient) / mass))) };
    return freefall_time;
}

/* Calculate object fall velocity on screen */ 
double Freefall_object::calculate_Distance_Travelled_In_Time(double fall_time, double mass)
{
    double height = mass/drag_coefficient*log(cosh(fall_time/sqrt(mass/g/drag_coefficient)));
    return height;
}

/* Calculate object fall velocity on screen
* Assume object dropped from top to bottom of screen. This function will calculate the y
* max screen = screen ht
* max distance = calculate_Distance_Travelled_In_Time();
* we combine the two to get a percentage = screen/distance
* multiply it by current distance made. */

void Freefall_object::obj_fall_pos(double screen_ht)
{
    static char first_pass{0};

    if (!first_pass)
    {
        ball.setPosition(ff_pos);
        cube.setPosition(ff_pos);

        ball.setRadius(ball_rad);
        cube.setSize(ff_cube_size);
        
        ff_clock.restart_clock();
        first_pass = 1;
    }
    
    double fall_time = ff_clock.return_elapsed_millisecs()/1000.0;
    double max_fall_time = calculate_free_fall_time(in_obj_mass, in_drop_ht);
    double max_distance = calculate_Distance_Travelled_In_Time(max_fall_time, in_obj_mass);
    
    if (fall_time > max_fall_time)
    {
        fall_time = max_fall_time;
    }

    double currentDistance = calculate_Distance_Travelled_In_Time(fall_time, in_obj_mass);
    double y = currentDistance / max_distance * screen_ht;

    if (fall_enabled)
    {
        switch(object_chosen)
        {
            case(Obj_choice::cube):
                cube.setPosition(cube.getPosition().x, y);
                break;

            case(Obj_choice::ball):
                ball.setPosition(ball.getPosition().x, y);
                break;

            case(Obj_choice::No_choice):
                break;
        }
    }
    
    if ((ball.getPosition().y > (screen_ht - (ball_rad * 2))) ||
        (cube.getPosition().y > (screen_ht - ff_cube_size.x)))
    {
        fall_enabled = false;
    }
}

std::string Freefall_object::get_obj_height()
{
    static double current_height{in_drop_ht};
    unsigned int screen_ht{ sf::VideoMode::getDesktopMode().height };
    object_chosen == Obj_choice::cube ? screen_ht -= ff_cube_size.y : screen_ht -= (ball_rad * 2);
    
    static double pix_per_meter{screen_ht / in_drop_ht};
    const double ppm {screen_ht / in_drop_ht};

    switch (object_chosen)
    {
         case Obj_choice::cube:
            if (cube.getPosition().y > pix_per_meter)
            {
                --current_height;
                pix_per_meter += ppm;
            }
            break;
        case Obj_choice::ball:
            if (ball.getPosition().y > pix_per_meter)
            {
                --current_height;
               pix_per_meter += ppm;
            }
            break;
        case(Obj_choice::No_choice):
            break;
    }
    return std::to_string(current_height );
}

std::string Freefall_object::get_elapsed_time()
{
    if (fall_enabled)
    {
        return std::to_string(ff_clock.return_elapsed_secs());
    }
    else
    {
        return std::to_string(ff_clock.stop_clock());
    }
}

/**************************************************/
/* Unused functions but may be used in the future */
/**************************************************/

/* Calculate meters per second */
//double Freefall_object::calculate_meters_per_second(double height, double fall_time)
//{
//    double fall_velocity_mps{ height / fall_time };
//    return fall_velocity_mps;
//}

// Calculate area of sphere
//double Freefall_object::calculate_projected_area(double diameter)
//{
//    double radius{ diameter / 2 };
//    return pi * pow(radius, 2.0);
//}

//double Freefall_object::calculate_velocity(double fall_time, double mass)
//{
//    double vel = (sqrt(mass*g/drag_coefficient)*tanh(fall_time/sqrt(mass/g/drag_coefficient)));
//    return vel;
//}

// Calculate terminal velocity of sphere
//double Freefall_object::calculate_terminal_velocity(double mass, double area)
//{
//    double cd{ 0.47 };    // Coefficient of drag of sphere
//    double terminal_velocity{ sqrt((2 * (mass * g)) / (cd * p * area)) };
//    return terminal_velocity;
//}