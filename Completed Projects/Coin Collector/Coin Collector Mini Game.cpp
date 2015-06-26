// Coin Collector Mini Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

struct Coin
{
	sf::RectangleShape rect;
	sf::Sprite sprite;

	float top, bottom, left, right;

	float time;

	sf::Vector2i source;
	float frameCounter, switchFrame, frameSpeed;

	Coin(sf::Texture &texture, sf::Vector2f position)
	{
		rect.setSize(sf::Vector2f(16, 16));
		rect.setPosition(position);
		rect.setFillColor(sf::Color::Yellow);

		sprite.setTexture(texture);
		sprite.setPosition(position);

		top = rect.getPosition().y;
		bottom = rect.getPosition().y + rect.getSize().y;
		left = rect.getPosition().x;
		right = rect.getPosition().x + rect.getSize().x;

		time = 0;

		source.x = 1; source.y = 0;
		frameCounter = 0;
		switchFrame = 100;
		frameSpeed = 500;

		sprite.setTextureRect(sf::IntRect(16*4, 16*4, 16, 16));
	}

	void Update(sf::Time deltaTime)
	{
		time += deltaTime.asSeconds();
	}

	void Animate(sf::Time deltaTime)
	{
		frameCounter += frameSpeed * deltaTime.asMilliseconds() * 0.03;
		if(frameCounter >= switchFrame)
		{
			frameCounter = 0;
			source.x++;
			if(source.x * 16 >= 16 * 8)
			{
				source.x = 0;
				source.y += 1;
			}
			if(source.y > 8)
				source.y = 0;
		}

		sprite.setTextureRect(sf::IntRect(source.x * 16, source.y * 16, 16, 16));
	}

	bool CoinDespawn()
	{
		if(time > 6)
			return true;
		else
			return false;
	}

	//NOTE: need to make a spawn and delete animation
};

struct Frost
{
	sf::RectangleShape rect;
	sf::Sprite sprite;

	float top, bottom, left, right;

	float time;

	bool stage1, stage2;
	bool fakeFrost1, fakeFrost2;

	sf::Vector2i source;
	float frameCounter, switchFrame, frameSpeed;

	Frost(sf::Texture &texture, sf::Vector2f position, sf::Vector2f size)
	{
		rect.setSize(sf::Vector2f(size));
		rect.setPosition(position);
		rect.setFillColor(sf::Color::Blue);

		texture.setRepeated(true);
		sprite.setTexture(texture);
		sprite.setPosition(position);
		sprite.setTextureRect(sf::IntRect(source.x * 32, source.y * 32, rect.getSize().x, rect.getSize().y));

		top = rect.getPosition().y;
		bottom = rect.getPosition().y + rect.getSize().y;
		left = rect.getPosition().x;
		right = rect.getPosition().x + rect.getSize().x;

		time = 0;

		stage1 = stage2 = false;
		fakeFrost1 = fakeFrost2 = false;

		source.x = 1; source.y = 0;
		frameCounter = 0;
		switchFrame = 100;
		frameSpeed = 500;
	}

	void Update(sf::Time deltaTime, sf::Time frostClock)
	{
		time += deltaTime.asSeconds();

		top = rect.getPosition().y;
		bottom = rect.getPosition().y + rect.getSize().y;
		left = rect.getPosition().x;
		right = rect.getPosition().x + rect.getSize().x;
	}

	void Animate(sf::Time deltaTime)
	{
		frameCounter += frameSpeed * deltaTime.asMilliseconds() * 0.002;
		if(frameCounter >= switchFrame)
		{
			frameCounter = 0;
			source.x++;
			if(source.x * 32 >= 32 * 5)
			{
				source.x = 0;
				source.y += 1;
			}
			if(source.y > 3)
				source.y = 0;
		}

		sprite.setTextureRect(sf::IntRect(source.x * 32, source.y * 32, rect.getSize().x, rect.getSize().y));
	}
};

struct Player
{
	sf::RectangleShape rect;
	sf::Sprite sprite;

	float health;
	int coins;
	sf::RectangleShape healthRectRed;
	sf::RectangleShape healthRectGreen;

	sf::Vector2f movement;
	bool isMovingUp, isMovingDown, isMovingLeft, isMovingRight;
	float top, bottom, left, right;

	enum Direction{Down, Left, Right, Up};
	sf::Vector2i source;
	float frameCounter, switchFrame, frameSpeed;

	Player(sf::Texture &texture, bool f)
	{
		rect.setSize(sf::Vector2f(32, 32));
		rect.setFillColor(sf::Color::Green);
		rect.setPosition(0, 0);

		sprite.setTexture(texture);
		sprite.setPosition(0, 0);

		health = 100;
		coins = 0;
		healthRectRed.setSize(sf::Vector2f(32, 6));
		healthRectRed.setPosition(-6, 0);
		healthRectRed.setFillColor(sf::Color::Red);
		healthRectGreen.setSize(sf::Vector2f(32, 6));
		healthRectGreen.setPosition(-6, 0);
		healthRectGreen.setFillColor(sf::Color::Green);


		movement.x = 0; movement.y = 0;
		isMovingUp = isMovingDown = isMovingLeft = isMovingRight = false;

		top = rect.getPosition().y;
		bottom = rect.getPosition().y + rect.getSize().y;
		left = rect.getPosition().x;
		right = rect.getPosition().x + rect.getSize().x;

		source.x = 1; source.y = Down;
		frameCounter = 0;
		switchFrame = 100;
		frameSpeed = 500;

		sprite.setTextureRect(sf::IntRect(source.x * 32, source.y * 32, 32, 32));
	}

	void Update()
	{
		top = rect.getPosition().y;
		bottom = rect.getPosition().y + rect.getSize().y;
		left = rect.getPosition().x;
		right = rect.getPosition().x + rect.getSize().x;

		healthRectRed.setPosition(rect.getPosition().x, rect.getPosition().y - healthRectRed.getSize().y);
		healthRectGreen.setSize(sf::Vector2f(32.f * health / 100, 6));
		healthRectGreen.setPosition(healthRectRed.getPosition());

		if(left <= 0)
			rect.setPosition(0, rect.getPosition().y);
		if(right >= 600 /* NOTE: This is window size! */)
			rect.setPosition(600 - rect.getSize().x, rect.getPosition().y);
		if(top <= 0)
			rect.setPosition(rect.getPosition().x, 0);
		if(bottom >= 600 /*NOTE: This is window size! */)
			rect.setPosition(rect.getPosition().x, 600 - rect.getSize().y);

		if(health <= 0)
		{
			std::cout<<"END THE GAMMEEEEEE.. EENNDDD THEEE GAAAMMMEEEEEEE"<<std::endl;
		}
	}

	void Animate(sf::Time deltaTime)
	{
		frameCounter += frameSpeed * deltaTime.asMilliseconds() * 0.001;
		if(frameCounter >= switchFrame)
		{
			frameCounter = 0;
			source.x++;
			if(source.x * 32 >= 32*3)
				source.x = 0;
		}

		if(movement.x > abs(movement.y))
			source.y = Right;
		else if(movement.x < -1 *abs(movement.y))
			source.y = Left;
		else if(movement.y > abs(movement.x))
			source.y = Down;
		else if(movement.y < -1 *abs(movement.x))
			source.y = Up;

		sprite.setTextureRect(sf::IntRect(source.x * 32, source.y * 32, 32, 32));
	}

	void HandleMovementEvents(sf::Keyboard::Key key, bool isPressed)
	{
		if (key == sf::Keyboard::Key::W)
			isMovingUp = isPressed;
		if (key == sf::Keyboard::Key::S)
			isMovingDown = isPressed;
		if (key == sf::Keyboard::Key::A)
			isMovingLeft = isPressed;
		if (key == sf::Keyboard::Key::D)
			isMovingRight = isPressed;
	}

	void Move(sf::Time &deltaTime)
	{
		if (isMovingUp)
			movement.y -= 0.6f;
		if (isMovingDown)
			movement.y += 0.6f;
		if (isMovingLeft)
			movement.x -= 0.6f;
		if (isMovingRight)
			movement.x += 0.6f;

		if(!isMovingUp && movement.y <= 0)
		{
			movement.y += 1.2f;
			if(movement.y > 0)
				movement.y = 0;
		}
		if(!isMovingDown && movement.y >= 0)
		{
			movement.y -= 1.2f;
			if(movement.y < 0)
				movement.y = 0;
		}
		if(!isMovingLeft && movement.x <= 0)
		{
			movement.x += 1.2f;
			if(movement.x > 0)
				movement.x = 0;
		}
		if(!isMovingRight && movement.x >= 0)
		{
			movement.x -= 1.2f;
			if(movement.x < 0)
				movement.x = 0;
		}

		if(movement.y >= 50)
			movement.y = 50;
		if(movement.y <= -50)
			movement.y = -50;
		if(movement.x >= 50)
			movement.x = 50;
		if(movement.x <= -50)
			movement.x = -50;

		if(left <= 0)
		{
			rect.setPosition(0, rect.getPosition().y);
			sprite.setPosition(0, rect.getPosition().y);
			if(movement.x < 0)
				movement.x = 0;
		}
		if(right >= 600 /* NOTE: This is window size! */)
		{
			rect.setPosition(600 - rect.getSize().x, rect.getPosition().y);
			sprite.setPosition(600 - rect.getSize().x, rect.getPosition().y);
			if(movement.x > 0)
				movement.x = 0;
		}
		if(top <= 0)
		{
			rect.setPosition(rect.getPosition().x, 0);
			sprite.setPosition(rect.getPosition().x, 0);
			if(movement.y < 0)
				movement.y = 0;
		}
		if(bottom >= 600 /*NOTE: This is window size! */)
		{
			rect.setPosition(rect.getPosition().x, 600 - rect.getSize().y);
			sprite.setPosition(rect.getPosition().x, 600 - rect.getSize().y);
			if(movement.y > 0)
				movement.y = 0;
		}

		rect.move(movement.x * deltaTime.asMilliseconds() * 0.005, movement.y * deltaTime.asMilliseconds() * 0.005);
		sprite.move(movement.x * deltaTime.asMilliseconds() * 0.005, movement.y * deltaTime.asMilliseconds() * 0.005);
	}

	void Draw(sf::RenderWindow &window)
	{
		window.draw(healthRectRed);
		window.draw(healthRectGreen);

		//window.draw(rect);
		window.draw(sprite);
	}
};

struct CoinSpawner
{
	std::vector<Coin> coins;
	sf::Texture coinTexture;

	CoinSpawner(sf::Texture &texture, bool f)
	{
		coins.clear();
		coinTexture = texture;
	}

	void Update(sf::Time deltaTime)
	{
		for(int i = 0; i < coins.size(); i++)
		{
			coins[i].Update(deltaTime);
			coins[i].Animate(deltaTime);
			if(coins[i].CoinDespawn())
				coins.erase(coins.begin() + i);
		}
	}

	void SpawnCoin(sf::RenderWindow &window)
	{
		int randomPosX = rand() % window.getSize().x;
		int randomPosY = rand() % window.getSize().y;

		Coin *coin = new Coin(coinTexture, sf::Vector2f(randomPosX, randomPosY));
		coins.push_back(*coin);
	}

	void Collision(Player &p)
	{
		for(int i = 0; i < coins.size(); i++)
		{
			if(coins[i].right < p.left || coins[i].left > p.right || coins[i].top > p.bottom || coins[i].bottom < p.top)
			{}

			else
			{
				coins.erase(coins.begin() + i);
				p.coins += 1;
				break;
			}
		}
	}

	void Draw(sf::RenderWindow &window)
	{
		for(int i = 0; i < coins.size(); i++)
		{
			//window.draw(coins[i].rect);
			window.draw(coins[i].sprite);
		}
	}

};

struct FrostSpawner
{
	std::vector<Frost> frosts;
	sf::Texture frostTexture;

	FrostSpawner(sf::Texture &texture, bool f)
	{
		frosts.clear();
		frostTexture = texture;
	}

	void Update(sf::Time deltaTime, sf::Time frostClock)
	{
		for(int i = 0; i < frosts.size(); i++)
		{
			frosts[i].Update(deltaTime, frostClock);
			frosts[i].Animate(deltaTime);

			if(frosts[i].time > 10)
				frosts.erase(frosts.begin() + i);

			else if(frosts[i].time > 6 && !frosts[i].stage2)
			{
				if(frosts[i].fakeFrost1)
				{
					frosts.erase(frosts.begin() + i);
					break;
				}

				frosts[i].rect.setPosition(frosts[i].rect.getPosition().x - 32, frosts[i].rect.getPosition().y - 32);
				frosts[i].sprite.setPosition(frosts[i].rect.getPosition().x, frosts[i].rect.getPosition().y);
				frosts[i].rect.setSize(sf::Vector2f(32*3, 32*3));

				Frost *frost1 = new Frost(frostTexture, sf::Vector2f(frosts[i].rect.getPosition().x + 32, frosts[i].rect.getPosition().y - 32), sf::Vector2f(32, 32));
				Frost *frost2 = new Frost(frostTexture, sf::Vector2f(frosts[i].rect.getPosition().x + 32*3, frosts[i].rect.getPosition().y + 32), sf::Vector2f(32, 32));
				Frost *frost3 = new Frost(frostTexture, sf::Vector2f(frosts[i].rect.getPosition().x + 32, frosts[i].rect.getPosition().y + 32*3), sf::Vector2f(32, 32));
				Frost *frost4 = new Frost(frostTexture, sf::Vector2f(frosts[i].rect.getPosition().x - 32, frosts[i].rect.getPosition().y + 32), sf::Vector2f(32, 32));

				frost1->time = frost2->time = frost3->time = frost4->time = frosts[i].time;
				frost1->stage1 = frost2->stage1 = frost3->stage1 = frost4->stage1 = true;
				frost1->stage2 = frost2->stage2 = frost3->stage2 = frost4->stage2 = true;
				frosts.push_back(*frost1); frosts.push_back(*frost2); frosts.push_back(*frost3); frosts.push_back(*frost4);

				frosts[i].stage2 = true;
			}

			else if(frosts[i].time > 3 && !frosts[i].stage1)
			{
				Frost *frost1 = new Frost(frostTexture, sf::Vector2f(frosts[i].rect.getPosition().x, frosts[i].rect.getPosition().y - 32), sf::Vector2f(32, 32));
				Frost *frost2 = new Frost(frostTexture, sf::Vector2f(frosts[i].rect.getPosition().x + 32, frosts[i].rect.getPosition().y), sf::Vector2f(32, 32));
				Frost *frost3 = new Frost(frostTexture, sf::Vector2f(frosts[i].rect.getPosition().x, frosts[i].rect.getPosition().y + 32), sf::Vector2f(32, 32));
				Frost *frost4 = new Frost(frostTexture, sf::Vector2f(frosts[i].rect.getPosition().x - 32, frosts[i].rect.getPosition().y), sf::Vector2f(32, 32));

				frost1->time = frost2->time = frost3->time = frost4->time = frosts[i].time;
				frost1->stage1 = frost2->stage1 = frost3->stage1 = frost4->stage1 = true;
				frost1->fakeFrost1 = frost2->fakeFrost1 = frost3->fakeFrost1 = frost4->fakeFrost1 = true;
				frosts.push_back(*frost1); frosts.push_back(*frost2); frosts.push_back(*frost3); frosts.push_back(*frost4);

				frosts[i].stage1 = true;
			}
		}
	}

	void SpawnFrost(sf::RenderWindow &window)
	{
		int randomPosX = rand() % window.getSize().x;
		int randomPosY = rand() % window.getSize().y;

		Frost *frost = new Frost(frostTexture, sf::Vector2f(randomPosX, randomPosY), sf::Vector2f(32, 32));
		frosts.push_back(*frost);
	}

	void Collision(Player &p, sf::Time deltaTime)
	{
		for(int i = 0; i < frosts.size(); i++)
		{
			if(frosts[i].right < p.left || frosts[i].left > p.right || frosts[i].top > p.bottom || frosts[i].bottom < p.top)
			{}

			else
			{
				p.health -= 1 * deltaTime.asMilliseconds() * 0.06;
				break;
			}
		}
	}

	void Draw(sf::RenderWindow &window)
	{
		for(int i = 0; i < frosts.size(); i++)
		{
			//window.draw(frosts[i].rect);
			window.draw(frosts[i].sprite);
		}
	}
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "Coin Collector Mini Game!");
	window.setFramerateLimit(300);
	sf::Clock clock;
	sf::Time deltaTime;

	sf::Font scoreFont; scoreFont.loadFromFile("Assets/scoreFont.otf");
	sf::Text scoreText; scoreText.setFont(scoreFont); scoreText.setCharacterSize(20);
	scoreText.setColor(sf::Color::White); scoreText.setPosition(window.getSize().x / 2, 0); scoreText.setString("0");

	sf::Texture backgroundTexture; backgroundTexture.loadFromFile("Assets/backgroundTexture.png"); backgroundTexture.setRepeated(true);
	sf::Sprite backgroundSprite; backgroundSprite.setTexture(backgroundTexture); backgroundSprite.setTextureRect(sf::IntRect(0, 0, 600, 600));

	sf::Texture playerTexture; playerTexture.loadFromFile("Assets/playerTexture.png");
	Player player(playerTexture, false);

	sf::Texture coinTexture; coinTexture.loadFromFile("Assets/coinTexture.png");
	CoinSpawner coinspawner(coinTexture, false);
	sf::Clock coinClock;

	sf::Texture frostTexture; frostTexture.loadFromFile("Assets/frostTexture.png");
	FrostSpawner frostspawner(frostTexture, false);
	sf::Clock frostClock;

	bool menuUp = true;
	sf::Texture menuTexture; menuTexture.loadFromFile("Assets/menuTexture.png");
	sf::Sprite menuSprite; menuSprite.setTexture(menuTexture);
	sf::Text menuInstructions; menuInstructions.setString("Press Escape To Play/Pause!"); menuInstructions.setPosition(75, 200); menuInstructions.setFont(scoreFont); menuInstructions.setCharacterSize(40);
	sf::Text menuScore; menuScore.setString("Highscore: 0"); menuScore.setPosition(175, 400); menuScore.setFont(scoreFont); menuScore.setCharacterSize(40);

	while(window.isOpen())
	{
		//TESTING TESTING
		if(player.health <= 0)
			window.close();

		scoreText.setString(std::to_string(player.coins));
		menuScore.setString("Highscore: " + std::to_string(player.coins));
		//TESTING TESTING

		deltaTime = clock.restart();

		sf::Event Event;
		while(window.pollEvent(Event))
		{
			switch(Event.type)
			{
			//handle keyboard events
			case sf::Event::KeyPressed:
				if(!menuUp)
					player.HandleMovementEvents(Event.key.code, true);
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					if(menuUp == true)
						menuUp = false;
					else if(menuUp == false)
						menuUp = true;
				}
				break;
			case sf::Event::KeyReleased:
				if(!menuUp)
					player.HandleMovementEvents(Event.key.code, false);
				break;

			//closed
			case sf::Event::Closed:
				window.close();
				break;
			}
		}

		if(!menuUp)
		{
			frostspawner.Update(deltaTime, frostClock.getElapsedTime());
			coinspawner.Update(deltaTime);
			player.Update();

			player.Animate(deltaTime);

			if(coinClock.getElapsedTime().asSeconds() > 3)
			{
				coinspawner.SpawnCoin(window);
				coinClock.restart();
			}
			if(frostClock.getElapsedTime().asSeconds() > 2)
			{
				frostspawner.SpawnFrost(window);
				frostClock.restart();
			}

			frostspawner.Collision(player, deltaTime);
			coinspawner.Collision(player);
			player.Move(deltaTime);
		}

		window.clear();
		window.draw(backgroundSprite);
		frostspawner.Draw(window);
		coinspawner.Draw(window);
		player.Draw(window);
		window.draw(scoreText);

		if(menuUp)
		{
			window.draw(menuSprite);
			window.draw(menuInstructions);
			window.draw(menuScore);
		}

		window.display();
	}

	return 0;
}

