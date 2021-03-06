#include "Unit.hpp"

Unit::Unit(std::string nam, int range, int fRange, int dmg, bool canDo, int playerNo, int iNo) : health(1), exp(0)
{
	name = nam;
	moveRange = range;
	fireRange = fRange;
	attackPower = dmg;
	ownedBy = playerNo;
	indexNo = iNo;

	canMove = canDo;
	canFire = canDo;

	if(!canDo)
		sprite.setColor(sf::Color(84,84,84));

	load();
}

void Unit::draw(sf::RenderWindow* window)
{ window->draw(sprite); }

void Unit::load()
{
	int numOfTex = 2;

	texture = new sf::Texture[numOfTex+1];

	for (int i = 1; i <= numOfTex; i++)
	{
		std::string filename = "Assets/Units/" + convertIntToString(i) + name + ".png";
	
		if(!texture[i].loadFromFile(filename))
			throw std::runtime_error("TextureHolder::load - Failed to load " + filename);
	}

	sprite.setTexture(texture[ownedBy]);
	sprite.setOrigin(8.f, 8.f);
	sprite.setScale(2.f, 2.f);
}

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

void Unit::newTurn()
{
	canMove = true;
	canFire = true;

	sprite.setColor(sf::Color::White);
}

bool Unit::getCanMove()
{ return canMove; }

void Unit::setCanMove(bool val)
{ canMove = val; }

int Unit::getMoveRange()
{ return moveRange; }

int Unit::getFireRange()
{ return fireRange; }

int Unit::getOwnedBy()
{ return ownedBy; }

int Unit::getHealth()
{ return health; }

void Unit::minusHealth(int val)
{ health -= val; }

int Unit::getExp()
{ return exp; }

void Unit::addExp(int val)
{ exp += val; }

int Unit::getAttackPower()
{ return attackPower; }

int Unit::getIndexNo()
{ return indexNo; }

sf::Vector2i Unit::getLocation()
{ return location; }

sf::Vector2f Unit::getPosition()
{ return sprite.getPosition(); }

void Unit::setPosition(sf::Vector2f pos)
{ sprite.setPosition(pos); }

void Unit::setLocation(sf::Vector2i loc)
{ location = loc; }

void Unit::setPositionAndLoc(sf::Vector2i loc, sf::Vector2f pos)
{
	location = loc;
	sprite.setPosition(pos);
}

std::string Unit::getType()
{ return name; }

void Unit::setColor(sf::Color color)
{ sprite.setColor(color); }


std::string Unit::convertIntToString(int i)
{
	return static_cast<std::ostringstream*>( &(std::ostringstream() << i))->str();
}