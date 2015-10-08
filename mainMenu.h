#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "gameState.h"
#include "block.h"

enum MenuOption
{
	MENU_OPTION_NEW_GAME,
	MENU_OPTION_LOAD_GAME,
	MENU_OPTION_ABOUT,
	MENU_OPTION_EXIT
};

class MainMenu : public GameState
{
public:
	MainMenu();
	void handleEvents();
	void logic();
	void render();
	
private:
	sf::Font gameLogoFont;
	sf::Text gameLogoText;	//Text to display as a game logo
	sf::Texture blocksTexture;
	sf::Texture buttonsTexture;//set of textures for buttons
	sf::Texture viewFinderTexture;
	std::vector<Block> blocksInBackground;
	std::vector<Block> buttonsInMenu;
	sf::Sprite viewFinder;	//viewFinder to point out buttons in menu
	MenuOption currentOption;
	
	//constructor's methods
	void loadNeededTextures();
	void loadNeededFonts();
	void prepareViewFinder();
	void prepareButtons();
	void prepareBackground();
	void prepareLogo();
	
	//logic's methods
	void closeGameWhenWindowClosed();
	void updateViewFinderPosition();
	
	//render's methods
	void drawBackground();
	void drawButtons();
};
