// Pong Alpha 0.0.1

// Random ball Y axis calculation
// All collision works, though it's not pretty
// Player paddles only serve as a collision wall, doesn't change angle
// No graphics, just colored rect and circ shapes.

#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics.hpp>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int FRAME_CAP = 60;

class Player
{
public:
	sf::RectangleShape rect; //general player initializations
	float bottom, left, right, top;

	Player(sf::Vector2f position, sf::Vector2f size, sf::Color color)
	{
		rect.setPosition(position);
		rect.setSize(size);
		rect.setFillColor(color);
	}

	void Update() //updating player coords
	{
		bottom = rect.getPosition().y + rect.getSize().y;
		left = rect.getPosition().x;
		right = rect.getPosition().x + rect.getSize().x;
		top = rect.getPosition().y;
	}

	bool CanMove(Player p) //can the player move in either direction?
	{
		if(p.top < 0 || p.bottom > WINDOW_HEIGHT)
			return false;
		else
			return true;
	}

	bool OnlyMoveUp(Player p) //the player can only move up
	{
		if(p.bottom > WINDOW_HEIGHT)
			return true;
		else
			return false;
	}

	bool OnlyMoveDown(Player p) //the player can only move down
	{
		if(p.top < 0)
			return true;
		else
			return false;
	}
};

class Ball
{
public:
	sf::CircleShape circ; //general ball initializations
	float bottom, left, right, top;

	Ball(sf::Vector2f position, float radius, sf::Color color)
	{
		circ.setPosition(position);
		circ.setRadius(radius);
		circ.setFillColor(color);
	}

	void Update() //updating ball coords
	{
		bottom = circ.getPosition().y + circ.getRadius();
		left = circ.getPosition().x;
		right = circ.getPosition().x + circ.getRadius();
		top = circ.getPosition().y;
	}

	bool CollisionLeft(Player p) //did the ball hit the left paddle?
	{
		if(left <= p.right && bottom >= p.top && top <= p.bottom && right >= p.left)
			return true;
		else
			return false;
	}

	bool CollisionRight(Player p) //did the ball hit the right paddle?
	{
		if(right >= p.left && bottom >= p.top && top <= p.bottom && left <= p.right)
			return true;
		else
			return false;
	}

	bool CollisionBotTop() //did the ball hit the top or bottom of the map?
	{
		if(top <= 0 || bottom >= WINDOW_HEIGHT)
			return true;
		else
			return false;
	}
};

int main()
{
	sf::RenderWindow Window; //general window initializations
	Window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "PONG - Alpha 0.0.1");
	Window.setFramerateLimit(FRAME_CAP);

	sf::Vector2f pSize(15, 100); //player number initializations
	sf::Vector2f pPosition1(10, 10);
	sf::Vector2f pPosition2(WINDOW_WIDTH - pSize.x - pPosition1.x, pPosition1.y);
	sf::Color pColor = sf::Color::White;

	Player player1(Player(pPosition1, pSize, pColor)); //creating the player
	Player player2(Player(pPosition2, pSize, pColor));

	sf::Vector2f bPosition(400, 200); //ball number initializations
	float bRadius(10);
	int ballVelY = 0;
	int ballVelX = -1;
	sf::Color bColor = sf::Color::White;

	Ball ball(Ball(bPosition, bRadius, bColor)); //creating the ball

	sf::Clock Clock; //creating clock for fps
	sf::Time deltaTime;

	sf::Event Event;
	while(Window.isOpen()) //game loop
	{
		deltaTime = Clock.restart();
		while(Window.pollEvent(Event)) //event loop
		{
			switch(Event.type)
			{
			case sf::Event::Closed:
				Window.close();
				break;
			case sf::Event::MouseButtonPressed:
				ball.circ.setPosition(bPosition);
				break;
			}
		}

		float paddleMovement = 0.0005f * deltaTime.asMicroseconds(); //paddle movement const

		if(player1.CanMove(player1)) //moving player 1
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				player1.rect.move( 0.0f, -paddleMovement );
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				player1.rect.move( 0.0f, paddleMovement );
		}
		else if(player1.OnlyMoveUp(player1)) //can only move up
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				player1.rect.move(0.0f, -paddleMovement );
		}
		else if(player1.OnlyMoveDown(player1)) //can only move down
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				player1.rect.move(0.0f, paddleMovement );
		}
		player1.Update(); //update player coords

		if(player2.CanMove(player2)) //moving player 2
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				player2.rect.move(0.0f, -paddleMovement );
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				player2.rect.move(0.0f, paddleMovement );
		}
		else if(player2.OnlyMoveUp(player2)) //can only move up
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				player2.rect.move(0.0f, -paddleMovement );
		}
		else if(player2.OnlyMoveDown(player2)) //can only move down
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				player2.rect.move(0.0f, paddleMovement );
		}
		player2.Update(); //update the coords

		if(ball.CollisionLeft(player1)) //ball hits left paddle
		{
			srand(static_cast<unsigned int>(time(0)));
			int randomNumber1 = (rand()%10)+1;
			int randomNumber2 = (rand()%20)+1;
			ballVelY = randomNumber1 - randomNumber2;
			ballVelX = 1; //switch x direction
		}
		else if(ball.CollisionRight(player2)) //ball hits right paddle
		{
			srand(static_cast<unsigned int>(time(0)));
			int randomNumber1 = (rand()%10)+1;
			int randomNumber2 = (rand()%20)+1;
			ballVelY = randomNumber1 - randomNumber2;
			ballVelX = -1; //switch x direction
		}
		else if(ball.CollisionBotTop()) //ball hits top or bottom of screen
		{
			ballVelY = -ballVelY;
		}

		float ballMovementX = 0.0005f * deltaTime.asMicroseconds(); //ball movement X const
		float ballMovementY = 0.00005f * deltaTime.asMicroseconds() * ballVelY; //ball movement Y const

		if(ballVelX == 1) //making the ball move around the screen when not hitting
			ball.circ.move(ballMovementX,  ballMovementY);
		else if(ballVelX == -1)
			ball.circ.move(-ballMovementX, ballMovementY);
		ball.Update();

		Window.clear(); //drawing things to the screen
		Window.draw(player1.rect);
		Window.draw(player2.rect);
		Window.draw(ball.circ);
		Window.display();
	}

	return 0;
}

