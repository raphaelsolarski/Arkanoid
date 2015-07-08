//plik nag³ówkowy state'a g³ównej rogrywki
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
	sf::Vector2f ballPosition;	//pozycja pi³ki
	sf::Vector2f racketPosition;//pozycja paletki
};