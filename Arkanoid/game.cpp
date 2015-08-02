//plik implementacyjny state'a g³ównej rozgrywki
#include "game.h"
#include <fstream>
#include <string>
#include <iostream>

const sf::Vector2f startPaddlePosition = sf::Vector2f(256, 448);	//pozycja pocz¹tkowa paletki
const float paddleSpeed = 5.0f;	//prêdkoœæ poruszania siê paletki

const sf::Vector2i ballSize = sf::Vector2i(32, 32);
const sf::Vector2f startBallPosition = sf::Vector2f(304, 224);

const int TILE_SIZE_X = 32;	//wymiary bloczków
const int TILE_SIZE_Y = 32;

Game::Game()
{
	paddleSize = sf::Vector2i(128, 32);

	//Stworzenie pi³eczki
	ball = new Ball(ballSize);
	ball->setPosition(startBallPosition);

	//Wczytanie tekstury rakiety
	if (!paddleTexture.loadFromFile("paddle.png"))
		std::cout << "paddle.png loading failed" << std::endl;
	
	//stworzenie bloczka paletki
	Block paddleBlock(paddleSize);
	paddleBlock.setTexture(paddleTexture);
	paddleBlock.setPosition(startPaddlePosition);

	//wrzucenie blocka paletki do vektora bloczków - bloczek paletki zawsze bêdzie na blocksVector[0]
	blocksVector.push_back(paddleBlock);

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

	//Tworzenie bloczków na podstawie map i wrzucanie ich do blocksVector'a
	for (unsigned int i = 0; i < map.size(); i++)
	{
		for (unsigned int j = 0; j < map[i].size(); j++)
		{
			if (map[i][j].x != -1)
			{
				Block newBlock(sf::Vector2i(TILE_SIZE_X, TILE_SIZE_Y));
				//sprawdzam czy nowy bloczek nie zalicza siê do otoczki planszy
				if (i == 0 || j == 0 || j == (SCREEN_WIDTH / TILE_SIZE_X - 1))
				{
					newBlock.setPosition(sf::Vector2f(static_cast<float>(j * TILE_SIZE_X), static_cast<float>(i * TILE_SIZE_Y)));
					newBlock.setTexture(tilesTexture);
					newBlock.setTextureRect(sf::IntRect(map[i][j].x * TILE_SIZE_X, map[i][j].y * TILE_SIZE_Y, TILE_SIZE_X, TILE_SIZE_Y));
					borderVector.push_back(newBlock);
				}
				else
				{
					newBlock.setPosition(sf::Vector2f(static_cast<float>(j * TILE_SIZE_X), static_cast<float>(i * TILE_SIZE_Y)));
					newBlock.setTexture(tilesTexture);
					newBlock.setTextureRect(sf::IntRect(map[i][j].x * TILE_SIZE_X, map[i][j].y * TILE_SIZE_Y, TILE_SIZE_X, TILE_SIZE_Y));
					blocksVector.push_back(newBlock);
				}
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
	
	//obs³u¿enie kolizji
	for (std::vector<Block>::iterator it = blocksVector.begin(); it != blocksVector.end(); it++)
	{
		if (ball->bounce(*it))
			break;
	}

	//przemieszczenie pi³ki
	ball->update();
}

void Game::render()
{
	//rysuje ramkê
	for (unsigned int i = 0; i < borderVector.size(); i++)
	{
		window->draw(borderVector[i]);
	}

	//rysuje blocki wewn¹trz ramki
	for (unsigned int i = 0; i < blocksVector.size(); i++)
	{
		window->draw(blocksVector[i]);
	}

	window->draw(*ball);
	window->display();
	window->clear();
}