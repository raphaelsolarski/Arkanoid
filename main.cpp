#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include "gameState.h"
#include "game.h"
#include "mainMenu.h"
#include "constants.h"

int main()
{ 
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Arkanoid");

	//State machine init
	GameState::init(new MainMenu, &window);

	//Main Loop
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
		
		//Fps stabilisation
		if (clock.getElapsedTime().asMilliseconds() < 1000 / FRAMES_PER_SECOND) 
		{ 
			sf::sleep(sf::milliseconds((1000 / FRAMES_PER_SECOND) - clock.getElapsedTime().asMilliseconds())); 
		}
	}
	GameState::freeResources();
	return 0;
}
