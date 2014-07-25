#include "Unit.hpp"

Unit::Unit(std::string nam, int range, int fRange, bool canDo, int playerNo)
{
	name = nam;
	health = 10;
	moveRange = range;
	fireRange = fRange;
	ownedBy = playerNo;

	canMove = canDo;
	canFire = canDo;

	if(!canDo)
		sprite.setColor(sf::Color(84,84,84));

	load();
}

void Unit::draw(sf::RenderWindow* window)
{ window->draw(sprite); }

void Unit::setPositionAndLoc(sf::Vector2i loc, sf::Vector2f pos)
{
	location = loc;
	sprite.setPosition(pos);
}

sf::Vector2i Unit::getLocation()
{ return location; }

void Unit::setColor(sf::Color color)
{ sprite.setColor(color); }

void Unit::setCanMove(bool val)
{ canMove = val; }

void Unit::load()
{
	std::string filename = "Assets/Units/" + name + ".png";

	if(!texture.loadFromFile(filename))
		throw std::runtime_error("TextureHolder::load - Failed to load " + filename);

	sprite.setTexture(texture);
	sprite.setOrigin(8.f, 8.f);
	sprite.setScale(2.f, 2.f);
}

bool Unit::getCanMove()
{ return canMove; }

int Unit::getMoveRange()
{ return moveRange; }

int Unit::getFireRange()
{ return fireRange; }

int Unit::getOwnedBy()
{ return ownedBy; }

void Unit::MoveTo(sf::Vector2i loc, std::queue<char>* q)
{
	float moveX = 0;
	float moveY = 0;

	while(!q->empty())
	{
		if(q->front() == 'r')
			moveX += 32.f;
		if(q->front() == 'l')
			moveX -= 32.f;
		if(q->front() == 'u')
			moveY -= 32.f;
		if(q->front() == 'd')
			moveY += 32.f;

		q->pop();
	}

	sprite.setPosition(sprite.getPosition().x + moveX, sprite.getPosition().y + moveY);
	location = loc;
}

void Unit::Battle(Unit* enemy)
{
	//deal damage
}