//plik nag��wkowy menu g��wnego 
#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include "gameState.h"
#include "block.h"

//typ okre�laj�cy opcje w menu
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
	sf::Texture tilesTexture;	//tekstura bloczk�w z kt�rych dla klimatu b�dzie tak�e zbudowane menu
	sf::Texture buttonsTexture;	//set tekstur do przycisk�w
	sf::Texture viewFinderTexture;	//tekstura do celownika
	sf::Texture gameLogoTexture;	//tekstura logo(du�e)
	std::vector<Block> backgroundElementsVector;	//wektor zawieraj�cy wszystkie elementy stanowi�ce background
	std::vector<Block> interactiveElementsVector;	//wektor zawieraj�cy interaktywne elementy menu(w odpowiedniej kolejno�ci)
	sf::Sprite viewFinderSprite;	//sprite celownika wyboru
	MenuOption actualOption;	//pole okre�laj�ce aktualnie najechan� opcj� w menu
};