// Warlock Alpha 0.0.2
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <queue>

sf::Vector2f screenDimensions(640, 640);

//map
const int TILE_W(20), TILE_H(20);
static int level[TILE_W][TILE_H] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
	0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
	0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
	0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
	0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
	0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
	0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
	0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0,
	0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0,
	0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0,
	0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0,
	0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0,
	0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
	0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
	0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
	0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

class TileMap
{
public:
	sf::RectangleShape rect;

	TileMap(sf::Vector2f size, sf::Color defaultColor)
	{
		rect.setSize(size);
		rect.setFillColor(defaultColor);
	}

	void Update(sf::RenderWindow &Window)
	{
		for(int i = 0; i < TILE_H; i++)
		{
			for(int j = 0; j < TILE_W; j++)
			{
				if(level[i][j] == 0)
					rect.setFillColor(sf::Color::Red);
				else if(level[i][j] == 1)
					rect.setFillColor(sf::Color::Black);
				else
					rect.setFillColor(sf::Color::Cyan);

				rect.setPosition(j*rect.getSize().x, i*rect.getSize().y);
				Window.draw(rect);
			}
		}
	}
};

class ScreenScroll
{
public:
	sf::RectangleShape rect;
	sf::View view;

	ScreenScroll(sf::Vector2f position, sf::Vector2f size)
	{
		rect.setPosition(position);
		rect.setSize(size);
		rect.setFillColor(sf::Color::Magenta);

		view.reset(sf::FloatRect(0, 0, screenDimensions.x, screenDimensions.y));
	}

	void Update(sf::RenderWindow &Window, float movementConstant)
	{
		int maxX = Window.getSize().x;
		int maxY = Window.getSize().y;

		int mX = sf::Mouse::getPosition(Window).x;
		int mY = sf::Mouse::getPosition(Window).y;

		if (mX < 0 || mY < 0 || mX > maxX || mY > maxY)
		{
			if (mX < 0)
				mX = 0;
			else if (mX > maxX)
				mX = maxX;

			if (mY < 0)
				mY = 0;
			else if (mY > maxY)
				mY = maxY;

			sf::Mouse::setPosition(sf::Vector2i(mX, mY), Window);
		}

		if(sf::Mouse::getPosition(Window).x == 0)
		{
			rect.move(-1 * movementConstant, 0);
			view.move(-1 * movementConstant, 0);
		}
		if(sf::Mouse::getPosition(Window).x == screenDimensions.x)
		{
			rect.move(1 * movementConstant, 0);
			view.move(1 * movementConstant, 0);
		}
		if(sf::Mouse::getPosition(Window).y == 0)
		{
			rect.move(0, -1 * movementConstant);
			view.move(0, -1 * movementConstant);
		}
		if(sf::Mouse::getPosition(Window).y == screenDimensions.y)
		{
			rect.move(0, 1 * movementConstant);
			view.move(0, 1 * movementConstant);
		}

		Window.setView(view);
	}
};

class Player
{
public:
	sf::RectangleShape rect;

	//void Update()
	float bottom, left, right, top;

	//void Walk()
	sf::Vector2f targetPos, walkVel, glitchMove;
	float hyp;

	//void Collide()
	std::vector<sf::Vector2i> tiles;
	bool collide;
	sf::Vector2i topLeft, topRight, bottomLeft, bottomRight;
	int sideCollide;

	Player(sf::Vector2f position, sf::Vector2f size)
	{
		rect.setPosition(position);
		rect.setSize(size);
		rect.setFillColor(sf::Color::Green);

		targetPos = position;
	}

	void Update()
	{
		bottom = rect.getPosition().y + rect.getSize().y;
		left = rect.getPosition().x;
		right = rect.getPosition().x + rect.getSize().x;
		top = rect.getPosition().y;

		topLeft = (sf::Vector2i((int)left / 32, (int)top / 32));
		topRight = (sf::Vector2i((int)right / 32, (int)top / 32));
		bottomLeft = (sf::Vector2i((int)left / 32, (int)bottom / 32));
		bottomRight = (sf::Vector2i((int)right / 32, (int)bottom / 32));

		tiles.clear();

		tiles.push_back(topLeft);
		if(std::find(tiles.begin(), tiles.end(), topRight) == tiles.end()) tiles.push_back(topRight);
		if(std::find(tiles.begin(), tiles.end(), bottomLeft) == tiles.end()) tiles.push_back(bottomLeft);
		if(std::find(tiles.begin(), tiles.end(), bottomRight) == tiles.end()) tiles.push_back(bottomRight);
	}

	void Collide()
	{ //collision is terrible and needs to be worked on MASSIVELY
	  //maybe level[part ab][ove player] == 0 might work well for all 4 sides immediatly, not corners
		collide = false;

		for(int i = 0; i < tiles.size(); i++)
		{
			if(level[tiles[i].y][tiles[i].x] == 0)
			{
				collide = true;
				break;
			}
		}

		if(collide)
		{
			sideCollide = 0;
			if(level[topLeft.y][topLeft.x] == 0)
			{
				sf::RectangleShape recterino;
				recterino.setPosition(topLeft.x * 32, topLeft.y * 32);
				recterino.setSize(sf::Vector2f(32, 32));

				int lefterino, toperino;

				lefterino = rect.getPosition().y - recterino.getPosition().y + recterino.getSize().y - 32;
				toperino = rect.getPosition().x - recterino.getPosition().x + recterino.getSize().x - 32;

				if(lefterino < toperino)
				{
					sideCollide = 4;
					rect.setPosition(recterino.getPosition().x + recterino.getSize().x - 0.01, rect.getPosition().y);
				}
				else if(toperino < lefterino)
				{
					sideCollide = 1;
					rect.setPosition(rect.getPosition().x, recterino.getPosition().y + recterino.getSize().y - 0.01);
				}
				else
					std::cout<<"Lefterino toperino messed up!"<<std::endl;
			}

			if(level[topRight.y][topRight.x] == 0)
			{
				sf::RectangleShape recterino;
				recterino.setPosition(topRight.x * 32, topRight.y * 32);
				recterino.setSize(sf::Vector2f(32, 32));

				int righterino, toperino;

				righterino = std::abs(rect.getPosition().y - recterino.getPosition().y + recterino.getSize().y - 32 - 32);
				toperino = rect.getPosition().x - recterino.getPosition().x + recterino.getSize().x;

				if(righterino > toperino)
				{
					sideCollide = 2;
					rect.setPosition(recterino.getPosition().x - rect.getSize().x + 0.01, rect.getPosition().y);
				}
				else if(toperino > righterino)
				{
					sideCollide = 1;
					rect.setPosition(rect.getPosition().x, recterino.getPosition().y + recterino.getSize().y - 0.01);
				}
				else
					std::cout<<"Righterino toperino messed up!"<<std::endl;
			}

			if(level[bottomLeft.y][bottomLeft.x] == 0)
			{
				sf::RectangleShape recterino;
				recterino.setPosition(bottomLeft.x * 32, bottomLeft.y * 32);
				recterino.setSize(sf::Vector2f(32, 32));

				int lefterino, bottomerino;

				lefterino = std::abs(recterino.getPosition().y - rect.getPosition().y + rect.getSize().y - 32 - 32);
				bottomerino = std::abs(recterino.getPosition().x - rect.getPosition().x + 32);

				if(lefterino > bottomerino)
				{
					sideCollide = 4;
					rect.setPosition(recterino.getPosition().x + recterino.getSize().x - 0.01, rect.getPosition().y);
				}
				else if(bottomerino > lefterino)
				{
					sideCollide = 3;
					rect.setPosition(rect.getPosition().x, recterino.getPosition().y - rect.getSize().y + 0.01);
				}
				else
					std::cout<<"Lefterino bottomerino messed up!"<<std::endl;
			}

			if(level[bottomRight.y][bottomRight.x] == 0)
			{
				sf::RectangleShape recterino;
				recterino.setPosition(bottomRight.x * 32, bottomRight.y * 32);
				recterino.setSize(sf::Vector2f(32, 32));

				int righterino, bottomerino;

				righterino = bottom - recterino.getPosition().y;
				bottomerino = right - recterino.getPosition().x;

				if(righterino > bottomerino)
				{
					sideCollide = 2;
					rect.setPosition(recterino.getPosition().x - rect.getSize().x + 0.01, rect.getPosition().y);
				}
				else if(bottomerino > righterino)
				{
					sideCollide = 3;
					rect.setPosition(rect.getPosition().x, recterino.getPosition().y - rect.getSize().y + 0.01);
				}
				else
					std::cout<<"Righterino bottomerino messed up!"<<std::endl;
			}
		}
	}

	void Walk(sf::RenderWindow &Window, ScreenScroll s, float movementConstant)
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
			targetPos = sf::Vector2f(sf::Mouse::getPosition(Window).x - rect.getSize().x/2 + s.rect.getPosition().x, sf::Mouse::getPosition(Window).y - rect.getSize().y + 5 + s.rect.getPosition().y);

		walkVel = sf::Vector2f(targetPos.x - left, targetPos.y - top);
		hyp = std::sqrt(walkVel.x*walkVel.x + walkVel.y*walkVel.y);
		if(hyp == 0)
		{
			walkVel = sf::Vector2f(0, 0);
			hyp = 1;
		}

		if(collide == true)
		{
			if(sideCollide == 1 && walkVel.y < 0)
				walkVel.y = 0;
			if(sideCollide == 2 && walkVel.x > 0)
				walkVel.x = 0;
			if(sideCollide == 3 && walkVel.y > 0)
				walkVel.y = 0;
			if(sideCollide == 4 && walkVel.x < 0)
				walkVel.x = 0;
		}

		glitchMove = (sf::Vector2f(left - targetPos.x, top - targetPos.y));
		if(1.5 > glitchMove.x && -1.5 < glitchMove.x && 1.5 > glitchMove.y && -1.5 < glitchMove.y)
		{}
		else
		{
			rect.move(walkVel.x/hyp * movementConstant, walkVel.y/hyp * movementConstant);
		}

		Window.draw(rect);
	}
};

int main()
{
	sf::RenderWindow Window;
	Window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Warlock 0.0.2: new beginnings, new endings!", sf::Style::Titlebar);
	Window.setFramerateLimit(300);

	sf::Time deltaTime;
	sf::Clock deltaClock;

	TileMap map(TileMap(sf::Vector2f(32, 32), sf::Color::Cyan));
	ScreenScroll screenscroll(ScreenScroll(sf::Vector2f(0, 0), sf::Vector2f(32, 32)));
	Player player(Player(sf::Vector2f(200, 96), sf::Vector2f(32, 32)));

	while(Window.isOpen())
	{
		deltaTime = deltaClock.restart();

		sf::Event Event;
		while(Window.pollEvent(Event))
		{
			switch(Event.type)
			{
			case sf::Event::Closed:
				Window.close();
				break;
			}

			if(Event.type == sf::Event::KeyPressed)
			{
				if(Event.key.code == sf::Keyboard::Escape)
					Window.close();
			}
		}

		screenscroll.Update(Window, deltaTime.asMilliseconds()*0.5);

		player.Update();
		player.Collide();

		map.Update(Window);
		player.Walk(Window, screenscroll, deltaTime.asMilliseconds()*0.2);

		Window.display();
		Window.clear();
	}

	return 0;
}

