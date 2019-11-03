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

	//Loading in the game map after getting amount of players, to properly initalize the game map
	Graph GameMap = (m.ReadMap(in, numberOfPlayers));
	int availableArmy = 14;
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
	
	Player p;			//Insert a number of players depending on the selected number, give them starting coins, set their ID, give them a "bidding facility"
	for (int i = 0; i < numberOfPlayers; i++) {
		p = Player();
		p.setAvailableCoins(startingCoins);
		p.setPlayerID(i + 1);
		p.setAvailableCities(3);
		p.setAvailableArmies(14);

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
		Card chosenCard = Card(); //This will be used to determine what action to take.
		//This loop ensures that each player goes once before the turn goes up by 1
		for (int numberOfPlayersWhoWent = 0; numberOfPlayersWhoWent < numberOfPlayers; numberOfPlayersWhoWent++) {

			cout << ":::::::::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
			cout << "::::::::::::It is currently Player " << currentPlayer + 1 << "'s turn::::::::::::" << endl;
			cout << ":::::::::::::::::::::::::::::::::::::::::::::::::::::::\n" << endl;

			deck.printDeck();
			cout << "You have " << players[currentPlayer].getAvailableCoins() << " coins." << endl;

			//Giving the player a choice of actions
			while (1) {			

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
			cout << "Time to do the action of your card" << endl;
			int numberOfActions = 0;
			if (chosenCard.getOperator() == "")
				numberOfActions = 1;
			else if (chosenCard.getOperator() == "or")
				numberOfActions = 1;
			else if (chosenCard.getOperator() == "and")
				numberOfActions = 2;

			int playerChoice = -1;
			//Say for example there is an AND/OR, then it is a tracker to see which action was selected
			//For example, Card has Action 1 and Action 2, Player selects Action 2, cardActionUsed will be set to 2
			//So next time, they cannot pick Action.
			int cardActionUsed = -1;
			bool multipleChoices = false;
			while (numberOfActions > 0) {
				cout << "You have " << numberOfActions << " actions remaining. You have the following choices: " << endl;
				cout << "1: " << chosenCard.formatAction(chosenCard.getAction1(), to_string(chosenCard.getNumA1())) << endl;

				if (chosenCard.getOperator() == "or" || chosenCard.getOperator() == "and") {
					multipleChoices = true;
					cout << chosenCard.getOperator() << endl;
					cout << "2:" << chosenCard.formatAction(chosenCard.getAction2(), to_string(chosenCard.getNumA2())) << endl;
				}
				else {
					cout << "2: No action available" << endl;
				}
				cout << "3: Ignore action" << endl;
				cin >> playerChoice;

				if (playerChoice == 1) {
					if (multipleChoices) {
						cardActionUsed = playerChoice;
					}
					int innerCounter = chosenCard.getNumA1();
					while (innerCounter > 0) {
						if (chosenCard.getAction1() == "build") {
							//Prompt player to build city
							//Looks for all countries that a player owns
							cin.clear();
							cin.ignore();
							if (players[currentPlayer].getAvailableCities() > 0) {
								cout << "Place your city!: " << endl;
								int regionToBuildIn = -1;
								if (players[currentPlayer].getArmyLocationsForCity(m).size() > 0) {
									while (regionToBuildIn > players[currentPlayer].getArmyLocationsForCity(m).size() || regionToBuildIn < 1) {
										cout << "Here are your options: " << endl;
										for (int playerCityOptions = 0; playerCityOptions < players[currentPlayer].getArmyLocationsForCity(m).size(); playerCityOptions++) {
											cout << playerCityOptions + 1 << ": Build in Country " << players[currentPlayer].getArmyLocationsForCity(m)[playerCityOptions] << endl;
										}
										if (regionToBuildIn > players[currentPlayer].getArmyLocationsForCity(m).size() || regionToBuildIn < 1)
											cin >> regionToBuildIn;

									}
									cout << "Building a city here: Country " << players[currentPlayer].getArmyLocationsForCity(m)[regionToBuildIn - 1] << endl;
									Country countryToBuildCityIn = m.getCountries()[players[currentPlayer].getArmyLocationsForCity(m)[regionToBuildIn - 1] - 1];
									players[currentPlayer].buildCity(countryToBuildCityIn);
								}
								else {
									cout << "Sorry, there are no available places for you to create a city!" << endl;
								}
							}
							else {
								cout << "Sorry you do not have any cities available" << endl;

							}
							innerCounter--;
						}
						//End While
						//End Action: BUILD
						//Still need to code for player choice
						else if (chosenCard.getAction1() == "move") {
							while (innerCounter > 0) {
								cout << "You can move " << innerCounter << " armies" << endl;
								cout << "You have armies in the following countries: " << endl;
								//Loading valid players armies:
								if (players[currentPlayer].getArmyLocations(m).size() > 0) {
									int moveChoice = -1;
									while (moveChoice > players[currentPlayer].getArmyLocations(m).size() || moveChoice < 1) {
										for (int i = 0; i < players[currentPlayer].getArmyLocations(m).size(); i++) {
											cout << i + 1 << ": Country " << m.getCountries()[players[currentPlayer].getArmyLocations(m)[i] - 1].getCountryId() << endl;
										}
										if (moveChoice > players[currentPlayer].getArmyLocations(m).size() || moveChoice < 1) {
											cin >> moveChoice;
										}

									}
									cout << "Here are your adjacent countries you can move into from Country " << players[currentPlayer].getArmyLocations(m)[moveChoice - 1] << endl;
									int continentId = m.getCountries()[players[currentPlayer].getArmyLocations(m)[moveChoice - 1] - 1].getContinentId();
									vector<int> countriesOnSameContinent = vector<int>(0);
									for (int i = 0; i < m.getCountries()[players[currentPlayer].getArmyLocations(m)[moveChoice - 1] - 1].returnAdjacencies(GameMap).size(); i++) {
										if (m.getCountries()[m.getCountries()[players[currentPlayer].getArmyLocations(m)[moveChoice - 1] - 1].returnAdjacencies(GameMap).at(i)].getContinentId() == continentId) {
											countriesOnSameContinent.push_back(m.getCountries()[players[currentPlayer].getArmyLocations(m)[moveChoice - 1] - 1].returnAdjacencies(GameMap).at(i));
										}
									}

									int countryDest = -1;
									while (countryDest > countriesOnSameContinent.size() || countryDest < 1) {
										for (int i = 0; i < countriesOnSameContinent.size(); i++) {
											cout << i + 1 << ": Country " << countriesOnSameContinent[i] << endl;

										}

										if (countryDest > countriesOnSameContinent.size() || countryDest < 1)
											cin >> countryDest;
									}

									players[currentPlayer].moveArmies(1, m.getCountries()[players[currentPlayer].getArmyLocations(m)[moveChoice - 1] - 1], m.getCountries()[countriesOnSameContinent[countryDest - 1] - 1]);
									m.setCountry(m.getCountries());

									innerCounter--;
								}
								else {
									cout << "Sorry you have no armies available!" << endl;
								}
							}


						}
						else if (chosenCard.getAction1() == "moveOver") {

							while (innerCounter > 0) {
								cout << "You can move " << innerCounter << " armies" << endl;
								cout << "You have armies in the following countries: " << endl;
								//Loading valid players armies:
								if (players[currentPlayer].getArmyLocations(m).size() > 0) {
									int moveChoice = -1;
									while (moveChoice > players[currentPlayer].getArmyLocations(m).size() || moveChoice < 1) {
										for (int i = 0; i < players[currentPlayer].getArmyLocations(m).size(); i++) {
											cout << i + 1 << ": Country " << m.getCountries()[players[currentPlayer].getArmyLocations(m)[i] - 1].getCountryId() << endl;
										}
										if (moveChoice > players[currentPlayer].getArmyLocations(m).size() || moveChoice < 1) {
											cin >> moveChoice;
											cin.clear();
											cin.ignore();
										}

									}
									cout << "Here are your adjacent countries you can move into from Country " << players[currentPlayer].getArmyLocations(m)[moveChoice - 1] << endl;
									int continentId = m.getCountries()[players[currentPlayer].getArmyLocations(m)[moveChoice - 1] - 1].getContinentId();


									int countryDest = -1;
									while (countryDest > m.getCountries()[players[currentPlayer].getArmyLocations(m)[moveChoice - 1] - 1].returnAdjacencies(GameMap).size() || countryDest < 1) {
										for (int i = 0; i < m.getCountries()[players[currentPlayer].getArmyLocations(m)[moveChoice - 1] - 1].returnAdjacencies(GameMap).size(); i++) {
											cout << i + 1 << ": Country " << m.getCountries()[players[currentPlayer].getArmyLocations(m)[moveChoice - 1] - 1].returnAdjacencies(GameMap).at(i) << endl;
										}

										if (countryDest > m.getCountries()[players[currentPlayer].getArmyLocations(m)[moveChoice - 1] - 1].returnAdjacencies(GameMap).size() || countryDest < 1)
											cin >> countryDest;
									}

									players[currentPlayer].moveArmies(1, m.getCountries()[players[currentPlayer].getArmyLocations(m)[moveChoice - 1] - 1], m.getCountries()[m.getCountries()[players[currentPlayer].getArmyLocations(m)[moveChoice - 1] - 1].returnAdjacencies(GameMap).at(countryDest - 1) - 1]);
									m.setCountry(m.getCountries());

									innerCounter--;
								}
								else {
									cout << "Sorry you have no armies available!" << endl;
								}
							}

						}//End PLACE
						else if (chosenCard.getAction1() == "place") {
							//Place armies. 
							while (innerCounter > 0) {
								if (players[currentPlayer].getAvailableArmies() > 0) {
									int spawnChoice = -1;
									cout << "You may place " << innerCounter << " armies at the following locations: " << endl;
									while (spawnChoice > players[currentPlayer].getArmySpawnLocations(m).size() || spawnChoice < 1) {
										for (int i = 0; i < players[currentPlayer].getArmySpawnLocations(m).size(); i++) {
											//cout << i + 1 << ": Country " << m.getCountries()[players[currentPlayer].getArmySpawnLocations(m).at(i)].getCountryId() << endl;
											cout << i + 1 << ": Country " << players[currentPlayer].getArmySpawnLocations(m)[i] << endl;
										}
										
										if (spawnChoice > players[currentPlayer].getArmySpawnLocations(m).size() || spawnChoice < 1) {
											cin >> spawnChoice;
										}

								
										}


									cout << "You have placed an army here" << endl;
									Country updatedCountry = m.getCountries()[players[currentPlayer].getArmySpawnLocations(m)[spawnChoice - 1] - 1];
									players[currentPlayer].placeNewArmies(1, updatedCountry);

									innerCounter--;
								}
								else {
									cout << "you do not have anymore armies!" << endl;
									innerCounter = 0;
								}
								


							}
							
						} 
						else if (chosenCard.getAction1() == "destroy") {

						}
						innerCounter--;
					}
					numberOfActions -= 1;
						
				}
				else if (playerChoice == 2) {
					if (multipleChoices) {
						cardActionUsed = playerChoice;
					}
				}
				else if (playerChoice == 3) {
					players[currentPlayer].ignore();
					numberOfActions -= 1;
				}
				else {
					cout << "Invalid Action" << endl;
					cin.clear();
					cin.ignore();
				}
			}
			//THIS GOES AT THE VERY END OF THE LOOP
			currentPlayer++; //Passes the turn to the next player
			if (currentPlayer > (numberOfPlayers - 1)) //Example: if there are 3 players and currentPlayer is 4, sets it to player[0]'s turn
				currentPlayer = 0;
		}


	}


}