//plik implementacyjny state'a g³ównej rozgrywki
#include "game.h"
#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include "constants.h"

Game::Game(int level)
{
	//ustawienie na sztywno wymiarów paletki
	paddleSize = sf::Vector2i(128, 32);

	//Stworzenie pi³eczki
	ball = new Ball(BALL_SIZE);
	ball->setPosition(START_BALL_POSITION);

	//Wczytanie tekstury rakiety
	if (!paddleTexture.loadFromFile("Graphics/paddle.png"))
		std::cout << "paddle.png loading failed" << std::endl;
	
	//stworzenie bloczka paletki
	paddle = new Block(paddleSize);
	paddle->setTexture(paddleTexture);
	paddle->setPosition(START_PADDLE_POSITION);

	//wyzerowanie licznika bloczków do zniszczenia
	blocksToWin = 0;

	//WCZYTYWANIE MAPY
	if (!tilesTexture.loadFromFile("Graphics/tiles32.png"))
		std::cout << "tiles32.png loading failed" << std::endl;

	//tworzê obiekt strumienia
	std::string fileName = "Maps/level" + std::to_string(level) + ".dat";	//tworzê nazwê pliku to odtworzenia
	std::ifstream mapFile(fileName);

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
				{	//mamy do czynienia ze zniszczalnym bloczkiem 
					blocksToWin++;
					newBlock.setBlockType(BLOCK_TYPE_BREAKABLE);
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

	//sprawdzenie czy pi³ka nie wypad³a z planszy
	if (ball->getPosition().y >= 480 - TILE_SIZE_Y)
		setNextState(GAME_STATE_EXIT);

	//sprawdzam czy nie zniszczono wszystkich bloczków
	if (blocksToWin <= 0)
		setNextState(GAME_STATE_EXIT);

	//live input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		if (paddle->getPosition().x > TILE_SIZE_X)
			paddle->move(sf::Vector2f(-PADDLE_SPEED, 0));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		if (paddle->getPosition().x < window->getSize().x - paddleSize.x- TILE_SIZE_X)
			paddle->move(sf::Vector2f(PADDLE_SPEED, 0));
	
	//obs³u¿enie kolizji
	//kolizja z paletk¹
	ball->bounce(*paddle);

	//kolizje z bloczkami
	for (std::vector<Block>::iterator it = blocksVector.begin(); it != blocksVector.end(); it++)
	{
		if (ball->bounce(*it))
		{	
			//jeœli trafiony bloczek jest zniszczalny to nale¿y go zniszczyæ
			if (it->getBlockType() == BLOCK_TYPE_BREAKABLE)
			{
				blocksVector.erase(it);
				blocksToWin--;
			}
			break;
		}
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

	//rysuje bi³kê
	window->draw(*ball);

	//rysuje paletkê
	window->draw(*paddle);

	window->display();
	window->clear();
}