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
	bool hasStarter = false; //a map is invalid if it has no starting point

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
		int* connectingContinent;
		bool* starter = false;
		bool* connectsAcrossSea = false;

		countryNumber = new int;
		continentNumber = new int;
		starter = new bool;
		connectingContinent = new int;
		connectsAcrossSea = new bool;


		std::string allAdjacent;

		//grabs first number (country number)
		std::size_t pos = line.find(":");
		std::istringstream iss(line.substr(0, pos));
		iss >> *countryNumber;
		if (*countryNumber == -1) { 
			cout << "Found a territory with no number. Map not created." << endl;
			return NULL;
		}
		//check if that's the starting country. If the find returns npos, that would mean nothing was found.
		if (line.find("S") != std::string::npos) {
			hasStarter = true;
			*starter = true;
		}
		//check if the country connects to a different continent. If the find returns npos, that would mean nothing was found.
		if (line.find("C") != std::string::npos) {
			std::size_t posC = line.find("C");
			std::istringstream issC(line.substr(posC + 1, posC+2));
			issC >> *connectingContinent;
			*connectsAcrossSea = true;
			issC.clear();
		}
		iss.clear();

		//grab the continent number
		std::size_t pos2 = line.find("-");
		std::istringstream iss2(line.substr(pos+1, pos2));
		iss2 >> *continentNumber;
		if (*continentNumber == -1) { //check if there is a map without a continent.
			cout << "Found a territory with no continent. Map not created." << endl;
			return NULL;
		}
		iss2.clear();
		
		//grab adjacencies
		std::istringstream iss3(line.substr(pos2 + 1));
		iss3 >> allAdjacent;
		temp = split(allAdjacent, ",");

		if (temp.size() == 0) { //make sure there is no country with no adjacencies.
			cout << "Found a country with no adjacencies. This is invalid. Map not created." << endl;
			return NULL;
		}

		//store all adjacencies in map
		for (int i = 0; i < temp.size(); i++) {
			
			int box;
			std::istringstream intvertex(temp.at(i));
			intvertex >> box;
			try {
				add_edge(*countryNumber, box, GameMap);
			}
			catch (const std::exception&) {
				cout << "Invalid country identifier. Map not created" << endl; //this would happen if a country has no identifier
				return NULL;
			}
		}

		//store continent adjacencies in subgraph, if continents were found to be connected
		if (*connectsAcrossSea == true) {
			add_edge(*continentNumber, *connectingContinent, ContinentMap);
		}

		//create a country, store it in the vector of countries
		Country c = Country(countryNumber, continentNumber, starter);
		mappedCountries.push_back(c);
		iss3.clear();
	}

	infile.close();
	if (hasStarter == true) { //checks if the map also has a starting point. Won't create a map without one.
		//output the map
		cout << "This is your current game map!" << endl;
		write_graphviz(cout, GameMap);
		//output continent subgraph
		cout << "\nThis is continent subgraph!" << endl;
		write_graphviz(cout, ContinentMap);
		return GameMap;
	}
	else {
		cout << "This map has no starting point, or is otherwise completely invalid. Map not created." << endl;
		return NULL;
	}
		
}


//Map has a vector of country objects
std::vector<Country> Map::getCountries() {
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

void Map::showEverything() {

	for (std::vector<int>::size_type i = 0; i < mappedCountries.size(); i++) {
		cout << "Region " << mappedCountries[i].getCountryId() << " [Continent " << mappedCountries[i].getContinentId() << "] Armies: [";
		mappedCountries[i].printArmies();
		cout << "] Cities: [";
		for (int i = 0; i < 5; i++) {
			cout << *mappedCountries[i].getCities().at(i) << " ";
		}
		cout << "] Connected to: ";
		mappedCountries[i].showAdjacencies(GameMap);
		cout << "" << endl;
	}

}
