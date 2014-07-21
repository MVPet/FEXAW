#ifndef _CO
#define _CO

#include "Unit.hpp"

namespace Faction
{
	enum ID { AW, FE };
}

class CO
{
public:
	CO(std::string nam, Faction::ID side, int unitNum);

	void			drawHUD(sf::RenderWindow* window);
	void			drawUnits(sf::RenderWindow* window);
	Unit*			addUnit(std::string name, sf::Vector2i loc, sf::Vector2f pos, int range, int fRange);
	Faction::ID		getFaction();

protected:

private:
	void	load();

	//static int		playerNo;
	std::string		name;
	Faction::ID		faction;

	sf::Texture		faceTex;
	sf::Sprite		face;

	sf::Texture		mugTex;
	sf::Sprite		mugshot;

	int				numOfUnits;
	Unit**			unitList;
};

#endif // CO.hpp