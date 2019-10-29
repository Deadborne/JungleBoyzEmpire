//// EightMinuteEmpire.cpp : Defines the entry point for the console application.
////
#pragma once
//
#include "stdafx.h"
/*


	Player player1 = Player();
	player1.setAvailableArmies(14);


	player1.setPlayerID(1);
	cout << "PlayerID: " << player1.getPlayerID() << "\n";
	//cout << player1.getAvailableCities();
		
	vector<int> vec = player1.getCountriesOwned();
		//cout << vec.at(0) << vec.at(1);

	for (int i = 0; i < vec.size(); i++) {
		cout << "Owns: " << vec.at(i);
	}
		
	cout << "Well aint that some shit: \n";
	cout << "Country 1's ID: " << m.getCountries().at(0).getCountryId() 
		<< "\n"; //Gets ID of the country at index 0 of vector of countries
	
	int testID = m.getCountries().at(0).getCountryId();
	//vector<int> arTest = { 0,0,0,0,0 };
	//m.getCountries().at(0).setArmiesPerPlayer(arTest);

	m.getCountries().at(0).printArmies();

	cout << "..." << testID;
	player1.placeNewArmies(3, testID);
	m.getCountries().at(0).printArmies();
	//m.getCountries().at(0).printArmies();

	cout << "TEST IN MAIN\n";


	//	______ _     _     _ _             
	//	| ___ (_)   | |   | (_)            
	//	| |_/ /_  __| | __| |_ _ __   __ _ 
	//	| ___ \ |/ _` |/ _` | | '_ \ / _` |
	//	| |_/ / | (_| | (_| | | | | | (_| |
	//	\____/|_|\__,_|\__,_|_|_| |_|\__, |
	//								  __/ |
	//								 |___/ 
	int startingPlayerIndex = -1;
	vector<Player> players = { Player(), Player(), Player(), Player(), Player() };
	for (int i = 0; i < players.size(); i++) {
		players[i].setAvailableCoins(8);
		players[i].setPlayerID(i);
		players[i].setBid();
	}

	vector<int> bidVector = vector<int>(players.size());
	
	for (int i = 0; i < players.size(); i++) {
		int playerBid = *players.at(i).playerBid->_bidAmount;
		bidVector[i] = playerBid;
	}
	cout << "vector size: " << bidVector.size() << "\n";
	Bid bidTest = Bid();
	int winningBid = bidTest.calculateBid(bidVector);
	if (winningBid == -1) {
		cout << "Bets are tied! Picking a random player to start!\n";
		srand(time(NULL));
		startingPlayerIndex = (rand()) % bidVector.size();
	}
	else {
		cout << "Player : " << winningBid + 1 << " wins the bid!\n";
		startingPlayerIndex = winningBid;
	}

	//Setting player bets back to 8 except for winner, unless it was a draw
	for (int i = 0; i < players.size(); i++) {
		if (i != startingPlayerIndex)
			players.at(i).setAvailableCoins(8);
	}
	
	cout << "Player " << startingPlayerIndex + 1 << " starts!";
	getline(cin, name);
	return 0;

}

void printAry() {
	//Driver todos
}
*/
//#include <string>
//#include <iostream>
//#include "Map.h"
//#include "Country.h"
//#include "Player.h" 
//#include <ostream>
////#include <vector>
//using namespace std;
//#include <boost/graph/adjacency_list.hpp>
//#include <boost/graph/graphviz.hpp>
//using namespace boost;
//
//
//int main()
//{	
//	string name;
//	name = "John";
//	cout << "Please Enter Map Name: ";
//	getline(cin, name);
//	Map m = Map(12);
//	m.getNum();
//	m.ReadMap(name);
//	
//
//	//START OF ACTUAL DRIVER -- DO NOT DELETE PLEASE -- WILL MOVE
//	Player player1 = Player();
//	player1.setAvailableArmies(14);
//	player1.setPlayerID(1);
//	player1.setAvailableCities(3);
//
//	cout << "\n\nPlayer 1 ID: " << player1.getPlayerID() <<"\n\n";
//
//
//	Player player2 = Player();
//	player2.setAvailableArmies(14);
//	player2.setPlayerID(2);
//	player2.setAvailableCities(3);
//
//	Country c1 = m.getCountries().at(0);
//	Country c2 = m.getCountries().at(1);
//
//	cout << "=====Place new armies in a country=====\n";
//	cout << "Armies in Country 1: \n";
//	c1.printArmies();
//	cout << "\n";
//
//	player1.placeNewArmies(5, c1);
//	cout << "\nPlayer 1 has placed 5 new armies in Country 1: \n";
//	c1.printArmies();
//	
//	getline(cin, name);
//	cout << "\n\n=====Move armies from Country 1 to Country 2=====\n";
//	cout << "Player 1 has 0 armies in Country 2:\n";
//	c2.printArmies();
//	player1.moveArmies(2, c1, c2);
//	cout << "\n     player 1 moving 2 armies from c1 to c2... \n";
//	
//	cout << "Armies now in Country 1:\n";
//	c1.printArmies();
//	cout << "\nArmies now in Country 2:\n";
//	c2.printArmies();
//
//	getline(cin, name);
//	cout << "\n\n=====Add a city to Country 1=====\n";
//	cout << "Player 1 has " << c1.getCities().at(0) << " cities in Country 1";
//	cout << "\n     player 1 building city in c1...";
//	player1.buildCity(c1);
//	cout << "\nPlayer 1 now has " << c1.getCities().at(0) << " city in Country 1";
//	
//	getline(cin, name);
//	cout << "\n\n=====Destroy another player's army=====\n";
//	cout << "Recall Player 1 has 2 armies in Country 2:\n";
//	c2.printArmies();
//	cout << "\n      player 2 destroying one of Player 1's armies in Country 2...\n";
//	player2.destroyArmy(c2, player1);
//	cout << "Player 1 now has one fewer armies in Country 2:\n";
//	c2.printArmies();
//
//	getline(cin, name);
//	cout << "\n\n=====Move Over Land=====\n";
//	cout << "Recall Player 1 had 3 armies remaining in Country 1\n      let's move one to the adjacent Country, 2...\n";
//	player1.moveOverLand(1, c1, c2, m.g);
//	c2.printArmies();
//
//	cout << "\n\n\n\n\nProgram end. Press Enter to terminate...";
//
//	//Start of bidding test
//	int startingPlayerIndex = -1;
//	vector<Player> players = { Player(), Player(), Player(), Player(), Player() };
//	for (int i = 0; i < players.size(); i++) {
//		players[i].setAvailableCoins(8);
//		players[i].setPlayerID(i);
//		players[i].setBid();
//	}
//
//	vector<int> bidVector = vector<int>(players.size());
//
//	for (int i = 0; i < players.size(); i++) {
//		int* playerBid = players.at(i).getBid()._bidAmount;
//		bidVector[i] = *playerBid;
//	}
//	cout << "vector size: " << bidVector.size() << "\n";
//	Bid bidTest = Bid();
//	int winningBid = bidTest.calculateBid(bidVector);
//	if (winningBid == -1) {
//		cout << "Bets are tied! Picking a random player to start!\n";
//		srand(time(NULL));
//		startingPlayerIndex = (rand()) % bidVector.size();
//	}
//	else {
//		cout << "Player : " << winningBid + 1 << " wins the bid!\n";
//		startingPlayerIndex = winningBid;
//	}
//
//	//Setting player bets back to 8 except for winner, unless it was a draw
//	for (int i = 0; i < players.size(); i++) {
//		if (i != startingPlayerIndex)
//			players.at(i).setAvailableCoins(8);
//	}
//
//	cout << "Player " << startingPlayerIndex + 1 << " starts!";
//	getline(cin, name);
//	return 0;
//}

