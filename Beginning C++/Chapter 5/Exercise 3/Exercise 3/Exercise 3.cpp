//Exercise 3
//Using default arguments, write a funtion that asks the user for a number and returns that number. The function
//should accept a string prompt from the calling code. If the caller doesn't supply a string prompt, the function
//should use a generic prompt. Next, using function overloading, write a function that achieves the same results.

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

void number(string enter = "WEFWEIOFJOWEJF");
void strin(string enter2 = "JFWOIEJFIOWJO!1!");

int ovrload(int enter);
string ovrload(string enter);

int main()
{
	cout<<"\nDefault arguments- \n";

	number("Enter a number: ");
	strin("Enter a string: ");

	cout<<"\n\nOverloaded function- \n";

	cout<<"Enter a number: ";
	int num;
	cin>>num;
	cout<<ovrload(num)<<endl;

	cout<<"Enter a string: ";
	string str;
	cin>>str;
	cout<<ovrload(str)<<endl;

	return 0;
}

void number(string enter)
{
	cout<<enter;
	int num;
	cin>>num;
	cout<<num<<endl;
}

void strin(string enter2)
{
	cout<<enter2;
	string str;
	cin>>str;
	cout<<str<<endl;
}

int ovrload(int enter)
{
	return (enter);
}

string ovrload(string enter)
{
	return (enter);
}