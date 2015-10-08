//implementation of main game
#include <fstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include "constants.h"
#include "game.h"
#include "mapLoader.h"

unsigned int Game::blocksToDestroyCounter = 0;

Game::Game(int level)
{
	prepareBall();
	preparePaddle();
		
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
	loadMapFromFileWithRules(level);
}

void Game::loadMapFromFileWithRules(int level)
{
	std::string nameOfFileToLoad = "Maps/level" + std::to_string(level) + ".dat";
	
	MapLoader mapLoader(nameOfFileToLoad, &blocksTexture);
	mapLoader.addRule(ruleOfBorderBlocks, &blocksOfBorder, BLOCK_TYPE_UNBREAKABLE);
	mapLoader.addRule(ruleOfBlocksInsideBorder, &blocksInsideBorder, BLOCK_TYPE_BREAKABLE);
	mapLoader.loadMap();
}

bool Game::ruleOfBorderBlocks(sf::Vector2u positionOnMap)
{
	if(positionOnMap.x == 0 || positionOnMap.x == 19 || positionOnMap.y == 0)
		return true;
	else
		return false;
}

bool Game::ruleOfBlocksInsideBorder(sf::Vector2u positionOnMap)
{
	if(positionOnMap.x != 0 && positionOnMap.x != 19 && positionOnMap.y != 0)
	{
		blocksToDestroyCounter++;
		return true;
	}
	else
		return false;
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