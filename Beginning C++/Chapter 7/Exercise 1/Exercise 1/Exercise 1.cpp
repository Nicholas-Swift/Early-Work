//Exercise 1
//Write a program with a pointer to a pointer to a string object. Use the pointer to the pointer to call the size()
//member function of the string object.

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	cout<<"Creating string, pointer to string, and pointer to pointer to string.\n\n";
	string str = "this is the string";
	string* pStr = &str;
	string* ptrToPStr = pStr;

	cout<<"String: "<<str<<"\n";
	cout<<"Pointer to string: "<<*pStr<<"\n";
	cout<<"Pointer to pointer to string: "<<*ptrToPStr<<"\n";
	cout<<"Pointer to pointer to string size: "<<(*ptrToPStr).size()<<"\n\n";

	cout<<"Creating string2, changing pointer to point to string2, and leaving pointer to pointer to string.\n\n";
	string str2 = "this is a new string";
	pStr = &str2;

	cout<<"String: "<<str<<"\n";
	cout<<"String2: "<<str2<<"\n";
	cout<<"Pointer to string: "<<*pStr<<"\n";
	cout<<"Pointer to pointer to string: "<<*ptrToPStr<<"\n";
	cout<<"Pointer to pointer to string size: "<<(*ptrToPStr).size()<<"\n\n";

	return 0;
}