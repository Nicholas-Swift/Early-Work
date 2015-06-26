//Exercise 3
//Write a program that gets three game scores from the user and displays the average.

#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{
	//Purposely set it as an integer, because you never end up with decimal scores
	int gameScore1, gameScore2, gameScore3;
	cout<<"Enter your three game scores.\n\n";

	cout<<"Game score 1: ";
	cin>>gameScore1;
	cout<<"Game score 2: ";
	cin>>gameScore2;
	cout<<"Game score 3: ";
	cin>>gameScore3;

	//Set up the last one to show a decimal, though, so you get a correct average.
	cout<<"\n\nYour average game score is "<<((gameScore1+gameScore2+gameScore3)/3.0)<<".\n\n";

	return 0;
}

