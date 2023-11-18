#pragma once

class App
{
public:
    App();
    void init();
    ~App();

private:
    /* Used to iterate through different pages of the application */
    int next_display = { 0 };

    /* User input page */
    int text_input = { 0 }; // changes input selection

    /* Used for object specific events            */
    /* This was static before it was moved here...*/
    int object_chosen{ 0 };
};