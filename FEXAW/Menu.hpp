#ifndef _MENU
#define _MENU

#include "TextureHolder.hpp"

namespace Menus
{
	enum ID { Unit, Shop };
}

class Menu 
{
public:
	Menu(Menus::ID type, int val);

	int getCurOption();
	int setCurOption(int val);

protected:

private:
	void load();
	
	Menus::ID id;
	int	numOfOptions;
	int curOption;
	TextureHolder textures;
	sf::Sprite* options;
	sf::Sprite background;
	sf::Sprite cursor;
};

#endif // Menu.hpp