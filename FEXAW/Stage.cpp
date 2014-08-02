#include "Stage.hpp"

Stage::Stage(int dem1, int dem2) : moveRight(false), heldRight(false), moveLeft(false), heldLeft(false), moveUp(false), heldUp(false), moveDown(false), heldDown(false), moveMode(false), confirmDown(false), heldConfirm(false), inMenu(false), backDown(false), heldBack(false), fireMode(false), numOfPlayers(2), winner(0)
{
	width = dem1;
	height = dem2;

	load();
	readStage();
}

void Stage::update(sf::Time deltaTime)
{
	if ((layout[players[0]->getHQLocation().x][players[0]->getHQLocation().y]->getOwnedBy() != players[0]->getPlayerNo()) || (layout[players[1]->getHQLocation().x][players[1]->getHQLocation().y]->getOwnedBy() != players[1]->getPlayerNo()))
		winner = curPlayer->getPlayerNo();


	if(!heldRight && moveRight)
	{
		heldRight = true;

		if(!inMenu)
		{
			if (cursorLoc.x != (width-1))
				cursorLoc.x += 1;
			cursor.setPosition(layout[cursorLoc.x][cursorLoc.y]->getPosition());
		}
	}
	else 
		heldRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

	if(!heldLeft && moveLeft)
	{
		heldLeft = true;

		if(!inMenu)
		{
			if (cursorLoc.x != 0)
				cursorLoc.x -= 1;
			cursor.setPosition(layout[cursorLoc.x][cursorLoc.y]->getPosition());
		}
	}
	else 
		heldLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);

	if(!heldUp && moveUp)
	{
		heldUp = true;

		if(!inMenu)
		{
			if (cursorLoc.y != 0)
				cursorLoc.y -= 1;
			cursor.setPosition(layout[cursorLoc.x][cursorLoc.y]->getPosition());
		}
		else
		{
			curMenu->setCurOption(curMenu->getCurOption() - 1);
		}
	}
	else
		heldUp = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);

	if(!heldDown && moveDown)
	{
		heldDown = true;

		if(!inMenu)
		{
			if (cursorLoc.y != (height-1))
				cursorLoc.y += 1;
			cursor.setPosition(layout[cursorLoc.x][cursorLoc.y]->getPosition());
		}
		else
		{
			curMenu->setCurOption(curMenu->getCurOption() + 1);
		}
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
	if(winner == 0)
	{
	for (int i = 0; i < width; i++)
		for(int j = 0; j < height; j++)
			layout[i][j]->draw(window);

	players[0]->drawUnits(window);
	players[1]->drawUnits(window);
	window->draw(cursor);
	curPlayer->drawHUD(window);

	if(inMenu)
		curMenu->draw(window);
	}
}

void Stage::load()
{
	textures.load(Textures::Cursor, "Assets/Misc/Cursor.png");
	cursor.setTexture(textures.get(Textures::Cursor));
	cursor.setOrigin(16.f, 16.f);
	cursorLoc = sf::Vector2i(7,5);

	unitMenu = new Menu(Tags::UnitMenu, 3, sf::Vector2f(100,100));
	shopMenu = new Menu(Tags::ShopMenu, 1, sf::Vector2f(140,185));
	turnMenu = new Menu(Tags::TurnMenu, 1, sf::Vector2f(140,185));

	curMenu = turnMenu;

	players = new CO*[numOfPlayers];
	players[0] = new CO(Tags::Andy, Faction::AW, 10, 1);
	players[1] = new CO(Tags::Andy, Faction::AW, 10, 2);
	curPlayer = players[0];
}

// temporary test stage, this function will not stay the same
void Stage::readStage()
{
	layout = new Tile**[width];

	for (int i = 0; i < width; i++)
	{
		layout[i] = new Tile*[height];


		for (int j = 0; j < height; j++)
			if ((i == 4) && (j == 3))
				layout[i][j] = new Tile(Tags::Factory, (float)(i * 16), (float)(j * 16), players[0]->getPlayerNo());
			else if ((i == 4) && (j == 5))
				layout[i][j] = new Tile(Tags::HQ, (float)(i * 16), (float)(j * 16), players[0]->getPlayerNo());
			else if ((i == 7) && (j == 2))
				layout[i][j] = new Tile(Tags::Factory, (float)(i * 16), (float)(j * 16), players[1]->getPlayerNo());
			else if ((i == 7) && (j == 5))
				layout[i][j] = new Tile(Tags::HQ, (float)(i * 16), (float)(j * 16), players[1]->getPlayerNo());
			else
				layout[i][j] = new Tile(Tags::Land, (float)(i * 16), (float)(j * 16), 0);
	}

	players[0]->setHQLocation(sf::Vector2i(4, 5));
	players[1]->setHQLocation(sf::Vector2i(7, 5));

	cursor.setPosition(layout[cursorLoc.x][cursorLoc.y]->getPosition());
}

void Stage::checkConfirm()
{
	if(moveMode)
	{
		if(layout[cursorLoc.x][cursorLoc.y]->getCanUse())
			prevUnitLoc = moveUnit();
	}

	else if(fireMode)
	{
		if(layout[cursorLoc.x][cursorLoc.y]->getCanUse() && layout[cursorLoc.x][cursorLoc.y]->getHasUnit() && (layout[cursorLoc.x][cursorLoc.y]->getUnitOn()->getOwnedBy() != focusedUnit->getOwnedBy()))
		{
			unitBattle(layout[cursorLoc.x][cursorLoc.y]->getUnitOn());
			unitWait();
			fireMode = false;
		}
	}

	else if(inMenu && curMenu->getType() == Tags::UnitMenu)
	{
		switch(curMenu->getCurOption())
		{
		case 0:
			enableFireMode();
			break;
		case 1:
			if ((layout[cursorLoc.x][cursorLoc.y]->getType() == Tags::Factory) || (layout[cursorLoc.x][cursorLoc.y]->getType() == Tags::HQ))
			{
				layout[cursorLoc.x][cursorLoc.y]->changeOwner(focusedUnit->getOwnedBy());
				unitWait();
			}
			break;
		case 2:
			unitWait();
			break;
		}
	}

	else if (inMenu && (curMenu->getType() == Tags::ShopMenu))
	{
		switch(curMenu->getCurOption())
		{
			case 0:
				layout[cursorLoc.x][cursorLoc.y]->setUnitOn(curPlayer->addUnit(Tags::Infantry, cursorLoc, cursor.getPosition(), 3, 1, 1, false));
				inMenu = false;
				break;
		}
	}

	else if (inMenu && (curMenu->getType() == Tags::TurnMenu))
	{
		switch(curMenu->getCurOption())
		{
			case 0:
				if(curPlayer->getPlayerNo() >= numOfPlayers)
					curPlayer = players[0];
				else
					curPlayer = players[curPlayer->getPlayerNo()];

				curPlayer->newTurn();
				inMenu = false;
				break;
		}
	}

	else if(layout[cursorLoc.x][cursorLoc.y]->getHasUnit() && layout[cursorLoc.x][cursorLoc.y]->getUnitOn()->getCanMove() && (layout[cursorLoc.x][cursorLoc.y]->getUnitOn()->getOwnedBy() == curPlayer->getPlayerNo()))
		enableMoveMode(true);

	else if((curPlayer->getNumOfUnits() < curPlayer->getMaxUnits()) && (layout[cursorLoc.x][cursorLoc.y]->getType() == Tags::Factory) && (!layout[cursorLoc.x][cursorLoc.y]->getHasUnit()) && (layout[cursorLoc.x][cursorLoc.y]->getOwnedBy() == curPlayer->getPlayerNo()))
		enableMenu(shopMenu);

	else
		enableMenu(turnMenu);
}

void Stage::checkBack()
{
	if(inMenu)
	{
		if (curMenu->getType() == Tags::UnitMenu)
		{
			focusedUnit->setPositionAndLoc(prevUnitLoc, layout[prevUnitLoc.x][prevUnitLoc.y]->getPosition());
			enableMoveMode(false);
		}
		
		inMenu = false;
	}
	else if(moveMode)
	{
		moveMode = false;
		resetStageColor();
	}
	else if (fireMode)
	{
		enableMenu(unitMenu);
	}
}

sf::Vector2i Stage::moveUnit()
{
	sf::Vector2i start = focusedUnit->getLocation();
	sf::Vector2i tracer = start;
	std::queue<char> q;

	while (tracer != cursorLoc)
	{
		if((tracer.x != cursorLoc.x) && (tracer.x < cursorLoc.x) && (layout[tracer.x+1][tracer.y]->getCanUse()))
		{
			q.push('r');
			tracer.x++;
		}
		else if((tracer.x != cursorLoc.x) && (tracer.x > cursorLoc.x) && (layout[tracer.x-1][tracer.y]->getCanUse()))
		{
			q.push('l');
			tracer.x--;
		}
		else if((tracer.y != cursorLoc.y) && (tracer.y < cursorLoc.y) && (layout[tracer.x][tracer.y+1]->getCanUse()))
		{
			q.push('d');
			tracer.y++;
		}
		else if((tracer.y != cursorLoc.y) && (tracer.y > cursorLoc.y) && (layout[tracer.x][tracer.y-1]->getCanUse()))
		{
			q.push('u');
			tracer.y--;
		}
	}

	focusedUnit->MoveTo(cursorLoc, &q);

	layout[start.x][start.y]->setUnitOn(NULL);
	layout[cursorLoc.x][cursorLoc.y]->setUnitOn(focusedUnit);

	moveMode = false;
	enableMenu(unitMenu);
	resetStageColor();
	return start;
}

void Stage::seeRange(sf::Vector2i point, int movesLeft, sf::Color color)
{
	if((movesLeft != 0) && ((point.x+1) < width) && ((point.x-1) >= 0) && ((point.y+1) < height) && ((point.y-1) >=0))
	{
		movesLeft--;

		if(!layout[point.x+1][point.y]->getIsHazard())
		{
			layout[point.x+1][point.y]->setColor(color);
			layout[point.x+1][point.y]->setCanUse(true);
			seeRange(sf::Vector2i(point.x+1, point.y), movesLeft, color);
		}
		if(!layout[point.x-1][point.y]->getIsHazard())
		{
			layout[point.x-1][point.y]->setColor(color);
			layout[point.x-1][point.y]->setCanUse(true);
			seeRange(sf::Vector2i(point.x-1, point.y), movesLeft, color);
		}
		if(!layout[point.x][point.y-1]->getIsHazard())
		{
			layout[point.x][point.y-1]->setColor(color);
			layout[point.x][point.y-1]->setCanUse(true);
			seeRange(sf::Vector2i(point.x, point.y-1), movesLeft, color);
		}
		if(!layout[point.x][point.y+1]->getIsHazard())
		{
			layout[point.x][point.y+1]->setColor(color);
			layout[point.x][point.y+1]->setCanUse(true);
			seeRange(sf::Vector2i(point.x, point.y+1), movesLeft, color);
		}
	}
}

void Stage::resetStageColor()
{
	for(int i = 0; i < width; i++)
		for(int j = 0; j < height; j++)
			if(layout[i][j]->getCanUse())
			{
				layout[i][j]->setCanUse(false);
				layout[i][j]->setColor(sf::Color::White);
			}
}

void Stage::enableMoveMode(bool focusOnUnit)
{
	if(focusOnUnit)
		focusedUnit = layout[cursorLoc.x][cursorLoc.y]->getUnitOn();

	moveMode = true;
	seeRange(focusedUnit->getLocation(), focusedUnit->getMoveRange(), sf::Color(100, 149,237));
}

void Stage::enableFireMode()
{
	resetStageColor();
	fireMode = true;
	moveMode = false;
	inMenu = false;
	seeRange(focusedUnit->getLocation(), focusedUnit->getFireRange(), sf::Color(255,0,0));
}

void Stage::enableMenu(Menu* newMenu)
{
	inMenu = true;
	curMenu = newMenu;
}

void Stage::unitWait()
{
	focusedUnit->setColor(sf::Color(84,84,84));
	focusedUnit->setCanMove(false);
	focusedUnit = NULL;
	moveMode = false;
	inMenu = false;
	resetStageColor();
}

void Stage::unitBattle(Unit* enemy)
{
	if((enemy->getHealth() - focusedUnit->getAttackPower()) <= 0)
	{
		layout[enemy->getLocation().x][enemy->getLocation().y]->setUnitOn(NULL);
		players[enemy->getOwnedBy()-1]->removeUnit(enemy->getIndexNo());

		if((focusedUnit->getExp() + 10) >= 10)
			curPlayer->upgradeUnit(focusedUnit->getIndexNo());
		else
			focusedUnit->addExp(1);
	}
	else
		enemy->minusHealth(focusedUnit->getAttackPower());
}