//plik nag³ówkowy state'a g³ównej rogrywki
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
	Game();	//konstruktor - tutaj znajduje siê modu³ wczytuj¹cy mapê
	~Game();	//destruktor
	//metody wirtualne dziedziczone od GameState
	//czyli MainLoop
	void handleEvents();
	void logic();
	void render();

private:
	unsigned int blocksToWin;	//licznik ile zosta³o bloków do zniszczenia
	sf::Vector2i paddleSize;	//wielkoœæ paletki
	Ball * ball;		//Pi³eczka
	Block * paddle;		//Paletka
	std::vector<Block> blocksVector;	//wektor zawieraj¹cy blocki znajduj¹ce siê wewn¹trz otoczki
	std::vector<Block> borderVector;	//wektor zabieraj¹cy bloczki sk³adaj¹ce siê na otoczkê
	sf::Texture tilesTexture;	//tekstura bloczków planszy
	sf::Texture paddleTexture;	//tekstura bloczka rakiety
};