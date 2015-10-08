#include <fstream>
#include "mainMenu.h"
#include "constants.h"
#include "mapLoader.h"

MainMenu::MainMenu()
{
	//set default option
	currentOption = MENU_OPTION_NEW_GAME;

	loadNeededTextures();
	loadNeededFonts();
	
	prepareViewFinder();
	prepareButtons();
	prepareBackground();
	prepareLogo();
}

void MainMenu::loadNeededTextures()
{
	if (!blocksTexture.loadFromFile("Graphics/tiles32.png"))
		std::cout << "tiled32.png loading failed" << std::endl;
	
	if (!buttonsTexture.loadFromFile("Graphics/mainMenuButtons.png"))
		std::cout << "mainMenuButtons.png loading failed" << std::endl;
	
	if (!viewFinderTexture.loadFromFile("Graphics/viewFinder.png"))
		std::cout << "viewFinder.png loading failed" << std::endl;
}

void MainMenu::loadNeededFonts()
{
	if (!gameLogoFont.loadFromFile("endor.ttf"))
		std::cout << "endor.ttf loading failed" << std::endl;
}

void MainMenu::prepareViewFinder()
{
	viewFinder.setTexture(viewFinderTexture);
}

void MainMenu::prepareButtons()
{
	Block newGameButton(sf::Vector2i(96, 32));
	newGameButton.setPosition(sf::Vector2f(272, 200));
	newGameButton.setTexture(buttonsTexture);
	newGameButton.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(96, 32)));
	buttonsInMenu.push_back(newGameButton);
	
	Block loadButton(sf::Vector2i(96, 32));
	loadButton.setPosition(sf::Vector2f(272, 248));
	loadButton.setTexture(buttonsTexture);
	loadButton.setTextureRect(sf::IntRect(sf::Vector2i(0, 32), sf::Vector2i(96, 32)));
	buttonsInMenu.push_back(loadButton);
	
	Block aboutButton(sf::Vector2i(96, 32));
	aboutButton.setPosition(sf::Vector2f(272, 296));
	aboutButton.setTexture(buttonsTexture);
	aboutButton.setTextureRect(sf::IntRect(sf::Vector2i(0, 64), sf::Vector2i(96, 32)));
	buttonsInMenu.push_back(aboutButton);
	
	Block exitButton(sf::Vector2i(96, 32));
	exitButton.setPosition(sf::Vector2f(272, 344));
	exitButton.setTexture(buttonsTexture);
	exitButton.setTextureRect(sf::IntRect(sf::Vector2i(0, 96), sf::Vector2i(96, 32)));
	buttonsInMenu.push_back(exitButton);
}

void MainMenu::prepareBackground()
{
	MapLoader mapLoader("Maps/mainMenu.dat", &blocksTexture);
	mapLoader.addRule(&blocksInBackground, BLOCK_TYPE_BREAKABLE);
	mapLoader.loadMap();
}

void MainMenu::prepareLogo()
{
	gameLogoText.setFont(gameLogoFont);
	gameLogoText.setCharacterSize(85);
	gameLogoText.setColor(sf::Color(0, 0, 0, 255));
	gameLogoText.setPosition(sf::Vector2f(165, 60));
	gameLogoText.setString(sf::String("Arkanoid"));
}

void MainMenu::handleEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
		else if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Return:
				switch (currentOption)
				{
				case MENU_OPTION_NEW_GAME:
					nextLevel = 1;
					setNextState(GAME_STATE_GAME);
					break;

				case MENU_OPTION_LOAD_GAME:
					setNextState(GAME_STATE_LOADING_MENU);
					break;
					
				case MENU_OPTION_ABOUT:
					setNextState(GAME_STATE_ABOUT_MENU);
					break;

				case MENU_OPTION_EXIT:
					setNextState(GAME_STATE_EXIT);
					break;
				}	
				break;

			case sf::Keyboard::Up:
				if (currentOption > 0)
					currentOption = static_cast<MenuOption>(currentOption - 1);
				break;

			case sf::Keyboard::Down:
				if (currentOption < 3)
					currentOption = static_cast<MenuOption>(currentOption + 1);
				break;
			
			default:;
			}
		}
	}
}

void MainMenu::logic()
{
	closeGameWhenWindowClosed();
	updateViewFinderPosition();
}

void MainMenu::closeGameWhenWindowClosed()
{
	if (!window->isOpen())
		setNextState(GAME_STATE_EXIT);
}

void MainMenu::updateViewFinderPosition()
{
	viewFinder.setPosition(sf::Vector2f(buttonsInMenu[static_cast<int>(currentOption)].getPosition().x - 5,
										buttonsInMenu[static_cast<int>(currentOption)].getPosition().y - 5));
}

void MainMenu::render()
{
	drawBackground();
	drawButtons();
	window->draw(viewFinder);
	window->draw(gameLogoText);

	window->display();
	window->clear();
}

void MainMenu::drawBackground()
{
	for (unsigned int i = 0; i < blocksInBackground.size(); i++)
	{
		window->draw(blocksInBackground[i]);
	}
}

void MainMenu::drawButtons()
{
	for (unsigned int i = 0; i < buttonsInMenu.size(); i++)
	{
		window->draw(buttonsInMenu[i]);
	}
}