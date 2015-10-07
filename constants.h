//this file contains all constants used in the game
#pragma once
#include <SFML/Graphics.hpp>

//window
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//wymiary bloczków
const int TILE_SIZE_X = 32;
const int TILE_SIZE_Y = 32;

//ball
const sf::Vector2i BALL_SIZE = sf::Vector2i(32, 32);
const sf::Vector2f START_BALL_POSITION = sf::Vector2f(250, 400);
const float BALL_SPEED = 5.0f;
const sf::Vector2f START_BALL_DIRECTION = sf::Vector2f(1, 1);

//paddle
const sf::Vector2f START_PADDLE_POSITION = sf::Vector2f(256, 448);
const float PADDLE_SPEED = 5.0f;
const sf::Vector2i PADDLE_SIZE = sf::Vector2i(128, 32);

//loading menu 
const unsigned int LEVELS_TO_CHO0SE_IN_LOADING_MENU = 5;
