#include "Tile.hpp"

Tile::Tile(std::string type, float locX, float locY) : hasUnit(false), unitOn(NULL), canUse(false)
{
	x = (8 + locX) * 2;
	y = (8 + locY) * 2;

	name = type;
	load();
	
	if(name == Tags::Land)
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

bool Tile::getIsHazard()
{ return isHazard; }

void Tile::setColor(sf::Color color)
{ sprite.setColor(color); }

void Tile::setCanUse(bool val)
{ canUse = val; }

void Tile::load()
{
	std::string filename = "Assets/Tiles/" + name + ".png";

	if(!texture.loadFromFile(filename))
		throw std::runtime_error("TextureHolder::load - Failed to load " + filename);

	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().x / 2);
	sprite.setPosition(x, y);
	sprite.setScale(2.f, 2.f);
}