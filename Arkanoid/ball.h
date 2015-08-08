#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "block.h" //trzeba wiedzieæ z czym siê zderzaæ

class Ball : public sf::Sprite
{
public:
	Ball(sf::Vector2i ballSize);	//kostruktor;
	sf::Vector2i getBallSize();
	void update();		//po wywo³aniu tej metody pi³ka przemieszcza siê 
	bool bounce(Block &block);	//metoda sprawdza czy nie wyst¹pi³a kolizja i jeœli tak to zmienia kierunek
	bool ballOutside();			//metoda informuj¹ca czy pi³ka nie wylecia³a za planszê
private:
	sf::Vector2f directionVector;	//vektor reprezentuj¹cy kierunek lotu pi³ki
	sf::Texture ballTexture;		//tekstura pi³ki
	sf::Vector2i ballSize;			//rozmiar pi³ki
};