
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"


int main() {

	sf::RenderWindow window(sf::VideoMode(800, 800), "D20 Game", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
	sf::Event e;

	while (window.isOpen())
	{
		while (window.pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (e.key.code == sf::Keyboard::Escape)
					window.close();
				break;
			}
		}

			window.clear();
			window.display();
		}


		return 0;
	}