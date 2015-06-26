// Tutorial 9
// Joystick Events

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	sf::RenderWindow Window;
	Window.create(sf::VideoMode(800, 600), "Tutorial 7!");

	Window.setKeyRepeatEnabled(false);

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
			//I don't think I'll ever be using this function...
			case sf::Event::JoystickConnected:
				std::cout<<"Joystick "<<Event.joystickConnect.joystickId + 1<<" is connected"<<std::endl;
				break;
			case sf::Event::JoystickDisconnected:
				std::cout<<"Joystick "<<Event.joystickConnect.joystickId + 1<<" is disconnected"<<std::endl;
				break;
			//it will tell you which button is being pressed (1, 2, 7, 9, etc.)
			case sf::Event::JoystickButtonPressed:
				std::cout<<"Button: "<<Event.joystickButton.button<<std::endl;
				break;
			case sf::Event::JoystickMoved:
				if(Event.joystickMove.axis == sf::Joystick::X)
				{
					std::cout<<"Position: "<<Event.joystickMove.position<<std::endl;
				}
				break;
			}
		}

		Window.display();
	}
}