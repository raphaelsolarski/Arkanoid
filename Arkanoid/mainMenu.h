//plik nag³ówkowy menu g³ównego 
#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include "gameState.h"
#include "block.h"

//typ okreœlaj¹cy opcje w menu
enum MenuOption
{
	MENU_OPTION_NEW_GAME,
	MENU_OPTION_LOAD_GAME,
	MENU_OPTION_EXIT
};

class MainMenu : public GameState
{
public:
	MainMenu();		//konstruktor
	//metody do MainLoop
	void handleEvents();
	void logic();
	void render();
private:
	sf::Texture tilesTexture;	//tekstura bloczków z których dla klimatu bêdzie tak¿e zbudowane menu
	sf::Texture buttonsTexture;	//set tekstur do przycisków
	sf::Texture viewFinderTexture;	//tekstura do celownika
	sf::Texture gameLogoTexture;	//tekstura logo(du¿e)
	std::vector<Block> backgroundElementsVector;	//wektor zawieraj¹cy wszystkie elementy stanowi¹ce background
	std::vector<Block> interactiveElementsVector;	//wektor zawieraj¹cy interaktywne elementy menu(w odpowiedniej kolejnoœci)
	sf::Sprite viewFinderSprite;	//sprite celownika wyboru
	MenuOption actualOption;	//pole okreœlaj¹ce aktualnie najechan¹ opcjê w menu
};