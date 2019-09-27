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
	Country c = Country(12);
	c.getNum();
	
    return 0;
}

