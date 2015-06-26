// Tutorial 23
// Sockets(TCP) continued

#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <string>

int main()
{
	sf::IpAddress ip = sf::IpAddress::getLocalAddress();
	sf::TcpSocket socket;
	char connectionType, mode;
	std::string text = "Connected to: ";
	char buffer[2000];
	std::size_t recieved;

	std::cout<<"Enter 's' for server, enter 'c' for client: "<<std::endl;
	std::cin>>connectionType;

	if(connectionType == 's')
	{
		sf::TcpListener listener;
		listener.listen(2000);
		listener.accept(socket);

		text += "Server.\n";
		mode = 's';
	}
	else if(connectionType == 'c')
	{
		socket.connect(ip, 2000);
		text += "Client.\n";
		mode = 'r';
	}

	socket.send(text.c_str(), text.length()+1);

	socket.receive(buffer, sizeof(buffer), recieved);
	std::cout<<buffer<<std::endl;

	bool done = false;
	while(!done)
	{
		if(mode == 's')
		{
			std::cout<<"Sent: ";
			std::getline(std::cin, text);
			socket.send(text.c_str(), text.length()+1);
			mode = 'r';
		}
		else if(mode == 'r')
		{
			socket.receive(buffer, sizeof(buffer), recieved);
			if(recieved > 0)
			{
				std::cout<<"\nRecieved: "<<buffer<<std::endl;
				mode = 's';
			}
		}
	}

	int g;
	std::cin>>g;

	return 0;
}