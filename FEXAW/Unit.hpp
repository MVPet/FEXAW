#ifndef _UNIT
#define _UNIT

#include <iostream>
#include <sstream>
#include <queue>
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Color.hpp"
#include "Tags.hpp"

class Unit
{
public:
	Unit(std::string nam, int range, int fRange, int dmg, bool canDo, int playerNo, int iNo);

	void			draw(sf::RenderWindow* window);
	void			setPositionAndLoc(sf::Vector2i loc, sf::Vector2f pos);
	sf::Vector2i	getLocation();
	bool			getCanMove();
	int				getMoveRange();
	int				getFireRange();
	int				getOwnedBy();
	int				getHealth();
	int				getAttackPower();
	int				getIndexNo();

	void			MoveTo(sf::Vector2i loc, std::queue<char>* q);
	void			newTurn();

	void			setColor(sf::Color color);
	void			setCanMove(bool val);
	void			setHealth(int val);

protected:

private:
	void	load();
	std::string convertIntToString(int i);

	std::string	name;
	int			health;
	bool		canMove;
	bool		canFire;
	int			moveRange;
	int			fireRange;
	int			attackPower;
	int			ownedBy;
	int			indexNo;	

	sf::Vector2i	location;
	sf::Texture*	texture;
	sf::Sprite		sprite;
};

#endif // Unit.hpp