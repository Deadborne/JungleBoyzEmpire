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
	string name;
	name = "John";
	cout << "Please Enter Map Name: ";
	getline(cin, name);
	Map m = Map(12);
	m.getNum();
	m.ReadMap(name);


	//START OF ACTUAL DRIVER -- DO NOT DELETE PLEASE -- WILL MOVE
	Player player1 = Player();
	player1.setAvailableArmies(14);
	player1.setPlayerID(1);
	player1.setAvailableCities(3);
	player1.setAvailableCoins(14);


	Player player2 = Player();
	player2.setAvailableArmies(14);
	player2.setPlayerID(2);
	player2.setAvailableCities(3);

	Country c1 = m.getCountries().at(0);
	Country c2 = m.getCountries().at(1);
	
	
	cout << "\n\n=====Pay a Coin=====\n";
	cout << "Player 1 currently has " << player1.getAvailableCoins() << " coins.\nIf he decided to purchase a card, he'd have to pay a coin\n";
	player1.PayCoin();
	cout << "      player 1 pays out one coin for a card...\n";
	cout << "This would leave Player 1 with " << player1.getAvailableCoins() << " coins left in his/her bank";
	
	getline(cin, name);
	cout << "\n\n=====Place new armies in a country=====\n";
	cout << "Armies in Country 1: \n";
	c1.printArmies();
	cout << "\n";

	player1.placeNewArmies(5, c1);
	cout << "\nPlayer 1 has placed 5 new armies in Country 1: \n";
	c1.printArmies();

	getline(cin, name);
	cout << "\n\n=====Move armies from Country 1 to Country 2=====\n";
	cout << "Player 1 has 0 armies in Country 2:\n";
	c2.printArmies();
	player1.moveArmies(2, c1, c2);
	cout << "\n     player 1 moving 2 armies from c1 to c2... \n";

	cout << "Armies now in Country 1:\n";
	c1.printArmies();
	cout << "\nArmies now in Country 2:\n";
	c2.printArmies();

	getline(cin, name);
	cout << "\n\n=====Add a city to Country 1=====\n";
	cout << "Player 1 has " << c1.getCities().at(0) << " cities in Country 1";
	cout << "\n     player 1 building city in c1...";
	player1.buildCity(c1);
	cout << "\nPlayer 1 now has " << c1.getCities().at(0) << " city in Country 1";

	getline(cin, name);
	cout << "\n\n=====Destroy another player's army=====\n";
	cout << "Recall Player 1 has 2 armies in Country 2:\n";
	c2.printArmies();
	cout << "\n      player 2 destroying one of Player 1's armies in Country 2...\n";
	player2.destroyArmy(c2, player1);
	cout << "Player 1 now has one fewer armies in Country 2:\n";
	c2.printArmies();

	getline(cin, name);
	cout << "\n\n=====Move Over Land=====\n";
	cout << "Recall Player 1 had 3 armies remaining in Country 1\n      let's move one to the adjacent Country, 2...\n";
	player1.moveOverLand(1, c1, c2, m.g);
	c2.printArmies();

	getline(cin, name);
	cout << "\n\n=====The rest of the requiremens would be printed here. Data members created in .h=====\n";



	cout << "\n\n\n\n\nProgram end. Press Enter to terminate...";
	
	



	
	getline(cin, name);
	return 0;
}