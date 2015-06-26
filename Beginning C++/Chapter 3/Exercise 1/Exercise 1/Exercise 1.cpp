//Exercise 1
//Improve the Word Jumble game by adding a scoring system. make the point value for a word based on its length. Deduct points
//if the player asks for a hint.

#include "stdafx.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
	cout<<"\t\t\tWelcome to Word Jumble!\n\n";
	cout<<"Unscramble the letters to make a word (No capital letters).\n";
	cout<<"Enter 'hint' for a hint.\n";
	cout<<"Every wrong answer is -5 points, while every correct answer is 1 point for each letter.\n";
	cout<<"A hint is -2 points.\n";
	cout<<"Enter 'quit' to quit the game.\n\n";

	enum fields {WORD, HINT, NUM_FIELDS};
	const int NUM_WORDS = 5;
	const string WORDS[NUM_WORDS][NUM_FIELDS] =
	{
		{"wall", "Do you feel you're banging your head against something?"},
		{"glasses", "These might help you see the answer."},
		{"labored", "Going slowly, is it?"},
		{"persistent", "Keep at it."},
		{"jumble", "It's what the game is all about."}
	};

	string guess;
	int score = 0;

	while(guess != "quit")
	{
		srand(static_cast<unsigned int>(time(0)));
		int choice = (rand() % NUM_WORDS);
		string theWord = WORDS[choice][WORD]; //Word to guess
		string theHint = WORDS[choice][HINT]; //Hint for word

		string jumble = theWord; //Jumbled version of word
		int length = jumble.size();
		for (int i = 0; i < length; ++i)
		{
			int index1 = (rand() % length);
			int index2 = (rand() % length);
			char temp = jumble[index1];
			jumble[index1] = jumble[index2];
			jumble[index2] = temp;
		}

		cout<<"The jumble is: "<<jumble;
		cout<<"\n\nYour guess: ";
		cin>>guess;

		while(guess != theWord)
		{
			if (guess == "hint")
			{
				cout<<theHint;
				score -= 2;
			}

			else if(guess == "quit")
			{
				break;
			}

			else
			{
				cout<<"Sorry that's not it.";
				score -= 5;
			}

			cout<<"\n\nYour guess: ";
			cin>>guess;
		}

		if (guess == theWord)
		{
			cout<<"\nThat's it! You guessed it!\n";
			int right = theWord.size();
			score += right;
		}
	}

	cout<<"\nThanks for playing.\n";
	cout<<"Your score is: "<<score<<"\n\n";

	return 0;
}