//plik nag³ówkowy menu pora¿ki
#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include "gameState.h"

class AboutMenu : public GameState
{
public:
	AboutMenu();		//konstruktor
	void handleEvents();
	void logic();
	void render();

private:
	sf::Font arkanoidFont;
	sf::Text arkanoidText;	//nazwa gry
	sf::Text aboutText;		//tekst
	sf::Texture tilesTexture;	//set teksturek do background'u
	sf::Texture buttonsTexture;	//set teksturek do "przycisków"
	sf::Texture viewFinderTexture;		//tekstura celownika
	std::vector<sf::Sprite> interactiveElements;
	std::vector<sf::Sprite> backgroundElements;
	sf::Sprite viewFinder;	//sprite celownika
	int actualOption;		//numer obecnie wybranej opcji
};