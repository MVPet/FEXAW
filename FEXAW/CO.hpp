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
	void			upgradeUnit(int indexNo);

	Faction::ID		getFaction();
	int				getPlayerNo();
	int				getMaxUnits();
	int				getNumOfUnits();
	sf::Vector2i	getHQLocation();

	void			setHQLocation(sf::Vector2i loc);

	void			newTurn();

protected:

private:
	void	load();
	std::string convertIntToString(int i);

	int				playerNo;
	std::string		name;
	Faction::ID		faction;

	sf::Texture		faceTex;
	sf::Sprite		face;

	sf::Texture		mugTex;
	sf::Sprite		mugshot;

	sf::Texture		backgroundTex;
	sf::Sprite		background;

	int				maxUnits;
	int				numOfUnits;
	sf::Vector2i	hqLocation;
	Unit**			unitList;
};

#endif // CO.hpp