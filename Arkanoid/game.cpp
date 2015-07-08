//plik implementacyjny state'a g��wnej rozgrywki
#include "game.h"

void Game::handleEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
	}
}

void Game::logic()
{
	if (!window->isOpen())
	{
		setNextState(GAME_STATE_EXIT);
	}
}

void Game::render()
{
	window->display();
}