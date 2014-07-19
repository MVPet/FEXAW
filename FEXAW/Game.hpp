#ifndef _GAME
#define _GAME

#include "Stage.hpp"


class Game
{
public:
			Game();
	void	run();

protected:
	void	processEvents();
	void	update(sf::Time);
	void	render();

private:
	Stage*				test;
	sf::RenderWindow	mWindow;
	sf::Time			timePerFrame;
};

#endif // Game.hpp