#pragma once
#include "SFML/System/Clock.hpp"
#include <vector>


class Clock
{
public:
    Clock();
    void restart_clock();
    double return_elapsed_secs();
    double return_elapsed_millisecs();
    double stop_clock();

private:
    sf::Clock clock;
    std::vector<double> time_stamps;


};
