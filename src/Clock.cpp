#include "Clock.h"
#include <iostream>

Clock::Clock()
= default;

void Clock::restart_clock()
{
    clock.restart();
}

double Clock::return_elapsed_secs()
{
    double time {clock.getElapsedTime().asSeconds()};
    time_stamps.push_back(time);
    return time;
}

double Clock::return_elapsed_millisecs()
{
    double time {static_cast<double>(clock.getElapsedTime().asMilliseconds())};
    return time;
}

double Clock::stop_clock()
{
    double time_when_stopped {};

    if(!time_stamps.empty())
    {
        time_when_stopped = time_stamps.back();
    }
    return time_when_stopped;
}


