#include "stdafx.h"
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
	Map m;

	//Selecting a map to read. M1, M5, M6, M8, M9, M10, M14 are all valid maps.
	cout << "Select the Map to load (Proper format is M#)" << endl;
	getline(cin, in);

	Graph GameMap = (m.ReadMap(in));
	m.showEverything();

	cout << "\nContinents:\n";
	//CONTINENT PARSER WORKS
	for (int i = 0; i < m.getContinents().size(); i++) {
		cout << m.getContinents().at(i);
	}

	Player player1 = Player();
	Player player2 = Player();

	player1.setPlayerID(1);
	player2.setPlayerID(2);

	player1.setAvailableArmies(20);
	player2.setAvailableArmies(20);

	player1.placeNewArmies(2, m.getCountries().at(10));
	player2.placeNewArmies(1, m.getCountries().at(9));
	player2.placeNewArmies(2, m.getCountries().at(10));
	player2.placeNewArmies(2, m.getCountries().at(12));
	cout << endl;
	m.showEverything();

	cout << "Player 2 ownership: " << player2.isCountryOwner(m.getCountries().at(9)) << endl;
	cout << "Player 2 ownership: " << player2.isCountryOwner(m.getCountries().at(10)) << endl;
	cout << "Player 1 ownership: " << player1.isCountryOwner(m.getCountries().at(10)) << endl;

	cout << "Player 2 owns the following countries\n";
	for (int i = 0; i < player2.getCountriesOwned(m).size(); i++) {
		cout << player2.getCountriesOwned(m).at(i).getCountryId() << " ";
	}

	player2.placeNewArmies(1, m.getCountries().at(21));
	player2.placeNewArmies(1, m.getCountries().at(22));
	player2.placeNewArmies(1, m.getCountries().at(23));
	player2.placeNewArmies(1, m.getCountries().at(24));
	//player2.placeNewArmies(1, m.getCountries().at(25)); //wont work for some reason
	
	m.showEverything();

	cout << "Player 2 has dominion over " << player2.getContinentsOwned(m).size() << "countries...\n";





}