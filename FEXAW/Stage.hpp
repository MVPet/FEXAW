#ifndef _STAGE
#define _STAGE

#include "TextureHolder.hpp"
#include "Tile.hpp"
#include "CO.hpp"
#include "Menu.hpp"
#include <queue>

class Stage {

public:
	Stage(int dem1, int dem2);
	void draw(sf::RenderWindow* window);
	void update(sf::Time deltaTime);
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

protected:

private:
	void			readStage();
	void			load();
	void			checkConfirm();
	void			checkBack();
	sf::Vector2i	moveUnit();
	bool			canUnitAttack();
	void			seeRange(sf::Vector2i point, int movesLeft, sf::Color color);
	void			resetStageColor();

	bool			moveMode;
	bool			fireMode;
	Unit*			focusedUnit;
	bool			heldRight;
	bool			moveRight;
	bool			heldLeft;
	bool			moveLeft;
	bool			heldUp;
	bool			moveUp;
	bool			heldDown;
	bool			moveDown;
	bool			heldConfirm;
	bool			confirmDown;
	bool			heldBack;
	bool			backDown;

	bool			inMenu;

	int				width;
	int				height;
	Tile***			layout;
	TextureHolder	textures;
	sf::Sprite		p1Hud;
	sf::Vector2i	cursorLoc;
	sf::Vector2i	prevUnitLoc;
	sf::Sprite		cursor;
	CO*				player1;
	CO*				curPlayer;

	Menu*			curMenu;
	Menu*			unitMenu;
	Menu*			shopMenu;
};

#endif // Stage.hpp