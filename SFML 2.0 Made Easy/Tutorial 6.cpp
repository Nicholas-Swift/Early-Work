// Tutorial 6
// Mouse Events

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>


int main()
{
	sf::RenderWindow Window;
	Window.create(sf::VideoMode(800, 600), "My first SFML game");

	while(Window.isOpen())
	{
		sf::Event Event;
		while(Window.pollEvent(Event))
		{
			if(Event.type == sf::Event::Closed)
			{
				Window.close();
			}

			switch(Event.type)
			{
			case sf::Event::Closed:
				Window.close();
				break;
			case sf::Event::MouseEntered: //when mouse is within screen bounds
				std::cout<<"Mouse within screen bounds"<<std::endl;
				break;
			case sf::Event::MouseLeft: //when the mouse has left the screen bounds
				std::cout<<"Mouse NOT within screen bounds"<<std::endl;
				break;
			case sf::Event::MouseMoved:
				//note that this is mouseMove not mouseMoved
				std::cout<<"X: "<<Event.mouseMove.x<<" Y: "<<Event.mouseMove.y<<std::endl;
				break;
			case sf::Event::MouseButtonPressed:
				if(Event.mouseButton.button == sf::Mouse::Left)
				{
					//make sure that this is Event.mouseButton not Event.mouseMove, for button presses
					std::cout<<"Left button pressed at: X: "<<Event.mouseButton.x<<" Y: "<<Event.mouseButton.y<<std::endl;
				}
				break;
			case sf::Event::MouseWheelMoved:
				//delta is how hard it is scrolled
				std::cout<<"delta: "<<Event.mouseWheel.delta<<std::endl;
				break;
			}
		}

		Window.display();
	}
}

