//plik zawieraj�cy wszystkie sta�e w grze(taki troche config)
#pragma once
#include <SFML\Graphics.hpp>

//window
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//wymiary bloczk�w
const int TILE_SIZE_X = 32;
const int TILE_SIZE_Y = 32;

//ball
const sf::Vector2i BALL_SIZE = sf::Vector2i(32, 32);
const sf::Vector2f START_BALL_POSITION = sf::Vector2f(100, 224);
const float BALL_SPEED = 5.0f;
const sf::Vector2f START_BALL_DIRECTION = sf::Vector2f(1, 1);

//paddle
const sf::Vector2f START_PADDLE_POSITION = sf::Vector2f(256, 448);	//pozycja pocz�tkowa paletki
const float PADDLE_SPEED = 5.0f;	//pr�dko�� poruszania si� paletki

//loading menu 
const unsigned int levelsInMenu = 11;	//liczba poziom�w do wybrania w menu