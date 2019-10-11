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
	//To see maps with errors, try entering: NoAdjacent, NoContinent, NoCountry, NoStarter.
	Map m;
	cout << "Alright! what map do you want to read? (Proper format is M#)" << endl;
	getline(cin, in);
	Graph GameMap = (m.ReadMap(in));

	//Empties the map of all pointers.
	m.purge();

	return 0;
}