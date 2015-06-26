// Tutorial 25
// Packets

#include "stdafx.h"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

int main()
{
	sf::IpAddress ip;
	std::cout<<sf::IpAddress::getLocalAddress()<<std::endl;
	std::cin>>ip;

	sf::TcpSocket socket;
	char connectionType;

	std::cout<<"Enter 's' for server, 'c' for client: ";
	std::cin>>connectionType;

	if(connectionType == 's')
	{
		sf::TcpListener listener;
		listener.listen(2000);
		listener.accept(socket);
	}
	else
		socket.connect(ip, 2000);

	sf::RectangleShape rect1, rect2;

	rect1.setSize(sf::Vector2f(20, 20));
	rect1.setFillColor(sf::Color::Red);

	rect2.setSize(sf::Vector2f(20, 20));
	rect2.setFillColor(sf::Color::Blue);

	sf::RenderWindow Window(sf::VideoMode(800, 600, 32), "Packets");

	sf::Vector2f prevPosition, p2Position;

	socket.setBlocking(false);

	bool Update = false;

	while(Window.isOpen())
	{
		sf::Event Event;
		while(Window.pollEvent(Event))
		{
			if(Event.type == sf::Event::Closed || Event.key.code == sf::Keyboard::Escape)
				Window.close();
			else if(Event.type == sf::Event::GainedFocus)
				Update = true;
			else if(Event.type == sf::Event::LostFocus)
				Update = false;
		}

		prevPosition = rect1.getPosition();

		if(Update)
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				rect1.move(0.5f, 0.0f);
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				rect1.move(-0.5f, 0.0f);
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				rect1.move(0.0f, -0.5f);
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				rect1.move(0.0f, 0.5f);
		}

		sf::Packet packet;

		if(prevPosition != rect1.getPosition())
		{
			packet<<rect1.getPosition().x<<rect1.getPosition().y;
			socket.send(packet);
		}

		socket.receive(packet);
		if(packet>>p2Position.x>>p2Position.y)
		{
			rect2.setPosition(p2Position);
		}

		Window.draw(rect1);
		Window.draw(rect2);

		Window.display();
		Window.clear();
	}

	return 0;
}

