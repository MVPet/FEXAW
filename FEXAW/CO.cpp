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

void CO::update(sf::Vector2f vec)
{
	background.setPosition(vec.x, vec.y + 30.f);
	face.setPosition(background.getPosition());
}

void CO::drawHUD(sf::RenderWindow* window)
{ 
	window->draw(background);
	window->draw(face); 
}

void CO::drawUnits(sf::RenderWindow* window)
{
	for (int i = 0; i < numOfUnits; i++)
		if(unitList[i] != NULL)
			unitList[i]->draw(window);
}

void CO::load()
{
	std::string filename = "Assets/Misc/" + convertIntToString(playerNo) + "HUD.png";

	if(!backgroundTex.loadFromFile(filename))
		throw std::runtime_error("TextureHolder::load - Failed to load " + filename);

	background.setTexture(backgroundTex);
	background.setPosition(0.f, 30.f);
	
	filename = "Assets/Char/" + name + "Thin.png";

	if(!faceTex.loadFromFile(filename))
		throw std::runtime_error("TextureHolder::load - Failed to load " + filename);

	face.setTexture(faceTex);
	face.setPosition(background.getPosition());

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

void CO::upgradeUnit(int indexNo)
{
	std::string id = unitList[indexNo]->getType();

	if(id == Tags::Infantry)
	{
		sf::Vector2i loc = unitList[indexNo]->getLocation();
		sf::Vector2f pos = unitList[indexNo]->getPosition();

		delete unitList[indexNo];
		unitList[indexNo] = new Unit(Tags::Mech, 3, 1, 2, false, playerNo, indexNo);
		unitList[indexNo]->setPositionAndLoc(loc, pos);
	}
}

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

Faction::ID CO::getFaction()
{ return faction; }

int CO::getPlayerNo()
{ return playerNo; }

int CO::getMaxUnits()
{ return maxUnits; }

int CO::getNumOfUnits()
{ return numOfUnits; }

sf::Vector2i CO::getHQLocation()
{ return hqLocation; }

void CO::setHQLocation(sf::Vector2i loc)
{ hqLocation = loc; }

std::string CO::convertIntToString(int i)
{
	return static_cast<std::ostringstream*>( &(std::ostringstream() << i))->str();
}
