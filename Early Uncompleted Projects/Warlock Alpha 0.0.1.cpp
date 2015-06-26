// Warlock Alpha 0.0.1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

const sf::Vector2f WINDOW_SIZE(800, 600);
const int FRAME_CAP(60);

const int tileHeight(10);
const int tileWidth(10);
sf::String MAP[tileHeight] = {
	"0000000000",
	"0000000000",
	"0000000000",
	"0000000000",
	"0000000000",
	"0000000000",
	"0000000000",
	"0000000000",
	"0000000000",
	"0000000000" };


class Tile
{
public:
	sf::Sprite tileSprite;

	Tile(sf::Texture &texture, float wtf)
	{
		tileSprite.setTexture(texture);
		std::cout<<wtf<<std::endl;
	}

	void Update(sf::RenderWindow &window)
	{
		for(int i = 0; i < tileHeight; i++)
		{
			for(int j = 0; j < tileWidth; j++)
			{
				if(MAP[i][j] == '0') tileSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
				tileSprite.setPosition(j*16, i*16);
				window.draw(tileSprite);
			}
		}
	}
};

class Selector
{
public:
	sf::RectangleShape rect;
	sf::Vector2f selectDown, selectCurrent;
	float bottom, left, right, top;

	Selector(float thickness, sf::Color color)
	{
		rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineThickness(thickness);
		rect.setOutlineColor(color);
	}

	void Update(sf::RenderWindow &Window)
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			rect.setPosition(selectDown);
			selectCurrent.x = sf::Mouse::getPosition(Window).x - selectDown.x;
			selectCurrent.y = sf::Mouse::getPosition(Window).y - selectDown.y;
			rect.setSize(selectCurrent);
			Window.draw(rect);
		}
		else
		{
			selectDown.x = sf::Mouse::getPosition(Window).x;
			selectDown.y = sf::Mouse::getPosition(Window).y;
		}

		if(rect.getSize().x >= 0 && rect.getSize().y >= 0)
		{
			bottom = rect.getPosition().y + rect.getSize().y;
			left = rect.getPosition().x;
			right = rect.getPosition().x + rect.getSize().x;
			top = rect.getPosition().y;
		}
		else if(rect.getSize().x <= 0 && rect.getSize().y <= 0)
		{
			bottom = rect.getPosition().y;
			left = rect.getPosition().x + rect.getSize().x;
			right = rect.getPosition().x;
			top = rect.getPosition().y + rect.getSize().y;
		}
		else if(rect.getSize().x >= 0 && rect.getSize().y <= 0)
		{
			bottom = rect.getPosition().y;
			left = rect.getPosition().x;
			right = rect.getPosition().x + rect.getSize().x;
			top = rect.getPosition().y + rect.getSize().y;
		}
		else
		{
			bottom = rect.getPosition().y + rect.getSize().y;
			left = rect.getPosition().x + rect.getSize().x;
			right = rect.getPosition().x;
			top = rect.getPosition().y;
		}
	}
};

class Player
{
public:
	//general player image and rect
	float bottom, left, right, top;
	sf::RectangleShape rect;
	sf::Sprite playerImage;

	//for void Walk(), selection, movement, and animation
	bool selected;
	sf::Vector2f targetPos;

	enum Direction{Down, Left, Right, Up};
	sf::Vector2i source;
	float frameCounter, switchFrame, frameSpeed;

	Player(sf::Vector2f position, sf::Vector2f size, sf::Texture &texture)
	{
		//general player initializations
		rect.setPosition(position);
		rect.setSize(size);

		rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineThickness(2); rect.setOutlineColor(sf::Color::White); //displayed when selected

		playerImage.setPosition(position);
		playerImage.setTexture(texture);

		//for void Walk()
		selected = false;
		targetPos = position;
		source.x = 1; source.y = Down;
		frameCounter = 0;
		switchFrame = 100;
		frameSpeed = 500;
	}

	void Update()
	{
		bottom = rect.getPosition().y + rect.getSize().y;
		left = rect.getPosition().x;
		right = rect.getPosition().x + rect.getSize().x;
		top = rect.getPosition().y;
	}

	void Walk(sf::RenderWindow &Window, Selector s, sf::Texture &texture, float movementConstant, float time)
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			//selection of player, is it collided?
			if(!(right < s.left || left > s.right || top > s.bottom || bottom < s.top))
				selected = true;
			else
				selected = false;
		}

		//movement and animation
		if(selected == true)
		{
			if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				targetPos.x = sf::Mouse::getPosition(Window).x - rect.getSize().x/2;
				targetPos.y = sf::Mouse::getPosition(Window).y - rect.getSize().y + 5;
			}

			Window.draw(rect);
		}

		sf::Vector2f walkVel(targetPos - rect.getPosition());
		float hyp = std::sqrt(walkVel.x * walkVel.x + walkVel.y * walkVel.y);
		if(hyp == 0) { walkVel.x = 0; walkVel.y = 0; hyp = 1; } //because can't divide by 0

		sf::Vector2f glitchMove(rect.getPosition().x - targetPos.x, rect.getPosition().y - targetPos.y);
		if(1.5 > glitchMove.x && -1.5 < glitchMove.x && 1.5 > glitchMove.y && -1.5 < glitchMove.y)
		{
			source.x = 1; //set the default hands down walk thing
		}
		else
		{
			//x part animation
			frameCounter += frameSpeed*time;
			if(frameCounter >= switchFrame)
			{
				frameCounter = 0;
				source.x++;
				if(source.x*32 >= texture.getSize().x)
				{
					source.x = 0;
				}
			}

			//y part animation
			if(walkVel.y > 0 && walkVel.x > 0 && walkVel.y > walkVel.x)		   {source.y = Down;}
			else if(walkVel.y > 0 && walkVel.x > 0 && walkVel.x > walkVel.y)   {source.y = Right;}
			else if(walkVel.y > 0 && walkVel.x < 0 && walkVel.y > -walkVel.x)  {source.y = Down;}
			else if(walkVel.y > 0 && walkVel.x < 0 && -walkVel.x > walkVel.y)  {source.y = Left;}
			else if(walkVel.y < 0 && walkVel.x < 0 && -walkVel.y > -walkVel.x) {source.y = Up;}
			else if(walkVel.y < 0 && walkVel.x < 0 && -walkVel.x > -walkVel.y) {source.y = Left;}
			else if(walkVel.y < 0 && walkVel.x > 0 && -walkVel.y > walkVel.x)  {source.y = Up;}
			else if(walkVel.y < 0 && walkVel.x > 0 && walkVel.x > -walkVel.y)  {source.y = Right;}

			//moving part
			rect.move(walkVel.x/hyp * movementConstant, walkVel.y/hyp * movementConstant);
			playerImage.move(walkVel.x/hyp * movementConstant, walkVel.y/hyp * movementConstant);
		}
		playerImage.setTextureRect(sf::IntRect(source.x*32, source.y*32, 32, 32));
	}
};

int main()
{
	//render window
	sf::RenderWindow Window;
	Window.create(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Warlock! No fun for all!");
	Window.setFramerateLimit(FRAME_CAP);

	//create player
	sf::Texture playerTexture;
	playerTexture.loadFromFile("playerTexture.png");
	sf::Vector2f playerPosition(100, 100); sf::Vector2f playerSize(32, 32);
	Player player1(Player(playerPosition, playerSize, playerTexture));

	//tile shit
	sf::Texture tileTexture;
	tileTexture.loadFromFile("tileTexture.png");
	Tile tile1(Tile(tileTexture, 5));

	//clocks and time
	sf::Clock Clock;
	sf::Time deltaTime;

	Selector selector(Selector(2, sf::Color::Blue));

	//game loop
	while(Window.isOpen())
	{
		deltaTime = Clock.restart();

		sf::Event Event;
		while(Window.pollEvent(Event))
		{
			switch(Event.type)
			{
			case sf::Event::Closed:
				Window.close();
				break;
			}
		}

		tile1.Update(Window);
		player1.Update();
		selector.Update(Window);
		player1.Walk(Window, selector, playerTexture, deltaTime.asMilliseconds() * 0.1, deltaTime.asSeconds());

		//draw to window
		Window.draw(player1.playerImage);
		Window.display();
		//Window.draw(selectorrectbaby);
		Window.clear();
	}

	return 0;
}

