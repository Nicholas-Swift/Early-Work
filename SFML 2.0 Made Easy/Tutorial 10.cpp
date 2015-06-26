// Tutorial 10
// Displaying images

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

int main()
{
	sf::RenderWindow Window;
	Window.create(sf::VideoMode(800, 600), "Graapphiicssss!! Yesss!!WOWOWOWOWOW");

	Window.setKeyRepeatEnabled(false);

	sf::Texture pTexture; //create a texture
	sf::Sprite playerImage; //create a sprite that is the player
														//here we crop the image. x axis, y axis, height, length
	if(!pTexture.loadFromFile("Player.png", sf::IntRect(32, 0, 32, 32)))
	{
		std::cout<<"Error could not load player image"<<std::endl;
	}

	playerImage.setTexture(pTexture); //set the sprite to have the certain texture

	while(Window.isOpen())
	{
		sf::Event Event;

		while(Window.pollEvent(Event))
		{
			switch(Event.type)
			{
			case::sf::Event::Closed:
				Window.close();
				break;
			}
		}

		Window.draw(playerImage);
		Window.display();
	}
}