//Exercise 2
//Rewrite the Hangman game from chapter 4 using functions. Include a function to get the player's guess and
//another function to determine whether the player's guess in in the secret word.

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

char getGuess(); char guess;//gets your guess
void checkGuess(); //checks your guess

int main()
{
	cout<<"Welcome to Hangman. Good luck!\n\n";
	checkGuess();

	return 0;
}

char getGuess()
{
	cout<<"\nEnter your guess: ";
	cin>>guess;
	guess = toupper(guess);
	return (guess);
}

void checkGuess()
{
	//setup
	const int MAX_WRONG = 8; //maximum number of incorrect guesses allowed

	vector<string> words; //collection of possible words to guess
	words.push_back("GUESS");
	words.push_back("HANGMAN");
	words.push_back("DIFFICULT");

	srand(static_cast<unsigned int>(time(0)));
	random_shuffle(words.begin(), words.end());
	const string THE_WORD = words[0];			//word to guess
	int wrong = 0;								//number of incorrect guesses
	string soFar(THE_WORD.size(), '-');			//word guessed so far
	string used = "";							//letters already guessed


	while ((wrong < MAX_WRONG) && (soFar != THE_WORD))
	{
		getGuess();
		while (used.find(guess) != string::npos)
		{
			cout<<"\nYou've already guessed "<<guess<<endl;
			cout<<"Enter your guess: ";
			cin>>guess;
			guess = toupper(guess);
		}

		used += guess;

		if (THE_WORD.find(guess) != string::npos)
		{
			cout<<"That's right! "<<guess<<" is in the word.\n";
	
			//update soFar to include newly guessed letter
			for (int i = 0; i < THE_WORD.length(); ++i)
			{
				if (THE_WORD[i] == guess)
				{
					soFar[i] = guess;
				}
			}
		}
		else
		{
			cout<<"Sorry, "<<guess<<" isn't in the word.\n";
			++wrong;
		}

		cout<<"\n\nYou have "<<(MAX_WRONG - wrong);
		cout<<" incorrect guesses left.\n";
		cout<<"\nYou've used the following letters:\n"<<used<<endl;
		cout<<"\nSo far, the word is:\n"<<soFar<<endl;
	}

	//shut down
	if (wrong == MAX_WRONG)
	{
		cout<<"\nYou've been hanged!";
	}

	else
	{
		cout<<"\nYou guessed it!";
	}

	cout<<"\nThe word was "<<THE_WORD<<"\n\n";
}