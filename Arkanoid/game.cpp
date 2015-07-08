//plik implementacyjny state'a g³ównej rozgrywki
#include "game.h"
#include <fstream>
#include <string>
#include <iostream>

Game::Game()
{
	//WCZYTYWANIE MAPY
	const int TILE_SIZE_X = 32;
	const int TILE_SIZE_Y = 32;

	if (!tilesTexture.loadFromFile("tiles32.png"))
		std::cout << "tiles32.png loading failed" << std::endl;

	//tworzê obiekt strumienia
	std::ifstream mapFile("level01.dat");

	//tablica dynamiczna zawieraj¹ca odwzorowanie pliku .dat
	//te tablice s¹ potrzebne tylko podczas budowania mapy
	std::vector<std::vector<sf::Vector2i>> map;
	std::vector<sf::Vector2i> tmpRow;

	std::string tmpString;

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

	////log testowy do konsoli
	//for (unsigned int i = 0; i < map.size(); i++)
	//{
	//	for (unsigned int j = 0; j < map[i].size(); j++)
	//	{
	//		std::cout << map[i][j].x << "," << map[i][j].y << "\t";
	//	}
	//	std::cout << std::endl;
	//}

	for (unsigned int i = 0; i < map.size(); i++)
	{
		for (unsigned int j = 0; j < map[i].size(); j++)
		{
			if (map[i][j].x != -1)
			{
				sf::Sprite actualSprite;
				actualSprite.setPosition(sf::Vector2f(static_cast<float>(j * TILE_SIZE_X), static_cast<float>(i * TILE_SIZE_Y)));
				actualSprite.setTexture(tilesTexture);
				actualSprite.setTextureRect(sf::IntRect(map[i][j].x * TILE_SIZE_X, map[i][j].y * TILE_SIZE_Y, TILE_SIZE_X, TILE_SIZE_Y));
				spritesVector.push_back(actualSprite);
			}
		}
	}
}
Game::~Game()
{
}

void Game::handleEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
	}
}

void Game::logic()
{
	if (!window->isOpen())
	{
		setNextState(GAME_STATE_EXIT);
	}
}

void Game::render()
{
	for (unsigned int i = 0; i < spritesVector.size(); i++)
	{
		window->draw(spritesVector[i]);
	}
	window->display();
	window->clear(sf::Color::Green);
}