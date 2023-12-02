#pragma once
#include <string>
#include <vector>
#include <map>

#include <SFML/Graphics.hpp>


class Text
{
public:
	Text(sf::Font* _font, int* _next_display);
	
	void welcome();
	void press_space();
	void choose_obj();
	void cube_sel();
	void ball_sel();
	void cube();
	void ball();
	void enter_drop_ht();
	void enter_obj_mass();
	void obj_height(const std::string& obj_ht);
	void elapsed_time(const std::string& obj_ht);

	void draw(sf::RenderWindow& window);

private:
	std::map<int, std::string> text_options =
	{
		{0, "Welcome to Free fall simulator!" },
		{1, "Please choose the object you would like to drop...."},
		{2, "Push space to continue..."},
		{3, "Cube selected!"},
		{4, "Ball selected!"},
		{5, "Cube"},
		{6, "Ball"},
		{7, "Enter drop height (Meters):"},
		{8, "Enter object mass (KG):"}
	};

	sf::Font* font;
	sf::Text text;
	int* next_display;
	void set_text(int text_choice);

	unsigned int screen_x{ sf::VideoMode::getDesktopMode().width };
	unsigned int centreScreen_x{ sf::VideoMode::getDesktopMode().width / 2 };
	unsigned int halfScreen_x{ centreScreen_x / 2 };
	
	unsigned int screen_y{ sf::VideoMode::getDesktopMode().height };
	unsigned int centreScreen_y{ sf::VideoMode::getDesktopMode().height / 2 };
	unsigned int halfScreen_y{ centreScreen_y / 2 };



};

