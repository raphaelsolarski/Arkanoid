//plik implemenuj�cy g��wne menu gry
#include <fstream>
#include "mainMenu.h"
#include "constants.h"

MainMenu::MainMenu()
{
	//Ustawienie domy�lnego wyboru
	actualOption = MENU_OPTION_NEW_GAME;

	//wczytuje fonty
	if (!arkanoidFont.loadFromFile("endor.ttf"))
		std::cout << "endor.ttf loading failed" << std::endl;

	//wczytanie potrzebnych tekstur
	if (!tilesTexture.loadFromFile("Graphics/tiles32.png"))				//bloczki do backgroundu
		std::cout << "tiled32.png loading failed" << std::endl;

	if (!buttonsTexture.loadFromFile("Graphics/mainMenuButtons.png"))	//przyciski menu
		std::cout << "mainMenuButtons.png loading failed" << std::endl;

	if (!viewFinderTexture.loadFromFile("Graphics/viewFinder.png"))		//celownik
		std::cout << "viewFinder.png loading failed" << std::endl;

	//przygotowuj� sprite'a celownika
	viewFinderSprite.setTexture(viewFinderTexture);

	//przygotowuj� bloczek "NEW GAME"
	Block newGameBlock(sf::Vector2i(96, 32));
	newGameBlock.setPosition(sf::Vector2f(272, 200));
	newGameBlock.setTexture(buttonsTexture);
	newGameBlock.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(96, 32)));
	interactiveElementsVector.push_back(newGameBlock);

	//przygotowuj� bloczek "LOAD"
	Block loadBlock(sf::Vector2i(96, 32));
	loadBlock.setPosition(sf::Vector2f(272, 248));
	loadBlock.setTexture(buttonsTexture);
	loadBlock.setTextureRect(sf::IntRect(sf::Vector2i(0, 32), sf::Vector2i(96, 32)));
	interactiveElementsVector.push_back(loadBlock);

	//przygotowuj� bloczek "ABOUT"
	Block aboutBlock(sf::Vector2i(96, 32));
	aboutBlock.setPosition(sf::Vector2f(272, 296));
	aboutBlock.setTexture(buttonsTexture);
	aboutBlock.setTextureRect(sf::IntRect(sf::Vector2i(0, 64), sf::Vector2i(96, 32)));
	interactiveElementsVector.push_back(aboutBlock);

	//przygotowuj� bloczek "EXIT"
	Block exitBlock(sf::Vector2i(96, 32));
	exitBlock.setPosition(sf::Vector2f(272, 344));
	exitBlock.setTexture(buttonsTexture);
	exitBlock.setTextureRect(sf::IntRect(sf::Vector2i(0, 96), sf::Vector2i(96, 32)));
	interactiveElementsVector.push_back(exitBlock);

	//tablica dynamiczna zawieraj�ca odwzorowanie pliku .dat
	//te tablice s� potrzebne tylko podczas budowania mapy
	std::vector<std::vector<sf::Vector2i>> map;
	std::vector<sf::Vector2i> tmpRow;
	std::string tmpString;
	std::ifstream mapFile("Maps/mainMenu.dat");		//sworzenie obiektu strumienia

	//Proces mapowania pliku tekstowego do tablicy dynamicznej
	if (mapFile.is_open())
	{
		while (!mapFile.eof())
		{
			mapFile >> tmpString;
			if (tmpString[0] != 'x' && tmpString[2] != 'x')
				tmpRow.push_back(sf::Vector2i(tmpString[0] - '0', tmpString[2] - '0'));
			else
				tmpRow.push_back(sf::Vector2i(-1, -1));

			if (mapFile.peek() == '\n')
			{
				map.push_back(tmpRow);
				tmpRow.clear();
			}
		}
		if (!tmpRow.empty())
		{
			map.push_back(tmpRow);
			tmpRow.clear();
		}
	}

	//Tworzenie bloczk�w na podstawie map i wrzucanie ich do blocksVector'a
	for (unsigned int i = 0; i < map.size(); i++)
	{
		for (unsigned int j = 0; j < map[i].size(); j++)
		{
			if (map[i][j].x != -1)
			{
				Block newBlock(sf::Vector2i(TILE_SIZE_X, TILE_SIZE_Y));
				newBlock.setPosition(sf::Vector2f(static_cast<float>(j * TILE_SIZE_X), static_cast<float>(i * TILE_SIZE_Y)));
				newBlock.setTexture(tilesTexture);
				newBlock.setTextureRect(sf::IntRect(map[i][j].x * TILE_SIZE_X, map[i][j].y * TILE_SIZE_Y, TILE_SIZE_X, TILE_SIZE_Y));
				backgroundElementsVector.push_back(newBlock);
			}
		}
	}

	//przygotowuje teksty
	arkanoidText.setFont(arkanoidFont);
	arkanoidText.setCharacterSize(85);
	arkanoidText.setColor(sf::Color(0, 0, 0, 255));
	arkanoidText.setPosition(sf::Vector2f(165, 60));
	arkanoidText.setString(sf::String("Arkanoid"));
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
				switch (actualOption)
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
				if (actualOption > 0)
					actualOption = static_cast<MenuOption>(actualOption - 1);
				break;

			case sf::Keyboard::Down:
				if (actualOption < 3)
					actualOption = static_cast<MenuOption>(actualOption + 1);
				break;
			}

		}
	}
}

void MainMenu::logic()
{
	if (!window->isOpen())
		setNextState(GAME_STATE_EXIT);

	//aktualizacja pozycji celownika
	viewFinderSprite.setPosition(sf::Vector2f(interactiveElementsVector[static_cast<int>(actualOption)].getPosition().x - 5,
												interactiveElementsVector[static_cast<int>(actualOption)].getPosition().y - 5));
}

void MainMenu::render()
{
	//rysowanie background'u
	for (unsigned int i = 0; i < backgroundElementsVector.size(); i++)
	{
		window->draw(backgroundElementsVector[i]);
	}

	//rysowanie element�w interaktywnych
	for (unsigned int i = 0; i < interactiveElementsVector.size(); i++)
	{
		window->draw(interactiveElementsVector[i]);
	}

	//rysowanie celownika
	window->draw(viewFinderSprite);

	//rysuje nazw� gry
	window->draw(arkanoidText);

	window->display();
	window->clear();
}