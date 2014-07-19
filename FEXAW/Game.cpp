#include "Game.hpp"

// Class will not stay this way forever, especially once menus are added in

// default constructor
Game::Game() : mWindow(sf::VideoMode(480,320), "FEXAW"), timePerFrame(sf::seconds(1.f / 60.f))
{
	test = new Stage(15, 10);
}

// our "infinte" loop that starts the game clock and loops while the window is open
// updates the game ~60fps
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
		}
		render();
	}
}

// process the events occuring inside the game
void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			test->handlePlayerInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			test->handlePlayerInput(event.key.code, false);
			break;

		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}

void Game::update(sf::Time deltaTime)
{
	test->update(deltaTime);
}

// render the game tot he screen, by clearing the window and drawing everything
void Game::render()
{
	mWindow.clear();
	test->draw(&mWindow);
	mWindow.display();
}