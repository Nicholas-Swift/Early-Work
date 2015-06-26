// Tutorial 12
// Keyboard Input

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
	enum Direction {Down, Left, Right, Up};
	sf::Vector2i source(1, Down);

	float frameCounter = 0, switchFrame = 100, frameSpeed = 500;
	sf::Clock clock;

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
			}
		}

		//process keyboard events, not within event loop
		//this is much smoother than in the event loop, but it slows down a lot when computer gets hot
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			source.y = Up;
			playerImage.move(0, -1);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			source.y = Down;
			playerImage.move(0, 1);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			source.y = Left;
			playerImage.move(-1, 0);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			source.y = Right;
			playerImage.move(1, 0);
		}

		//animates the player so the animation is slower
		std::cout<<clock.getElapsedTime().asSeconds()<<std::endl;
		frameCounter += frameSpeed*clock.restart().asSeconds();
		if(frameCounter >= switchFrame)
		{
			frameCounter = 0;
			source.x++;
			if(source.x*32 >= pTexture.getSize().x)
			{
				source.x = 0;
			}
		}

		//in the game loop, drawing things to screen
		playerImage.setTextureRect(sf::IntRect(source.x*32, source.y*32, 32, 32));
		Window.draw(playerImage);
		Window.display();
		Window.clear();
	}
}