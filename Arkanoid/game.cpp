//plik implementacyjny state'a g³ównej rozgrywki
#include "game.h"
#include <fstream>
#include <string>
#include <iostream>

const sf::Vector2f startPaddlePosition = sf::Vector2f(256, 448);	//pozycja pocz¹tkowa paletki
const float paddleSpeed = 7.0f;	//prêdkoœæ poruszania siê paletki

const int TILE_SIZE_X = 32;	//wymiary bloczków
const int TILE_SIZE_Y = 32;

Game::Game()
{
	paddleSize = sf::Vector2i(128, 32);

	//Wczytanie tekstury rakiety
	if (!paddleTexture.loadFromFile("paddle.png"))
		std::cout << "paddle.png loading failed" << std::endl;
	
	//stworzenie bloczka paletki
	Block paddleSprite;
	paddleSprite.setTexture(paddleTexture);
	paddleSprite.setPosition(startPaddlePosition);

	//wrzucenie blocka paletki do vektora bloczków - bloczek paletki zawsze bêdzie na blocksVector[0]
	blocksVector.push_back(paddleSprite);

	//WCZYTYWANIE MAPY
	if (!tilesTexture.loadFromFile("tiles32.png"))
		std::cout << "tiles32.png loading failed" << std::endl;

	//tworzê obiekt strumienia
	std::ifstream mapFile("restrictedMap.dat");

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
				Block newBlock;
				newBlock.setPosition(sf::Vector2f(static_cast<float>(j * TILE_SIZE_X), static_cast<float>(i * TILE_SIZE_Y)));
				newBlock.setTexture(tilesTexture);
				newBlock.setTextureRect(sf::IntRect(map[i][j].x * TILE_SIZE_X, map[i][j].y * TILE_SIZE_Y, TILE_SIZE_X, TILE_SIZE_Y));
				blocksVector.push_back(newBlock);
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
	//sprawdzenie czy okno nie zosta³o zamkniête
	if (!window->isOpen())
	{
		setNextState(GAME_STATE_EXIT);
	}

	//live input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		if (blocksVector[0].getPosition().x > TILE_SIZE_X)
			blocksVector[0].move(sf::Vector2f(-paddleSpeed, 0));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		if(blocksVector[0].getPosition().x < window->getSize().x - paddleSize.x- TILE_SIZE_X)
			blocksVector[0].move(sf::Vector2f(paddleSpeed, 0));
}

void Game::render()
{
	for (unsigned int i = 0; i < blocksVector.size(); i++)
	{
		window->draw(blocksVector[i]);
	}
	window->display();
	window->clear();
}