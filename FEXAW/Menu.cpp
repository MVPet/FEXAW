#include "Menu.hpp"

Menu::Menu(std::string nam, int val, sf::Vector2f pos) : curOption(0)
{
	position = pos;
	name = nam;
	numOfOptions = val;
	load();
}

void Menu::draw(sf::RenderWindow* window)
{
	window->draw(background);
	for (int i = 0; i < numOfOptions; i++)
		window->draw(options[i]);
	window->draw(cursor);
}

std::string Menu::getType()
{ return name; }

int Menu::getCurOption()
{ return curOption; }

void Menu::setCurOption(int val)
{ 
	if(val < numOfOptions && val >= 0)
		curOption = val; 

	cursor.setPosition(background.getPosition().x - ((background.getTexture()->getSize().x / 2) + 0.f), options[curOption].getPosition().y);;
}

void Menu::load()
{
	textures = new sf::Texture[numOfOptions];
	options = new sf::Sprite[numOfOptions];

	std::string filename = "Assets/Misc/Menus/" + name + "/Background.png";

	//if(!backTex.loadFromFile("background.png"))
		//throw std::runtime_error("TextureHolder::load - Failed to load " + filename);

	backTex.loadFromFile(filename);
	background.setTexture(backTex);
	background.setOrigin(backTex.getSize().x / 2, backTex.getSize().y / 2);
	background.setPosition(position);

	float x = position.x;
	float y = position.y - (background.getTexture()->getSize().y / 2);

	for(int i = 0; i < numOfOptions; i++)
	{
		filename = "Assets/Misc/Menus/" + name + "/" + convertIntToString(i) + ".png";

		if(!textures[i].loadFromFile(filename))
			throw std::runtime_error("TextureHolder::load - Failed to load " + filename);

		options[i].setTexture(textures[i]);
		options[i].setOrigin(textures[i].getSize().x / 2, textures[i].getSize().y / 2);
		options[i].setPosition(x, y += (textures[i].getSize().y));
	}

	filename = "Assets/Misc/Menus/Cursor.png";

	curTex.loadFromFile(filename);
	cursor.setTexture(curTex);
	cursor.setOrigin(curTex.getSize().x / 2, curTex.getSize().y / 2);
	cursor.setPosition(background.getPosition().x - ((background.getTexture()->getSize().x / 2) + 0.f), options[0].getPosition().y);
}

std::string Menu::convertIntToString(int i)
{
	return static_cast<std::ostringstream*>( &(std::ostringstream() << i))->str();
}