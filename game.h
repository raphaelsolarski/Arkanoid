//header file of main game module
#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "block.h"
#include "ball.h"
#include "gameState.h"

class Game : public GameState
{
public:
	Game(int level);
	~Game();
	void handleEvents();
	void logic();
	void render();
	
private:
	unsigned int blocksToDestroyCounter;
	Ball * ball;
	Block * paddle;
	std::vector<Block> blocksInsideBorder;
	std::vector<Block> blocksOfBorder;
	sf::Texture blocksTexture;
	sf::Texture paddleTexture;
	
	//costructor's methods
	void prepareBall();
	void preparePaddle();
	void prepareMap(int level);
	void loadMapFromFile(int level);
	
	//logic's methods
	void closeEntireGameWhenWindowClosed();
	void closeGameWhenBallOutside();
	void closeGameWhenAllBlocksDestroyed();
	void updatePaddlePosition();
	void handleCollisions();
	
	//render's methods
	void drawBorder();
	void drawBlocksInsideBorder();
};
