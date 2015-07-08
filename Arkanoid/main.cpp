#include <iostream>
#include <SFML\Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480, 32), "Arkanoid");

	while (window.isOpen())
	{
		//EVENTS
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//LOGIC
		//RENDER
		window.display();
		window.clear();
	}
	return 0;
}