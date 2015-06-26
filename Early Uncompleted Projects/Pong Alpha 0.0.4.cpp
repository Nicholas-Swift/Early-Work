//Pong Alpha 0.0.4
//fjwefiweof

#include "stdafx.h"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 500;
const int FRAME_CAP = 120;

class Paddle
{
public:
	sf::RectangleShape rect;
	sf::Sprite PaddleImage;
	float top, right, bottom, left;

	Paddle(sf::Vector2f size, sf::Vector2f position, sf::Texture &texture)
	{
		rect.setSize(size);
		rect.setPosition(position);
		rect.setFillColor(sf::Color::Blue);

		PaddleImage.setPosition(position);
		PaddleImage.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
		PaddleImage.setTexture(texture);
	}

	void Update()
	{
		bottom = rect.getPosition().y + rect.getSize().y;
		left = rect.getPosition().x;
		right = rect.getPosition().x + rect.getSize().x;
		top = rect.getPosition().y;
	}
};

class Ball
{
public:
	sf::RectangleShape rect;
	sf::Sprite BallImage;
	float top, right, bottom, left;

	Ball(sf::Vector2f size, sf::Vector2f position, sf::Texture &texture)
	{
		rect.setSize(size);
		rect.setPosition(position);
		rect.setFillColor(sf::Color::Blue);
		
		BallImage.setPosition(position);
		BallImage.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
		BallImage.setTexture(texture);
	}

	void Update()
	{
		bottom = rect.getPosition().y + rect.getSize().y;
		left = rect.getPosition().x;
		right = rect.getPosition().x + rect.getSize().x;
		top = rect.getPosition().y;
	}

	bool CollisionRightLeft( Paddle pRight, Paddle pLeft )
	{
		if( right >= pRight.left && top <= pRight.bottom && bottom >= pRight.top )
			return true;
		else if( left <= pLeft.right && top <= pRight.bottom && bottom >= pRight.top )
			return true;
		else
			return false;
	}

	bool CollisionTopBot( Paddle pTop, Paddle pBottom )
	{
		if( top <= pTop.bottom && right >= pTop.left && left <= pTop.right )
			return true;
		else if( bottom >= pBottom.top && right >= pTop.left && left <= pTop.right )
			return true;
		else
			return false;
	}
};

int main()
{
	sf::RenderWindow Window;
	Window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pong Alpha 0.0.4");
	Window.setFramerateLimit(FRAME_CAP);

	sf::Clock Clock;
	sf::Time DeltaTime;

	float BallDX = 0.5f;
	float BallDY = BallDX;

	/*=============================================================================================
	Class Initializations! BLEOW.
	Just keep going and ignore this if you are not looking to modify any class initializations.
	=============================================================================================*/
	/*sf::Font wowFont; wowFont.loadFromFile("RosewoodStd-Regular.otf"); int sbSize(50); sf::Color sbColor(sf::Color::Black);
	std::string sbStr = "zero"; sf::Vector2f sbPos1(10, 10);
	sf::Text scoreBoard1(sbStr, wowFont, sbSize); scoreBoard1.setColor(sbColor); scoreBoard1.setPosition(sbPos1);

	std::string sbStr2 = "zero"; sf::Vector2f sbPos2(600, 10);
	sf::Text scoreBoard2(sbStr2, wowFont, sbSize); scoreBoard2.setColor(sbColor); scoreBoard2.setPosition(sbPos2);*/

	sf::Texture paddleTexture; paddleTexture.loadFromFile("paddleTexture.png");
	sf::Vector2f p1Size(WINDOW_WIDTH/8, 10); sf::Vector2f p1Position(WINDOW_WIDTH/2 - p1Size.x/2, 0);
	Paddle paddleTop(Paddle(p1Size, p1Position, paddleTexture));

	sf::Vector2f p2Size(10, WINDOW_HEIGHT/8); sf::Vector2f p2Position(WINDOW_WIDTH - 10, WINDOW_HEIGHT/2 - p2Size.y/2);
	Paddle paddleRight(Paddle(p2Size, p2Position, paddleTexture));

	sf::Vector2f p3Size(WINDOW_WIDTH/8, 10); sf::Vector2f p3Position(WINDOW_WIDTH/2 - p3Size.x/2, WINDOW_HEIGHT - 10);
	Paddle paddleBottom(Paddle(p3Size, p3Position, paddleTexture));

	sf::Vector2f p4Size(10, WINDOW_HEIGHT/8); sf::Vector2f p4Position(0, WINDOW_HEIGHT/2 - p4Size.y/2);
	Paddle paddleLeft(Paddle(p4Size, p4Position, paddleTexture));

	sf::Vector2f bSize(WINDOW_WIDTH/30, WINDOW_WIDTH/30); sf::Vector2f bPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
	Ball ball(Ball(bSize, bPosition, paddleTexture));
	/*=============================================================================================
	Class Initializations! ABOVE.
	=============================================================================================*/

	sf::Event Event;
	while(Window.isOpen())
	{
		DeltaTime = Clock.restart();

		while(Window.pollEvent(Event))
		{
		switch(Event.type)
			{
			case sf::Event::Closed:
				Window.close();
				break;
			case sf::Event::MouseButtonPressed:
				ball.rect.setPosition(bPosition);
				break;
			}
		}

		/*=============================================================================================
		Paddle Movement! BLEOW.
		Just keep going and ignore this if the problem has nothing to do with paddle movement.
		=============================================================================================*/
		bool topBotCanLeft(true); bool topBotCanRight(true);
		bool rightLeftCanUp(true); bool rightLeftCanDown(true);

		float PadDX = WINDOW_WIDTH/500;
		float PadDY = WINDOW_HEIGHT/500;

		//top paddle, which will be the same as bottom
		if(paddleTop.left <= 0)
			topBotCanLeft = false;
		else if(paddleTop.right >= WINDOW_WIDTH)
			topBotCanRight = false;
		
		//right paddle, which will be the same as leftt
		if(paddleRight.top <= 0)
			rightLeftCanUp = false;
		else if(paddleRight.bottom >= WINDOW_HEIGHT)
			rightLeftCanDown = false;
		
		//top and bot paddle
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && topBotCanRight == true)
		{
			paddleTop.rect.move( PadDX * DeltaTime.asMilliseconds(), 0 );
			paddleBottom.rect.move( -PadDX * DeltaTime.asMilliseconds(), 0 );
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && topBotCanLeft == true)
		{
			paddleTop.rect.move( -PadDX * DeltaTime.asMilliseconds(), 0 );
			paddleBottom.rect.move( PadDX * DeltaTime.asMilliseconds(), 0 );
		}

		//right and left paddle
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && rightLeftCanUp == true)
		{
			paddleRight.rect.move( 0, -PadDY * DeltaTime.asMilliseconds() );
			paddleLeft.rect.move( 0, PadDY * DeltaTime.asMilliseconds() );
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && rightLeftCanDown == true)
		{
			paddleRight.rect.move( 0, PadDY * DeltaTime.asMilliseconds() );
			paddleLeft.rect.move( 0, -PadDY * DeltaTime.asMilliseconds() );
		}

		/*if(paddle1.top < 0)
			paddle1.rect.setPosition(paddle1.rect.getPosition().x, 0);
		else if(paddle1.bottom > WINDOW_HEIGHT)
			paddle1.rect.setPosition(paddle1.rect.getPosition().x, WINDOW_HEIGHT - paddle1.rect.getSize().y);
		
		if(paddle2.top < 0)
			paddle2.rect.setPosition(paddle2.rect.getPosition().x, 0);
		else if(paddle2.bottom > WINDOW_HEIGHT)
			paddle2.rect.setPosition(paddle2.rect.getPosition().x, WINDOW_HEIGHT - paddle2.rect.getSize().y);

		if(paddle1.top < 0)
			paddle1.rect.setPosition(paddle1.rect.getPosition().x, 0);
		else if(paddle1.bottom > WINDOW_HEIGHT)
			paddle1.rect.setPosition(paddle1.rect.getPosition().x, WINDOW_HEIGHT - paddle1.rect.getSize().y);
		
		if(paddle2.top < 0)
			paddle2.rect.setPosition(paddle2.rect.getPosition().x, 0);
		else if(paddle2.bottom > WINDOW_HEIGHT)
			paddle2.rect.setPosition(paddle2.rect.getPosition().x, WINDOW_HEIGHT - paddle2.rect.getSize().y);*/

		paddleTop.Update();
		paddleRight.Update();
		paddleBottom.Update();
		paddleLeft.Update();
		/*=============================================================================================
		Paddle Movement! ABOVE.
		=============================================================================================*/

		/*=============================================================================================
		Ball Movement! BLEOW.
		Just keep going and ignore this if the problem has nothing to do with ball movement.
		=============================================================================================*/
		if(ball.CollisionTopBot(paddleTop, paddleBottom)) {
			BallDY = -BallDY; std::cout<<"WOW HIT TOP AND BOT"<<std::endl; }
		else if(ball.CollisionRightLeft(paddleRight, paddleLeft)) {
			BallDX = -BallDX; std::cout<<" WOW HIT RIGHT AND LEFT"<<std::endl; }
		ball.rect.move(BallDX * DeltaTime.asMilliseconds(), BallDY * DeltaTime.asMilliseconds());

		/*if(ball1.Collision(paddle1, paddle2) && ball1.circ.getPosition().x < WINDOW_WIDTH/2 && ball1.circ.getPosition().x < paddle1.right + ball1.circ.getRadius())
			ball1.circ.setPosition(paddle1.right + ball1.circ.getRadius(), ball1.circ.getPosition().y);
		else if(ball1.Collision(paddle1, paddle2) && ball1.circ.getPosition().x > WINDOW_WIDTH/2 && ball1.circ.getPosition().x > paddle2.left - ball1.circ.getRadius())
			ball1.circ.setPosition(paddle2.left - ball1.circ.getRadius(), ball1.circ.getPosition().y);*/

		ball.Update();
		/*=============================================================================================
		Ball Movement! ABOVE.
		=============================================================================================*/

		/*=============================================================================================
		Score Board Change! BLEOW.
		Just keep going and ignore this if the problem has nothing to do with the score board.
		=============================================================================================*/
		/*if(ball1.right < 0)
		{
			if(sbStr == "zero")       {sbStr = "one"; ball1.circ.setPosition(bPosition);}
			else if(sbStr == "one")   {sbStr = "two"; ball1.circ.setPosition(bPosition);}
			else if(sbStr == "two")   {sbStr = "three"; ball1.circ.setPosition(bPosition);}
			else if(sbStr == "three") {sbStr = "four"; ball1.circ.setPosition(bPosition);}
			else if(sbStr == "four")  {sbStr = "five"; ball1.circ.setPosition(bPosition);}
		}
		scoreBoard1.setString(sbStr);

		if(ball1.left > WINDOW_WIDTH)
		{
			if(sbStr2 == "zero")       {sbStr2 = "one"; ball1.circ.setPosition(bPosition);}
			else if(sbStr2 == "one")   {sbStr2 = "two"; ball1.circ.setPosition(bPosition);}
			else if(sbStr2 == "two")   {sbStr2 = "three"; ball1.circ.setPosition(bPosition);}
			else if(sbStr2 == "three") {sbStr2 = "four"; ball1.circ.setPosition(bPosition);}
			else if(sbStr2 == "four")  {sbStr2 = "five"; ball1.circ.setPosition(bPosition);}
		}
		scoreBoard2.setString(sbStr2);*/

		Window.clear();
		Window.draw(paddleTop.rect);
		Window.draw(paddleRight.rect);
		Window.draw(paddleBottom.rect);
		Window.draw(paddleLeft.rect);
		Window.draw(ball.rect);
		Window.display();
	}

	return 0;
}