#pragma once

#include "stdafx.h"
#include <string>
#include <iostream>
#include "Map.h"
#include "Country.h"
#include "Player.h" 
#include "Card.h"
#include "Bid.h"
#include <ostream>
#include <vector>
using namespace std;
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>
using namespace boost;



int main()
{

	//:::::::::::::::::::::::::::::::::::PART 1::::::::::::::::::::::::::::::::::::::::::::::

	//[Requirement 1: Reading the Map]

	cout << "[PART 1: GAME START]" << endl;

	typedef boost::adjacency_list<listS, vecS, undirectedS> Graph;

	string in;
	Map m;

	//Selecting a map to read. M1, M5, M6, M8, M9, M10, M14 are all valid maps.
	cout << "Select the Map to load (Proper format is M#)" << endl;
	getline(cin, in);

	Graph GameMap = (m.ReadMap(in));

	//[Requirement 2: Selecting the number of Players]

	int numberOfPlayers; //the number of players, as selected in the beginning
	int startingCoins; //the number of coins started with, adjusted to the number of players

	//Entering the number of players. Loops until a correct number is chosen.
	while (1) {
		cout << "Select the number of players, from 2 to 5." << endl;
		cin >> numberOfPlayers;
		if (numberOfPlayers != NULL && numberOfPlayers > 1 && numberOfPlayers < 6)
			break;
		else {
			cin.clear();
			cin.ignore();
			cout << "Invalid number of players." << endl;
		}
	}

	//giving each player the right amount of coins, depending on the number of players.
	switch (numberOfPlayers) {
	case 2:
		startingCoins = 14;
		break;
	case 3:
		startingCoins = 11;
		break;
	case 4:
		startingCoins = 9;
		break;
	case 5:
		startingCoins = 8;
		break;
	}

	vector<Player> players; //The players

	//Insert a number of players depending on the selected number, give them starting coins, set their ID, give them a "bidding facility"
	for (int i = 0; i < numberOfPlayers; i++) {
		Player p = Player();
		p.setAvailableCoins(startingCoins);
		p.setPlayerID(i);

		players.insert(players.begin()+i, p); //inserting players
		cout << "Player " << p.getPlayerID() + 1 << " is ready, and has " << p.getAvailableCoins() << " coins!" << endl;
	}

	//[Requirement 3: Initializing Deck]

	Deck deck = Deck(numberOfPlayers); //Note: this automatically shuffles the deck

	//[Requirement 4: Initializing Hands]

	for (int i = 0; i < numberOfPlayers; i++) {
		cout << "Player " << i + 1 << ": ";
		players[i].initializeHand(); //giving each player an empty hand with 0 cards
		players[i].printHand(); //Displaying the hand. Look, ma, there's nothing in my hands! (should show nothing)
	}
	cout << "" << endl;

	//:::::::::::::::::::::::::::::::::::PART 2::::::::::::::::::::::::::::::::::::::::::::::

	//[Requirement 1: Shuffling Deck]
	// The shuffling already appears on the Deck Constructor. To verify, we are printing the card space. Each time we get different amount of cards.
	deck.printDeck();

	//[Requirement 2: Give Armies to players]

	cout << endl;

	for (int i = 0; i < numberOfPlayers; i++) {
		players[i].setAvailableArmies(14);
		players[i].setAvailableCities(3);
		players[i].placeNewArmies(3, m.getStartingCountry());
	}

	if (numberOfPlayers == 2) {
		Player npc = Player();
		npc.setAvailableArmies(10);
		int selectCountry = 0;
		for (int i = 0; i < npc.getAvailableArmies(); i++) {
			cout << "Enter countryID to place non-player army: ";
			cin >> selectCountry;

			while (selectCountry > m.getCountries().size() || selectCountry < 1) {
				cout << "Invalid Country ID. Try again: ";
				cin >> selectCountry;
			}
			npc.placeNewArmies(1, m.giveMeCountry(selectCountry));
		}
	}

	m.showEverything();
	cout << endl;

	for (int i = 0; i < numberOfPlayers; i++) { // Display and verify initial army placement
		cout << "Player " << players[i].getPlayerID() << " has " << players[i].getAvailableArmies() << ", " << players[i].getAvailableCities() << " and placed 3 at country 1" << endl;
	}

	//[Requirement 3: Give coins to players (done above at line 54 or 160)]

	//[Requirement 4: Bidding System]

	// Step 1: Prompt each player to enter their bidding coins and their birthdate in the form of YYYYMMDD
	for (int i = 0; i < numberOfPlayers; i++) {
		cin.clear(); //removing bad values from cin.
		cin.ignore(); 
		players[i].setBid();
		players[i].setBirthday();
	}

	// Create vectors and enter their values to be compared after. The appropriate values match with the appropriate player index
	vector<int> bids(numberOfPlayers);
	vector<int> dates(numberOfPlayers);
	for (int i = 0; i < numberOfPlayers; i++) {
		bids[i] = players[i].getBid().getBidAmount();
		dates[i] = players[i].getBirthday();
	}
	Bid calculator = Bid();
	//cin.clear();
	//cin.ignore();
	int maxIndex = calculator.calculateBid(bids);
	// If no maximum bidding cost was found, which may happen often, the players' dates are compared.
	// The younger player (meaning the one with the biggest integer date) will start first
	if (maxIndex == -1)
		maxIndex = calculator.calculateDate(dates);

	cout << "The winner of the bid is Player " << maxIndex + 1 << endl;

}