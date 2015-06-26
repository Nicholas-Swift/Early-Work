// Tutorial 5
// Keyboard Events

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>


int main()
{
	sf::RenderWindow Window;
	Window.create(sf::VideoMode(800, 600), "My First SFML Game");

	std::string message = "Hello my name is Nick";
	std::string display = "";

	int index = 0;

	Window.setKeyRepeatEnabled(false); //this disables having repeated keys (holding a key)
									   //instead you now have to press it multiple times

	while(Window.isOpen())
	{
		sf::Event Event;
		while(Window.pollEvent(Event)) //this polls an event. An event happens and it goes into queue
		{
			if(Event.type == sf::Event::Closed)
			{
				Window.close();
			}

			if(Event.type == sf::Event::KeyPressed) //you can make this KeyReleased too
			{
				if(Event.key.code == sf::Keyboard::Return && Event.key.control) //keyboard return (enter) key
															//with the &&, you now have to press both
															//you can't have 2 Event.key.codes at the same time
				{
					display += message[index]; //the empty string adds 1 letter from message
					index++; //should make an for thing here. for(index <= message.length; index++;)
					system("cls"); //clear cmd so string doesn't go hhehellhellohellomhellomy
					std::cout<<display; //display the empty string that's growing
				}
			}
		}

		Window.display();
	}
}