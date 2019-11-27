#include "stdafx.h"/*
#include <string>
#include <iostream>
#include "Map.h"
#include "Country.h"
#include "Player.h" 
#include "Card.h"
#include <ostream>
#include <vector>
using namespace std;
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>
using namespace boost;


int main()
{
	typedef boost::adjacency_list<listS, vecS, undirectedS> Graph;

	string in;

	//Selecting a map to read. M1, M5, M6, M8, M9, M10, M14 are all valid maps.
	cout << "Select the Map to load (Proper format is M#)" << endl;
	getline(cin, in);

	Graph GameMap = (Map::instance()->ReadMap(in));
	Map::instance()->showEverything();

	cout << "\nContinents that exist:\n";
	//CONTINENT PARSER WORKS
	for (int i = 0; i < Map::instance()->getContinents().size(); i++) {
		cout << Map::instance()->getContinents().at(i) << " ";
	}

	cout << endl;

	Player player1 = Player();
	Player player2 = Player();

	player1.setPlayerID(1);
	player2.setPlayerID(2);

	player1.setAvailableArmies(20);
	player2.setAvailableArmies(20);

	player1.placeNewArmies(2, Map::instance()->getCountries().at(10));
	player2.placeNewArmies(1, Map::instance()->getCountries().at(9));
	player2.placeNewArmies(2, Map::instance()->getCountries().at(10));
	player2.placeNewArmies(2, Map::instance()->getCountries().at(12));
	cout << endl;
	Map::instance()->showEverything();

	cout << "Player 2 ownership of c9: " << player2.isCountryOwner(Map::instance()->getCountries().at(9)) << endl;
	cout << "Player 2 ownership of c10: " << player2.isCountryOwner(Map::instance()->getCountries().at(10)) << endl;
	cout << "Player 1 ownership of c10: " << player1.isCountryOwner(Map::instance()->getCountries().at(10)) << endl;

	cout << "Player 2 owns the following countries:\n";
	for (int i = 0; i < player2.getCountriesOwned(*Map::instance()).size(); i++) {
		cout << player2.getCountriesOwned(*Map::instance()).at(i).getCountryId() << " ";
	}

	player2.placeNewArmies(1, Map::instance()->getCountries().at(21));
	player2.placeNewArmies(1, Map::instance()->getCountries().at(22));
	player2.placeNewArmies(1, Map::instance()->getCountries().at(23));
	player2.placeNewArmies(1, Map::instance()->getCountries().at(24));

	Map::instance()->showEverything();

	cout << "\n\nPlayer 2 has dominion over " << player2.getContinentsOwned(*Map::instance()).size() << " countries...\n";
	cout << Map::instance()->getCountries().at(9).getCountryId();
}*/
