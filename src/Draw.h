#pragma once

#include "Freefall_object.h"
#include "User_input_text.h"
#include "Text.h"

class Draw
{
public:
	Draw(sf::RenderWindow* _window,
		int* _next_display,
		int* _object_chosen,
		int* _text_input,
		Text* _m_text,
		Text* _space,
		Text* _obj_text,
		Text* _e_drop_ht,
		Text* _e_obj_mass,
		Freefall_object* _menu_ball,
		Freefall_object* _menu_cube,
		User_input_text* _user_input_mass,
		User_input_text* _user_input_height,
		Text* _ff_ht,
		Text*_ff_time);

	void main_draw();
	
private:

	sf::RenderWindow* window;
	
	int* next_display;
	int* object_chosen;
	int* text_input;
	
	Text* m_text;
	Text* space;
	Text* obj_text;
	Text* e_drop_ht;
	Text* e_obj_mass;
	Text* ff_ht;
	Text* ff_time;

	Freefall_object* menu_ball;
	Freefall_object* menu_cube;

	User_input_text* user_input_mass;
	User_input_text* user_input_height;
};

