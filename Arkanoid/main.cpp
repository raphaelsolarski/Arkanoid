#include <iostream>
#include <SFML\Graphics.hpp>
#include "gameState.h"
#include "game.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480, 32), "Arkanoid");
	GameState::init(new Game(), &window);

	while (GameState::getStateID() != GAME_STATE_EXIT)
	{
		//EVENTS
		GameState::getCurrentState().handleEvents();
		//LOGIC
		GameState::getCurrentState().logic();
		GameState::changeState();
		//RENDER
		GameState::getCurrentState().render();
	}
	return 0;
}