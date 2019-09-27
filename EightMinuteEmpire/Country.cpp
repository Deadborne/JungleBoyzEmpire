#pragma once
#include "stdafx.h"
#include "Country.h"
#include <iostream>
#include <string>

using namespace std;
int countryId;
Country::Country(int num) {
	countryId = num;
}
int Country::getNum()
{
	cout << "Calling from Country test! \n Hit 'Enter' to close the console\n";
	string rofl;
	getline(cin, rofl);
	return countryId;
};



