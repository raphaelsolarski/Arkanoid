#include <fstream>
#include "pauseMenu.h"

//konstruktor
PauseMenu::PauseMenu()
{
	//domyœlna obecnie wybrana opcja
	actualOption = 0;

	//wczytuje tekstury
	if (!tilesTexture.loadFromFile("Graphics/tiles32.png"))		//bloczki t³a
		std::cout << "tiles32.png loading failed" << std::endl;

	if (!buttonsTexture.loadFromFile("Graphics/pauseMenuButtons.png"))	//przyciski
		std::cout << "loadingMenuButtons.png loading failed" << std::endl;

	if (!viewFinderTexture.loadFromFile("Graphics/viewFinder.png"))	//teksturea celownika
		std::cout << "viewFinder.png loading failed" << std::endl;

	//przygotowujê sprite'a "RESTUME"
	sf::Sprite restumeButton;
	restumeButton.setTexture(buttonsTexture);
	restumeButton.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(96, 32)));
	restumeButton.setPosition(sf::Vector2f(272, 200));
	interactiveElements.push_back(restumeButton);

	//przygotowujê sprite'a "MENU"
	sf::Sprite menuButton;
	menuButton.setTexture(buttonsTexture);
	menuButton.setTextureRect(sf::IntRect(sf::Vector2i(0, 32), sf::Vector2i(96, 32)));
	menuButton.setPosition(sf::Vector2f(272, 248));
	interactiveElements.push_back(menuButton);

	//przygotowujê sprite'a "EXIT GAME"
	sf::Sprite exitButton;
	exitButton.setTexture(buttonsTexture);
	exitButton.setTextureRect(sf::IntRect(sf::Vector2i(0, 64), sf::Vector2i(96, 32)));
	exitButton.setPosition(sf::Vector2f(272, 296));
	interactiveElements.push_back(exitButton);

	//tablica dynamiczna zawieraj¹ca odwzorowanie pliku .dat
	//te tablice s¹ potrzebne tylko podczas budowania mapy
	std::vector<std::vector<sf::Vector2i>> map;
	std::vector<sf::Vector2i> tmpRow;
	std::string tmpString;
	std::ifstream mapFile("Maps/pauseMenu.dat");		//sworzenie obiektu strumienia

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

//destruktor
PauseMenu::~PauseMenu()
{

}

//metody wirtualne dziedziczone od GameState
//czyli MainLoop
void PauseMenu::handleEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window->close();
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Return)
			{
				switch (actualOption)
				{
				case 0:
					setNextState(GAME_STATE_RESTUME);
					break;
				case 1:
					setNextState(GAME_STATE_MAIN_MENU);
					break;
				case 2:
					setNextState(GAME_STATE_EXIT);
					break;
				}
			}
			else if (event.key.code == sf::Keyboard::Down)
			{
				if (actualOption < 2)
					actualOption++;
			}
			else if (event.key.code == sf::Keyboard::Up)
			{
				if (actualOption > 0)
					actualOption--;
			}
		}
	}
}

void PauseMenu::logic()
{
	//sprawdzam czy okno gry jest otwarte
	if (!window->isOpen())
		setNextState(GAME_STATE_EXIT);

	//aktualizacja pozycji celownika
	viewFinder.setPosition(sf::Vector2f(interactiveElements[actualOption].getPosition().x - 5,
		interactiveElements[actualOption].getPosition().y - 5));
}

void PauseMenu::render()
{
	//rysuje t³o
	for (unsigned int i = 0; i < backgroundElements.size(); i++)
	{
		window->draw(backgroundElements[i]);
	}
	
	//rysuje blocki przycisków
	for (unsigned int i = 0; i < interactiveElements.size(); i++)
	{
		window->draw(interactiveElements[i]);
	}

	//rysuje celownik
	window->draw(viewFinder);

	window->display();
	window->clear();
}