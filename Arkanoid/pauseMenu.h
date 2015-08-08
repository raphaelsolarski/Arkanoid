#include <SFML\Graphics.hpp>
#include <iostream>
#include "gameState.h"
#include "constants.h"

class PauseMenu : public GameState
{
public:
	PauseMenu();	//konstruktor
	~PauseMenu();	//destruktor
	//metody wirtualne dziedziczone od GameState
	//czyli MainLoop
	void handleEvents();
	void logic();
	void render();
private:
	sf::Texture tilesTexture;	//set teksturek do background'u
	sf::Texture buttonsTexture;	//set teksturek do "przycisków"
	sf::Texture viewFinderTexture;		//tekstura celownika
	std::vector<sf::Sprite> interactiveElements;
	std::vector<sf::Sprite> backgroundElements;
	sf::Sprite viewFinder;	//sprite celownika
	int actualOption;		//numer obecnie wybranej opcji
};