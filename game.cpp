//implementation of main game
#include "game.h"
#include <fstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include "constants.h"

Game::Game(int level)
{
	prepareBall();
	preparePaddle();
	
	blocksToDestroyCounter = 0;
	
	prepareMap(level);
}

void Game::prepareBall()
{
	ball = new Ball(BALL_SIZE);
	ball->setPosition(START_BALL_POSITION);
}

void Game::preparePaddle()
{
	// load paddle's texture
	if (!paddleTexture.loadFromFile("Graphics/paddle.png"))
		std::cout << "paddle.png loading failed" << std::endl;
	
	// create paddle
	paddle = new Block(PADDLE_SIZE);
	paddle->setTexture(paddleTexture);
	paddle->setPosition(START_PADDLE_POSITION);
}

void Game::prepareMap(int level)
{
	//load block tiles
	if (!blocksTexture.loadFromFile("Graphics/tiles32.png"))
	{
		std::cout << "tiles32.png loading failed" << std::endl;
	}
	
	loadMapFromFile(level);
}

void Game::loadMapFromFile(int level)
{
	std::string nameOfFileToLoad = "Maps/level" + std::to_string(level) + ".dat";
	std::ifstream mapFileOfLevel(nameOfFileToLoad);
	
	if (!mapFileOfLevel.is_open())
	{
		std::cout << "There isn't suitable map file" << std::endl;
		system("pause");
		exit(-1);
	}
	
	std::vector<std::vector<sf::Vector2i> > map;
	std::vector<sf::Vector2i> newRowOfMap;
	
	std::string currentTurple;
	
	//Load values form .dat file into dynamic arrays
	if (mapFileOfLevel.is_open())
	{
		while (!mapFileOfLevel.eof())
		{
			mapFileOfLevel >> currentTurple;
			if (currentTurple[0] != 'x' && currentTurple[2] != 'x')
				newRowOfMap.push_back(sf::Vector2i(currentTurple[0] - '0', currentTurple[2] - '0'));
			else
				newRowOfMap.push_back(sf::Vector2i(-1, -1));
			
			if (mapFileOfLevel.peek() == '\n')
			{
				map.push_back(newRowOfMap);
				newRowOfMap.clear();
			}
		}
		if (!newRowOfMap.empty())
		{
			map.push_back(newRowOfMap);
			newRowOfMap.clear();
		}
	}
	
	
	for (unsigned int row = 0; row < map.size(); row++)
	{
		for (unsigned int column = 0; column < map[row].size(); column++)
		{
			if (map[row][column].x != -1)
			{
				Block newBlock(sf::Vector2i(TILE_SIZE_X, TILE_SIZE_Y));
				//check if the block belongs to border
				if (row == 0 || column == 0 || column == (SCREEN_WIDTH / TILE_SIZE_X - 1))
				{
					newBlock.setPosition(sf::Vector2f(static_cast<float>(column * TILE_SIZE_X), static_cast<float>(row * TILE_SIZE_Y)));
					newBlock.setTexture(blocksTexture);
					newBlock.setTextureRect(sf::IntRect(map[row][column].x * TILE_SIZE_X, map[row][column].y * TILE_SIZE_Y, TILE_SIZE_X, TILE_SIZE_Y));
					blocksOfBorder.push_back(newBlock);
				}
				else
				{	
					// the block is breakable
					blocksToDestroyCounter++;
					newBlock.setBlockType(BLOCK_TYPE_BREAKABLE);
					newBlock.setPosition(sf::Vector2f(static_cast<float>(column * TILE_SIZE_X), static_cast<float>(row * TILE_SIZE_Y)));
					newBlock.setTexture(blocksTexture);
					newBlock.setTextureRect(sf::IntRect(map[row][column].x * TILE_SIZE_X, map[row][column].y * TILE_SIZE_Y, TILE_SIZE_X, TILE_SIZE_Y));
					blocksInsideBorder.push_back(newBlock);
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

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
				setNextState(GAME_STATE_PAUSE_MENU);
		}
	}
}

void Game::logic()
{
	closeEntireGameWhenWindowClosed();
	closeGameWhenBallOutside();
	closeGameWhenAllBlocksDestroyed();

	handleCollisions();
	
	updatePaddlePosition();
	ball->update();
}

void Game::closeEntireGameWhenWindowClosed()
{
	if (!window->isOpen())
	{
		setNextState(GAME_STATE_EXIT);
	}
}

void Game::closeGameWhenBallOutside()
{
	if (ball->getPosition().y >= SCREEN_HEIGHT - ball->getBallSize().y)
		setNextState(GAME_STATE_DEFEAT_MENU);
}

void Game::closeGameWhenAllBlocksDestroyed()
{
	if (blocksToDestroyCounter <= 0)
		setNextState(GAME_STATE_LEVEL_FINISHED_MENU);
}

void Game::handleCollisions()
{
	//collisions with paddle
	ball->bounce(*paddle);

	//collisions with blocks
	for (std::vector<Block>::iterator it = blocksInsideBorder.begin(); it != blocksInsideBorder.end(); it++)
	{
		if (ball->bounce(*it))
		{	
			//if the block collided with ball, the block will be destroyed
			if (it->getBlockType() == BLOCK_TYPE_BREAKABLE)
			{
				blocksInsideBorder.erase(it);
				blocksToDestroyCounter--;
			}
			break;
		}
	}
}

void Game::updatePaddlePosition()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		if (paddle->getPosition().x > TILE_SIZE_X)
			paddle->move(sf::Vector2f(-PADDLE_SPEED, 0));
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			if (paddle->getPosition().x < window->getSize().x - PADDLE_SIZE.x- TILE_SIZE_X)
				paddle->move(sf::Vector2f(PADDLE_SPEED, 0));
}

void Game::render()
{
	drawBorder();
	drawBlocksInsideBorder();
	window->draw(*ball);
	window->draw(*paddle);

	window->display();
	window->clear();
}

void Game::drawBorder()
{
	for (unsigned int i = 0; i < blocksOfBorder.size(); i++)
	{
		window->draw(blocksOfBorder[i]);
	}
}

void Game::drawBlocksInsideBorder()
{
	for (unsigned int i = 0; i < blocksInsideBorder.size(); i++)
	{
		window->draw(blocksInsideBorder[i]);
	}
}




