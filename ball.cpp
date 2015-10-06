#include "ball.h"
#include "constants.h"

Ball::Ball(sf::Vector2i ballSize)
{
	directionVector = START_BALL_DIRECTION;

	if (!ballTexture.loadFromFile("Graphics/ballTexture.png"))
		std::cout << "ballTexture.png loading failed" << std::endl;
	setTexture(ballTexture);
	setTextureRect(sf::IntRect(sf::Vector2i(0, 0), ballSize));
	this->ballSize = ballSize;
}

sf::Vector2i Ball::getBallSize()
{
	return ballSize;
}

//po wywo�aniu tej metody pi�ka przemieszcza si� 
void Ball::update()
{
	//je�li pi�eczka dotyka ramki to ma si� odbi�
	if (getPosition().x < 32)
		directionVector.x = 1;
	else if (getPosition().x >= 576)
		directionVector.x = -1;
	else if (getPosition().y < 32)
		directionVector.y = 1;

	move(sf::Vector2f(directionVector.x*BALL_SPEED, directionVector.y*BALL_SPEED));
}

//metoda sprawdza czy nie wyst�pi�a kolizja i je�li tak to zmienia kierunek
bool Ball::bounce(Block &block)
{
	//sprawdzam czy dosz�o do kolizji -- d�ugi warunek
	if (getPosition().x <= block.getPosition().x + block.getBlockSize().x &&
		getPosition().x + ballSize.x >= block.getPosition().x &&
		getPosition().y <= block.getPosition().y + block.getBlockSize().y &&
		getPosition().y + ballSize.y >= block.getPosition().y)
	{
		if (directionVector.x == 1 && directionVector.y == 1)
		{
			if (((getPosition().x < block.getPosition().x)?(getPosition().x + ballSize.x - block.getPosition().x):
				(block.getPosition().x + block.getBlockSize().x - getPosition().x)) < 
				((getPosition().y < block.getPosition().y)?(getPosition().y + ballSize.y - block.getPosition().y):
				(block.getPosition().y + block.getBlockSize().y - getPosition().y)))
			{
				directionVector = sf::Vector2f(-1, 1);
			}
			else
			{
				directionVector = sf::Vector2f(1, -1);
			}
		}
		else if (directionVector.x == 1 && directionVector.y == -1)
		{
			if (((getPosition().x < block.getPosition().x) ? (getPosition().x + ballSize.x - block.getPosition().x) :
				(block.getPosition().x + block.getBlockSize().x - getPosition().x)) <
				((getPosition().y < block.getPosition().y) ? (getPosition().y + ballSize.y - block.getPosition().y) :
				(block.getPosition().y + block.getBlockSize().y - getPosition().y)))
			{
				directionVector = sf::Vector2f(-1, -1);
			}
			else
			{
				directionVector = sf::Vector2f(1, 1);
			}
		}
		else if (directionVector.x == -1 && directionVector.y == -1)
		{
			if (((getPosition().x < block.getPosition().x) ? (getPosition().x + ballSize.x - block.getPosition().x) :
				(block.getPosition().x + block.getBlockSize().x - getPosition().x)) <
				((getPosition().y < block.getPosition().y) ? (getPosition().y + ballSize.y - block.getPosition().y) :
				(block.getPosition().y + block.getBlockSize().y - getPosition().y)))
			{
				directionVector = sf::Vector2f(1, -1);
			}
			else
			{
				directionVector = sf::Vector2f(-1, 1);
			}
		}
		else if (directionVector.x == -1 && directionVector.y == 1)
		{
			if (((getPosition().x < block.getPosition().x) ? (getPosition().x + ballSize.x - block.getPosition().x) :
				(block.getPosition().x + block.getBlockSize().x - getPosition().x)) <
				((getPosition().y < block.getPosition().y) ? (getPosition().y + ballSize.y - block.getPosition().y) :
				(block.getPosition().y + block.getBlockSize().y - getPosition().y)))
			{
				directionVector = sf::Vector2f(1, 1);
			}
			else
			{
				directionVector = sf::Vector2f(-1, -1);
			}
		}
		return true;
	}
	return false;
}