// Tutorial 8
// Text Event

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

int main()
{
	sf::RenderWindow Window;
	Window.create(sf::VideoMode(800, 600), "Tutorial 7!");

	std::string message = "Hello my name is Nick!";
	std::string display = "";

	int index = 0;

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
			case sf::Event::TextEntered:
				//here we are displaying text only within certain parameters. no spaces and stuff.
			  /*if(Event.text.unicode >= 33 && Event.text.unicode <= 126)
				{
					display += (char)Event.text.unicode;
				}*/

				//this naturally will display space and enter, but not backspace
				if(Event.text.unicode != 8)
				{
					display += (char)Event.text.unicode;
				}
				//if there is a backspace, delete it from the back
				else if(Event.text.unicode == 8)
				{
					display = display.substr(0, display.length() - 1);
				}

				system("cls");
				std::cout<<display<<std::endl;
				break;
			}
		}

		Window.display();
	}
}