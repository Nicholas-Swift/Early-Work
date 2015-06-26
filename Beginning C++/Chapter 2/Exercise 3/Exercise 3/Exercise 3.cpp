//Exercise 3
//Write a new version of the Guess My Number program in which the player and the computer switch roles. That is, the player
//picks a number and the computer must guess what it is

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
using namespace std;

int main()
{
	cout<<"\tWelcome to Guess my Number\n\n";

	int myNumber;
	while(true)
	{
		cout<<"Pick a number, between 1 and 100, for the computer to guess: ";
		cin>>myNumber;

		if(myNumber >= 1 && myNumber <= 100)
		{
			break;
		}

		cout<<"The number wasn't between 1 and 100... Try again.\n\n";
	}



	srand(static_cast<unsigned int>(time(0)));
	int computerNumber = (rand()%100)+1;
	int lowestNumber = 0;
	int highestNumber = 100;
	int tries = 0;

	while(computerNumber != myNumber)
	{
		if(computerNumber < myNumber)
		{
			lowestNumber = computerNumber;
			if(computerNumber + 10 < highestNumber)
			{
			    computerNumber = computerNumber + 10;
			}
			else
			{
			    ++computerNumber;
			}
		}

		else
		{
			highestNumber = computerNumber;
			if(computerNumber - lowestNumber > 10)
			{
			    computerNumber = computerNumber - 10;
			}
			else
			{
			    --computerNumber;
			}
		}

		cout<<"\nThe computer Guesses: "<<computerNumber<<endl;

		++tries;
		Sleep(500);
	}

	cout<<"\nThe computer guessed your number in only "<<tries<<" tries!\n\n";

	return 0;
}