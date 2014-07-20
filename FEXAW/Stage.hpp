#ifndef _STAGE
#define _STAGE

#include "TextureHolder.hpp"
#include "Tile.hpp"
#include "CO.hpp"
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
	void			seeRange(sf::Vector2i point, int movesLeft);
	void			resetStageColor();
	void			drawMenu(sf::RenderWindow* window);

	bool			movingMode;
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

	bool			inUnitMenu;
	int				width;
	int				height;
	Tile***			layout;
	TextureHolder	textures;
	sf::Sprite		p1Hud;
	sf::Vector2i	cursorLoc;
	sf::Vector2i	prevUnitLoc;
	sf::Sprite		cursor;
	CO*				player1;

	sf::Sprite		menuTop;
	sf::Sprite		menuBot;
	sf::Sprite		waitMenu;
	sf::Sprite		fireMenu;
	sf::Sprite		menuCursor;
};

#endif // Stage.hpp