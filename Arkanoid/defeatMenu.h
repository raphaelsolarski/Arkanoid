//plik nag³ówkowy menu pora¿ki
#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include "gameState.h"

class DefeatMenu : public GameState
{
public:
	DefeatMenu();		//konstruktor
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