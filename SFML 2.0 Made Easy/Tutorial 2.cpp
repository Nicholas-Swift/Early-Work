// Tutorial 2
// RenderWindow

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>


int main()
{
	sf::RenderWindow Window;
	Window.create(sf::VideoMode(800, 600), "My First SFML Game");

	//in these next 3 lines, I change the size of the window. I also display the size in console window.
	sf::Vector2u size(400, 400);
	std::cout<<size.x<<" "<<size.y<<std::endl;
	Window.setSize(size); //Window.setSize(sf::Vector2u(400, 400)); also works

	//we can also change the title
	Window.setTitle("Welcome to the game");

	while(Window.isOpen())
	{
		sf::Event Event;
		while(Window.pollEvent(Event))
		{
			if(Event.type == sf::Event::Closed)
			{
				Window.close();
			}

		}

		Window.display();
	}
}

