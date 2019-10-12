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

	//Reads a map.
	//M1, M5, M6, M8, M9, M10, M14 are all valid maps.
	//To see maps with errors, try entering: NoAdjacent, NoContinent, NoCountry, NoStarter, Crap.

	Map m;
	cout << "Alright! what map do you want to read? (Proper format is M#)" << endl;
	getline(cin, in);
	Graph GameMap = (m.ReadMap(in));

	//Empties the map of all pointers.

	//Here is something we can use to test whether territory ownership is working:
	int ctry = 1;
	int ctnt = 2;
	bool start = false;

	vector <int> armies = { 1,7,3,2,5 }; //This means: Player 1 has 1 army, Player 2 has 7 armies, Player 3 has 3 armies, Player 4 has 2 Armies, Player 5 has 5 armies.
	Country c = Country(&ctry, &ctnt, armies);

	c.setOwner(); //calculates who the owner is
	cout << "The owner of this country is player " << c.getOwner() << endl;


	m.purge();
	
	return 0;
}