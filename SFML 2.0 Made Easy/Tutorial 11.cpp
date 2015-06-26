// Tutorial 11
// SpriteSheet Animation

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

int main()
{
	//general window renders
	sf::RenderWindow Window;
	Window.create(sf::VideoMode(800, 600), "Graapphiicssss!! Yesss!!");

	//setting textures and creating the player
	sf::Texture pTexture;
	sf::Sprite playerImage;
	if(!pTexture.loadFromFile("Player.png"))
	{
		std::cout<<"Error could not load player image"<<std::endl;
	}
	playerImage.setTexture(pTexture);

	//making the character move around the screen
	enum Direction {Down, Left, Right, Up}; //value is 1, 2, 3, 4
	sf::Vector2i source(1, Down); //stoes 2 values under 1 name. 2 ints. source.x, source.y

	//game loop
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
			case::sf::Event::KeyPressed:
				if(Event.key.code == sf::Keyboard::Up)
				{
					source.y = Up;
				}
				else if(Event.key.code == sf::Keyboard::Down)
				{
					source.y = Down;
				}
				else if(Event.key.code == sf::Keyboard::Left)
				{
					source.y = Left;
				}
				else if(Event.key.code == sf::Keyboard::Right)
				{
					source.y = Right; //it's always source.y cuz if you look at the sprite sheet it's y that changes stuff
				}
				break;
			}
		}

		source.x++;
		if(source.x*32 >= pTexture.getSize().x)
		{
			source.x = 0;
		}

		//in the game loop, drawing things to screen
		playerImage.setTextureRect(sf::IntRect(source.x*32, source.y*32, 32, 32));
		Window.draw(playerImage);
		Window.display();
		Window.clear();
	}
}