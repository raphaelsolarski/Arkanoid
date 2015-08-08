#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "block.h" //trzeba wiedzie� z czym si� zderza�

class Ball : public sf::Sprite
{
public:
	Ball(sf::Vector2i ballSize);	//kostruktor;
	sf::Vector2i getBallSize();
	void update();		//po wywo�aniu tej metody pi�ka przemieszcza si� 
	bool bounce(Block &block);	//metoda sprawdza czy nie wyst�pi�a kolizja i je�li tak to zmienia kierunek
	bool ballOutside();			//metoda informuj�ca czy pi�ka nie wylecia�a za plansz�
private:
	sf::Vector2f directionVector;	//vektor reprezentuj�cy kierunek lotu pi�ki
	sf::Texture ballTexture;		//tekstura pi�ki
	sf::Vector2i ballSize;			//rozmiar pi�ki
};