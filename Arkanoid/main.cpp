#include <iostream>
#include <SFML\Graphics.hpp>
#include "gameState.h"
#include "game.h"
#include <cstdlib>

//docelowa liczba klatek na sekundê
const int FRAMES_PER_SECOND = 60;

int main()
{ 
	//stworzenie okna sfml
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Arkanoid");

	//inicjalizacja state machine
	GameState::init(new Game(), &window);

	//bloczek testowy
	std::cout << window.getSize().x << std::endl;

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
		
		//Stabilizacja fps'ów
		if (clock.getElapsedTime().asMilliseconds() < 1000 / FRAMES_PER_SECOND) 
		{ 
			sf::sleep(sf::milliseconds((1000 / FRAMES_PER_SECOND) - clock.getElapsedTime().asMilliseconds())); 
		}
	}
	GameState::freeResources();
	return 0;
}