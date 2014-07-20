#ifndef _TILE
#define _TILE

#include <SFML/Graphics.hpp>
#include "Unit.hpp"
#include "Tags.hpp"

class Tile {

public:
	Tile(std::string type, float locX, float locY);
	void draw(sf::RenderWindow* window);
	void setUnitOn(Unit* newUnit);

	sf::Vector2f	getPosition();
	bool			getHasUnit();
	bool			getCanMoveTo();
	bool			getIsHazard();
	Unit*			getUnitOn();

	void			setColor(sf::Color color);
	void			setCanMoveTo(bool val);

protected:

private:
	void		load();

	int			x;
	int			y;
	bool		canMoveTo;
	bool		hasUnit;
	bool		isHazard;
	std::string name;
	Unit*		unitOn;
	sf::Texture texture;
	sf::Sprite	 sprite;
};

#endif // Tile.hpp