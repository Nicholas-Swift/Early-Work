// Tutorial 4
// Events Overview

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>


int main()
{
	sf::RenderWindow Window;
	Window.create(sf::VideoMode(800, 600), "My First SFML Game");

	std::cout<<"Press any key to continue..."<<std::endl;

	while(Window.isOpen()) //game loop
	{
		sf::Event Event;
		while(Window.pollEvent(Event)) //this polls an event. An event happens and it goes into queue
		{
			if(Event.type == sf::Event::Closed)
			{
				Window.close();
			}
		}

		if(Window.waitEvent(Event)) //every time an event happens from pollEvent(Event), it will display "Event Activated"
		{
			std::cout<<"Event Activated"<<std::endl;
		}

		Window.display();
	}
}