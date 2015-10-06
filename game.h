//plik nag³ówkowy state'a g³ównej rogrywki
#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "block.h"
#include "ball.h"
#include "gameState.h"

class Game : public GameState
{
public:
	Game(int level); //konstruktor - tutaj znajduje siê modu³ wczytuj¹cy mapê dla wskazanego levela
	~Game();	//destruktor
	//metody wirtualne dziedziczone od GameState
	//czyli MainLoop
	void handleEvents();
	void logic();
	void render();
private:
	unsigned int blocksToWin;	//licznik ile zosta³o bloków do zniszczenia
	Ball * ball;		//Pi³eczka
	Block * paddle;		//Paletka
	std::vector<Block> blocksVector;	//wektor zawieraj¹cy blocki znajduj¹ce siê wewn¹trz otoczki
	std::vector<Block> borderVector;	//wektor zabieraj¹cy bloczki sk³adaj¹ce siê na otoczkê
	sf::Texture tilesTexture;	//tekstura bloczków planszy
	sf::Texture paddleTexture;	//tekstura bloczka rakiety
	void prepareBall();
	void preparePaddle();
	void loadMap(int level);
	void closeGameWhenWindowClosed();
	void closeGameWhenBallOutside();
};
