// Space Shooter
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>

/*struct Intro
{
	sf::Vector2f windowMiddle;

	int topRow;
	std::vector<sf::RectangleShape> topVec;
	int botRow;
	std::vector<sf::RectangleShape> botVec;

	Intro(sf::RenderWindow &window, bool g)
	{
		std::cout<<"Intro started."<<std::endl;
		//CONSTANTS
		topRow = 5;
		botRow = 7;

		sf::Vector2f imageSize(32.f, 32.f);

		windowMiddle = sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2);
		//CONSTANTS

		topVec.clear(); botVec.clear();

		for(int i = 0; i < topRow; i++)
		{
			sf::RectangleShape *rect = new sf::RectangleShape;
			rect->setSize(imageSize);
			rect->setPosition(window.getSize().x * (i + 1) / topRow, -imageSize.y * 2);
			rect->setFillColor(sf::Color::Yellow);
			topVec.push_back(*rect);
			std::cout<<"topVec.push_back(*rect["<<i<<"]);"<<std::endl;
		}

		for(int i = 0; i < botRow; i++)
		{
			sf::RectangleShape *rect = new sf::RectangleShape;
			rect->setSize(imageSize);
			rect->setPosition(window.getSize().x * (i + 1) / botRow, window.getSize().x + imageSize.y * 2);
			rect->setFillColor(sf::Color::Green);
			botVec.push_back(*rect);
			std::cout<<"botVec.push_back(*rect["<<i<<"]);"<<std::endl;
		}

		std::cout<<"Intro successfully completed!"<<std::endl<<std::endl;
	}

	void Animate(sf::Time &deltaTime)
	{
		std::cout<<"Animation started."<<std::endl;
		for(int i = 0; i < topVec.size(); i++)
		{
			if(topVec[i].getPosition().y >= windowMiddle.y)
			{
				topVec[i].setPosition(sf::Vector2f(topVec[i].getPosition().x, windowMiddle.y));
			}
			else
			{
				topVec[i].move(0, 1 * deltaTime.asMilliseconds());
				std::cout<<"topVec["<<i<<"].move(0, 1);"<<std::endl;
			}
		}

		for(int i = 0; i < botVec.size(); i++)
		{
			if(botVec[i].getPosition().y <= windowMiddle.y)
			{
				botVec[i].setPosition(sf::Vector2f(botVec[i].getPosition().x, windowMiddle.y));
			}
			else
			{
				botVec[i].move(0, -1 * deltaTime.asMilliseconds());
				std::cout<<"botVec["<<i<<"].move(0, -1);"<<std::endl;
			}
		}
		std::cout<<"Animation successfully completed!"<<std::endl<<std::endl;
	}

	void Draw(sf::RenderWindow &window)
	{
		for(int i = 0; i < topRow; i++)
			window.draw(topVec[i]);
		for(int i = 0; i < botRow; i++)
			window.draw(botVec[i]);
	}

};*/

struct BackDrop
{
	//shape and image
	sf::Sprite sprite;
	float levelLength;

	BackDrop(float lvl, sf::Texture &texture, sf::IntRect &intrect)
	{
		sprite.setTexture(texture);
		sprite.setTextureRect(intrect);
	}

	void Update(sf::Time &deltaTime)
	{
		sprite.move(0, 0.01 * deltaTime.asMilliseconds());
	}

	void Draw(sf::RenderWindow &window)
	{
		window.draw(sprite);
	}
};

struct Bullet
{
	//shape and image
	sf::RectangleShape rect;
	sf::Sprite sprite;

	//movement
	float movementConstant;

	//collision
	float top, bottom, left, right;

	Bullet(sf::Vector2f position, sf::Texture &texture)
	{
		//shape and image
		rect.setPosition(position);
		rect.setSize(sf::Vector2f(5.f, 5.f));
		rect.setFillColor(sf::Color::Red);

		sprite.setPosition(position);
		sprite.setTexture(texture);

		//movement
		movementConstant = 0.5f;

		//collision
		top = rect.getPosition().y;
		bottom = rect.getPosition().y + rect.getSize().y;
		left = rect.getPosition().x;
		right = rect.getPosition().x + rect.getSize().x;
	}

	void Update(sf::Time deltaTime)
	{
		//movement
		rect.move(0, -1 * movementConstant * deltaTime.asMilliseconds());
		sprite.move(0, -1 * movementConstant * deltaTime.asMilliseconds());

		//collision properties
		top = rect.getPosition().y;
		bottom = rect.getPosition().y + rect.getSize().y;
		left = rect.getPosition().x;
		right = rect.getPosition().x + rect.getSize().x;
	}
};

struct Astroid
{
	//shape and image
	sf::RectangleShape rect;
	sf::Sprite sprite;

	//movement
	float movementConstantVertical;
	float movementConstantHorizontal;

	//collision
	float top, bottom, left, right;

	Astroid(sf::Vector2f position, float moveX, float moveY, sf::Texture &texture)
	{
		//shape and image
		rect.setPosition(position);
		rect.setSize(sf::Vector2f(32.f, 32.f));
		rect.setFillColor(sf::Color::Yellow);

		sprite.setTexture(texture);
		sprite.setPosition(position);
		sprite.setScale(0.6, 0.6);

		//movement
		movementConstantHorizontal = moveX;
		movementConstantVertical = moveY;

		//collision
		top = rect.getPosition().y;
		bottom = rect.getPosition().y + rect.getSize().y;
		left = rect.getPosition().x;
		right = rect.getPosition().x + rect.getSize().x;
	}

	void Update(sf::Time deltaTime)
	{
		rect.move(1 * movementConstantHorizontal * deltaTime.asMilliseconds(),
			1 * movementConstantVertical * deltaTime.asMilliseconds());

		sprite.move(1 * movementConstantHorizontal * deltaTime.asMilliseconds(),
			1 * movementConstantVertical * deltaTime.asMilliseconds());

		top = rect.getPosition().y;
		bottom = rect.getPosition().y + rect.getSize().y;
		left = rect.getPosition().x;
		right = rect.getPosition().x + rect.getSize().x;
	}
};

struct Player
{
	//shape and image
	sf::RectangleShape rect;
	sf::Sprite sprite;
	
	//movement
	bool isMovingUp, isMovingDown, isMovingLeft, isMovingRight;
	sf::Vector2f movement;
	float movementConstant;

	float top, bottom, left, right; //player collision

	//shooting
	bool isShooting;
	std::vector<Bullet> bullets;
	float whenBullet1;
	float whenBullet2;

	Player(sf::Texture &texture, int d, bool f)
	{
		//shape and image
		rect.setPosition(100.f, 100.f);
		rect.setSize(sf::Vector2f(112.f, 75.f));
		rect.setFillColor(sf::Color::Green);

		sprite.setPosition(100.f, 100.f);
		sprite.setTexture(texture);

		//movement
		isMovingUp = isMovingDown = isMovingLeft = isMovingRight = false;
		movement = sf::Vector2f(0.f, 0.f);
		movementConstant = 0.05f;

		//collision
		top = rect.getPosition().y;
		bottom = rect.getPosition().y + rect.getSize().y;
		left = rect.getPosition().x;
		right = rect.getPosition().x + rect.getSize().x;

		//shooting
		isShooting = false;
		bullets.clear();
		whenBullet1 = 0.f;
		whenBullet2 = 0.5f;
	}

	void HandleEvents(sf::Keyboard::Key key, bool isPressed)
	{
		//movement
		if (key == sf::Keyboard::Key::W)
			isMovingUp = isPressed;
		if (key == sf::Keyboard::Key::S)
			isMovingDown = isPressed;
		if (key == sf::Keyboard::Key::A)
			isMovingLeft = isPressed;
		if (key == sf::Keyboard::Key::D)
			isMovingRight = isPressed;

		//shooting
		if (key == sf::Keyboard::Key::Space)
			isShooting = isPressed;
	}

	void Move(sf::Time &deltaTime)
	{
		if (isMovingUp && movement.y > -3.f)
				movement.y -= 0.5f;
		if (isMovingDown && movement.y < 3.f)
				movement.y += 0.5f;
		if (isMovingLeft && movement.x > -3.f)
				movement.x -= 0.5f;
		if (isMovingRight && movement.x < 3.f)
				movement.x += 0.5f;

		rect.move(movement.x * movementConstant * deltaTime.asMilliseconds(), movement.y * movementConstant * deltaTime.asMilliseconds());
		sprite.move(movement.x * movementConstant * deltaTime.asMilliseconds(), movement.y * movementConstant * deltaTime.asMilliseconds());
	}

	void Shoot(sf::Time deltaTime, sf::Texture &texture)
	{
		if (isShooting)
			whenBullet1 += deltaTime.asSeconds();

		if (isShooting && whenBullet1 > whenBullet2)
		{
			Bullet *bullet = new Bullet(sf::Vector2f(rect.getPosition().x + 0.5 * rect.getSize().x, rect.getPosition().y), texture);
			bullets.push_back(*bullet);
			whenBullet2 += 0.3;
		}
	}

	void Update(sf::Time deltaTime)
	{
		//bullet update
		for (int i = 0; i < bullets.size(); i++)
			bullets[i].Update(deltaTime);

		//collision
		top = rect.getPosition().y;
		bottom = rect.getPosition().y + rect.getSize().y;
		left = rect.getPosition().x;
		right = rect.getPosition().x + rect.getSize().x;
	}

	void draw(sf::RenderWindow &window)
	{
		for (int i = 0; i < bullets.size(); i++)
		{
			//window.draw(bullets[i].rect);
			window.draw(bullets[i].sprite);
		}

		//window.draw(rect);
		window.draw(sprite);
	}

	void PlayerCollision(std::vector<Astroid> &a)
	{
		for (int i = 0; i < a.size(); i++)
		{
			if(a[i].right < left || a[i].left > right || a[i].top > bottom || a[i].bottom < top)
			{
				//not colliding!
			}

			else
			{
				//is colliding!
				a.erase(a.begin() + i);
				
				std::cout<<"END THE GAME, HE'S HIT!"<<std::endl;

				break;
			}
		}
	}
};

struct AstroidFall
{
	std::vector<Astroid> astroids;
	sf::Texture astroidTexture;

	AstroidFall(sf::Texture &texture, bool f)
	{
		astroidTexture = texture;
		astroids.clear();
	}

	void CreateAstroid()
	{
		int randomPos = rand() % 800;
		int randMoveX = rand() % 2;
		int randMoveY = rand() % 50 + 1;

		Astroid *astroid = new Astroid(sf::Vector2f(randomPos, -10), 0, randMoveY * 0.01, astroidTexture);
		astroids.push_back(*astroid);
	}

	void UpdateAstroid(sf::Time deltaTime)
	{
		for (int i = 0; i < astroids.size(); i++)
			astroids[i].Update(deltaTime);
	}

	void draw(sf::RenderWindow &window)
	{
		for (int i = 0; i < astroids.size(); i++)
		{
			window.draw(astroids[i].rect);
			window.draw(astroids[i].sprite);
		}
	}

	void CollisionB(std::vector<Bullet> &b)
	{
		//update bullets going past screen
		for (int i = 0; i < b.size(); i++)
		{
			if (b[i].rect.getPosition().y < -5)
				b.erase(b.begin() + i);
		}
	}

	void CollisionA()
	{
		for(int i = 0; i < astroids.size(); i++)
		{
			if (astroids[i].rect.getPosition().y > 610 || astroids[i].rect.getPosition().x < -10 || astroids[i].rect.getPosition().x > 810)
				astroids.erase(astroids.begin() + i);
		}
	}

	void CollisionAandB(std::vector<Bullet> &b)
	{
		for (int i = 0; i < astroids.size(); i++)
		{
			for (int j = 0; j < b.size(); j++)
			{
				if(astroids[i].right < b[j].left || astroids[i].left > b[j].right || astroids[i].top > b[j].bottom || astroids[i].bottom < b[j].top)
				{
					//not colliding!
				}

				else
				{
					//is colliding!
					astroids.erase(astroids.begin() + i);

					b.erase(b.begin() + j);

					//FINALLY FIXED BUG RIGHT HERE! YES
					break;
				}
			}
		}
	}
};

int main()
{
	//window setup
	sf::RenderWindow window(sf::VideoMode(800, 600), "Space Shooter");
	window.setFramerateLimit(60);
	sf::Clock clock;
	sf::Time deltaTime;
	
	//create backdrop
	sf::Texture backDropTexture; backDropTexture.loadFromFile("Assets/Backdrop.png"); backDropTexture.setSmooth(true);
	sf::IntRect intrect(0, 0, window.getSize().x, window.getSize().y);
	BackDrop backdrop(BackDrop(1, backDropTexture, intrect));

	//create player
	sf::Texture playerTexture; playerTexture.loadFromFile("Assets/Jet.png"); playerTexture.setSmooth(true);
	Player player(Player(playerTexture, 0, false));

	sf::Texture laserTexture; laserTexture.loadFromFile("Assets/BlueLaser.png"); laserTexture.setSmooth(true);

	//astroids
	sf::Clock astroidClock;
	sf::Texture astroidTexture; astroidTexture.loadFromFile("Assets/Astroid.png"); astroidTexture.setSmooth(true);
	AstroidFall astroidfall(AstroidFall(astroidTexture, false));

	while (window.isOpen())
	{
		deltaTime = clock.restart();
		sf::Event Event;

		while (window.pollEvent(Event))
		{
			switch(Event.type)
			{
			//handle keyboard events
			case sf::Event::KeyPressed:
				player.HandleEvents(Event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				player.HandleEvents(Event.key.code, false);
				break;

			//closed
			case sf::Event::Closed:
				window.close();
				break;
			}
		}

		//Important! Must stay, more or less, in this order!

		backdrop.Update(deltaTime);

		player.Move(deltaTime);
		player.Shoot(deltaTime, laserTexture);

		if (astroidClock.getElapsedTime().asSeconds() > 1)
		{
			astroidfall.CreateAstroid();
			astroidClock.restart();
		}

		player.Update(deltaTime);
		astroidfall.UpdateAstroid(deltaTime);

		astroidfall.CollisionB(player.bullets);
		astroidfall.CollisionA();
		astroidfall.CollisionAandB(player.bullets);

		player.PlayerCollision(astroidfall.astroids);

		window.clear();

		backdrop.Draw(window);
		player.draw(window);
		astroidfall.draw(window);

		window.display();
	}

	return 0;
}

