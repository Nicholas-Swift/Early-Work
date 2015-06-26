// Tutorial 3
// Time

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>


int main()
{
	sf::RenderWindow Window;
	Window.create(sf::VideoMode(800, 600), "My First SFML Game");

	//all of this stuff is general time stuff
	sf::Time time = sf::seconds(2); //can set to microsecond, millisecond, or second
	time += sf::milliseconds(2000);

	sf::Time time2 = sf::milliseconds(2000);
	time += time2;

	std::cout<<time.asSeconds()<<std::endl; //can set to .asMicroseconds, .asMilliseconds, or .asSeconds

	//now we are creating a clock
	sf::Clock clock;
	sf::Time clockTime;

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

		//in the game loop we start a clock and display it to command console
		clockTime = clock.getElapsedTime();
		std::cout<<clockTime.asSeconds()<<std::endl;
		clock.restart(); //when we call clock.restart, it gives us the amount of time since the last frame
						 
		//instead of clock.restart() we can also do
		//clockTime = clock.restart(); to turn 2 lines into 1 line

		Window.display();
	}
}