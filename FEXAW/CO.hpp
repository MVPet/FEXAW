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
	CO(std::string nam, Faction::ID side, int unitNum, int pNo);

	void			drawHUD(sf::RenderWindow* window);
	void			drawUnits(sf::RenderWindow* window);
	Unit*			addUnit(std::string name, sf::Vector2i loc, sf::Vector2f pos, int range, int fRange, int dmg, bool canDo);
	void			removeUnit(int indexNo);
	Faction::ID		getFaction();
	int				getPlayerNo();
	int				getMaxUnits();
	int				getNumOfUnits();

	void			newTurn();

protected:

private:
	void	load();

	int				playerNo;
	std::string		name;
	Faction::ID		faction;

	sf::Texture		faceTex;
	sf::Sprite		face;

	sf::Texture		mugTex;
	sf::Sprite		mugshot;

	int				maxUnits;
	int				numOfUnits;
	Unit**			unitList;
};

#endif // CO.hpp