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

		players.insert(players.begin(), p); //inserting players

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

	//[Requirement 1: Shuffling the deck and drawing cards]
	cout << "Displaying available cards:" << endl;
	deck.printDeck();


	m.showEverything();


	
	//:::::::::::::::::::::::::::::::::::PART 3::::::::::::::::::::::::::::::::::::::::::::::
	cout << "[PART 3: MAIN GAME LOOP]\n" << endl;
	
	//UNTIL PART 2 GETS DONE, we assume starting player is player 1 [aka players[0]]
	int startingPlayer = 0; 

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
				cout << "You are: " << currentPlayer << endl; //tracing
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
							//deck.getSpace().erase(deck.getSpace().begin() + cardChoice); //we'll be able to do this after step 5 is coded
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
								//deck.getSpace().erase(deck.getSpace().begin() + cardChoice); //we'll be able to do this after step 5 is coded
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
								//deck.getSpace().erase(deck.getSpace().begin() + cardChoice); //we'll be able to do this after step 5 is coded
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
								//deck.getSpace().erase(deck.getSpace().begin() + cardChoice); //we'll be able to do this after step 5 is coded
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


			//THIS GOES AT THE VERY END OF THE LOOP
			currentPlayer++; //Passes the turn to the next player
			if (currentPlayer > (numberOfPlayers - 1)) //Example: if there are 3 players and currentPlayer is 4, sets it to player[0]'s turn
				currentPlayer = 0;
		}


	}


}

