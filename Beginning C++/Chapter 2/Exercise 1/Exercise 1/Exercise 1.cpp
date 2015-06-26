//Exercise 1
//Rewrite the Menu Chooser program from this chapter using an enumeration to represent difficulty levels. The variable
//choice will still be of type int.

#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{
	cout<<"Difficulty Levels\n\n";
	cout<<"1 - Easy\n";
	cout<<"2 - Normal\n";
	cout<<"3 - Hard\n\n";

	enum difficulty{EASY = 1, NORMAL, HARD};
	difficulty easyDif = EASY;
	difficulty normalDif = NORMAL;
	difficulty hardDif = HARD;

	cout<<"Your choice: ";
	int num;
	cin>>num;

	switch (num)
	{
	case 1: cout<<"You picked Easy.\n";
		break;
	
	case 2: cout<<"You picked Normal.\n";
		break;

	case 3: cout<<"You picked Hard.\n";
		break; 

	default: cout<<"You made an illegal choice.\n";
		break;
	}
	
	return 0;
}