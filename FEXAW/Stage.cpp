#include "Stage.hpp"

Stage::Stage(int dem1, int dem2) : moveRight(false), heldRight(false), moveLeft(false), heldLeft(false), moveUp(false), heldUp(false), moveDown(false), heldDown(false), movingMode(false), confirmDown(false), heldConfirm(false), inUnitMenu(false), backDown(false), heldBack(false)
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

	if(!heldBack && backDown)
	{
		heldBack = true;
		checkBack();
	}
	else
		heldBack = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
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

	if(key == sf::Keyboard::S)
		backDown = isPressed;
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
	drawMenu(window);
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

	textures.load(Textures::MenuTop, "Assets/Misc/MenuTop.png");
	menuTop.setTexture(textures.get(Textures::MenuTop));
	menuTop.setPosition(100.f, 100.f);
	menuTop.setOrigin(53.f, 5.5);

	textures.load(Textures::FireMenu, "Assets/Misc/FireMenu.png");
	fireMenu.setTexture(textures.get(Textures::FireMenu));
	fireMenu.setOrigin(53.5, 17.f);

	textures.load(Textures::WaitMenu, "Assets/Misc/WaitMenu.png");
	waitMenu.setTexture(textures.get(Textures::WaitMenu));
	waitMenu.setOrigin(53.5, 16.5);

	textures.load(Textures::MenuBot, "Assets/Misc/MenuBot.png");
	menuBot.setTexture(textures.get(Textures::MenuBot));
	menuBot.setOrigin(53.5, 7.f);

	textures.load(Textures::MenuCursor, "Assets/Misc/MenuCursor.png");
	menuCursor.setTexture(textures.get(Textures::MenuCursor));
	menuCursor.setOrigin(15.f, 15.f);

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
	layout[cursorLoc.x][cursorLoc.y]->setUnitOn(player1->addUnit(Tags::Infantry, cursorLoc, cursor.getPosition(), 3));
}

void Stage::checkConfirm()
{
	if(movingMode)
	{
		if(!inUnitMenu)
		{
			if(layout[cursorLoc.x][cursorLoc.y]->getCanMoveTo())
				prevUnitLoc = moveUnit();
		}
		else
		{
			focusedUnit->setColor(sf::Color(84,84,84));
			focusedUnit->setCanMove(false);
			focusedUnit = NULL;
			movingMode = false;
			inUnitMenu = false;
			resetStageColor();
		}
	}
	else
		if(layout[cursorLoc.x][cursorLoc.y]->getHasUnit() && layout[cursorLoc.x][cursorLoc.y]->getUnitOn()->getCanMove())
		{
			movingMode = true;
			focusedUnit = layout[cursorLoc.x][cursorLoc.y]->getUnitOn();
			seeRange(focusedUnit->getLocation(), focusedUnit->getMoveRange());
		}
}

void Stage::checkBack()
{
	if(movingMode)
	{
		if(inUnitMenu)
		{
			focusedUnit->setPositionAndLoc(prevUnitLoc, layout[prevUnitLoc.x][prevUnitLoc.y]->getPosition());
			inUnitMenu = false;
		}
		else
		{
			movingMode = false;
			resetStageColor();
		}
	}

}

sf::Vector2i Stage::moveUnit()
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

	inUnitMenu = true;
	return start;
}

void Stage::seeRange(sf::Vector2i point, int movesLeft)
{
	if((movesLeft != 0) && ((point.x+1) < width) && ((point.x-1) >= 0) && ((point.y+1) < height) && ((point.y-1) >=0))
	{
		movesLeft--;

		if(!layout[point.x+1][point.y]->getIsHazard())
		{
			layout[point.x+1][point.y]->setColor(sf::Color(100, 149,237));
			layout[point.x+1][point.y]->setCanMoveTo(true);
			seeRange(sf::Vector2i(point.x+1, point.y), movesLeft);
		}
		if(!layout[point.x-1][point.y]->getIsHazard())
		{
			layout[point.x-1][point.y]->setColor(sf::Color(100, 149,237));
			layout[point.x-1][point.y]->setCanMoveTo(true);
			seeRange(sf::Vector2i(point.x-1, point.y), movesLeft);
		}
		if(!layout[point.x][point.y-1]->getIsHazard())
		{
			layout[point.x][point.y-1]->setColor(sf::Color(100, 149,237));
			layout[point.x][point.y-1]->setCanMoveTo(true);
			seeRange(sf::Vector2i(point.x, point.y-1), movesLeft);
		}
		if(!layout[point.x][point.y+1]->getIsHazard())
		{
			layout[point.x][point.y+1]->setColor(sf::Color(100, 149,237));
			layout[point.x][point.y+1]->setCanMoveTo(true);
			seeRange(sf::Vector2i(point.x, point.y+1), movesLeft);
		}
	}
}

void Stage::resetStageColor()
{
	for(int i = 0; i < width; i++)
		for(int j = 0; j < height; j++)
			if(layout[i][j]->getCanMoveTo())
			{
				layout[i][j]->setCanMoveTo(false);
				layout[i][j]->setColor(sf::Color::White);
			}
}

void Stage::drawMenu(sf::RenderWindow* window)
{
	waitMenu.setPosition(menuTop.getPosition().x - 1, menuTop.getPosition().y + ((menuTop.getTexture()->getSize().y / 2) + (waitMenu.getTexture()->getSize().y / 2)));
	menuBot.setPosition(waitMenu.getPosition().x, waitMenu.getPosition().y + ((waitMenu.getTexture()->getSize().y / 2) + (menuBot.getTexture()->getSize().y / 2)));
	menuCursor.setPosition(waitMenu.getPosition().x - (waitMenu.getTexture()->getSize().x / 2), waitMenu.getPosition().y);

	if(inUnitMenu)
	{
		window->draw(waitMenu);
		window->draw(menuTop);
		window->draw(menuBot);
		window->draw(menuCursor);
	}
}