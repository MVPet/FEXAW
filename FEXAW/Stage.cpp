#include "Stage.hpp"

Stage::Stage(int dem1, int dem2) : moveRight(false), heldRight(false), moveLeft(false), heldLeft(false), moveUp(false), heldUp(false), moveDown(false), heldDown(false), movingMode(false), confirmDown(false), heldConfirm(false)
{
	width = dem1;
	height = dem2;

	load();
	readStage();
}

void Stage::update(sf::Time deltaTime)
{
	if(!heldRight && moveRight)
	{
		heldRight = true;
		if (cursorLoc.x != (width-1))
			cursorLoc.x += 1;
		cursor.setPosition(layout[cursorLoc.x][cursorLoc.y]->getPosition());
	}
	else 
		heldRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

	if(!heldLeft && moveLeft)
	{
		heldLeft = true;
		if (cursorLoc.x != 0)
			cursorLoc.x -= 1;
		cursor.setPosition(layout[cursorLoc.x][cursorLoc.y]->getPosition());
	}
	else 
		heldLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);

	if(!heldUp && moveUp)
	{
		heldUp = true;
		if (cursorLoc.y != 0)
			cursorLoc.y -= 1;
		cursor.setPosition(layout[cursorLoc.x][cursorLoc.y]->getPosition());
	}
	else
		heldUp = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);

	if(!heldDown && moveDown)
	{
		heldDown = true;
		if (cursorLoc.y != (height-1))
			cursorLoc.y += 1;
		cursor.setPosition(layout[cursorLoc.x][cursorLoc.y]->getPosition());
	}
	else 
		heldDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);

	if(!heldConfirm && confirmDown)
	{
		heldConfirm = true;
		checkConfirm();
	}
	else
		heldConfirm = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
}

void Stage::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if(key == sf::Keyboard::Right)
		moveRight = isPressed;
	else if(key == sf::Keyboard::Left)
		moveLeft = isPressed;
	
	if(key == sf::Keyboard::Up)
		moveUp = isPressed;
	else if (key == sf::Keyboard::Down)
		moveDown = isPressed;

	if(key == sf::Keyboard::A)
		confirmDown = isPressed;
}

void Stage::draw(sf::RenderWindow* window)
{
	for (int i = 0; i < width; i++)
		for(int j = 0; j < height; j++)
			layout[i][j]->draw(window);

	window->draw(p1Hud);
	player1->drawUnits(window);
	window->draw(cursor);
	player1->drawHUD(window);
}

void Stage::load()
{
	textures.load(Textures::P1HUD, "Assets/Misc/P1HUD.png");
	p1Hud.setTexture(textures.get(Textures::P1HUD));
	p1Hud.setPosition(0.f, 30.f);

	textures.load(Textures::Cursor, "Assets/Misc/Cursor.png");
	cursor.setTexture(textures.get(Textures::Cursor));
	cursor.setOrigin(16.f, 16.f);
	cursorLoc = sf::Vector2i(7,5);

	player1 = new CO(Tags::Andy, Faction::AW, 10);
}

// temporary test stage, this function will not stay the same
void Stage::readStage()
{
	layout = new Tile**[width];

	for (int i = 0; i < width; i++)
	{
		layout[i] = new Tile*[height];

		for (int j = 0; j < height; j++)
			layout[i][j] = new Tile(Tags::Land, (float)(i * 16), (float)(j * 16));
	}

	cursor.setPosition(layout[cursorLoc.x][cursorLoc.y]->getPosition());
	layout[cursorLoc.x][cursorLoc.y]->setUnitOn(player1->addUnit(Tags::Infantry, cursorLoc, cursor.getPosition()));
}

void Stage::checkConfirm()
{
	if(movingMode)
	{
		if(focusedUnit->getCanMove())
			moveUnit();
	}
	else
		if(layout[cursorLoc.x][cursorLoc.y]->getHasUnit())
		{
			movingMode = true;
			focusedUnit = layout[cursorLoc.x][cursorLoc.y]->getUnitOn();
		}
}

void Stage::moveUnit()
{
	sf::Vector2i start = focusedUnit->getLocation();
	sf::Vector2i tracer = start;
	std::queue<char> q;

	while (tracer != cursorLoc)
	{
		if((tracer.x != cursorLoc.x) && (tracer.x < cursorLoc.x) && (layout[tracer.x+1][tracer.y]->getCanMoveTo()))
		{
			q.push('r');
			tracer.x++;
		}
		else if((tracer.x != cursorLoc.x) && (tracer.x > cursorLoc.x) && (layout[tracer.x-1][tracer.y]->getCanMoveTo()))
		{
			q.push('l');
			tracer.x--;
		}
		else if((tracer.y != cursorLoc.y) && (tracer.y < cursorLoc.y) && (layout[tracer.x][tracer.y+1]->getCanMoveTo()))
		{
			q.push('d');
			tracer.y++;
		}
		else if((tracer.y != cursorLoc.y) && (tracer.y > cursorLoc.y) && (layout[tracer.x][tracer.y-1]->getCanMoveTo()))
		{
			q.push('u');
			tracer.y--;
		}
	}

	focusedUnit->MoveTo(cursorLoc, &q);

	layout[start.x][start.y]->setUnitOn(NULL);
	layout[cursorLoc.x][cursorLoc.y]->setUnitOn(focusedUnit);

	focusedUnit = NULL;
	movingMode = false;
}