// Game 2.0
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class Enemy
{
public:
	sf::RectangleShape rect;
	float bottom, left, right, top;

	sf::Sprite enemyImage;
	Enemy(sf::Vector2f position, sf::Vector2f size, sf::Texture &texture)
	{
		rect.setPosition(position);
		rect.setSize(size);

		enemyImage.setTexture(texture);
		enemyImage.setPosition(position);
	}

	void Update()
	{
		bottom = rect.getPosition().y + rect.getSize().y;
		left = rect.getPosition().x;
		right = rect.getPosition().x + rect.getSize().x;
		top = rect.getPosition().y;
	}

	bool Collision(Enemy p)
	{
		if(right < p.left || left > p.right || top > p.bottom || bottom < p.top)
			return false;
		else
			return true;
	}
};

class Player
{
public:
	sf::RectangleShape rect;
	float bottom, left, right, top;
	sf::RectangleShape rectWalkBox;
	float bottomWalkBox, leftWalkBox, rightWalkBox, topWalkBox;

	sf::Sprite playerImage;
	Player(sf::Vector2f position, sf::Vector2f size, sf::Texture &texture)
	{
		rect.setPosition(position);
		rect.setSize(size);
		rect.setFillColor(sf::Color::White);

		sf::Vector2f posWalkBox(96, 96);
		rectWalkBox.setPosition(position - posWalkBox);
		rectWalkBox.setSize(size + posWalkBox + posWalkBox);
		rect.setFillColor(sf::Color::Green);

		playerImage.setTexture(texture);
		playerImage.setPosition(position);
	}

	void Update()
	{
		bottom = rect.getPosition().y + rect.getSize().y;
		left = rect.getPosition().x;
		right = rect.getPosition().x + rect.getSize().x;
		top = rect.getPosition().y;

		bottomWalkBox = rectWalkBox.getPosition().y + rectWalkBox.getSize().y;
		leftWalkBox = rectWalkBox.getPosition().x;
		rightWalkBox = rectWalkBox.getPosition().x + rectWalkBox.getSize().x;
		topWalkBox = rectWalkBox.getPosition().y;
	}

	void Move(Player c, sf::Vector2f d)
	{
		c.playerImage.move(d);
		c.rect.move(d);
		c.rectWalkBox.move(d);
	}

	bool Collision(Enemy p)
	{
		if(right < p.left || left > p.right || top > p.bottom || bottom < p.top)
			return false;
		else
			return true;
	}

	bool CollisionWalkBox(Enemy p)
	{
		if(rightWalkBox < p.left || leftWalkBox > p.right || topWalkBox > p.bottom || bottomWalkBox < p.top)
			return false;
		else
			return true;
	}
};

class PlayerAttack
{
public:
	sf::RectangleShape rect;

	/*sf::Sprite attackImage;
	sf::Texture attackTexture;*/
	PlayerAttack(sf::Vector2f position, sf::Vector2f size)
	{
		rect.setPosition(position);
		rect.setSize(size);
		rect.setFillColor(sf::Color::Red);

		/*attackTexture.loadFromFile("attackText.png");
		attackImage.setTexture(attackTexture);
		attackImage.setPosition(position);*/
	}

	float bottom, left, right, top;

	void Update()
	{
		bottom = rect.getPosition().y + rect.getSize().y;
		left = rect.getPosition().x;
		right = rect.getPosition().x + rect.getSize().x;
		top = rect.getPosition().y;
	}

	bool Collision(Enemy p)
	{
		if(right < p.left || left > p.right || top > p.bottom || bottom < p.top)
			return false;
		else
			return true;
	}

};

int main()
{
	/*=======================
	General Window Renders
	=======================*/
	sf::Vector2i WINDOW_SIZE(800, 608);

	sf::RenderWindow Window;
	Window.create(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Game");

	/*=======================
	Player and enemy initialization
	=======================*/
	sf::Texture playerTexture;
	playerTexture.loadFromFile("playerText.png");
	Player playerCharacter(Player(sf::Vector2f(10, 10), sf::Vector2f(32, 32), playerTexture));

	sf::Texture enemyTexture;
	enemyTexture.loadFromFile("enemyText.png");
	Enemy enemyCharacter(Enemy(sf::Vector2f(150, 150), sf::Vector2f(32, 32), enemyTexture));

	PlayerAttack attackCharacter(PlayerAttack(sf::Vector2f(playerCharacter.playerImage.getPosition()), sf::Vector2f(32, 32)));

	/*=======================
	Enemy movement
	=======================*/
	sf::Vector2f velocityTemp;
	sf::Clock clock;
	clock.restart();
	sf::Time time;

	/*=======================
	Animation of player and enemy
	=======================*/
	enum Direction {Down, Left, Right, Up};
	float frameCounter = 0, switchFrame = 100, frameSpeed = 500;
	sf::Clock animationClock;
	sf::Vector2i playerSource(1, Down);

	float frameCounterE = 0, switchFrameE = 100, frameSpeedE = 500;
	sf::Clock animationClockE;
	sf::Vector2i enemySource(1, Down);

	/*=======================
	FUCKING CLOCK FPS SHIITT
	=======================*/
	sf::Clock fuckyouclock;
	float fucklastTime = 0;

	/*=======================
	Game loop
	=======================*/
	sf::Event Event;
	while(Window.isOpen())
	{
		while(Window.pollEvent(Event))
		{
			switch(Event.type)
			{
			case sf::Event::Closed:
				Window.close();
				break;
			case sf::Event::MouseButtonPressed:
				std::cout<<Event.mouseButton.x<<", "<<Event.mouseButton.y<<std::endl;
				break;
			}
		}

		/*float currentTime = fuckyouclock.restart().asSeconds();
		float fps = 1.f / (currentTime - fucklastTime);
		fucklastTime = currentTime;
		std::cout<<fucklastTime<<std::endl;

		sf::Time elapsed = fuckyouclock.restart();
		float fuckthis = elapsed.asSeconds();
		std::cout<<fuckthis<<std::endl;*/

		sf::Vector2f velocityNeutral(0, 0), velocityUp(0, -1 /*fuckthis*/), velocityLeft(-1 /*fuckthis*/, 0), velocityRight(1 /* fuckthis*/, 0), velocityDown(0, 1 /* fuckthis*/);

		bool animate = true;

		/*=======================
		Enemy movement and animation
		=======================*/
		if(enemyCharacter.enemyImage.getPosition().y < playerCharacter.playerImage.getPosition().y)
		{
			enemyCharacter.enemyImage.move(velocityDown);
			enemyCharacter.rect.move(velocityDown);
			enemySource.y = Down;
		}
		else if(enemyCharacter.enemyImage.getPosition().y > playerCharacter.playerImage.getPosition().y)
		{
			enemyCharacter.enemyImage.move(velocityUp);
			enemyCharacter.rect.move(velocityUp);
			enemySource.y = Up;
		}
		if(enemyCharacter.enemyImage.getPosition().x < playerCharacter.playerImage.getPosition().x)
		{
			enemyCharacter.enemyImage.move(velocityRight);
			enemyCharacter.rect.move(velocityRight);
			enemySource.y = Right;
		}
		else if(enemyCharacter.enemyImage.getPosition().x > playerCharacter.playerImage.getPosition().x)
		{
			enemyCharacter.enemyImage.move(velocityLeft);
			enemyCharacter.rect.move(velocityLeft);
			enemySource.y = Left;
		}

		/*=======================
		Player attack
		=======================*/
		sf::Vector2f attackY(32, 16), attackX(16, 32);

		if(playerSource.y == Down)
		{
			attackCharacter.rect.setPosition(playerCharacter.playerImage.getPosition().x, playerCharacter.playerImage.getPosition().y + 32);
			attackCharacter.rect.setSize(attackY);
		}
		else if(playerSource.y == Left)
		{
			attackCharacter.rect.setPosition(playerCharacter.playerImage.getPosition().x - 16, playerCharacter.playerImage.getPosition().y);
			attackCharacter.rect.setSize(attackX);
		}
		else if(playerSource.y == Right)
		{
			attackCharacter.rect.setPosition(playerCharacter.playerImage.getPosition().x + 32, playerCharacter.playerImage.getPosition().y);
			attackCharacter.rect.setSize(attackX);
		}
		else if(playerSource.y == Up)
		{
			attackCharacter.rect.setPosition(playerCharacter.playerImage.getPosition().x, playerCharacter.playerImage.getPosition().y - 16);
			attackCharacter.rect.setSize(attackY);
		}

		/*=======================
		Player movement and animation + attack
		=======================*/
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			playerCharacter.Move(playerCharacter, (velocityUp + velocityUp));

			playerSource.y = Up;

			attackCharacter.rect.move(velocityUp + velocityUp);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			playerCharacter.Move(playerCharacter, (velocityLeft + velocityLeft));
			playerSource.y = Left;

			attackCharacter.rect.move(velocityLeft + velocityLeft);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			playerCharacter.Move(playerCharacter, (velocityRight + velocityRight));
			playerSource.y = Right;

			attackCharacter.rect.move(velocityRight + velocityRight);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			playerCharacter.Move(playerCharacter, (velocityDown + velocityDown));
			playerSource.y = Down;

			attackCharacter.rect.move(velocityDown + velocityDown);
		}
		else
		{
			animate = false;
		}

		enemyCharacter.Update();
		attackCharacter.Update();
		playerCharacter.Update();

		/*=======================
		Collision
		=======================*/
		if(playerCharacter.Collision(enemyCharacter))
		{
			//std::cout<<"WOAH DUDE, YOU'RE COLLIDING!"<<std::endl;
		}

		/*=======================
		The actual animating component, needs to still be worked out
		=======================*/
		frameCounterE += frameSpeedE*animationClockE.restart().asSeconds();
		if(frameCounterE >= switchFrameE)
		{
			frameCounterE = 0;
			enemySource.x++;
			if(enemySource.x*32 >= enemyTexture.getSize().x)
			{
				enemySource.x = 0;
			}
		}

		if(animate)
		{
			frameCounter += frameSpeed*animationClock.restart().asSeconds();
			if(frameCounter >= switchFrame)
			{
				frameCounter = 0;
				playerSource.x++;
				if(playerSource.x*32 >= playerTexture.getSize().x)
				{
					playerSource.x = 0;
				}
			}
		}
		else
		{
			playerSource.x = 1;
		}

		sf::Texture backgroundTexture;
		backgroundTexture.loadFromFile("backgroundText.png");
		sf::Sprite backgroundSprite;
		backgroundSprite.setTexture(backgroundTexture);


		/*=======================
		Drawing to screen
		=======================*/
		playerCharacter.playerImage.setTextureRect(sf::IntRect(playerSource.x*32, playerSource.y*32, 32, 32));
		//Window.draw(playerCharacter.rectWalkBox);
		//Window.draw(playerCharacter.rect);
		Window.draw(backgroundSprite);
		Window.draw(playerCharacter.playerImage);

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			Window.draw(attackCharacter.rect);
			attackCharacter.Update();
			if(attackCharacter.Collision(enemyCharacter))
			{
				std::cout<<"HOLY SHIT"<<std::endl;
			}
		}

		enemyCharacter.enemyImage.setTextureRect(sf::IntRect(enemySource.x*32, enemySource.y*32, 32, 32));
		Window.draw(enemyCharacter.enemyImage);

		Window.display();
		Window.clear();
	}

	return 0;
}