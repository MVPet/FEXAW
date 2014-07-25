#ifndef _TILE
#define _TILE

#include <SFML/Graphics.hpp>
#include "Unit.hpp"
#include "Tags.hpp"
#include <iostream>
#include <sstream>

class Tile {

public:
	Tile(std::string type, float locX, float locY, int playerNo);
	void draw(sf::RenderWindow* window);
	void setUnitOn(Unit* newUnit);

	sf::Vector2f	getPosition();
	bool			getHasUnit();
	bool			getCanUse();
	bool			getIsHazard();
	Unit*			getUnitOn();
	std::string		getType();
	int				getOwnedBy();

	void			setColor(sf::Color color);
	void			setCanUse(bool val);
	void			changeOwner(int playerNo);

protected:

private:
	void		load();
	std::string convertIntToString(int i);

	std::string name;
	int			x;
	int			y;
	int			ownedBy;
	bool		canUse;
	bool		hasUnit;
	bool		isHazard;
	Unit*		unitOn;
	sf::Texture* texture;
	sf::Sprite	 sprite;
};

#endif // Tile.hpp