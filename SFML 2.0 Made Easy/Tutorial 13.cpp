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

	//clock for frames
	float frameCounter = 0, switchFrame = 100, frameSpeed = 500;
	sf::Clock clock;

	bool updateFrame = true;

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
			
		//keyboard presses to move
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
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) //closes the window if you press enter
		{
			Window.close();
		}

		//mouse input. animates character if right is pressed, not if left
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			updateFrame = true;
		}
		else if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			updateFrame = false;
		}


		//gets mouse input. sets the mouse position to 100, 100 forever though, very annoying
		sf::Vector2i mousePostion = sf::Mouse::getPosition(Window);
		sf::Mouse::setPosition(sf::Vector2i(100, 100), Window);
		std::cout<<"X: "<<mousePostion.x<<" Y: "<<mousePostion.y<<std::endl;


		//animates the player so the animation is slower
		if(updateFrame)
		{
			frameCounter += frameSpeed*clock.restart().asSeconds();
		}
		else
		{
			frameCounter = 0;
		}

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