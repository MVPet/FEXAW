#include "Menu.hpp"

Menu::Menu(Menus::ID type, int val) : curOption(1)
{
	id = type;
	numOfOptions = val;
	load();
}

void Menu::load()
{
	// load background

	options = new sf::Sprite[numOfOptions];

	for(int i = 0; i < numOfOptions; i++)
	{
		// load textures here
		// assign that texture to the sprite
	}

	//load cursor
}

int Menu::getCurOption()
{ return curOption; }

int Menu::setCurOption(int val)
{ curOption = val; }