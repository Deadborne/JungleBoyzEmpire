#pragma once

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
/*
int main()
{


	cout << "		    __ _____ _____ _____ __    _____	" << endl;
	cout << "		 __|  |  |  |   | |   __|  |  |   __|	" << endl;
	cout << "		|  |  |  |  | | | |  |  |  |__|   __|	" << endl;
	cout << "		|_____|_____|_|___|_____|_____|_____|	" << endl;
	cout << "		 ____  _____ __ __ _____				" << endl;
	cout << "		| __  |     |  |  |__   |				" << endl;
	cout << "		| __ -|  |  |_   _|   __|				" << endl;
	cout << "		|_____|_____| |_| |_____|				" << endl;
	cout << "		 _____ _____ _____ _____ _____ _____	" << endl;
	cout << "		|   __|     |  _  |     | __  |   __|	" << endl;
	cout << "		|   __| | | |   __|-   -|    -|   __|	" << endl;
	cout << "		|_____|_|_|_|__|  |_____|__|__|_____|	" << endl;
	cout << endl;

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

		players.push_back(p); //inserting players

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


	cout << "\n[PART 2: STARTUP PHASE]\n" << endl;

	//[Requirement 1: Shuffling Deck]
	// The shuffling already appears on the Deck Constructor. To verify, we are printing the card space. Each time we get different amount of cards.
	deck.printDeck();

	//[Requirement 2: Give Armies to players]

	cout << endl;

	//initializing starting info.
	for (int i = 0; i < numberOfPlayers; i++) {
		players[i].setAvailableArmies(14);
		players[i].setAvailableCities(3);
		players[i].placeNewArmies(3, m.getStartingCountry());
	}

	for (int i = 0; i < numberOfPlayers; i++) { // Display and verify initial army placement
		cout << "Player " << players[i].getPlayerID() + 1 << " starts with " << players[i].getAvailableArmies() << " armies and ";
		cout << players[i].getAvailableCities() << " cities, and placed 3 armies at the starting region, " << m.getStartingCountry().getCountryId() << endl;
	}

	//this loop is for placing NPCs in a 2 player game.
	if (numberOfPlayers == 2) {
		cout << endl;
		Player npc = Player();
		npc.setAvailableArmies(10);
		npc.setPlayerID(2); //NPC is effectively player 3
		int selectCountry = 0;
		int placingPlayer = 1; //The player who gets to choose where to place the army
		for (int i = 0; i < npc.getAvailableArmies(); i++) {
			m.showEverything(); //show the map so players can decide where to put NPC armies
			cout << "Player " << placingPlayer << ", choose a region to place non-player army: ";
			cin >> selectCountry;
			while (selectCountry > m.getCountries().size() || selectCountry < 1) {
				cout << "Invalid Country ID. Try again: ";
				cin >> selectCountry;
			}
			npc.placeNewArmies(1, m.giveMeCountry(selectCountry));
			//It's the next player's turn to place NPC armies
			if (placingPlayer == 1)
				placingPlayer = 2;
			else
				placingPlayer = 1;
		}
	}

	m.showEverything();
	cout << endl;

	//[Requirement 3: Give coins to players - we did this in part 1. Sorry!

	//[Requirement 4: Bidding System]

	// Step 1: Prompt each player to enter their bidding coins and their birthdate in the form of YYYYMMDD
	for (int i = 0; i < numberOfPlayers; i++) {
		cin.clear(); //removing bad values from cin.
		cin.ignore();
		players[i].setBid(startingCoins);
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
	int maxIndex = calculator.calculateBid(bids);
	// If no maximum bidding cost was found, which may happen often, the players' dates are compared.
	// The younger player (meaning the one with the biggest integer date) will start first
	if (maxIndex == -1)
		maxIndex = calculator.calculateDate(dates);

	cout << "The winner of the bid is Player " << maxIndex + 1 << endl;
	cout << "\n" << endl;

	//:::::::::::::::::::::::::::::::::::PART 3::::::::::::::::::::::::::::::::::::::::::::::
	cout << "[PART 3: MAIN GAME LOOP]\n" << endl;

	//setting the first player to the bid winner
	int startingPlayer = maxIndex;

	int currentPlayer = startingPlayer; //Makes it so that starting player is the first "current player"
	int numberOfTurns; //At what turn the game ends

	switch (numberOfPlayers) {
	case 2:
		numberOfTurns = 13;
		break;
	case 3:
		numberOfTurns = 10;
		break;
	case 4:
		numberOfTurns = 8;
		break;
	case 5:
		numberOfTurns = 7;
		break;
	}

	//This is the main game loop!
	for (int currentTurn = 0; currentTurn < numberOfTurns; currentTurn++) {

		//This loop ensures that each player goes once before the turn goes up by 1
		for (int numberOfPlayersWhoWent = 0; numberOfPlayersWhoWent < numberOfPlayers; numberOfPlayersWhoWent++) {

			cout << ":::::::::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
			cout << "::::::::::::It is currently Player " << currentPlayer + 1 << "'s turn::::::::::::" << endl;
			cout << ":::::::::::::::::::::::::::::::::::::::::::::::::::::::\n" << endl;

			deck.printDeck();
			cout << "You have " << players[currentPlayer].getAvailableCoins() << " coins." << endl;

			//Giving the player a choice of actions
			while (1) {

				Card chosenCard = Card(); //This will be used to determine what action to take.

				int choice = 0;
				cout << "\nWhat would you like to do: " << endl;
				cout << "1: View Map." << endl;
				cout << "2: See available cards again." << endl;
				cout << "3: See my hand." << endl;
				cout << "4: Pick a card." << endl;
				cout << "You are Player: " << currentPlayer + 1 << endl; //tracing
				cin >> choice;

				if (choice == 1) //display the map
					m.showEverything();
				else if (choice == 2) { //show what cards they can pick
					deck.printDeck();
					cout << "You have " << players[currentPlayer].getAvailableCoins() << " coins." << endl;
				}
				else if (choice == 3) { //show what cards they already picked
					players[currentPlayer].printHand();

				}
				else if (choice == 4) { //pick a card
					deck.printDeck();
					cout << "You have " << players[currentPlayer].getAvailableCoins() << " coins." << endl;
					while (1) {

						int cardChoice = 0;
						cout << "Select your card (1-6):" << endl;
						cin >> cardChoice;

						if (cardChoice == 1) {
							chosenCard = deck.getSpace()[cardChoice - 1];

							vector<Card> v = players[currentPlayer].getHand();
							v.push_back(chosenCard);

							players[currentPlayer].setHand(v);
							deck.removeCard(cardChoice);
							break;
						}
						else if (cardChoice == 2 || 3) {

							if (players[currentPlayer].getAvailableCoins() < 1)
								cout << "You don't have enough coins." << endl;
							else {
								players[currentPlayer].PayCoin();
								chosenCard = deck.getSpace()[cardChoice - 1];

								vector<Card> v = players[currentPlayer].getHand();
								v.push_back(chosenCard);

								players[currentPlayer].setHand(v);
								deck.removeCard(cardChoice);
								break;
							}
						}
						else if (cardChoice == 4 || 5) {
							if (players[currentPlayer].getAvailableCoins() < 2)
								cout << "You don't have enough coins." << endl;
							else {
								players[currentPlayer].PayCoin(2);
								chosenCard = deck.getSpace()[cardChoice - 1];

								vector<Card> v = players[currentPlayer].getHand();
								v.push_back(chosenCard);

								players[currentPlayer].setHand(v);
								deck.removeCard(cardChoice);
								break;
							}
						}
						else if (cardChoice == 6) {
							if (players[currentPlayer].getAvailableCoins() < 3)
								cout << "You don't have enough coins." << endl;
							else {
								players[currentPlayer].PayCoin(3);
								chosenCard = deck.getSpace()[cardChoice - 1];

								vector<Card> v = players[currentPlayer].getHand();
								v.push_back(chosenCard);

								players[currentPlayer].setHand(v);
								deck.removeCard(cardChoice);
								break;
							}
						}
						else { //entered something invalid
							cout << "Pick a valid card." << endl;
						}
						cin.clear();
						cin.ignore();
					}
					break;
				}
				else { //entered something invalid
					cin.clear();
					cin.ignore();
					cout << "Invalid choice of action" << endl;
				}
			}

			//:::::::::::::::::::::::::::::::::::PART 4::::::::::::::::::::::::::::::::::::::::::::::


			//:::::::::::::::::::::::::::::::::::PART 5::::::::::::::::::::::::::::::::::::::::::::::
			// After a player has made a valid card choice and the card has been pulled from card space,
			// a new card from the deck is drawn and placed again in card space (at the right-most space)
			deck.draw();
			deck.printDeck();


			//THIS GOES AT THE VERY END OF THE LOOP
			currentPlayer++; //Passes the turn to the next player
			if (currentPlayer > (numberOfPlayers - 1)) //Example: if there are 3 players and currentPlayer is 4, sets it to player[0]'s turn
				currentPlayer = 0;
		}


	}


	//THIS IS OUTSIDE OF THE MAIN GAME LOOP. THIS IS WHERE WE WILL BE CALCULATING SCORES FOR RESPECTIVE PLAYERS

	//Player scores		i0 == p1's score
	//					i1 == p2's score
	//					i4 == p5's score
	//					in ==p (n+1)'s score
	cout << "\nProof of Concept\n";
	cout << players.at(2).isCountryOwner(m.getCountries().at(2));





	//for each player, we need to calculate a score
	//for (int p = 0; p < players.size(); p++) {




		//cout << "Player " << p + 1 << " owns "<< players.at(p).getCountriesOwned(m).size() << " countries\n";

		//cout << "Player " << p + 1 << " owns " << players.at(p).getContinentsOwned(m).size() << " continents\n";

		//cout << "Player " << p + 1 << " owns " << players.at(p).PointsFromCards() << " points from cards\n";

	//}


}*/