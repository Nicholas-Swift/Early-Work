//Exercise 1
//Write a program using vectors and iterators that allows a user to maintain a list of his or her favorite games.
//The program should all the user to list all game titles, add a game title, and remove a game title.

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	//the instructions and setup
	cout<<"Commands:	Add    - Lets you add another title.\n";
	cout<<"		Remove - Lets you remove a title.\n";
	cout<<"		Quit   - Quits the program.\n";
	cout<<"		(use underlines instead of spaces\n";

	vector<string> favGames;
	vector<string>::const_iterator iter;
	string whatToDo;
	string addRemove;

	//main loop
	while(1)
	{
		cout<<"\nAdd, remove, or quit. Up to you: ";
		cin>>whatToDo;
		transform(whatToDo.begin(), whatToDo.end(), whatToDo.begin(), toupper); //changed whatToDo to capitols

		if (whatToDo == "ADD")
		{
			cout<<"\nWhat you would like to add: ";
			cin>>addRemove;
			transform(addRemove.begin(), addRemove.end(), addRemove.begin(), toupper); //changed addRemove to capitols

			favGames.push_back(addRemove);
			cout<<"\nList: \n";
			for (iter = favGames.begin(); iter != favGames.end(); ++iter)
			{
				cout<<*iter<<endl;
			}
		}

		else if (whatToDo == "REMOVE")
		{
			cout<<"\nWhat you would like to remove: ";
			cin>>addRemove;
			transform(addRemove.begin(), addRemove.end(), addRemove.begin(), toupper); //changed addRemove to capitols

			iter = find(favGames.begin(), favGames.end(), addRemove);
			if (iter != favGames.end())
			{
					favGames.erase((favGames.begin() + (iter - favGames.begin()) ));
					cout<<"\nList:\n";
					for (iter = favGames.begin(); iter != favGames.end(); ++iter)
					{
						cout<<*iter<<endl;
					}
			}

			else
			{
				cout<<"\nSorry, couldn't find the game to remove!\n";
			}
			
		}

		else if (whatToDo == "QUIT")
		{
			break;
		}

		else
		{
			cout<<"\nAlright, so what you just typed wasn't 'add', 'remove', or 'quit'.\n";
			cout<<"Try again please.\n";
		}
	}

	cout<<"\nGood bye.\n"<<endl;


	return 0;
}