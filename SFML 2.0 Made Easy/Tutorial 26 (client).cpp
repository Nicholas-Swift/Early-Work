// Tutorial 26 (client)
// Socket Selector

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

//client

int main()
{
	sf::IpAddress ip = sf::IpAddress("192.168.1.5");
	std::cout<<ip<<std::endl;
	std::string publicIp = ip.toString();
	sf::TcpSocket socket;
	bool done = false;
	std::string id;
	std::string text = "";

	std::cout<<"\nEnter online id: "<<std::endl;
	std::cin>>id;

	ip = sf::IpAddress(publicIp);

	socket.connect(ip, 2000);

	sf::RenderWindow Window(sf::VideoMode(800, 600), "Chat");
	std::vector<sf::Text> chat;

	sf::Packet packet;
	packet<<id;
	socket.send(packet);
	socket.setBlocking(false);

	Window.setTitle(id);

	sf::Font font;
	font.loadFromFile("arial.ttf");

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
			case sf::Event::KeyPressed:
				if(Event.key.code == sf::Keyboard::Escape)
					Window.close();
				else if(Event.key.code == sf::Keyboard::Return)
				{
					sf::Packet packet;
					packet<<id + ": " + text;
					socket.send(packet);
					sf::Text displayText(text, font, 20);
					displayText.setColor(sf::Color::Green);
					chat.push_back(displayText);
					text = "";
				}
				break;
			case sf::Event::TextEntered:
				text += Event.text.unicode;
				break;
			}

			sf::Packet packet;
			socket.receive(packet);

			std::string tempText;
			if(packet >> tempText)
			{
				sf::Text displayText(tempText, font, 20);
				displayText.setColor(sf::Color::Blue);
				chat.push_back(displayText);
			}

			int i = 0;
			for(i; i < chat.size(); i++)
			{
				chat[i].setPosition(0, i * 20);
				Window.draw(chat[i]);
			}

			sf::Text drawText(text, font, 20);
			drawText.setColor(sf::Color::Red);
			drawText.setPosition(0, i * 20);
			Window.draw(drawText);

			Window.display();
			Window.clear();
		}
	}

	return 0;
}

