//plik nag��wkowy state'a g��wnej rogrywki
#pragma once
#include "block.h"
#include "ball.h"
#include "gameState.h"
#include "SFML\Graphics.hpp"
#include <vector>

//na sztywno ustawione rozmiary okna
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

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
	unsigned int blocksToWin;	//licznik ile zosta�o blok�w do zniszczenia
	sf::Vector2i paddleSize;	//wielko�� paletki
	Ball * ball;		//Pi�eczka
	Block * paddle;		//Paletka
	std::vector<Block> blocksVector;	//wektor zawieraj�cy blocki znajduj�ce si� wewn�trz otoczki
	std::vector<Block> borderVector;	//wektor zabieraj�cy bloczki sk�adaj�ce si� na otoczk�
	sf::Texture tilesTexture;	//tekstura bloczk�w planszy
	sf::Texture paddleTexture;	//tekstura bloczka rakiety
};