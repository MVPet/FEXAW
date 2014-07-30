#include  "CO.hpp"

CO::CO(std::string nam, Faction::ID side, int unitNum, int pNo)
{
	playerNo = pNo;
	name = nam;
	faction = side;
	maxUnits = unitNum;

	unitList = new Unit*[maxUnits];
	numOfUnits = 0;

	load();
}

void CO::drawHUD(sf::RenderWindow* window)
{ window->draw(face); }

void CO::drawUnits(sf::RenderWindow* window)
{
	for (int i = 0; i < numOfUnits; i++)
		if(unitList[i] != NULL)
			unitList[i]->draw(window);
}

void CO::load()
{
	std::string filename = "Assets/Char/" + name + "Thin.png";

	if(!faceTex.loadFromFile(filename))
		throw std::runtime_error("TextureHolder::load - Failed to load " + filename);

	face.setTexture(faceTex);
	face.setPosition(0.f, 30.f);

	filename = "Assets/Char/" + name + "Mug.png";

	if(!mugTex.loadFromFile(filename))
		throw std::runtime_error("TextureHolder::load - Failed to load " + filename);

	mugshot.setTexture(mugTex);
}

Unit* CO::addUnit(std::string name, sf::Vector2i loc, sf::Vector2f pos, int range, int fRange, int dmg, bool canDo)
{
	unitList[numOfUnits] = new Unit(name, range, fRange, dmg, canDo, playerNo, numOfUnits);
	unitList[numOfUnits]->setPositionAndLoc(loc, pos);

	numOfUnits++;

	return unitList[numOfUnits - 1];
}

void CO::removeUnit(int indexNo)
{
	delete unitList[indexNo];
	numOfUnits--;

	for(int i = indexNo; i < numOfUnits; i++)
	{
		unitList[i] = unitList[i+1];
		unitList[i+1] = NULL;
	}
}

Faction::ID CO::getFaction()
{ return faction; }

int CO::getPlayerNo()
{ return playerNo; }

int CO::getMaxUnits()
{ return maxUnits; }

int CO::getNumOfUnits()
{ return numOfUnits; }

void CO::newTurn()
{
	if(numOfUnits > 0)
	{
		for (int i = 0; i < numOfUnits; i++)
		{
			unitList[i]->newTurn();
		}
	}
}