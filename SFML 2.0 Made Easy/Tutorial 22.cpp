// Tutorial 22
// Sockets(TCP)

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
	}
	else if(connectionType == 'c')
	{
		socket.connect(ip, 2000);
		text += "Client.\n";
	}

	socket.send(text.c_str(), text.length());

	socket.receive(buffer, sizeof(buffer), recieved);
	//std::cout<<buffer<<std::endl;

	int g;
	std::cin>>g;

	return 0;
}

