//plik implementuj�cy ekran informuj�cy o tw�rcy
#include <iostream>
#include <fstream>
#include "aboutMenu.h"
#include "constants.h"

//konstruktor
AboutMenu::AboutMenu()
{
	//domy�lna obecnie wybrana opcja
	actualOption = 0;

	//wczytuje fonty
	if (!arkanoidFont.loadFromFile("endor.ttf"))
		std::cout << "endor.ttf loading failed" << std::endl;

	//wczytuje tekstury
	if (!tilesTexture.loadFromFile("Graphics/tiles32.png"))		//bloczki t�a
		std::cout << "tiles32.png loading failed" << std::endl;

	if (!buttonsTexture.loadFromFile("Graphics/aboutMenuButtons.png"))	//przyciski
		std::cout << "loadingMenuButtons.png loading failed" << std::endl;

	if (!viewFinderTexture.loadFromFile("Graphics/viewFinder.png"))	//teksturea celownika
		std::cout << "viewFinder.png loading failed" << std::endl;

	//przygotowuj� sprite'a "BACK"
	sf::Sprite backButton;
	backButton.setTexture(buttonsTexture);
	backButton.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(96, 32)));
	backButton.setPosition(sf::Vector2f(272, 350));
	interactiveElements.push_back(backButton);

	//tablica dynamiczna zawieraj�ca odwzorowanie pliku .dat
	//te tablice s� potrzebne tylko podczas budowania mapy
	std::vector<std::vector<sf::Vector2i>> map;
	std::vector<sf::Vector2i> tmpRow;
	std::string tmpString;
	std::ifstream mapFile("Maps/aboutMenu.dat");		//sworzenie obiektu strumienia

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

	//Tworzenie bloczk�w na podstawie map i wrzucanie ich do backgroundElements(vektora)
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
	//przygotowuj� celownik
	viewFinder.setTexture(viewFinderTexture);
	viewFinder.setPosition(sf::Vector2f(interactiveElements[actualOption].getPosition().x - 5, interactiveElements[actualOption].getPosition().y - 5));

	//przygotowuje teksty
	arkanoidText.setFont(arkanoidFont);
	arkanoidText.setCharacterSize(50);
	arkanoidText.setPosition(sf::Vector2f(225, 120));
	arkanoidText.setString(sf::String("Arkanoid"));

	aboutText.setFont(arkanoidFont);
	aboutText.setCharacterSize(20);
	aboutText.setPosition(sf::Vector2f(214, 200));
	aboutText.setString(sf::String("This game was developed \n   by Raphael Solarski\n solarski.rafal@gmail.com"));
}

void AboutMenu::handleEvents()
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
				case 0:	//back to menu
					setNextState(GAME_STATE_MAIN_MENU);
					break;
				}
			}
			else if (event.key.code == sf::Keyboard::Down)
			{
				if (actualOption < 0)
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

void AboutMenu::logic()
{
	//sprawdzam czy okno gry jest otwarte
	if (!window->isOpen())
		setNextState(GAME_STATE_EXIT);

	//aktualizacja pozycji celownika
	viewFinder.setPosition(sf::Vector2f(interactiveElements[actualOption].getPosition().x - 5,
		interactiveElements[actualOption].getPosition().y - 5));
}

void AboutMenu::render()
{
	//rysuje t�o
	for (unsigned int i = 0; i < backgroundElements.size(); i++)
	{
		window->draw(backgroundElements[i]);
	}

	//rysuje blocki przycisk�w
	for (unsigned int i = 0; i < interactiveElements.size(); i++)
	{
		window->draw(interactiveElements[i]);
	}

	//rysuje celownik
	window->draw(viewFinder);

	//rysuje teksty
	window->draw(arkanoidText);
	window->draw(aboutText);

	window->display();
	window->clear();
}