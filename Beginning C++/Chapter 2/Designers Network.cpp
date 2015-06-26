//Designers Network
//Demonstrates logical operators

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	string username;
	string password;
	bool success;

	cout<<"\tGame Designer's Network\n";

	do
	{
		cout<<"\nUsername: ";
		cin>>username;

		cout<<"Password: ";
		cin>>password;

		if(username == "T.Thongtan" && password == "Broski")
		{
			cout<<"\nSup, broski.\n\n";
			success = true;
		}

		else if(username == "C.Zitnik" && password == "Sir")
		{
			cout<<"\nGood day, sir.\n\n";
			success = true;
		}

		else if(username == "M.Hinsvark" && password == "Narwhal")
		{
			cout<<"\nSup my nugget.\n\n";
			success = true;
		}

		else if(username == "guest" || password == "guest")
		{
			cout<<"\nWelcome, guest.\n\n";
			success = true;
		}

		else
		{
			cout<<"\nYour login failed.";
			success = false;
		}
	}while(!success);

	return 0;
}