//plik zawieraj¹cy wszystkie sta³e w grze(taki troche config)
#pragma once
#include <SFML\Graphics.hpp>

//window
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//wymiary bloczków
const int TILE_SIZE_X = 32;
const int TILE_SIZE_Y = 32;

//ball
const sf::Vector2i BALL_SIZE = sf::Vector2i(32, 32);
const sf::Vector2f START_BALL_POSITION = sf::Vector2f(100, 224);
const float BALL_SPEED = 5.0f;
const sf::Vector2f START_BALL_DIRECTION = sf::Vector2f(1, 1);

//paddle
const sf::Vector2f START_PADDLE_POSITION = sf::Vector2f(256, 448);	//pozycja pocz¹tkowa paletki
const float PADDLE_SPEED = 5.0f;	//prêdkoœæ poruszania siê paletki

//loading menu 
const unsigned int levelsInMenu = 11;	//liczba poziomów do wybrania w menu