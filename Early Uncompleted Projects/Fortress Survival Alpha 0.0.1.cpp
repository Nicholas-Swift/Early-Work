// Fortress Survival Alpha 0.0.1
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

const sf::Vector2i WINDOW_SIZE(800, 600); //window size
const int FRAME_CAP(60); //frame limit cap

const int tileMapHeight(38); //because 600/16 = 37.5
const int tileMapWidth(50); //because 800/16 = 50
sf::String Map[tileMapHeight] = {
	"00000000000000000000000000000000000000000000000000",
	"00000000000000000000000000000000000000000000000000",
	"0000000000000000000000t  0000000000000000000000000",
	"0000000000000000000000   0000000000000000000000000",
	"0000000000000000000000   0000000000000000000000000",
	"0000000000000000000000   0000000000000000000000000",
	"00000000000000000000000000qwwwwwwwwwe0000000000000",
	"00000000000000000000000000a000000000d0000000000000",
	"00000000000000000000000000a000000000d0000000000000",
	"00000000000000000000000000zxxxxxxxxxc0000000000000",
	"00000000000000000000000000000000000000000000000000",
	"00000000000000000000000000000000000000000000000000",
	"0000000000000000000000t  0000000000000000000000000",
	"0000000000000000000000   0000000000000000000000000",
	"0000000000000000000000   0000000000000000000000000",
	"0000000000000000000000   0000000000000000000000000",
	"00000000000000000000000000000000000000000000000000",
	"00000000000000000000000000000000000000000000000000",
	"00000000000000000000000000000000000000000000000000",
	"00000000000000000000000000000000000000000000000000",
	"00000000000000000000000000000000000000000000000000",
	"00000000000000000000000000000000000000000000000000",
	"0000000000000000000000t  0000000000000000000000000",
	"0000000000000000000000   0000000000000000000000000",
	"0000000000000000000000   0000000000000000000000000",
	"0000000000000000000000   0000000000000000000000000",
	"00000000000000000000000000000000000000000000000000",
	"00000000000000000000000000000000000000000000000000",
	"00000000000000000000000000000000000000000000000000",
	"00000000000000000000000000000000000000000000000000",
	"00000000000000000000000000000000000000000000000000",
	"00000000000000000000000000000000000000000000000000",
	"0000000000000000000000t  0000000000000000000000000",
	"0000000000000000000000   0000000000000000000000000",
	"0000000000000000000000   0000000000000000000000000",
	"0000000000000000000000   0000000000000000000000000",
	"00000000000000000000000000000000000000000000000000",
	"00000000000000000000000000000000000000000000000000"};

class TileMap
{
public:
	sf::Sprite tileSprite;
	int grassRand;

	TileMap(sf::Texture &texture, float position)
	{
		tileSprite.setTexture(texture);
	}

	void Update(sf::RenderWindow &window)
	{
		for(int i = 0; i < tileMapHeight; i++)
		{
			for(int j = 0; j < tileMapWidth; j++)
			{
				if(Map[i][j] == '0') tileSprite.setTextureRect(sf::IntRect(0, 0, 16, 16)); //normal grass block
				else if(Map[i][j] == 't') tileSprite.setTextureRect(sf::IntRect(32, 0, 48, 64)); //tree

				else if(Map[i][j] == 'q') tileSprite.setTextureRect(sf::IntRect(80, 0, 16, 16)); //fences in qweasdzxc keyboard way
				else if(Map[i][j] == 'w') tileSprite.setTextureRect(sf::IntRect(96, 0, 16, 16));
				else if(Map[i][j] == 'e') tileSprite.setTextureRect(sf::IntRect(112, 0, 16, 16));
				else if(Map[i][j] == 'a') tileSprite.setTextureRect(sf::IntRect(80, 16, 16, 16));
				else if(Map[i][j] == 'd') tileSprite.setTextureRect(sf::IntRect(112, 16, 16, 16));
				else if(Map[i][j] == 'z') tileSprite.setTextureRect(sf::IntRect(80, 32, 16, 16));
				else if(Map[i][j] == 'x') tileSprite.setTextureRect(sf::IntRect(96, 32, 16, 16));
				else if(Map[i][j] == 'c') tileSprite.setTextureRect(sf::IntRect(112, 32, 16, 16));

				else if(Map[i][j] == ' ' || '-') continue;

				tileSprite.setPosition(j*16, i*16);
				window.draw(tileSprite);
			}
		}
	}
};

class Player
{
public:
	//for creating the Player
	float bottom, left, right, top;
	sf::RectangleShape rect;
	sf::Sprite playerImage;

	//for void Walk()
	enum Direction{Down, Left, Right, Up};
	sf::Vector2i source;
	float frameCounter, switchFrame, frameSpeed;

	Player(sf::Vector2f position, sf::Vector2f size, sf::Texture &texture)
	{
		//set general player stuff
		rect.setPosition(position);
		rect.setSize(size);
		rect.setFillColor(sf::Color::Green);
		playerImage.setPosition(position);
		playerImage.setTexture(texture);

		//for void Walk()
		source.x = 1; source.y = Down;
		frameCounter = 0;
		switchFrame = 100;
		frameSpeed = 500;
	}

	void Walk(sf::Vector2f targetPos, float movementConstant, float time, sf::Texture &texture)
	{
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

	void Update()
	{
		bottom = rect.getPosition().y + rect.getSize().y;
		left = rect.getPosition().x;
		right = rect.getPosition().x + rect.getSize().x;
		top = rect.getPosition().y;
	}
};

int main()
{
	//render window
	sf::RenderWindow Window;
	Window.create(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Fortress Survival! No fun for all!");
	Window.setFramerateLimit(FRAME_CAP);

	//create tile map
	sf::Texture tileTexture;
	tileTexture.loadFromFile("tileTexture.png");
	TileMap tilemap(TileMap(tileTexture, 0));

	//create player
	sf::Texture playerTexture;
	playerTexture.loadFromFile("playerTexture.png");
	sf::Vector2f playerPosition(100, 100); sf::Vector2f playerSize(32, 32);
	Player player1(Player(playerPosition, playerSize, playerTexture));
	sf::Vector2f targetPosition(playerPosition);

	//animation stuff
	enum Direction{Down, Left, Right, Up};
	sf::Vector2i source(1, Down);

	//clocks and time
	sf::Clock Clock;
	sf::Time deltaTime;

	//game loop
	while(Window.isOpen())
	{
		deltaTime = Clock.restart();

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

		//player movement
		if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			targetPosition.x = sf::Mouse::getPosition(Window).x - player1.rect.getSize().x/2;
			targetPosition.y = sf::Mouse::getPosition(Window).y - player1.rect.getSize().y + 5;
		}
		player1.Walk(targetPosition, deltaTime.asMilliseconds() * 0.1, deltaTime.asSeconds(), playerTexture);
		player1.Update();

		//draw
		tilemap.Update(Window);
		Window.draw(player1.playerImage);
		Window.display();
		Window.clear();
	}

	return 0;
}

