// Tutorial 24
// Sockets(UDP)

#include "stdafx.h"
#include <iostream>
#include <SFML/Network.hpp>
#include <string>
#include <conio.h>

int main()
{
	sf::IpAddress ip = sf::IpAddress::getLocalAddress();

	sf::UdpSocket socket;
	char connectionType, mode;
	char buffer[2000];
	std::size_t recieved;
	std::map<unsigned short, sf::IpAddress> computerID;
	std::string text = "Connected to: ";

	std::cout<<ip<<std::endl;

	std::cout<<"Enter 's' for server, 'c' for client: ";
	std::cin>>connectionType;

	unsigned short port;

	std::cout<<"\nSet port number: ";
	std::cin>>port;

	socket.bind(port);

	//socket.setBlocking(false);

	if(connectionType == 's')
	{
		char answer = 'b';
		while(answer != 'a')
		{
			sf::IpAddress rIp;
			unsigned short port;
			socket.receive(buffer, sizeof(buffer), recieved, rIp, port);
			if(recieved > 0)
				computerID[port] = rIp;
			std::cin>>answer;
		}
	}
	else if(connectionType == 'c')
	{
		std::string sIp;
		std::cout<<"Enter server ip: ";
		char c;
		while(true)
		{
			c = (char)_getch();
			if(c == 13)
				break;
			sIp += c;
			std::cout<<"*";
		}
		sf::IpAddress sendIP(sIp);
		socket.send(text.c_str(), text.length(), sendIP, 2000);
	}

	bool done = false;

	while(!done)
	{
		if(connectionType == 's')
		{
			std::getline(std::cin, text);
			std::map<unsigned short, sf::IpAddress>::iterator tempIterator;
			for(tempIterator = computerID.begin(); tempIterator != computerID.end(); tempIterator++)
				socket.send(text.c_str(), text.length(), tempIterator->second, tempIterator->first);
		}
		else if(connectionType == 'c')
		{
			sf::IpAddress tempIp;
			unsigned short tempPort;
			socket.receive(buffer, sizeof(buffer), recieved, tempIp, tempPort);
			if(recieved > 0)
				std::cout<<"Recieved: "<<buffer<<std::endl; //for some reason i get a bunch of [|[|[| after the text.
		}
	}

	return 0;
}

