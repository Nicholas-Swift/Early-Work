// Tutorial 26 (server)
// Socket Selectors

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

//server

int main()
{
	std::cout<<"Server Running"<<std::endl;

	sf::TcpListener listener;
	sf::SocketSelector selector;
	bool done = false;
	std::vector<sf::TcpSocket*> clients;

	listener.listen(2000);
	selector.add(listener);

	while(!done)
	{
		if(selector.wait())
		{
			if(selector.isReady(listener))
			{
				sf::TcpSocket *socket = new sf::TcpSocket;
				listener.accept(*socket);
				sf::Packet packet;
				std::string id;
				if(socket->receive(packet) == sf::Socket::Done)
					packet>>id;

				std::cout<<id<<" has connected to the server."<<std::endl;
				clients.push_back(socket);
				selector.add(*socket);
			}
			else
			{
				for(int i = 0; i < clients.size(); i++)
				{
					if(selector.isReady(*clients[i]))
					{
						sf::Packet packet, sendPacket;
						if(clients[i]->receive(packet) == sf::Socket::Done)
						{
							std::string text;
							packet>>text;
							sendPacket<<text;
							for(int j = 0; j < clients.size(); j++)
							{
								if(i != j)
									clients[j]->send(sendPacket);
							}
						}
					}
				}
			}
		}
	}

	for(std::vector<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); it++)
			delete *it;

	return 0;
}

