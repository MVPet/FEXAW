#ifndef _UNIT
#define _UNIT

#include <iostream>
#include <queue>
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Color.hpp"
#include "Tags.hpp"

class Unit
{
public:
	Unit(std::string nam, int range);

	void			draw(sf::RenderWindow* window);
	void			setPositionAndLoc(sf::Vector2i loc, sf::Vector2f pos);
	sf::Vector2i	getLocation();
	bool			getCanMove();
	int				getMoveRange();
	void			MoveTo(sf::Vector2i loc, std::queue<char>* q);

	void			setColor(sf::Color color);
	void			setCanMove(bool val);

protected:

private:
	void	load();

	std::string	name;
	int			health;
	bool		canMove;
	int			moveRange;

	sf::Vector2i	location;
	sf::Texture		texture;
	sf::Sprite		sprite;
};

#endif // Unit.hpp