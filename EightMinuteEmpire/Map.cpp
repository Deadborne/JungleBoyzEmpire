#pragma once
#include "stdafx.h"
#include "Map.h"
#include <iostream>
#include <string>

using namespace std;
int number;
Map::Map(int num) {
	number = num;
}
int Map::getNum()
{
	cout << "Calling from map test! \n Hit 'Enter' to close the console\n";
	string rofl;
	getline(cin, rofl);
	return number;
};


