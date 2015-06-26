// Fortress Survival Alpha 0.0.3
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

sf::Vector2f WINDOW_SIZE(800, 600);
float FRAME_CAP(120);

const int tileHeight(60);
const int tileWidth(80);
sf::String MAP[tileHeight] = {
"oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"o                                                                              o",
"oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo"};

class Selection
{
public:
	sf::RectangleShape rect;
	sf::Vector2f selectDown, selectCurrent;

	Selection(float thickness, sf::Color color)
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
	}
};

class Player
{
public:
	sf::RectangleShape rect;
	sf::Sprite playerImage;

	bool collide;

	bool selected;
	int selectionOffsetDraw;
	sf::Vector2f targetPos;

	sf::Vector2f walkVel;
	float hyp;
	sf::Vector2f glitchMove;

	enum Direction{Down, Left, Right, Up};
	sf::Vector2i source;
	float frameCounter, switchFrame, frameSpeed;

	Player(sf::Vector2f position, sf::Vector2f size, sf::Texture &texture)
	{
		rect.setPosition(position);
		rect.setSize(size);
		playerImage.setPosition(position);
		playerImage.setTexture(texture);

		selected = false;
		selectionOffsetDraw = 0;
		targetPos = position;
		source.x = 1; source.y = Down;
		frameCounter = 0;
		switchFrame = 100;
		frameSpeed = 500;
	}

	void isColliding(std::vector<Player> v)
	{
		for(int i = 0; i != v.size(); ++i)
		{
			if(rect.getPosition() == v[i].rect.getPosition())
				collide = false;
			else if(rect.getGlobalBounds().intersects(v[i].rect.getGlobalBounds()))
			{
				collide = true;
				break;
			}
			else
				collide = false;
		}
	}

	void Walk(sf::RenderWindow &Window, Selection &s, sf::Texture &texture, float movementConstant, float time)
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if(rect.getGlobalBounds().intersects(s.rect.getGlobalBounds()) || (sf::Mouse::getPosition(Window).x > rect.getPosition().x && sf::Mouse::getPosition(Window).x < rect.getPosition().x + rect.getSize().x && sf::Mouse::getPosition(Window).y > rect.getPosition().y && sf::Mouse::getPosition(Window).y < rect.getPosition().y + rect.getSize().y))
				selected = true;
			else
				selected = false;
		}

		if(selected == true)
		{
			if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				targetPos.x = sf::Mouse::getPosition(Window).x - rect.getSize().x/2;
				targetPos.y = sf::Mouse::getPosition(Window).y - rect.getSize().y + 5;
			}

			selectionOffsetDraw = 142;
		}
		else
			selectionOffsetDraw = 0;

		walkVel.x = targetPos.x - rect.getPosition().x;
		walkVel.y = targetPos.y - rect.getPosition().y;
		hyp = std::sqrt(walkVel.x * walkVel.x + walkVel.y * walkVel.y);
		if(hyp == 0)
		{
			walkVel.x = 0;
			walkVel.y = 0;
			hyp = 1;
		}

		glitchMove.x = rect.getPosition().x - targetPos.x;
		glitchMove.y = rect.getPosition().y - targetPos.y;
		if(1.5 > glitchMove.x && -1.5 < glitchMove.x && 1.5 > glitchMove.y && -1.5 < glitchMove.y)
			source.x = 1;
		else
		{
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

			if(walkVel.y > 0 && walkVel.x > 0 && walkVel.y > walkVel.x)		   {source.y = Down;}
			else if(walkVel.y > 0 && walkVel.x > 0 && walkVel.x > walkVel.y)   {source.y = Right;}
			else if(walkVel.y > 0 && walkVel.x < 0 && walkVel.y > -walkVel.x)  {source.y = Down;}
			else if(walkVel.y > 0 && walkVel.x < 0 && -walkVel.x > walkVel.y)  {source.y = Left;}
			else if(walkVel.y < 0 && walkVel.x < 0 && -walkVel.y > -walkVel.x) {source.y = Up;}
			else if(walkVel.y < 0 && walkVel.x < 0 && -walkVel.x > -walkVel.y) {source.y = Left;}
			else if(walkVel.y < 0 && walkVel.x > 0 && -walkVel.y > walkVel.x)  {source.y = Up;}
			else if(walkVel.y < 0 && walkVel.x > 0 && walkVel.x > -walkVel.y)  {source.y = Right;}

			rect.move(walkVel.x/hyp * movementConstant, walkVel.y/hyp * movementConstant);
			playerImage.move(walkVel.x/hyp * movementConstant, walkVel.y/hyp * movementConstant);
		}

		playerImage.setTextureRect(sf::IntRect(source.x*32, source.y*32 + selectionOffsetDraw, 32, 32));
		Window.draw(playerImage);
	}
};

class PressurePlate
{
public:
	sf::RectangleShape rectPlate;
	sf::Sprite plateImage;
	sf::RectangleShape rectWall;
	sf::Sprite wallImage;

	bool collideP;
	bool collideW;

	PressurePlate(sf::Vector2f positionP, sf::Vector2f sizeP, sf::Texture &textureP, sf::Vector2f positionW, sf::Vector2f sizeW, sf::Texture &textureW)
	{
		rectPlate.setPosition(positionP);
		rectPlate.setSize(sizeP);
		rectPlate.setFillColor(sf::Color::Red);
		plateImage.setPosition(positionP);
		plateImage.setTexture(textureP);

		rectWall.setPosition(positionW);
		rectWall.setSize(sizeW);
		rectWall.setFillColor(sf::Color::Magenta);
		wallImage.setPosition(positionW);
		wallImage.setTexture(textureW);
	}

	void collidePlate(std::vector<Player> v)
	{
		for(int i = 0; i != v.size(); ++i)
		{
			if(rectPlate.getGlobalBounds().intersects(v[i].rect.getGlobalBounds()))
			{
				collideP = true;
				break;
			}
			else
				collideP = false;
		}
	}

	void collideWall(std::vector<Player> v)
	{
		for(int i = 0; i != v.size(); ++i)
		{
			if(rectWall.getGlobalBounds().intersects(v[i].rect.getGlobalBounds()))
			{
				collideW = true;
				break;
			}
			else
				collideW = false;
		}
	}
};

int main()
{
	sf::RenderWindow Window;
	Window.create(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Fortress Survival 0.0.3, working mechanics!");
	Window.setFramerateLimit(FRAME_CAP);
	sf::Clock Clock;
	sf::Time deltaTime;

	Selection selection(Selection(2, sf::Color::Blue));

	sf::Vector2f zero(0, 0);
	sf::Vector2f poss(500, 500), sizee(32, 32), posss(200, 200), sizeee(32, 112);
	sf::Texture ttt, tttt;
	PressurePlate plate(PressurePlate(poss, sizee, ttt, posss, sizeee, tttt));

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
		selection.Update(Window);

		plate.collidePlate(players);
		plate.collideWall(players);
		Window.draw(plate.rectPlate);
		if(plate.collideP == true) //<----------- temp stuff
			plate.rectWall.setSize(zero);
		else
			plate.rectWall.setSize(sizeee);

		Window.draw(plate.rectWall);
		if(plate.collideW == true) //<---------- more temp
			std::cout<<"WTF COLLIDE WITH WALL?"<<std::endl;

		for(int i = 0; i != players.size(); ++i)
		{
			players[i].isColliding(players);
			if(players[i].collide == true) //<------------ temp stuff
			{
				std::cout<<"Woah player "<<i<<" is colliding man"<<std::endl;
			}
			players[i].Walk(Window, selection, whiteTexture, deltaTime.asMilliseconds()*0.1, deltaTime.asSeconds());
		}

		Window.display();
		Window.clear();
	}

	return 0;
}