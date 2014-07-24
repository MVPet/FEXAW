#ifndef _MENU
#define _MENU

#include <SFML/Graphics.hpp>
#include "Tags.hpp"
#include <iostream>
#include <sstream>

class Menu 
{
public:
	Menu(std::string nam, int val, sf::Vector2f pos);

	void draw(sf::RenderWindow* window);
	int getCurOption();
	void setCurOption(int val);

protected:

private:
	void load();
	std::string convertIntToString(int i);

	std::string name;
	int	numOfOptions;
	int curOption;
	sf::Vector2f position;
	sf::Texture* textures;
	sf::Texture	backTex;
	sf::Texture	curTex;
	sf::Sprite* options;
	sf::Sprite background;
	sf::Sprite cursor;

	sf::Texture* texture;
};

#endif // Menu.hpp