//plik nag��wkowy state'a g��wnej rogrywki
#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "block.h"
#include "ball.h"
#include "gameState.h"

class Game : public GameState
{
public:
	Game(int level); //konstruktor - tutaj znajduje si� modu� wczytuj�cy map� dla wskazanego levela
	~Game();	//destruktor
	//metody wirtualne dziedziczone od GameState
	//czyli MainLoop
	void handleEvents();
	void logic();
	void render();
private:
	unsigned int blocksToWin;	//licznik ile zosta�o blok�w do zniszczenia
	Ball * ball;		//Pi�eczka
	Block * paddle;		//Paletka
	std::vector<Block> blocksVector;	//wektor zawieraj�cy blocki znajduj�ce si� wewn�trz otoczki
	std::vector<Block> borderVector;	//wektor zabieraj�cy bloczki sk�adaj�ce si� na otoczk�
	sf::Texture tilesTexture;	//tekstura bloczk�w planszy
	sf::Texture paddleTexture;	//tekstura bloczka rakiety
	void prepareBall();
	void preparePaddle();
	void loadMap(int level);
	void closeGameWhenWindowClosed();
	void closeGameWhenBallOutside();
};
