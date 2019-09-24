// EightMinuteEmpire.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include<iostream>
using namespace std;

int main()
{
	cout << "Hello World! What is your name? \n";
	string name;
	getline(cin, name);
	cout << "Hello " << name << "!\n";
	cout << "Please press enter to close the console :D";
	getline(cin, name);
	return 0;
}
