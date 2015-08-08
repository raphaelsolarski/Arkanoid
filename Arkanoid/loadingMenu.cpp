//implementacja menu wczytywania poziomu
#include <fstream>
#include "loadingMenu.h"
#include "constants.h"

LoadingMenu::LoadingMenu()
{
	//domyœlna obecnie wybrana opcja
	actualOption = 0;

	//wczytuje tekstury
	if (!tilesTexture.loadFromFile("Graphics/tiles32.png"))		//bloczki t³a
		std::cout << "tiles32.png loading failed" << std::endl;

	if (!buttonsTexture.loadFromFile("Graphics/loadingMenuButtons.png"))	//przyciski
		std::cout << "loadingMenuButtons.png loading failed" << std::endl;

	if (!viewFinderTexture.loadFromFile("Graphics/viewFinder.png"))	//teksturea celownika
		std::cout << "viewFinder.png loading failed" << std::endl;

	//przygotowujê sprite'a "BACK"
	sf::Sprite backButton;
	backButton.setTexture(buttonsTexture);
	backButton.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(96, 32)));
	backButton.setPosition(sf::Vector2f(64, 32));
	interactiveElements.push_back(backButton);

	//przygotowanie sprite'ów leveli(przycisków)
	unsigned int collumn = 0;
	for (unsigned int i = 1; i <= levelsInMenu; i++)
	{
		if (i % 9 == 0)
			collumn++;

		sf::Sprite newLevelBlock;
		newLevelBlock.setTexture(buttonsTexture);
		newLevelBlock.setTextureRect(sf::IntRect(sf::Vector2i(0, i*32), sf::Vector2i(96, 32)));
		newLevelBlock.setPosition(sf::Vector2f(backButton.getPosition().x + collumn * 106, backButton.getPosition().y + 42 * i - 378 * collumn));
		interactiveElements.push_back(newLevelBlock);
	}

	//tablica dynamiczna zawieraj¹ca odwzorowanie pliku .dat
	//te tablice s¹ potrzebne tylko podczas budowania mapy
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

	//Tworzenie bloczków na podstawie map i wrzucanie ich do backgroundElements(vektora)
	for (unsigned int i = 0; i < map.size(); i++)
	{
		for (unsigned int j = 0; j < map[i].size(); j++)
		{
			if (map[i][j].x != -1)
			{
				sf::Sprite newSprite;
				newSprite.setPosition(sf::Vector2f(static_cast<float>(j * TILE_SIZE_X), static_cast<float>(i * TILE_SIZE_Y)));
				newSprite.setTexture(tilesTexture);
				newSprite.setTextureRect(sf::IntRect(map[i][j].x * TILE_SIZE_X, map[i][j].y * TILE_SIZE_Y, TILE_SIZE_X, TILE_SIZE_Y));
				backgroundElements.push_back(newSprite);
			}
		}
	}

	//przygotowujê celownik
	viewFinder.setTexture(viewFinderTexture);
	viewFinder.setPosition(sf::Vector2f(interactiveElements[actualOption].getPosition().x - 5, interactiveElements[actualOption].getPosition().y - 5));
}

void LoadingMenu::handleEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Return)
			{
				if (actualOption == 0)
				{
					setNextState(GAME_STATE_MAIN_MENU);
				}
				else
				{	//wybrano bloczek level'a
					nextLevel = actualOption;
					setNextState(GAME_STATE_GAME);
				}
			}
			else if (event.key.code == sf::Keyboard::Down)	//naciœniêto klawisz w dó³
			{
				if (actualOption < levelsInMenu)
					actualOption++;
			}
			else if (event.key.code == sf::Keyboard::Up)	//naciœniêto klawisz do góry
			{
				if (actualOption > 0)
					actualOption--;
			}
		}
	}
}

void LoadingMenu::logic()
{
	//sprawdzam czy onko wci¹¿ jest otwarte
	if (!window->isOpen())
		setNextState(GAME_STATE_EXIT);

	//uaktualniam pozycjê celownika
	viewFinder.setPosition(sf::Vector2f(interactiveElements[actualOption].getPosition().x - 5, interactiveElements[actualOption].getPosition().y - 5));
}

void LoadingMenu::render()
{
	//rysuje elementy backgroundu
	for (unsigned int i = 0; i < backgroundElements.size(); i++)
	{
		window->draw(backgroundElements[i]);
	}

	//rysuje przyciski
	for (unsigned int i = 0; i < interactiveElements.size(); i++)
	{
		window->draw(interactiveElements[i]);
	}

	//renderuje celownik
	window->draw(viewFinder);

	window->display();
	window->clear();
}