// EightMinuteEmpire.cpp : Defines the entry point for the console application.
//
#pragma once

#include "stdafx.h"
#include <string>
#include<iostream>
#include "Map.h"
#include "Country.h"

#include <boost/graph/adjacency_list.hpp>

using namespace std;

int main()
{
	cout << "Hello World! What is your name? \n";
	string name;
	name = "rofl";
	getline(cin, name);
	cout << "Hello " << name << "!\n";
	cout << "Please press enter to close the console :D";
	getline(cin, name);
	Map m = Map(12);
	m.getNum();
	Country c = Country(12, 1);
	c.getId();
	
	Country d = Country(1, 1);
	d.setOwner(1);

	d.buildCity(3);



	cout << "The owner of country 1 is " << d.getOwner();
	cout << "\nDoes player 4 have a city in this country?: " << d.hasCity(3);
	cout << "\nDoes player 2 have a city in this country?: " << d.hasCity(1);
	getline(cin, name);



    return 0;
}

