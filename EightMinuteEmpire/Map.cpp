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
int number;
static std::vector<Country> mappedCountries;


Map::Map() {
	
}


Map::Map(int num) {
	number = num;
}

int Map::getNum()
{
	cout << "Calling from map test! \n Hit 'Enter' to close the console\n";
	string rofl;
	getline(cin, rofl);
	return number;
}

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


void Map::ReadMap(string f)
{
	std::ifstream infile;
	infile.open("./Maps/" + f + ".txt");

	std::string str;

	if (!infile) {
		cout << "That file is not valid.\n";
	}


	typedef boost::adjacency_list<listS, vecS, undirectedS> Graph;
	Graph GameMap;
	vector<string> v;

	while (std::getline(infile, str)) {
		
		std::string line; //the line we grabbed

		line = str;
		int countryNumber;
		int continentNumber;
		bool starter = false;
		std::string allAdjacent;
		
		//grabs first number (country number)
		std::size_t pos = line.find(":");
		std::istringstream iss(line.substr(0, pos));
		iss >> countryNumber;
		if (line.find("S") != std::string::npos) {
			starter = true;
		}
		iss.clear();

		//grab the continent number
		std::size_t pos2 = line.find("-");
		std::istringstream iss2(line.substr(pos+1, pos2));
		iss2 >> continentNumber;
		iss2.clear();
		
		//grab adjacencies
		std::istringstream iss3(line.substr(pos2 + 1));
		iss3 >> allAdjacent;
		v = split(allAdjacent, ",");

		//store all adjacencies in map
		for (int i = 0; i < v.size(); i++) {
			
			int box;
			std::istringstream intvertex(v.at(i));
			intvertex >> box;

			add_edge(countryNumber, box, GameMap);
			
		}

		//create a country, store it in the vector of countries
		Country c = Country(countryNumber, continentNumber, starter);
		mappedCountries.push_back(c);
		iss3.clear();
	}

	//output the map
	//write_graphviz(cout, GameMap);    //THIS MUST BE ACTIVE
	infile.close();
}


//Map has a vector of country objects
std::vector<Country> Map::getCountries() {
	/*for (int i = 0; i < mappedCountries.size(); i++) {
		cout << "Mapped Country: " << mappedCountries.at(i).getCountryId();
	}*/
	string test = "";
	getline(cin, test);
	return mappedCountries;
}




