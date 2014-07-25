#include  "CO.hpp"

int CO::playerNo = 0;

CO::CO(std::string nam, Faction::ID side, int unitNum)
{
	CO::playerNo++;

	name = nam;
	faction = side;
	unitList = new Unit*[unitNum];
	numOfUnits = 0;

	load();
}

void CO::drawHUD(sf::RenderWindow* window)
{ window->draw(face); }

void CO::drawUnits(sf::RenderWindow* window)
{
	for (int i = 0; i < numOfUnits; i++)
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

Unit* CO::addUnit(std::string name, sf::Vector2i loc, sf::Vector2f pos, int range, int fRange, bool canDo)
{
	unitList[numOfUnits] = new Unit(name, range, fRange, canDo, playerNo);
	unitList[numOfUnits]->setPositionAndLoc(loc, pos);

	numOfUnits++;

	return unitList[numOfUnits - 1];
}

Faction::ID CO::getFaction()
{ return faction; }

int CO::getPlayerNo()
{ return playerNo; }