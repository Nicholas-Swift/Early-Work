// Pong Alpha 0.0.3
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int FRAME_CAP = 120;

class Background
{
public:
	sf::RectangleShape rect;

	Background(sf::Vector2f size, sf::Color color)
	{
		rect.setPosition(0, 0);
		rect.setSize(size);
		rect.setFillColor(color);
	}
};

class Paddle
{
public:
	sf::RectangleShape rect;
	sf::RectangleShape rectShadow;
	float bottom, left, right, top;

	Paddle(sf::Vector2f position, sf::Vector2f size, sf::Color color)
	{
		rect.setPosition(position);
		rect.setSize(size);
		rect.setFillColor(color);
		rect.setOutlineThickness(0.5);
		rect.setOutlineColor(sf::Color(255,204,0));

		rectShadow.setPosition(position.x + 3, position.y +3);
		rectShadow.setSize(size);
		rectShadow.setFillColor(sf::Color(20,53,59));
	}

	void Update()
	{
		bottom = rect.getPosition().y + rect.getSize().y;
		left = rect.getPosition().x;
		right = rect.getPosition().x + rect.getSize().x;
		top = rect.getPosition().y;

		rectShadow.setPosition(rect.getPosition().x + 3, rect.getPosition().y + 3);
	}
};

class Ball
{
public:
	sf::CircleShape circ;
	sf::CircleShape circShadow;
	float bottom, left, right, top;

	Ball(sf::Vector2f position, float radius, sf::Color color)
	{
		circ.setPosition(position);
		circ.setRadius(radius);
		circ.setFillColor(color);
		circ.setOutlineThickness(0.5);
		circ.setOutlineColor(sf::Color(255,204,0));

		circShadow.setPosition(position.x + 3, position.y + 3);
		circShadow.setRadius(radius);
		circShadow.setFillColor(sf::Color(20,53,59));
	}

	void Update()
	{
		bottom = circ.getPosition().y + circ.getRadius();
		left = circ.getPosition().x;
		right = circ.getPosition().x + circ.getRadius();
		top = circ.getPosition().y;

		circShadow.setPosition(circ.getPosition().x + 3, circ.getPosition().y + 3);
	}

	bool Collision(Paddle p, Paddle p2)
	{
		if(left <= p.right && bottom >= p.top && top <= p.bottom && right >= p.left)
			return true;
		else if(right >= p2.left && bottom >= p2.top && top <= p2.bottom && left <= p2.right)
			return true;
		else
			return false;
	}

	bool Collisiontop()
	{
		if(top <= 0 || bottom >= WINDOW_HEIGHT)
			return true;
		else
			return false;
	}

};

int main()
{
	sf::RenderWindow Window;
	Window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pong Alpha 0.0.3");
	Window.setFramerateLimit(FRAME_CAP);

	sf::Clock Clock;
	sf::Time DeltaTime;

	bool invert(false);
	float BallDX = 0.5f;
	float BallDY = BallDX;

	/*=============================================================================================
	Class Initializations! BLEOW.
	Just keep going and ignore this if you are not looking to modify any class initializations.
	=============================================================================================*/
	//orange(253,147,8);
	//blue(138,147,157);

	sf::Vector2f backSize(WINDOW_WIDTH, WINDOW_HEIGHT); sf::Color backColor(sf::Color(138,147,157));
	Background background1(Background(backSize, backColor));

	sf::Font wowFont; wowFont.loadFromFile("RosewoodStd-Regular.otf"); int sbSize(50); sf::Color sbColor(sf::Color::Black);
	std::string sbStr = "zero"; sf::Vector2f sbPos1(10, 10);
	sf::Text scoreBoard1(sbStr, wowFont, sbSize); scoreBoard1.setColor(sbColor); scoreBoard1.setPosition(sbPos1);

	std::string sbStr2 = "zero"; sf::Vector2f sbPos2(600, 10);
	sf::Text scoreBoard2(sbStr2, wowFont, sbSize); scoreBoard2.setColor(sbColor); scoreBoard2.setPosition(sbPos2);

	sf::Vector2f p1Position(10, 10); sf::Vector2f p1Size(15, 100); sf::Color p1Color(sf::Color(253,147,8));
	Paddle paddle1(Paddle(p1Position, p1Size, p1Color));

	sf::Vector2f p2Position(780, 10); sf::Vector2f p2Size(15, 100); sf::Color p2Color(sf::Color(253,147,8));
	Paddle paddle2(Paddle(p2Position, p2Size, p2Color));

	sf::Vector2f bPosition(300, 300); float bRadius(10); sf::Color bColor(sf::Color(253,147,8));
	Ball ball1(Ball(bPosition, bRadius, bColor));
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
				ball1.circ.setPosition(bPosition);
				sbStr = "zero";
				sbStr2 = "zero";
				break;
			}
		}

		/*=============================================================================================
		Paddle Movement! BLEOW.
		Just keep going and ignore this if the problem has nothing to do with paddle movement.
		=============================================================================================*/
		bool CanUp(true), CanDown(true);
		bool CanUp2(true), CanDown2(true);
		float PadDY = 0.8f;

		if(paddle1.top <= 0)
			CanUp = false;
		else if(paddle1.bottom >= WINDOW_HEIGHT)
			CanDown = false;
		
		if(paddle2.top <= 0)
			CanUp2 = false;
		else if(paddle2.bottom >= WINDOW_HEIGHT)
			CanDown2 = false;
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && CanUp == true)
			paddle1.rect.move(0, -PadDY * DeltaTime.asMilliseconds());
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && CanDown == true)
			paddle1.rect.move(0, PadDY * DeltaTime.asMilliseconds());

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && CanUp2 == true)
			paddle2.rect.move(0, -PadDY * DeltaTime.asMilliseconds());
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && CanDown2 == true)
			paddle2.rect.move(0, PadDY * DeltaTime.asMilliseconds());

		if(paddle1.top < 0)
			paddle1.rect.setPosition(paddle1.rect.getPosition().x, 0);
		else if(paddle1.bottom > WINDOW_HEIGHT)
			paddle1.rect.setPosition(paddle1.rect.getPosition().x, WINDOW_HEIGHT - paddle1.rect.getSize().y);
		
		if(paddle2.top < 0)
			paddle2.rect.setPosition(paddle2.rect.getPosition().x, 0);
		else if(paddle2.bottom > WINDOW_HEIGHT)
			paddle2.rect.setPosition(paddle2.rect.getPosition().x, WINDOW_HEIGHT - paddle2.rect.getSize().y);

		paddle1.Update();
		paddle2.Update();
		/*=============================================================================================
		Paddle Movement! ABOVE.
		=============================================================================================*/

		/*=============================================================================================
		Ball Movement! BLEOW.
		Just keep going and ignore this if the problem has nothing to do with ball movement.
		=============================================================================================*/
		if(ball1.Collision(paddle1, paddle2))
			BallDX = -BallDX;
		else if(ball1.Collisiontop())
			BallDY = -BallDY;
		ball1.circ.move(BallDX * DeltaTime.asMilliseconds(), BallDY * DeltaTime.asMilliseconds());

		if(ball1.top < 0)
			ball1.circ.setPosition(ball1.circ.getPosition().x, 0 + ball1.circ.getRadius());
		else if(ball1.bottom > WINDOW_HEIGHT)
			ball1.circ.setPosition(ball1.circ.getPosition().x, WINDOW_HEIGHT - ball1.circ.getRadius()*2);
		else if(ball1.Collision(paddle1, paddle2) && ball1.circ.getPosition().x < WINDOW_WIDTH/2 && ball1.circ.getPosition().x < paddle1.right + ball1.circ.getRadius())
			ball1.circ.setPosition(paddle1.right + ball1.circ.getRadius(), ball1.circ.getPosition().y);
		else if(ball1.Collision(paddle1, paddle2) && ball1.circ.getPosition().x > WINDOW_WIDTH/2 && ball1.circ.getPosition().x > paddle2.left - ball1.circ.getRadius())
			ball1.circ.setPosition(paddle2.left - ball1.circ.getRadius(), ball1.circ.getPosition().y);

		ball1.Update();
		/*=============================================================================================
		Ball Movement! ABOVE.
		=============================================================================================*/

		/*=============================================================================================
		Score Board Change! BLEOW.
		Just keep going and ignore this if the problem has nothing to do with the score board.
		=============================================================================================*/
		if(ball1.right < 0)
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
		scoreBoard2.setString(sbStr2);

		Window.clear();
		Window.draw(background1.rect);
		Window.draw(paddle1.rectShadow);
		Window.draw(paddle2.rectShadow);
		Window.draw(ball1.circShadow);
		Window.draw(scoreBoard1);
		Window.draw(scoreBoard2);
		Window.draw(paddle1.rect);
		Window.draw(paddle2.rect);
		Window.draw(ball1.circ);
		Window.display();
	}

	return 0;
}

