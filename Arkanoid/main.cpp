#include <iostream>
#include <SFML\Graphics.hpp>
#include "gameState.h"
#include "game.h"
#include <cstdlib>

const int FRAMES_PER_SECOND = 60;

int main()
{ 
	sf::RenderWindow window(sf::VideoMode(640, 480, 32), "Arkanoid");
	GameState::init(new Game(), &window);

	//bloczek testowy

	while (GameState::getStateID() != GAME_STATE_EXIT)
	{
		sf::Clock clock;

		//EVENTS
		GameState::getCurrentState().handleEvents();

		//LOGIC
		GameState::getCurrentState().logic();
		GameState::changeState();

		//RENDER
		GameState::getCurrentState().render();
		
		if (clock.getElapsedTime().asMilliseconds() < 1000 / FRAMES_PER_SECOND) 
		{ 
			sf::sleep(sf::milliseconds((1000 / FRAMES_PER_SECOND) - clock.getElapsedTime().asMilliseconds())); 
		}
	}

	GameState::freeResources();
	system("pause");
	return 0;
}