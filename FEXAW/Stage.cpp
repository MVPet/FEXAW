#include "Stage.hpp"

Stage::Stage(int dem1, int dem2) : moveRight(false), heldRight(false), moveLeft(false), heldLeft(false), moveUp(false), heldUp(false), moveDown(false), heldDown(false), moveMode(false), confirmDown(false), heldConfirm(false), inMenu(false), backDown(false), heldBack(false), fireMode(false), numOfPlayers(2), winner(0)
{
	width = dem1;
	height = dem2;

	view.setCenter(sf::Vector2f(240,160));
	view.setSize(sf::Vector2f(480,320));

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

		if(!inMenu && (cursorLoc.x != (width-1)))
		{
			if (moveMode && (!layout[cursorLoc.x+1][cursorLoc.y]->getIsHazard(focusedUnit->getType())) && (layout[cursorLoc.x+1][cursorLoc.y]->getCanUse()))
			{
				cursorLoc.x += 1;
				cursor.setPosition(layout[cursorLoc.x][cursorLoc.y]->getPosition());
				focusedUnit->setPosition(cursor.getPosition());

				if((cursor.getPosition().x > (view.getCenter().x + (view.getSize().x / 2) - 32)) && (cursorLoc.x <= width-2))
					view.move(32,0);
			}
			else if (!moveMode)
			{
				cursorLoc.x += 1;
				cursor.setPosition(layout[cursorLoc.x][cursorLoc.y]->getPosition());
				if((cursor.getPosition().x > (view.getCenter().x + (view.getSize().x / 2) - 32)) && (cursorLoc.x <= width-2))
					view.move(32,0);
			}
		}
	}
	else 
		heldRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

	if(!heldLeft && moveLeft)
	{
		heldLeft = true;

		if(!inMenu && (cursorLoc.x != 0))
		{
			if (moveMode && (!layout[cursorLoc.x-1][cursorLoc.y]->getIsHazard(focusedUnit->getType())) && (layout[cursorLoc.x-1][cursorLoc.y]->getCanUse()))
			{
				cursorLoc.x -= 1;
				cursor.setPosition(layout[cursorLoc.x][cursorLoc.y]->getPosition());
				focusedUnit->setPosition(cursor.getPosition());
				if((cursor.getPosition().x < (view.getCenter().x - (view.getSize().x / 2) + 32)) && (cursorLoc.x >= 1))
					view.move(-32,0);
			}
			else if (!moveMode)
			{
				cursorLoc.x -= 1;
				cursor.setPosition(layout[cursorLoc.x][cursorLoc.y]->getPosition());
				if((cursor.getPosition().x < (view.getCenter().x - (view.getSize().x / 2) + 32) && (cursorLoc.x >= 1)))
					view.move(-32,0);
			}
		}
	}
	else 
		heldLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);

	if(!heldUp && moveUp)
	{
		heldUp = true;

		if(!inMenu && (cursorLoc.y != 0))
		{
			if (moveMode && (!layout[cursorLoc.x][cursorLoc.y-1]->getIsHazard(focusedUnit->getType())) && (layout[cursorLoc.x][cursorLoc.y-1]->getCanUse()))
			{
				cursorLoc.y -= 1;
				cursor.setPosition(layout[cursorLoc.x][cursorLoc.y]->getPosition());
				focusedUnit->setPosition(cursor.getPosition());
				if((cursor.getPosition().y < (view.getCenter().y - (view.getSize().y / 2) + 32)) && (cursorLoc.y >= 1))
					view.move(0,-32);
			}
			else if (!moveMode)
			{
				cursorLoc.y -= 1;
				cursor.setPosition(layout[cursorLoc.x][cursorLoc.y]->getPosition());
				if((cursor.getPosition().y < (view.getCenter().y - (view.getSize().y / 2) + 32)) && (cursorLoc.y >= 1))
					view.move(0,-32);
			}
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

		if(!inMenu && (cursorLoc.y != (height-1)))
		{
			if (moveMode && (!layout[cursorLoc.x][cursorLoc.y+1]->getIsHazard(focusedUnit->getType())) && (layout[cursorLoc.x][cursorLoc.y+1]->getCanUse()))
			{
				cursorLoc.y += 1;
				cursor.setPosition(layout[cursorLoc.x][cursorLoc.y]->getPosition());
				focusedUnit->setPosition(cursor.getPosition());
				if((cursor.getPosition().y > (view.getCenter().y + (view.getSize().y / 2) - 32)) && (cursorLoc.y <= height-2))
					view.move(0,32);
			}
			else if (!moveMode)
			{
				cursorLoc.y += 1;
				cursor.setPosition(layout[cursorLoc.x][cursorLoc.y]->getPosition());
				if((cursor.getPosition().y > (view.getCenter().y + (view.getSize().y / 2) - 32)) && (cursorLoc.y <= height-2))
					view.move(0,32);
			}
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

	curPlayer->update(sf::Vector2f(view.getCenter().x - (view.getSize().x / 2), view.getCenter().y - (view.getSize().y / 2)));
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
	window->setView(view);

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
	beanIsland();
	/*layout = new Tile**[width];

	for (int i = 0; i < width; i++)
	{
		layout[i] = new Tile*[height];


		for (int j = 0; j < height; j++)
			/*if ((i == 4) && (j == 3))
				layout[i][j] = new Tile(Tags::Factory, (float)(i * 16), (float)(j * 16), players[0]->getPlayerNo());
			else if ((i == 4) && (j == 5))
				layout[i][j] = new Tile(Tags::HQ, (float)(i * 16), (float)(j * 16), players[0]->getPlayerNo());
			else if ((i == 7) && (j == 2))
				layout[i][j] = new Tile(Tags::Factory, (float)(i * 16), (float)(j * 16), players[1]->getPlayerNo());
			else if ((i == 7) && (j == 5))
				layout[i][j] = new Tile(Tags::HQ, (float)(i * 16), (float)(j * 16), players[1]->getPlayerNo());
			else if ((i == 5) || (i == 6))
				layout[i][j] = new Tile(Tags::Ocean, (float)(i * 16), (float)(j * 16), 0);
			else if ((i == 3))
				layout[i][j] = new Tile(Tags::City, (float)(i * 16), (float)(j * 16), 0);
			else
				//layout[i][j] = new Tile(Tags::Land, (float)(i * 16), (float)(j * 16), 0);
	}*/

	players[0]->setHQLocation(sf::Vector2i(1, 7));
	players[1]->setHQLocation(sf::Vector2i(14, 7));

	cursorLoc = players[0]->getHQLocation();
	cursor.setPosition(layout[cursorLoc.x][cursorLoc.y]->getPosition());
}

void Stage::checkConfirm()
{
	if(moveMode)
	{
		if(layout[cursorLoc.x][cursorLoc.y]->getCanUse())
		{
			layout[focusedUnit->getLocation().x][focusedUnit->getLocation().y]->setUnitOn(NULL);
			layout[cursorLoc.x][cursorLoc.y]->setUnitOn(focusedUnit);
			focusedUnit->setLocation(cursorLoc);

			moveMode = false;
			enableMenu(unitMenu);
			resetStageColor();
			//prevUnitLoc = moveUnit();
		}
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
			if ((layout[cursorLoc.x][cursorLoc.y]->getType() == Tags::Factory) || (layout[cursorLoc.x][cursorLoc.y]->getType() == Tags::HQ) || (layout[cursorLoc.x][cursorLoc.y]->getType() == Tags::City))
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
		focusedUnit->setPosition(prevUnitPos);
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

		if(!layout[point.x+1][point.y]->getIsHazard(focusedUnit->getType()))
		{
			layout[point.x+1][point.y]->setColor(color);
			layout[point.x+1][point.y]->setCanUse(true);
			seeRange(sf::Vector2i(point.x+1, point.y), movesLeft, color);
		}
		if(!layout[point.x-1][point.y]->getIsHazard(focusedUnit->getType()))
		{
			layout[point.x-1][point.y]->setColor(color);
			layout[point.x-1][point.y]->setCanUse(true);
			seeRange(sf::Vector2i(point.x-1, point.y), movesLeft, color);
		}
		if(!layout[point.x][point.y-1]->getIsHazard(focusedUnit->getType()))
		{
			layout[point.x][point.y-1]->setColor(color);
			layout[point.x][point.y-1]->setCanUse(true);
			seeRange(sf::Vector2i(point.x, point.y-1), movesLeft, color);
		}
		if(!layout[point.x][point.y+1]->getIsHazard(focusedUnit->getType()))
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
	{
		focusedUnit = layout[cursorLoc.x][cursorLoc.y]->getUnitOn();
		prevUnitPos = focusedUnit->getPosition();
	}

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

void Stage::beanIsland()
{
	layout = new Tile**[width];

	for (int i = 0; i < width; i++)
	{
		layout[i] = new Tile*[height];

		for (int j = 0; j < height; j++)
			if ((i == 0) || (j == 0) || (i == 15))
				layout[i][j] = new Tile(Tags::Ocean, (float)(i * 16), (float)(j * 16), 0);
			else if(((j == 1) && ((i <= 4) || (i == 7) || (i == 8) || (i == 9) || (i == 12)|| (i == 13) || (i == 14))))
				layout[i][j] = new Tile(Tags::Ocean, (float)(i * 16), (float)(j * 16), 0);
			else if(((j == 1) && ((i == 11))))
				layout[i][j] = new Tile(Tags::Mountain, (float)(i * 16), (float)(j * 16), 0);
			else if(((j == 2) && ((i == 1) || (i == 14))))
				layout[i][j] = new Tile(Tags::Ocean, (float)(i * 16), (float)(j * 16), 0);
			else if(((j == 2) && ((i == 4) || (i == 11) || (i == 12))))
				layout[i][j] = new Tile(Tags::Mountain, (float)(i * 16), (float)(j * 16), 0);
			else if(((j == 2) && ((i >= 5) && (i <= 10))))
				layout[i][j] = new Tile(Tags::Woods, (float)(i * 16), (float)(j * 16), 0);
			else if(((j == 3) && ((i == 3) || (i == 4) || (i == 11) || (i == 12))))
				layout[i][j] = new Tile(Tags::Mountain, (float)(i * 16), (float)(j * 16), 0);
			else if(((j == 4) && ((i == 3) || (i == 4) || (i == 11) || (i == 12))))
				layout[i][j] = new Tile(Tags::Mountain, (float)(i * 16), (float)(j * 16), 0);
			else if(((j == 4) && ((i == 1) || (i == 2))))
				layout[i][j] = new Tile(Tags::City, (float)(i * 16), (float)(j * 16), players[0]->getPlayerNo());
			else if(((j == 4) && ((i == 13) || (i == 14))))
				layout[i][j] = new Tile(Tags::City, (float)(i * 16), (float)(j * 16), players[1]->getPlayerNo());
			else if(((j == 4) && ((i >= 5) && (i <= 10))))
				layout[i][j] = new Tile(Tags::City, (float)(i * 16), (float)(j * 16), 0);
			else if(((j == 5) && ((i == 4) || (i == 11))))
				layout[i][j] = new Tile(Tags::Mountain, (float)(i * 16), (float)(j * 16), 0);
			else if(((j == 6) && ((i == 1) || (i == 3))))
				layout[i][j] = new Tile(Tags::Factory, (float)(i * 16), (float)(j * 16), players[0]->getPlayerNo());
			else if(((j == 6) && ((i == 12) || (i == 14))))
				layout[i][j] = new Tile(Tags::Factory, (float)(i * 16), (float)(j * 16), players[1]->getPlayerNo());
			else if(((j == 6) && ((i == 4) || (i == 11) || (i == 7) || (i == 8))))
				layout[i][j] = new Tile(Tags::Mountain, (float)(i * 16), (float)(j * 16), 0);
			else if(((j == 7) && ((i == 1))))
				layout[i][j] = new Tile(Tags::HQ, (float)(i * 16), (float)(j * 16), players[0]->getPlayerNo());
			else if(((j == 7) && ((i == 14))))
				layout[i][j] = new Tile(Tags::HQ, (float)(i * 16), (float)(j * 16), players[1]->getPlayerNo());
			else if(((j == 7) && ((i == 2))))
				layout[i][j] = new Tile(Tags::Factory, (float)(i * 16), (float)(j * 16), players[0]->getPlayerNo());
			else if(((j == 7) && ((i == 13))))
				layout[i][j] = new Tile(Tags::Factory, (float)(i * 16), (float)(j * 16), players[1]->getPlayerNo());
			else if(((j == 7) && ((i == 6))))
				layout[i][j] = new Tile(Tags::City, (float)(i * 16), (float)(j * 16), players[0]->getPlayerNo());
			else if(((j == 7) && ((i == 9))))
				layout[i][j] = new Tile(Tags::City, (float)(i * 16), (float)(j * 16), players[1]->getPlayerNo());
			else if(((j == 7) && ((i == 4) || (i == 7) || (i == 8) || (i == 11))))
				layout[i][j] = new Tile(Tags::Mountain, (float)(i * 16), (float)(j * 16), 0);
			else if(((j == 8) && ((i == 1))))
				layout[i][j] = new Tile(Tags::Factory, (float)(i * 16), (float)(j * 16), players[0]->getPlayerNo());
			else if(((j == 8) && ((i == 14))))
				layout[i][j] = new Tile(Tags::Factory, (float)(i * 16), (float)(j * 16), players[1]->getPlayerNo());
			else if(((j == 8) && ((i == 2) || (i == 13))))
				layout[i][j] = new Tile(Tags::Woods, (float)(i * 16), (float)(j * 16), 0);
			else if(((j == 8) && ((i == 4) || (i == 7) || (i == 8) || (i == 11))))
				layout[i][j] = new Tile(Tags::Mountain, (float)(i * 16), (float)(j * 16), 0);
			else if(((j == 9) && ((i == 6))))
				layout[i][j] = new Tile(Tags::City, (float)(i * 16), (float)(j * 16), players[0]->getPlayerNo());
			else if(((j == 9) && ((i == 9))))
				layout[i][j] = new Tile(Tags::City, (float)(i * 16), (float)(j * 16), players[1]->getPlayerNo());
			else if(((j == 9) && ((i == 7) || (i == 8))))
				layout[i][j] = new Tile(Tags::Mountain, (float)(i * 16), (float)(j * 16), 0);
			else if(((j == 10) && ((i == 1)|| (i == 2))))
				layout[i][j] = new Tile(Tags::City, (float)(i * 16), (float)(j * 16), players[0]->getPlayerNo());
			else if(((j == 10) && ((i == 13) || (i == 14))))
				layout[i][j] = new Tile(Tags::City, (float)(i * 16), (float)(j * 16), players[1]->getPlayerNo());
			else if(((j == 10) && ((i == 4) || (i == 5) || (i == 10) || (i == 11) || (i == 12))))
				layout[i][j] = new Tile(Tags::Woods, (float)(i * 16), (float)(j * 16), 0);
			else if(((j == 10) && ((i >= 6) && (i <= 11))))
				layout[i][j] = new Tile(Tags::Mountain, (float)(i * 16), (float)(j * 16), 0);
			else if(((j == 11) && ((i == 1) || (i == 2) || (i == 8) || (i == 14))))
				layout[i][j] = new Tile(Tags::Ocean, (float)(i * 16), (float)(j * 16), 0);
			else if(((j == 11) && ((i == 12))))
				layout[i][j] = new Tile(Tags::Mountain, (float)(i * 16), (float)(j * 16), 0);
			else if(((j == 12) && (((i >= 1) && (i <= 3)) || ((i >= 6) && (i <= 10)) || ((i >= 12) && (i <= 14)))))
				layout[i][j] = new Tile(Tags::Ocean, (float)(i * 16), (float)(j * 16), 0);
			else if ((j == 13))
				layout[i][j] = new Tile(Tags::Ocean, (float)(i * 16), (float)(j * 16), 0);
			else if ((j == 14))
				layout[i][j] = new Tile(Tags::Ocean, (float)(i * 16), (float)(j * 16), 0);
			else
				layout[i][j] = new Tile(Tags::Land, (float)(i * 16), (float)(j * 16), 0);
	}
}