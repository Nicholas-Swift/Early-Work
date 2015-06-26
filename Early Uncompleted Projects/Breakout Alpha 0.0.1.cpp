// Breakout Alpha 0.0.1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <array>
#include <string>
#include <SFML/Graphics.hpp>

const int WINDOW_HEIGHT(400);
const int WINDOW_WIDTH(800);

class Paddle
{
public:
	sf::RectangleShape rect;
	float top, right, left;

	Paddle(sf::Vector2f size, sf::Vector2f position, sf::Color color)
	{
		rect.setSize(size);
		rect.setPosition(position);
		rect.setFillColor(color);
	}

	void Update()
	{
		top = rect.getPosition().y;
		right = rect.getPosition().x + rect.getSize().x;
		left = rect.getPosition().x;
	}

};

/*class BlockWall
{
public:
	std::vector<Block>Blocks;
	sf::String TileMap[WINDOW_HEIGHT];

	void Add(const Block& aBlock)
	{
		Blocks.push_back(aBlock);
	}

	void Display() const
	{
		for(int i = 0; i < 25; ++i)
		{
			for(int j = 0; j < 50; ++j)
			{
				if(TileMap[i][j] == 'b')
					BlockWall.Ad
			}
		}
	}

	BlockWall(int wow)
	{}
};*/

class Ball
{
public:
	sf::RectangleShape rect;
	float top, right, bottom, left;

	Ball(sf::Vector2f size, sf::Vector2f position, sf::Color color)
	{
		rect.setSize(size);
		rect.setPosition(position);
		rect.setFillColor(color);
	}

	void Update()
	{
		top = rect.getPosition().y;
		right = rect.getPosition().x + rect.getSize().x;
		bottom = rect.getPosition().y + rect.getSize().y;
		left = rect.getPosition().x;
	}

	bool CollisionTopBot(Paddle p/*, Block b*/)
	{
		if(top < 0)
			return true;

		else if(bottom > p.top && right > p.left && left < p.right)
			return true;

		/*else if(bottom > b.top && right > b.left && left < b.right)
			return true;
		else if(top < b.bottom && right > b.left && left < b.right)
			return true;*/

		else
			return false;
	}

	bool CollisionLeftRight(/*Block b*/)
	{
		if(left < 0)
			return true;
		else if(right > WINDOW_WIDTH)
			return true;

		/*else if(left < b.right && top < b.bottom && bottom > b.top)
			return true;
		else if(right > b.left && top < b.bottom && bottom > b.top)
			return true;*/

		else
			return false;
	}
};

class Block
{
public:
	sf::RectangleShape rect;
	float top, right, bottom, left;

	/*Block(sf::Vector2f size, sf::Vector2f position, sf::Color color)
	{
		rect.setSize(size);
		rect.setPosition(position);
		rect.setFillColor(color);
	}*/

	void Update()
	{
		top = rect.getPosition().y;
		right = rect.getPosition().x + rect.getSize().x;
		bottom = rect.getPosition().y + rect.getSize().y;
		left = rect.getPosition().x;
	}
};

int main()
{
	sf::RenderWindow Window;
	Window.create(sf::VideoMode(800, 600), "Woah");
	Window.setFramerateLimit(60);

	sf::Vector2f size(10,10); sf::Vector2f position(10,10); sf::Color color(sf::Color::Green);
	Paddle paddle1(Paddle(size, position, color));

	//Block block(Block(size, position, color));

	//BlockWall blockwall1(BlockWall(5));

	std::string TileMap[60] = {
		"b", "b", "b", "b", "b", "b", "b", "b", "b", "b", "b", "b",
		"b", "b", "b", "b", "b", "b", "b", "b", "b", "b", "b", "b", 
		"b", "b", "b", "b", "b", "b", "b", "b", "b", "b", "b", "b", 
		"b", "b", "b", "b", "b", "b", "b", "b", "b", "b", "b", "b", 
		" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "};

	std::array<Block, 60> blockss;
	sf::Vector2f sizemann(WINDOW_WIDTH/10, WINDOW_HEIGHT/20);

	for(int i = 0; i < /*WINDOW_WIDTH * sizemann.x*/ 60; ++i)
	{
		for(int j = 0; j < 0.1 * 0.5; ++j)
		{
			if(TileMap[i] == "b")
			{
				blockss[i].rect.setPosition(sizemann.x * i, 20);
				blockss[i].rect.setSize(sizemann);
				blockss[i].rect.setFillColor(sf::Color::Green);
			}	
			else
			{
				continue;
			}
		}
	}

	std::cout<<TileMap[0]<<std::endl;

	while(Window.isOpen())

	{
		sf::Event Event;
		while(Window.pollEvent(Event))
		{
			if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				std::cout<<"blockss[1] - x: "<<blockss[1].rect.getPosition().x<<", y: "<<blockss[1].rect.getPosition().y<<std::endl;
				std::cout<<"blockss[2] - x: "<<blockss[2].rect.getPosition().x<<", y: "<<blockss[2].rect.getPosition().y<<std::endl;
				std::cout<<"blockss[3] - x: "<<blockss[3].rect.getPosition().x<<", y: "<<blockss[3].rect.getPosition().y<<std::endl;
				std::cout<<"blockss[4] - x: "<<blockss[4].rect.getPosition().x<<", y: "<<blockss[4].rect.getPosition().y<<std::endl;
				std::cout<<"blockss[5] - x: "<<blockss[5].rect.getPosition().x<<", y: "<<blockss[5].rect.getPosition().y<<std::endl;
				std::cout<<"blockss[6] - x: "<<blockss[6].rect.getPosition().x<<", y: "<<blockss[6].rect.getPosition().y<<std::endl;
				std::cout<<"blockss[7] - x: "<<blockss[7].rect.getPosition().x<<", y: "<<blockss[7].rect.getPosition().y<<std::endl;
				std::cout<<"blockss[8] - x: "<<blockss[8].rect.getPosition().x<<", y: "<<blockss[8].rect.getPosition().y<<std::endl;
				std::cout<<"blockss[9] - x: "<<blockss[9].rect.getPosition().x<<", y: "<<blockss[9].rect.getPosition().y<<std::endl;
				/*std::cout<<"blockss[1] - x: "<<blockss[1].rect.getPosition().x<<", y: "<<blockss[1].rect.getPosition().y<<std::endl;
				std::cout<<"blockss[1] - x: "<<blockss[1].rect.getPosition().x<<", y: "<<blockss[1].rect.getPosition().y<<std::endl;
				std::cout<<"blockss[1] - x: "<<blockss[1].rect.getPosition().x<<", y: "<<blockss[1].rect.getPosition().y<<std::endl;
				std::cout<<"blockss[1] - x: "<<blockss[1].rect.getPosition().x<<", y: "<<blockss[1].rect.getPosition().y<<std::endl;*/

			}
		}

		for(int i = 0; i < 25*50; ++i)
		{
			Window.draw(blockss[i].rect);
			blockss[i].Update();
			//std::cout<<"Woah"<<std::endl;
		}

		sf::Vector2f wtf = blockss[1].rect.getPosition();
		//std::cout<<wtf.x<<", "<<wtf.y<<std::endl;

		Window.display();

		//Window.display();
		//Window.clear();
	}

	return 0;
}