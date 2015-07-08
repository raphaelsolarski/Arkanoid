//plik nag��wkowy state'a g��wnej rogrywki
#pragma once
#include "block.h"
#include "ball.h"
#include "gameState.h"
#include "SFML\Graphics.hpp"
#include <vector>

class Game : public GameState
{
public:
	Game();	//konstruktor - tutaj znajduje si� modu� wczytuj�cy map�
	~Game();	//destruktor
	//metody wirtualne dziedziczone od GameState
	//czyli MainLoop
	void handleEvents();
	void logic();
	void render();
private:
	sf::Vector2f ballPosition;	//pozycja pi�ki
	sf::Vector2f racketPosition;//pozycja paletki
	std::vector<sf::Sprite> spritesVector;	//wektor zawieraj�cy wszystkie sprite'y
	sf::Texture tilesTexture;	//tekstura wszystkich bloczk�w
};