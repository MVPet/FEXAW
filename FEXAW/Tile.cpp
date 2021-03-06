#include "Tile.hpp"

Tile::Tile(std::string type, float locX, float locY, int playerNo) : hasUnit(false), unitOn(NULL), canUse(false)
{
	x = (8 + locX) * 2;
	y = (8 + locY) * 2;

	name = type;
	ownedBy = playerNo;
	load();

	//if(name == Tags::Land || name == Tags::Land)
	isHazard = false;
}

void Tile::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
}

void Tile::setUnitOn(Unit* newUnit)
{
	(newUnit == NULL) ? hasUnit = false : hasUnit = true;
	unitOn = newUnit;
}

sf::Vector2f Tile::getPosition()
{ return sprite.getPosition(); }

bool Tile::getHasUnit()
{ return hasUnit; }

bool Tile::getCanUse()
{ return canUse; }

Unit* Tile::getUnitOn()
{ return unitOn; }

bool Tile::getIsHazard(std::string unit)
{
	if((unit == Tags::Infantry) || (unit == Tags::Mech))
	{
		if(name == Tags::Ocean)
			return true;
		else
			return false;
	}
}

std::string Tile::getType()
{ return name; }

int Tile::getOwnedBy()
{ return ownedBy; }

void Tile::setColor(sf::Color color)
{ sprite.setColor(color); }

void Tile::setCanUse(bool val)
{ canUse = val; }

void Tile::changeOwner(int playerNo)
{
	ownedBy = playerNo;
	sprite.setTexture(texture[ownedBy]);
}

void Tile::load()
{
	int numOfTex;

	((name == Tags::Factory) || (name == Tags::HQ) || (name == Tags::City)) ? numOfTex = 3 : numOfTex = 1;

	texture = new sf::Texture[numOfTex];


	std::string filename;

	for (int i = 0; i < numOfTex; i++)
	{
		filename ="Assets/Tiles/" + convertIntToString(i) + name + ".png";

		if(!texture[i].loadFromFile(filename))
			throw std::runtime_error("TextureHolder::load - Failed to load " + filename);
	}

	sprite.setTexture(texture[ownedBy]);
	sprite.setOrigin(8.f , texture[ownedBy].getSize().y - 8.f);//texture[ownedBy].getSize().y / 2);
	sprite.setPosition(x, y);
	sprite.setScale(2.f, 2.f);
}

std::string Tile::convertIntToString(int i)
{
	return static_cast<std::ostringstream*>( &(std::ostringstream() << i))->str();
}
