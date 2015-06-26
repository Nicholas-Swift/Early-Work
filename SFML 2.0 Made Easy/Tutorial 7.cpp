// Tutorial 7
// Window Events

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	sf::RenderWindow Window;
	Window.create(sf::VideoMode(800, 600), "Tutorial 7!");

	while(Window.isOpen())
	{
		sf::Event Event;
		while(Window.pollEvent(Event))
		{
			switch(Event.type)
			{
			case sf::Event::Closed:
				Window.close();
				break;
			case sf::Event::GainedFocus:
				std::cout<<"Window Active"<<std::endl;
				break;
			/*if you click outside the game window, it is LostFocus. You can pause the game if someone accidently
			  clicks outside the game, so they don't die to monsters.*/
			case sf::Event::LostFocus:
				std::cout<<"Window Not Active"<<std::endl;
				break;
			//if they resize the window, you don't want characters to go out of proportion
			case sf::Event::Resized:
				std::cout<<"X: "<<Event.size.width<<" Y: "<<Event.size.height<<std::endl;
				break;
			}
		}

		Window.display();
	}
}

