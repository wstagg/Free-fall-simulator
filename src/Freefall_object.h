#pragma once

#include "SFML/Graphics/Color.hpp"
#include "SFML/System/Vector2.hpp"
#include "Clock.h"

#include <SFML/Graphics.hpp>
#include <string>

enum class Obj_choice {cube, ball, No_choice};

class Freefall_object
{
    
public:
    Freefall_object(const sf::Texture& _texture, Obj_choice _choice);
    
    void draw(sf::RenderWindow& window);
    void set_outline_thickness(Obj_choice choice);
    void menu_drop(float y_res, int &next_display);
    void get_user_inputs(double drop_ht, double object_mass);
    void obj_fall_pos(double screen_ht);
    std::string get_obj_height();
    std::string get_elapsed_time();

private:
    sf::CircleShape ball;
    sf::RectangleShape cube;
    sf::Vector2f ball_position {600.f, 300.f};
    sf::Vector2f cube_position {200.f, 300.f};
    sf::Vector2f object_position;
    sf::Color outline_colour {sf::Color::White};
    sf::Texture texture;
    sf::Vector2f cube_size {150.f, 150.f};
    float ball_rad{ 30.f };
    sf::Vector2f ff_pos {500.f, 0.f};
    sf::Vector2f ff_cube_size {60.f, 60.f};

    float outline_thickness{10.f};
    float radius{75.f};
    double in_drop_ht{};
    double in_obj_mass{};
    Clock ff_clock;
    Obj_choice object_chosen {};
    void setPosition(sf::Vector2f pos);
    bool fall_enabled {true};

    /* Freefall calulations */
    double calculate_free_fall_time(double mass, double height);
    double calculate_Distance_Travelled_In_Time(double fall_time, double mass);

    const double g{ 9.80665 };       // Gravity (m/s2)
    const double p{ 1.2041 };        // Density of air (kg/m3)
    const double e{ 2.71828 };       // Euler's number (e)
    const double k_sphere{ 0.47 };   //  sphere(kg/m)
    const double k_cube{ 1.05 };     // Air resistance cube(kg/m)
    const double pi{ 3.142 };        // Pi
    double drag_coefficient{0};
};

/* Not used */
//    double calculate_velocity(double fall_time, double mass);
//    static double calculate_meters_per_second(double height, double fall_time);
//    double obj_fall_velocity(double fall_time, double drop_ht, double screen_ht);
//    double calculate_projected_area(double diameter);
//    double calculate_terminal_velocity(double mass, double area);