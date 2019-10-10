#pragma once
#include "stdafx.h"
#include "Map.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Country.h"
using namespace std;
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
using namespace boost;

//Hard code for the size, fixing later

static std::vector<Country> mappedCountries;

typedef boost::adjacency_list<listS, vecS, undirectedS> Graph;

Graph GameMap;
Graph ContinentMap;

Map::Map() {
	
}

//this method is used to split the strings during file I/O
vector<string> Map::split(string _stringToBeSplit, string _delimeter)
{
	std::vector<std::string> splittedString;
	int startIndex = 0;
	int  endIndex = 0;
	while ((endIndex = _stringToBeSplit.find(_delimeter, startIndex)) < _stringToBeSplit.size())
	{

		std::string val = _stringToBeSplit.substr(startIndex, endIndex - startIndex);
		splittedString.push_back(val);
		startIndex = endIndex + _delimeter.size();

	}
	if (startIndex < _stringToBeSplit.size())
	{
		std::string val = _stringToBeSplit.substr(startIndex);
		splittedString.push_back(val);
	}
	return splittedString;

}


Graph Map::ReadMap(string f)
{
	std::ifstream infile;
	infile.open("./Maps/" + f + ".txt");

	std::string str;

	if (!infile) {
		cout << "That file is not valid.\n";
	}

	vector<string> temp;

	while (std::getline(infile, str)) {
		
		std::string line; //the line we grabbed

		line = str;

		int* countryNumber;
		int* continentNumber;
		bool* starter = false;
		countryNumber = new int;
		continentNumber = new int;
		starter = new bool;

		
		std::string allAdjacent;
		
		//grabs first number (country number)
		std::size_t pos = line.find(":");
		std::istringstream iss(line.substr(0, pos));
		iss >> *countryNumber;
		if (line.find("S") != std::string::npos) {
			*starter = true;
		}
		iss.clear();

		//grab the continent number
		std::size_t pos2 = line.find("-");
		std::istringstream iss2(line.substr(pos+1, pos2));
		iss2 >> *continentNumber;
		iss2.clear();
		
		//grab adjacencies
		std::istringstream iss3(line.substr(pos2 + 1));
		iss3 >> allAdjacent;
		temp = split(allAdjacent, ",");

		//store all adjacencies in map
		for (int i = 0; i < temp.size(); i++) {
			
			int box;
			std::istringstream intvertex(temp.at(i));
			intvertex >> box;

			add_edge(*countryNumber, box, GameMap);	
		}

		//create a country, store it in the vector of countries
		Country c = Country(countryNumber, continentNumber, starter);
		mappedCountries.push_back(c);
		iss3.clear();
	}

	//output the map
	write_graphviz(cout, GameMap);
	infile.close();
	return GameMap;
}

Graph Map::ContinentMap(string f)
{
	std::ifstream infile;
	infile.open("./Maps/" + f + ".txt");

	std::string str;

	if (!infile) {
		cout << "That file is not valid.\n";
	}

	vector<string> temp;

	while (std::getline(infile, str)) {

		std::string line; //the line we grabbed

		line = str;
		int countryNumber;
		int continentNumber;
		bool starter = false;
		std::string allAdjacent;


	}

	//output the map
	write_graphviz(cout, GameMap);
	infile.close();
	return GameMap;
}

//Map has a vector of country objects
std::vector<Country> Map::getCountries() {
	for (int i = 0; i < mappedCountries.size(); i++) {
		cout << "Country ID: " << mappedCountries.at(i).getCountryId() << endl;
		cout << "Continent ID: " << mappedCountries.at(i).getContinentId() << endl;
	}
	string test = "";
	getline(cin, test);
	return mappedCountries;
}
//deletes the vector of countries and all its contents
void Map::purge() {

	for (int i = 0; i < mappedCountries.size(); i++) {
		mappedCountries.at(i).setContinentId(NULL);
		mappedCountries.at(i).setCountryId(NULL);
		mappedCountries.at(i).setStarterStatus(NULL);
	}
	
}


