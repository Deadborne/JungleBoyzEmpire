#pragma once

#include "stdafx.h"
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
