// Fortress Survival Alpha 0.0.2
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

const sf::Vector2f WINDOW_SIZE(800, 600);
const int FRAME_CAP(60);

const int tileHeight(38);
const int tileWidth(50);
sf::String MAP[tileHeight] = {
"                                                  ",
"                                                  ",
"          12222223                                ",
"          q------e                                ",
"          q------e                                ",
"          q-------222222222222223                 ",
"          q----------------------222222222222223  ",
"          q------------------------------------e  ",
"          q------------------------------------e  ",
"  12222222-------------------------------------e  ",
"  q--------------------------------------------e  ",
"  q--------------------------------------------e  ",
"  q--------------------------------------------e  ",
"  q--------------------------------------------e  ",
"  q--------------------------------------------e  ",
"  q--------------------------------------------e  ",
"  q--------------------------------------------e  ",
"  q--------------------------------------------e  ",
"  q--------------------------------------------e  ",
"  q--------------------------------------------e  ",
"  q--------------------------------------------e  ",
"  q--------------------------------------------e  ",
"  q--------------------------------------------e  ",
"  q--------------------------------------------e  ",
"  q----------------5---------------------------e  ",
"  q----------------+---------------------------e  ",
"  q--------------------------------------------e  ",
"  q--4+----------------------------------------e  ",
"  q--++----------------------------------------e  ",
"  q--------------------------------------------e  ",
"  asssssssssssssssssssssssssssss---------------e  ",
"  zxxxxxxxxxxxxxxxxxxxxxxxxxxxxxq--------------e  ",
"                                q--------------e  ",
"                                assssssssssssssd  ",
"                                zxxxxxxxxxxxxxxc  ",
"                                                  ",
"                                                  ",
"                                                  " };
class Tile
{
public:
	sf::Sprite tileSprite;

	Tile(sf::Texture &texture, bool wtf)
	{
		tileSprite.setTexture(texture);
		//std::cout<<wtf<<std::endl;
	}

	void Update(sf::RenderWindow &window)
	{
		for(int i = 0; i < tileHeight; i++)
		{
			for(int j = 0; j < tileWidth; j++)
			{
				if(MAP[i][j] == '1') tileSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
				else if(MAP[i][j] == '2') tileSprite.setTextureRect(sf::IntRect(16, 0, 16, 16));
				else if(MAP[i][j] == '3') tileSprite.setTextureRect(sf::IntRect(32, 0, 16, 16));
				else if(MAP[i][j] == 'q') tileSprite.setTextureRect(sf::IntRect(0, 16, 16, 32));
				else if(MAP[i][j] == '-') tileSprite.setTextureRect(sf::IntRect(16, 16, 16, 32));
				else if(MAP[i][j] == 'e') tileSprite.setTextureRect(sf::IntRect(32, 16, 16, 32));
				else if(MAP[i][j] == 'a') tileSprite.setTextureRect(sf::IntRect(0, 32, 16, 16));
				else if(MAP[i][j] == 's') tileSprite.setTextureRect(sf::IntRect(16, 32, 16, 16));
				else if(MAP[i][j] == 'd') tileSprite.setTextureRect(sf::IntRect(32, 32, 16, 16));
				else if(MAP[i][j] == 'z') tileSprite.setTextureRect(sf::IntRect(0, 48, 16, 16));
				else if(MAP[i][j] == 'x') tileSprite.setTextureRect(sf::IntRect(16, 48, 16, 16));
				else if(MAP[i][j] == 'c') tileSprite.setTextureRect(sf::IntRect(32, 48, 16, 16));

				else if(MAP[i][j] == '4') tileSprite.setTextureRect(sf::IntRect(0, 128, 32, 32));
				else if(MAP[i][j] == '5') tileSprite.setTextureRect(sf::IntRect(32, 128, 16, 32));
				else if(MAP[i][j] == '6') tileSprite.setTextureRect(sf::IntRect(64, 128, 48, 32));
				//else if(MAP[i][j] == '5') tileSprite.setTextureRect(sf::IntRect(112, 32, 32, 32));

				else if(MAP[i][j] == ' ') tileSprite.setTextureRect(sf::IntRect(80, 0, 16, 16));
				else continue;

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
	int drawSelected;
	sf::Vector2f targetPos;

	enum Direction{Down, Left, Right, Up};
	sf::Vector2i source;
	float frameCounter, switchFrame, frameSpeed;

	//for collision
	bool collide;

	Player(sf::Vector2f position, sf::Vector2f size, sf::Texture &texture)
	{
		//general player initializations
		rect.setPosition(position);
		rect.setSize(size);
		playerImage.setPosition(position);
		playerImage.setTexture(texture);

		//for void Walk()
		selected = false;
		drawSelected = 0;
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

	void isColliding(std::vector<Player> v)
	{
		for(int i = 0; i != v.size(); ++i)
		{
			if(rect.getPosition() == v[i].rect.getPosition())
				collide = false;
			else if(rect.getGlobalBounds().intersects(v[i].rect.getGlobalBounds()))
			{collide = true; break;}
			else
				collide = false;
		}
	}

	void Walk(sf::RenderWindow &Window, Selector &s, sf::Texture &texture, float movementConstant, float time)
	{
		//selection of player
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			//selection of player, is it collided?
			if(rect.getGlobalBounds().intersects(s.rect.getGlobalBounds()))
				selected = true;
			//else if(single click)
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

			drawSelected = 142;
		} else {drawSelected = 0;}

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
		playerImage.setTextureRect(sf::IntRect(source.x*32, source.y*32 + drawSelected, 32, 32));
		Window.draw(playerImage);
	}
};

int main()
{
	//render window
	sf::RenderWindow Window;
	Window.create(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Fortress Survival 0.0.2, finally coming together :)");
	Window.setFramerateLimit(FRAME_CAP);
	sf::Clock Clock;
	sf::Time deltaTime;

	//create tile ground
	sf::Texture tileTexture; tileTexture.loadFromFile("tileTexture.png");
	Tile tile(Tile(tileTexture, false));

	//create selector
	Selector selector(Selector(2, sf::Color::White));

	//create players
	sf::Vector2f playerSize(32, 32);
	sf::Texture whiteTexture; whiteTexture.loadFromFile("whiteKnight.png"); sf::Vector2f whitePos(10, 10);
	Player whiteKnight(Player(whitePos, playerSize, whiteTexture)); //maybe can do this all in vector?
	sf::Texture greyTexture; greyTexture.loadFromFile("greyKnight.png"); sf::Vector2f greyPos(40, 10);
	Player greyKnight(Player(greyPos, playerSize, greyTexture));
	sf::Texture goldTexture; goldTexture.loadFromFile("goldKnight.png"); sf::Vector2f goldPos(80, 10);
	Player goldKnight(Player(goldPos, playerSize, goldTexture));
	sf::Texture redTexture; redTexture.loadFromFile("redKnight.png"); sf::Vector2f redPos(120, 10);
	Player redKnight(Player(redPos, playerSize, redTexture));
	sf::Texture blueTexture; blueTexture.loadFromFile("blueKnight.png"); sf::Vector2f bluePos(160, 10);
	Player blueKnight(Player(bluePos, playerSize, blueTexture));
	sf::Texture greenTexture; greenTexture.loadFromFile("greenKnight.png"); sf::Vector2f greenPos(200, 10);
	Player greenKnight(Player(greenPos, playerSize, greenTexture));

	std::vector<Player> players;
	players.push_back(whiteKnight); players.push_back(greyKnight); players.push_back(goldKnight);
	players.push_back(redKnight); players.push_back(blueKnight); players.push_back(greenKnight);
	

	//game loop
	while(Window.isOpen())
	{
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

		deltaTime = Clock.restart();

		tile.Update(Window);
		selector.Update(Window);

		for(int i = 0; i != players.size(); ++i)
		{
			players[i].Update();
			players[i].isColliding(players);
			if(players[i].collide == true)
			{
				std::cout<<"wttff"<<std::endl;
			}

			players[i].Walk(Window, selector, whiteTexture, deltaTime.asMilliseconds()*0.1, deltaTime.asSeconds());
		}

		//draw
		Window.display();
		Window.clear();
	}

	return 0;
}

