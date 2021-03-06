//plik implementuj�cy menu uko�czenia poziomu
#include <iostream>
#include <fstream>
#include "levelFinishedMenu.h"
#include "constants.h"

//konstruktor
LevelFinishedMenu::LevelFinishedMenu()
{
	//domy�lna obecnie wybrana opcja
	actualOption = 0;

	//wczytuje fonty
	if (!arkanoidFont.loadFromFile("endor.ttf"))
		std::cout << "endor.ttf loading failed" << std::endl;

	//wczytuje tekstury
	if (!tilesTexture.loadFromFile("Graphics/tiles32.png"))		//bloczki t�a
		std::cout << "tiles32.png loading failed" << std::endl;

	if (!buttonsTexture.loadFromFile("Graphics/levelFinishedMenuButtons.png"))	//przyciski
		std::cout << "loadingMenuButtons.png loading failed" << std::endl;

	if (!viewFinderTexture.loadFromFile("Graphics/viewFinder.png"))	//teksturea celownika
		std::cout << "viewFinder.png loading failed" << std::endl;

	//przygotowuj� sprite'a "NEXT"
	sf::Sprite nextButton;
	nextButton.setTexture(buttonsTexture);
	nextButton.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(96, 32)));
	nextButton.setPosition(sf::Vector2f(272, 200));
	interactiveElements.push_back(nextButton);

	//przygotowuj� sprite'a "REPEAT"
	sf::Sprite repeatButton;
	repeatButton.setTexture(buttonsTexture);
	repeatButton.setTextureRect(sf::IntRect(sf::Vector2i(0, 32), sf::Vector2i(96, 32)));
	repeatButton.setPosition(sf::Vector2f(272, 248));
	interactiveElements.push_back(repeatButton);

	//przygotowuj� sprite'a "MENU"
	sf::Sprite menuButton;
	menuButton.setTexture(buttonsTexture);
	menuButton.setTextureRect(sf::IntRect(sf::Vector2i(0, 64), sf::Vector2i(96, 32)));
	menuButton.setPosition(sf::Vector2f(272, 296));
	interactiveElements.push_back(menuButton);

	//tablica dynamiczna zawieraj�ca odwzorowanie pliku .dat
	//te tablice s� potrzebne tylko podczas budowania mapy
	std::vector<std::vector<sf::Vector2i>> map;
	std::vector<sf::Vector2i> tmpRow;
	std::string tmpString;
	std::ifstream mapFile("Maps/levelFinishedMenu.dat");		//sworzenie obiektu strumienia

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
	arkanoidText.setCharacterSize(85);
	arkanoidText.setColor(sf::Color(0, 0, 0, 255));
	arkanoidText.setPosition(sf::Vector2f(165, 60));
	arkanoidText.setString(sf::String("Arkanoid"));
}

//destruktor
LevelFinishedMenu::~LevelFinishedMenu()
{

}

//metody wirtualne dziedziczone od GameState
//czyli MainLoop
void LevelFinishedMenu::handleEvents()
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
				case 0:	//nast�pny poziom
					nextLevel++;
					setNextState(GAME_STATE_GAME);
					break;

				case 1:	//powt�rzenie poziomu
					setNextState(GAME_STATE_GAME);
					break;

				case 2:	//do menu
					setNextState(GAME_STATE_MAIN_MENU);
					break;
				}
			}
			else if (event.key.code == sf::Keyboard::Down)	//naci�ni�to klawisz w d�
			{
				if (actualOption < 2)
					actualOption++;
			}
			else if (event.key.code == sf::Keyboard::Up)	//naci�ni�to klawisz do g�ry
			{
				if (actualOption > 0)
					actualOption--;
			}
		}
	}
}

void LevelFinishedMenu::logic()
{
	//sprawdzam czy okno nie zosta�o zamkni�te
	if (!window->isOpen())
	{
		setNextState(GAME_STATE_EXIT);
	}

	//uaktualniam pozycj� celownika
	viewFinder.setPosition(sf::Vector2f(interactiveElements[actualOption].getPosition().x - 5, interactiveElements[actualOption].getPosition().y - 5));
}

void LevelFinishedMenu::render()
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

	//wy�wietla nazw� gry
	window->draw(arkanoidText);

	window->display();
	window->clear();
}