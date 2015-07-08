//plik nag��wkowy state'a g��wnej rogrywki
#pragma once
#include "block.h"
#include "ball.h"
#include "gameState.h"
#include "SFML\Graphics.hpp"

class Game : public GameState
{
public:
	//metody wirtualne dziedziczone od GameState
	//czyli MainLoop
	void handleEvents();
	void logic();
	void render();
private:
	sf::Vector2f ballPosition;	//pozycja pi�ki
	sf::Vector2f racketPosition;//pozycja paletki
};