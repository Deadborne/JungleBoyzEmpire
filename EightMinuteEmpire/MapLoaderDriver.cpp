// EightMinuteEmpire.cpp : Defines the entry point for the console application.
//
#pragma once

#include "stdafx.h"
#include <string>
#include <iostream>
#include "Map.h"
#include "Country.h"
#include "Player.h" 
#include <ostream>
using namespace std;
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
using namespace boost;


int main()
{

	typedef boost::adjacency_list<listS, vecS, undirectedS> Graph;
	std::string in;
	/*
	//Reads a map.
	//M1, M5, M6, M8, M9, M10, M14 are all valid maps.
	//To see maps with errors, try entering: NoAdjacent, NoContinent, NoCountry, NoStarter, Crap.

	Map m;
	cout << "Alright! what map do you want to read? (Proper format is M#)" << endl;
	getline(cin, in);
	Graph GameMap = (m.ReadMap(in));

	//Empties the map of all pointers.
	m.purge();
	*/

	///This is the Map section of the driver.

	//Generating a map, going through several test cases of invalid maps.
	Map m;
	cout << "Are you ready to go on a magical journey? Along the way, you can press Enter to see the next part." << endl;
	cout << "First, let's generate a valid map! It looks like this:" << endl;
	getline(cin, in);
	Graph GameMap = (m.ReadMap("M6"));
	cout << "Next, this is what happens when a map has no adjacencies." << endl;
	getline(cin, in);
	m.ReadMap("NoAdjacent");
	cout << "Next, this is what happens when there's a country with no continent." << endl;
	getline(cin, in);
	m.ReadMap("NoContinent");
	cout << "Next, this is what happens when there's a country with no ID" << endl;
	getline(cin, in);
	m.ReadMap("NoCountry");
	cout << "Next, this is what happens when there's no defined starting point on the map." << endl;
	getline(cin, in);
	m.ReadMap("NoStarter");
	cout << "";
	cout << "Testing territory-ownership function:" << endl;
	getline(cin, in);

	//Testing territory-based stuff:
	int ctry = 1;
	int ctnt = 2;
	bool start = false;

	int p1Armies = 1;
	int p2Armies = 7;
	int p3Armies = 3;
	int p4Armies = 2;
	int p5Armies = 5;

	//This means: Player 1 has 1 army, Player 2 has 7 armies, Player 3 has 3 armies, Player 4 has 2 Armies, Player 5 has 5 armies.
	vector <int*> armies = { &p1Armies, &p2Armies, &p3Armies, &p4Armies, &p5Armies }; 
	Country c = Country(&ctry, &ctnt, armies);

	c.setOwner(); //calculates who the owner is
	cout << "The owner of this country is player " << c.getOwner() << endl;

	return 0;
}