// Tutorial 1
// Introduction

#include "stdafx.h"
#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow Window;
	Window.create(sf::VideoMode(800, 600), "My First SFML Game"); //this creates a window that is 800x600 and called "My Fi..."

	while(Window.isOpen()) //this is the game loop
	{
		sf::Event Event; //need to create an event, even if no event loop
		while(Window.pollEvent(Event))
		{
			if(Event.type == sf::Event::Closed) //we did create an event loop though, and it checks for close
			{
				Window.close();
			}
		}

		Window.display();
	}
}

