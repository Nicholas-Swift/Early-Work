//Guess My Number
//The classic number guessing game
//Made this by only looking at the example the book gave. Didn't look at the actual code at all.

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
	cout<<"\tWelcome to Guess My Number\n\n";

	srand(static_cast<unsigned int>(time(0)));
	int myNumber = (rand()%100)+1;
	int myGuess;
	int numberGuesses = 0;

	do
	{
		cout<<"Enter a guess: ";
		cin>>myGuess;

		if(myGuess > myNumber)
		{
			cout<<"Too high!\n\n";
		}

		else if(myGuess < myNumber)
		{
			cout<<"Too low!\n\n";
		}

		else
			continue;

		++numberGuesses;
	}while(myGuess != myNumber);

	cout<<"\nThat's it! You got it in "<<numberGuesses+1<<" guesses!\n\n";

	return 0;
}