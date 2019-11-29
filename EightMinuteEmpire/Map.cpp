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
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/connected_components.hpp>
using namespace boost;

//Hard code for the size, fixing later

static std::vector<Country> mappedCountries;

typedef boost::adjacency_list<listS, vecS, undirectedS> Graph;

Graph GameMap;
Graph ContinentMap;

Map::Map() {
	
}

//Initializing static data member
Map* Map::mapInstance = 0;

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

	while (1){

		GameMap = NULL;

		std::ifstream infile;
		infile.open("./Maps/" + f + ".txt");
		std::string str;

		while (!infile) {
			cout << "That file is not valid.\n";
			cout << "Select the Map to load (Proper format is M#)" << endl;
			getline(cin, f);
			infile.open("./Maps/" + f + ".txt");
			//cin.clear();
			//cin.ignore();
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
			starter = new bool(false);
			connectingContinent = new int;
			connectsAcrossSea = new bool;

			//mappedCountries.push_back(c0);
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
				//cout << *countryNumber << " is starter" << endl;
				hasStarter = true;
				*starter = true;
				startingCountry = countryNumber; //stores this value
			}
			//check if the country connects to a different continent. If the find returns npos, that would mean nothing was found.
			if (line.find("C") != std::string::npos) {
				std::size_t posC = line.find("C");
				std::istringstream issC(line.substr(posC + 1, posC + 2));
				issC >> *connectingContinent;
				*connectsAcrossSea = true;
				issC.clear();
			}
			iss.clear();

			//grab the continent number
			std::size_t pos2 = line.find("-");
			std::istringstream iss2(line.substr(pos + 1, pos2));
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
			// cout << "Pushed Ctry " << *countryNumber << " ctnt " << *continentNumber << "Starter: " << *starter << " to map." << endl; //uncomment to see what goes in map
			mappedCountries.push_back(c);

			iss3.clear();
		}

		infile.close();
		//check if the graph is connected

		std::vector<int> component(num_vertices(GameMap));
		int connectedComponents = connected_components(GameMap, &component[0]);
		bool connected = false;

		if (connectedComponents == 2) {
			connected = true;
		}

		if (hasStarter && connected) { //checks if the map also has a starting point. Won't create a map without one.
			//output the map
			cout << "Map loaded!\n" << endl;

			return GameMap;
		}
		else if (!connected) {
			cout << "This map is not connected. Map not created." << endl;
			cout << "Select the Map to load (Proper format is M#)" << endl;
			getline(cin, f);
		}
		else {
			cout << "This map has no starting point, or is otherwise completely invalid. Map not created." << endl;
			cout << "Select the Map to load (Proper format is M#)" << endl;
			getline(cin, f);
		}
	}
}

//Map has a vector of country objects
std::vector<Country> Map::getCountries() {
	return mappedCountries;
}

//returns the starting country
Country Map::getStartingCountry() {

	return mappedCountries.at(*startingCountry - 1);
}

//gives whatever country in the map that is asked
Country Map::giveMeCountry(int id) {
	return mappedCountries[id-1];
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
		cout << "Region\t" << mappedCountries[i].getCountryId() << "\t [Continent " << mappedCountries[i].getContinentId() << "] Armies: [";
		mappedCountries[i].printArmies();
		cout << "] Cities: [";
		for (int j = 0; j < 5; j++) {
			cout << *mappedCountries[i].getCities().at(j) << " ";
		}
		cout << "] Connected to: ";
		mappedCountries[i].showAdjacencies(GameMap);
		cout << "" << endl;
	}

}

vector<int> Map::getContinents() {

	//Intermediary vector
	vector<int> c;
	//What we will return
	vector<int> continents;

	//Get all the countries
	vector<Country> countries = getCountries();

	//Get all the country's continent id's
	for (int i = 0; i < getCountries().size(); i++)
		c.push_back(countries.at(i).getContinentId());

	//Trim it back to get just a list of all the continent id's on the map
	c.erase(unique(c.begin(), c.end()), c.end());

	//Move them to a readable vector
	for (auto it = c.cbegin(); it != c.cend(); ++it)
		continents.push_back(*it);

	return continents;
}

void Map::setCountry(std::vector<Country> countries) {
	mappedCountries = countries;
}

Map* Map::instance() {
	if (!mapInstance)
		mapInstance = new Map();
	return mapInstance;
}

void Map::resetInstance() {
	delete mapInstance;
	mapInstance = NULL;
}

void Map::setPlayers(std::vector<Player*> x) {
	players = x;
}

std::vector<Player*> Map::getPlayers() {
	return players;
}

void Map::killArmy(int countryID, int playerID) {
	
	//temporary army vector for country's armies
	vector<int*> armies = mappedCountries.at(countryID-1).getArmiesPerPlayer();

	if (*armies.at(playerID - 1) > 0) //making sure there is an army to destroy
	{ 
		*armies.at(playerID - 1) = *(armies.at(playerID - 1)) - 1; //deduct one army
		mappedCountries.at(countryID - 1).setArmiesPerPlayer(armies); //set the new army vector for that country
		Map::players.at(playerID - 1)->setAvailableArmies((Map::players.at(playerID - 1)->getAvailableArmies()) + 1); //give the player one army back
	}
	else
	{
		cout << "The poor bastard doesn't even have an army to destroy!" << endl;
	}
}