#pragma once

#include "stdafx.h"
#include <string>
#include <iostream>
#include "Map.h"
#include "Country.h"
#include "Player.h" 
#include "Card.h"
#include "Statistics.h"
#include "Phases.h"
#include "Npc.h"
#include <ostream>
#include <vector>
#include "time.h"
using namespace std;
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>
using namespace boost;


//Handles final calculations

const int random(int a, int b);
void declareWinner(vector<int> scores, vector<Player> players) {

	//get the top score
	int topScore = *max_element(scores.begin(), scores.end());


	//get the index of the top score
	int topIndex = std::distance(scores.begin(), max_element(scores.begin(), scores.end()));


	//Are there even any duplicates high scores out here
	//Run through scores and see if there is more than one value matching topScore

	int dupeTop = 0;
	for (int i = 0; i < scores.size(); i++) {
		if (scores[i] == topScore)
			dupeTop++;
	}

	vector<Player*> tied;
	vector<Player*> stillTied;

	//if theres more than one value matching the topScore, we have some sort of tie and need to compare 'em
	if (dupeTop > 1) {
		for (int i = 0; i < scores.size(); i++) {
			//if they are one of the fools who tied, get that player and add em to a subset of players who have the same score
			if (scores[i] == topScore)
				tied.push_back(Map::instance()->getPlayers()[i]);
		}

		//now we need to check who of the tied players has the most remaining coins
		int coinsMax = 0;
		Player* coinWinner;

		//For each tied player
		for (int i = 0; i < tied.size(); i++) {
			//if a player has more coins than the current max coins,
			if (tied[i]->getAvailableCoins() > coinsMax) {
				coinsMax = tied[i]->getAvailableCoins();			//that player's coin count becomes the max
				coinWinner = tied[i];							//and that player becomes the winner of the tie
			}
		}

		//We must now see if there is more than one person with that same number of coins
		int dupeCoins = 0;
		for (int i = 0; i < tied.size(); i++) {
			if (tied[i]->getAvailableCoins() == coinsMax)
				dupeCoins++;
		}

		//if theres still a tie between players after checking their coin counts
		if (dupeCoins > 1) {
			

			//Get the people who are still somehow tied
			for (int i = 0; i < tied.size(); i++) {
				if (tied[i]->getAvailableCoins() == coinsMax)
					stillTied.push_back(tied[i]);
			}

			//Find minimum remaining armies - meaning whoever has placed the most armies wins
			int minArmies = 100;
			Player* finalWinner;

			for (int i = 0; i < stillTied.size(); i++) {
				if (stillTied[i]->getAvailableArmies() < minArmies) {
					minArmies = stillTied[i]->getAvailableArmies();
					finalWinner = stillTied[i];
				}

			}

			int dupeArmies = 0;
			for (int i = 0; i < stillTied.size(); i++) {
				if (stillTied[i]->getAvailableArmies() == minArmies)
					dupeArmies++;
			}

			if (dupeArmies <= 1) {
				cout << "\n\n CONGRATS PLAYER" << finalWinner->getPlayerID() << ". YOU WIN, AND ARE NOW AN HONORARY JUNGLE BOI.";
				return;

			}
			else {
				cout << "\nA TIE OF THIS PROPORTIONS HAS NOT BEEN SEEN SINCE THE TIME OF THE DINOSAURS. YOU ARE ALL WINNERS!" << endl;
				return;
			}


		}
		else {
			cout << "\n\n CONGRATS PLAYER" << coinWinner->getPlayerID() << ". YOU WIN, AND ARE NOW AN HONORARY JUNGLE BOI.";
			return;
		}

	}
	else {
		//otherwise, the player with the top score wins, obviously
		cout << "\n\n CONGRATS PLAYER" << players.at(topIndex).getPlayerID() << ". YOU WIN, AND ARE NOW AN HONORARY JUNGLE BOI.";
		return;
	}

}

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

	//Selecting a map to read. M1, M5, M6, M8, M9, M10, M14 are all valid maps.
	cout << "Select the Map to load (Proper format is M#)" << endl;
	getline(cin, in);

	Graph GameMap = (Map::instance()->ReadMap(in));

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

	int numberOfBots = 0;
	if (numberOfPlayers <= 4) {
		//Gets the most number of bots you can get
		int maxBots = 5 - numberOfPlayers;
		cout << "Select how many bots you would like to add to your game" << endl;
		numberOfBots = -1;
		while (numberOfBots > maxBots + 1 || numberOfBots < 1) {
			for (int i = 0; i <= maxBots; i++) {
				cout << i + 1 << "): Add " << i << " bot(s) to the game" << endl;
			}

			if (numberOfBots > maxBots + 1 || numberOfBots < 1) {
				cin >> numberOfBots;
			}
		}
		
	}
	//Fixing off by 1 error :) 
	numberOfBots = numberOfBots - 1;

	//giving each player the right amount of coins, depending on the number of players.
	switch (numberOfPlayers + numberOfBots) {
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
		p.setPlayerID(i + 1);
		p.setIsNPC(false);
		players.push_back(p); //inserting players

		cout << "Player " << p.getPlayerID() << " is ready, and has " << p.getAvailableCoins() << " coins!" << endl;
	}

	//Adding our bots into the game
	for (int i = 0; i < numberOfBots; i++) {
		Player p = Player();
		p.setAvailableCoins(startingCoins);
		p.setPlayerID(players.size() + 1);
		p.setIsNPC(true);
		//p.setGreedStrategy(GreedStrategy());
		players.push_back(p);
	}

	int oldNumberOfPlayers = numberOfPlayers;
	//Updating numberOfPlayers
	numberOfPlayers = numberOfPlayers + numberOfBots;
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
	cout << Map::instance()->getCountries().at(9).getCountryId();
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
		players[i].placeNewArmies(3, Map::instance()->getStartingCountry());
	}

	for (int i = 0; i < numberOfPlayers; i++) { // Display and verify initial army placement
		cout << "Player " << players[i].getPlayerID() << " starts with " << players[i].getAvailableArmies() << " armies and ";
		cout << players[i].getAvailableCities() << " cities, and placed 3 armies at the starting region, " << Map::instance()->getStartingCountry().getCountryId() << endl;
	}
	
	
	
	//this loop is for placing NPCs in a 2 player game.
	if (numberOfPlayers == 2) {
		

		cout << endl;
		Player npc = Player();
		npc.setAvailableArmies(10);
		npc.setPlayerID(3); //NPC is effectively player 3
		int selectCountry = 0;
		int placingPlayer = 1; //The player who gets to choose where to place the army
		for (int i = 0; i < npc.getAvailableArmies(); i++) {
			Map::instance()->showEverything(); //show the map so players can decide where to put NPC armies
			cout << "Player " << placingPlayer << ", choose a region to place non-player army: ";
			cin >> selectCountry;
			while (selectCountry > Map::instance()->getCountries().size() || selectCountry < 1) {
				cout << "Invalid Country ID. Try again: ";
				cin >> selectCountry;
			}
			npc.placeNewArmies(1, Map::instance()->giveMeCountry(selectCountry));
			//It's the next player's turn to place NPC armies
			if (placingPlayer == 1)
				placingPlayer = 2;
			else
				placingPlayer = 1;
		}
	}
	else {

	}

	Map::instance()->showEverything();
	cout << endl;

	//[Requirement 3: Give coins to players - we did this in part 1. Sorry!

	//[Requirement 4: Bidding System]

	// Step 1: Prompt each player to enter their bidding coins and their birthdate in the form of YYYYMMDD
	for (int i = 0; i < oldNumberOfPlayers; i++) {
		cin.clear(); //removing bad values from cin.
		cin.ignore();
		players[i].setBid(startingCoins);
		players[i].setBirthday();
	}

	// Create vectors and enter their values to be compared after. The appropriate values match with the appropriate player index
	vector<int> bids(numberOfPlayers);
	vector<int> dates(numberOfPlayers);
	for (int i = 0; i < oldNumberOfPlayers; i++) {
		bids[i] = players[i].getBid().getBidAmount();
		dates[i] = players[i].getBirthday();
	}

	//bots automatically bid 0 and are infinitely old, guaranteeing they don't start.
	for (int i = 0; i < players.size(); i++) {
		if (players[i].getIsNPC() == true) {
			bids[i] = 0;
			dates[i] = 0;
		}
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

	//Attaching Observers


	Statistics *s1 = new Statistics();
	Phases *ph1 = new Phases();

	Player *p1;
	p1 = &players[0];
	s1->setSubject(p1);
	ph1->setSubject(p1);

	Statistics *s2 = new Statistics();
	Phases *ph2 = new Phases();

	Player *p2;
	p2 = &players[1];
	s2->setSubject(p2);
	ph2->setSubject(p2);

	if (players.size() >= 3) {
		Statistics *s3 = new Statistics();
		Phases *ph3 = new Phases();

		Player *p3;
		p3 = &players[2];
		s3->setSubject(p3);
		ph3->setSubject(p3);
	}
	if (players.size() >= 4) {
		Statistics *s4 = new Statistics();
		Phases *ph4 = new Phases();

		Player *p4;
		p4 = &players[3];
		s4->setSubject(p4);
		ph4->setSubject(p4);
	}
	if (players.size() == 5) {
		Statistics *s5 = new Statistics();
		Phases *ph5 = new Phases();

		Player *p5;
		p5 = &players[4];
		s5->setSubject(p5);
		ph5->setSubject(p5);
	}

	//setting the first player to the bid winner
	int startingPlayer = maxIndex;

	int currentPlayer = startingPlayer; //Makes it so that starting player is the first "current player"
	int numberOfTurns; //At what turn the game end

	switch (numberOfPlayers) {
	case 2:
		numberOfTurns = 13;
		break;
	case 3:
		numberOfTurns = 11;
		break;
	case 4:
		numberOfTurns = 8;
		break;
	case 5:
		numberOfTurns = 7;
		break;
	}

	//Copy the players into the map so we can use it globally w/o passing as param																	
	vector<Player*> playersCopy;																																				
	for (int i = 0; i != players.size(); i++) {												
		playersCopy.push_back(&players[i]);													
	}																																								
	Map::instance()->setPlayers(playersCopy);												

	//This is the main game loop!
	for (int currentTurn = 0; currentTurn < numberOfTurns; currentTurn++) {

		//This loop ensures that each player goes once before the turn goes up by 1
		for (int numberOfPlayersWhoWent = 0; numberOfPlayersWhoWent < numberOfPlayers; numberOfPlayersWhoWent++) {

			cout << ":::::::::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
			cout << "::::::::::::It is currently Player " << currentPlayer + 1 << "'s turn::::::::::::" << endl;
			cout << ":::::::::::::::::::::::::::::::::::::::::::::::::::::::\n" << endl;

			//if it's the last turn, sets the "last turn" boolean inside the Player
			if (currentTurn == numberOfTurns - 1) {
				players[currentPlayer].setHandStatus(true);
			}


			deck.printDeck();
			if (!players[currentPlayer].getIsNPC()) {
				cout << "You have " << players[currentPlayer].getAvailableCoins() << " coins." << endl;
			}
			else {
				int yesOrNo = -1;
				yesOrNo = 1;
				cout << "NPCs Turn" << endl;
				if (yesOrNo == 1) {
					//Selects new strategy for bot
					yesOrNo = -1;
					while (yesOrNo != 1 && yesOrNo != 2) {
						cout << "Choose the bots strategy!" << endl;
						cout << "1: Greed Bot" << endl;
						cout << "2: Moderate Bot" << endl;
						if (yesOrNo != 1 && yesOrNo != 2) {
							cin >> yesOrNo;
						}
					}
					if (yesOrNo == 1) {
						players[currentPlayer].setGreedStrategy(GreedStrategy());
					}
					else {
						players[currentPlayer].setModerateStrategy(ModerateStrategy());
					}

				}
				else {

				}
			}
			Card chosenCard = Card(); //This will be used to determine what action to take.

			//Giving the player a choice of actions
			while (1) {
				int choice = 0;
				if (!players[currentPlayer].getIsNPC()) {
					cout << "\nWhat would you like to do: " << endl;
					cout << "1: View Map." << endl;
					cout << "2: See available cards again." << endl;
					cout << "3: See my hand." << endl;
					cout << "4: Pick a card." << endl;
					cout << "You are Player: " << currentPlayer+1 << endl; //tracing
					cin >> choice;
				}
				else {
					choice = 4;
					cout << "\nBOT CHOSE TO SELECT CARD 4\n" << endl;
				}
				if (choice == 1) //display the map
					Map::instance()->showEverything();
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
						if (!players[currentPlayer].getIsNPC()) {
							cout << "Select your card (1-6):" << endl;
							cin >> cardChoice;
						}							
						else {
							cardChoice = players[currentPlayer].getStrategy()->getCard(deck.getSpace(), players[currentPlayer].getAvailableCoins()) + 1;

						}

						if (cardChoice == 1) {
							chosenCard = deck.getSpace()[cardChoice - 1];

							vector<Card> v = players[currentPlayer].getHand();
							v.push_back(chosenCard);
							//WELTON+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							//====================================================================================

							players[currentPlayer].setHand(v);
							deck.removeCard(cardChoice);
							/////////////////////////////////////////////////////////////////////////////////////
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
			//cout << "Time to do the action of your card" << endl;
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
				if (!players[currentPlayer].getIsNPC()) {
					cout << "You have " << numberOfActions << " actions remaining. You have the following choices: " << endl;
					if (cardActionUsed != 1)
						cout << "1: " << chosenCard.formatAction(chosenCard.getAction1(), to_string(chosenCard.getNumA1())) << endl;
					else
						cout << "1: No action Available" << endl;

					if ((chosenCard.getOperator() == "or" || chosenCard.getOperator() == "and") && cardActionUsed != 2) {
						multipleChoices = true;
						cout << chosenCard.getOperator() << endl;
						cout << "2:" << chosenCard.formatAction(chosenCard.getAction2(), to_string(chosenCard.getNumA2())) << endl;
					}
					else {
						cout << "2: No action available" << endl;
					}
					cout << "3: Ignore action" << endl;
					cin >> playerChoice;
				}
				else {
					playerChoice = players[currentPlayer].getStrategy()->getChoice(chosenCard) + 1;
					if (playerChoice == 1 && cardActionUsed == 1)
						playerChoice = 2;
					if (playerChoice == 2 && cardActionUsed == 2)
						playerChoice = 1;
				}
				

				if (playerChoice == 1 && cardActionUsed != 1) {
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
							int regionToBuildIn = -1;
							if (players[currentPlayer].getAvailableCities() > 0) {
								if (!players[currentPlayer].getIsNPC()) {
									cout << "Place your city!: " << endl;
								}
								
								
								if (players[currentPlayer].getArmyLocationsForCity(*Map::instance()).size() > 0) {
									if (players[currentPlayer].getArmyLocationsForCity(*Map::instance()).size() == 1)
										regionToBuildIn = 1;
									else
										regionToBuildIn = random(1, players[currentPlayer].getArmyLocationsForCity(*Map::instance()).size());
									while (regionToBuildIn > players[currentPlayer].getArmyLocationsForCity(*Map::instance()).size() || regionToBuildIn < 1) {
										cout << "Here are your options: " << endl;
										for (int playerCityOptions = 0; playerCityOptions < players[currentPlayer].getArmyLocationsForCity(*Map::instance()).size(); playerCityOptions++) {
											cout << playerCityOptions + 1 << ": Build in Country " << players[currentPlayer].getArmyLocationsForCity(*Map::instance())[playerCityOptions] << endl;
										}
										if (regionToBuildIn > players[currentPlayer].getArmyLocationsForCity(*Map::instance()).size() || regionToBuildIn < 1)
											cin >> regionToBuildIn;

									}
									if (!players[currentPlayer].getIsNPC())
									cout << "Building a city here: Country " << players[currentPlayer].getArmyLocationsForCity(*Map::instance())[regionToBuildIn - 1] << endl;
									Country countryToBuildCityIn = Map::instance()->getCountries()[players[currentPlayer].getArmyLocationsForCity(*Map::instance())[regionToBuildIn - 1] - 1];
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
								if (players[currentPlayer].getArmyLocations(*Map::instance()).size() > 0) {
									int moveChoice = -1;
									if (players[currentPlayer].getIsNPC()) {
										moveChoice = random(1, players[currentPlayer].getArmyLocations(*Map::instance()).size());
									}
									else {
										while (moveChoice > players[currentPlayer].getArmyLocations(*Map::instance()).size() || moveChoice < 1) {
											for (int i = 0; i < players[currentPlayer].getArmyLocations(*Map::instance()).size(); i++) {
												cout << i + 1 << ": Country " << Map::instance()->getCountries()[players[currentPlayer].getArmyLocations(*Map::instance())[i] - 1].getCountryId() << endl;
											}
											if (moveChoice > players[currentPlayer].getArmyLocations(*Map::instance()).size() || moveChoice < 1) {
												cin >> moveChoice;
											}

										}
										cout << "Here are your adjacent countries you can move into from Country " << players[currentPlayer].getArmyLocations(*Map::instance())[moveChoice - 1] << endl;
									}									
									int continentId = Map::instance()->getCountries()[players[currentPlayer].getArmyLocations(*Map::instance())[moveChoice - 1] - 1].getContinentId();
									vector<int> countriesOnSameContinent = vector<int>(0);
									for (int i = 0; i < Map::instance()->getCountries()[players[currentPlayer].getArmyLocations(*Map::instance())[moveChoice - 1] - 1].returnAdjacencies(GameMap).size(); i++) {
										if (Map::instance()->getCountries()[Map::instance()->getCountries()[players[currentPlayer].getArmyLocations(*Map::instance())[moveChoice - 1] - 1].returnAdjacencies(GameMap).at(i)].getContinentId() == continentId) {
											countriesOnSameContinent.push_back(Map::instance()->getCountries()[players[currentPlayer].getArmyLocations(*Map::instance())[moveChoice - 1] - 1].returnAdjacencies(GameMap).at(i));
										}
									}

									int countryDest = -1;
									if (players[currentPlayer].getIsNPC()) {
										countryDest = random(1, countriesOnSameContinent.size());
									}
									else {
										while (countryDest > countriesOnSameContinent.size() || countryDest < 1) {
											for (int i = 0; i < countriesOnSameContinent.size(); i++) {
												cout << i + 1 << ": Country " << countriesOnSameContinent[i] << endl;

											}

											if (countryDest > countriesOnSameContinent.size() || countryDest < 1)
												cin >> countryDest;
										}
									}
									

									players[currentPlayer].moveArmies(1, Map::instance()->getCountries()[players[currentPlayer].getArmyLocations(*Map::instance())[moveChoice - 1] - 1], Map::instance()->getCountries()[countriesOnSameContinent[countryDest - 1] - 1]);
									Map::instance()->setCountry(Map::instance()->getCountries());

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
								if (players[currentPlayer].getArmyLocations(*Map::instance()).size() > 0) {
									int moveChoice = -1;
									if (players[currentPlayer].getIsNPC()) {
										moveChoice = random(1, players[currentPlayer].getArmyLocations(*Map::instance()).size());
									}
									while (moveChoice > players[currentPlayer].getArmyLocations(*Map::instance()).size() || moveChoice < 1) {
										for (int i = 0; i < players[currentPlayer].getArmyLocations(*Map::instance()).size(); i++) {
											cout << i + 1 << ": Country " << Map::instance()->getCountries()[players[currentPlayer].getArmyLocations(*Map::instance())[i] - 1].getCountryId() << endl;
										}
										if (moveChoice > players[currentPlayer].getArmyLocations(*Map::instance()).size() || moveChoice < 1) {
											cin >> moveChoice;
										}

									}
									cout << "Here are your adjacent countries you can move into from Country " << players[currentPlayer].getArmyLocations(*Map::instance())[moveChoice - 1] << endl;
									int continentId = Map::instance()->getCountries()[players[currentPlayer].getArmyLocations(*Map::instance())[moveChoice - 1] - 1].getContinentId();


									int countryDest = -1;
									if (players[currentPlayer].getIsNPC()) {
										countryDest = random(1, Map::instance()->getCountries()[players[currentPlayer].getArmyLocations(*Map::instance())[moveChoice - 1] - 1].returnAdjacencies(GameMap).size() + 1);
									}
									while (countryDest > Map::instance()->getCountries()[players[currentPlayer].getArmyLocations(*Map::instance())[moveChoice - 1] - 1].returnAdjacencies(GameMap).size() || countryDest < 1) {
										for (int i = 0; i < Map::instance()->getCountries()[players[currentPlayer].getArmyLocations(*Map::instance())[moveChoice - 1] - 1].returnAdjacencies(GameMap).size(); i++) {
											cout << i + 1 << ": Country " << Map::instance()->getCountries()[players[currentPlayer].getArmyLocations(*Map::instance())[moveChoice - 1] - 1].returnAdjacencies(GameMap).at(i) << endl;
										}

										if (countryDest > Map::instance()->getCountries()[players[currentPlayer].getArmyLocations(*Map::instance())[moveChoice - 1] - 1].returnAdjacencies(GameMap).size() || countryDest < 1)
											cin >> countryDest;
									}

									players[currentPlayer].moveArmies(1, Map::instance()->getCountries()[players[currentPlayer].getArmyLocations(*Map::instance())[moveChoice - 1] - 1], Map::instance()->getCountries()[Map::instance()->getCountries()[players[currentPlayer].getArmyLocations(*Map::instance())[moveChoice - 1] - 1].returnAdjacencies(GameMap).at(countryDest - 1) - 1]);
									Map::instance()->setCountry(Map::instance()->getCountries());

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
								cout << players[currentPlayer].getAvailableArmies() << " :Available Armies" << endl;
								if (players[currentPlayer].getAvailableArmies() > 0) {
									int spawnChoice = -1;
									if (players[currentPlayer].getIsNPC()) {
										spawnChoice = random(1, players[currentPlayer].getArmySpawnLocations(*Map::instance()).size());
									}
									else {
										cout << "You may place " << innerCounter << " armies at the following locations: " << endl;
										while (spawnChoice > players[currentPlayer].getArmySpawnLocations(*Map::instance()).size() || spawnChoice < 1) {
											for (int i = 0; i < players[currentPlayer].getArmySpawnLocations(*Map::instance()).size(); i++) {
												//cout << i + 1 << ": Country " << Map::instance()->getCountries()[players[currentPlayer].getArmySpawnLocations(*Map::instance()).at(i)].getCountryId() << endl;
												cout << i + 1 << ": Country " << players[currentPlayer].getArmySpawnLocations(*Map::instance())[i] << endl;
											}

											if (spawnChoice > players[currentPlayer].getArmySpawnLocations(*Map::instance()).size() || spawnChoice < 1) {
												cin >> spawnChoice;
											}


										}
									}
									

									Country updatedCountry = Map::instance()->getCountries()[players[currentPlayer].getArmySpawnLocations(*Map::instance())[spawnChoice - 1] - 1];
									players[currentPlayer].placeNewArmies(1, updatedCountry);

									innerCounter--;
								}
								else {
									cout << "You do not have anymore armies!" << endl;
									innerCounter = 0;
								}



							}

						}
						else if (chosenCard.getAction1() == "destroy") {

							while (innerCounter > 0) {
								//First getting all players
								players[currentPlayer].getPlayerID();
								vector<int> playersTargeted = vector<int>(0);
								for (int i = 0; i < players.size(); i++) {
									if (i != players[currentPlayer].getPlayerID() - 1 && players.at(i).getArmyLocations(*Map::instance()).size() > 0) {
										playersTargeted.push_back(i);
									}
								}

								int playerSelected = -1;
								if (players[currentPlayer].getIsNPC()) {
									playerSelected = random(1, playersTargeted.size());
								}
								if (playersTargeted.size() > 0) {
									while (playerSelected > playersTargeted.size() || playerSelected < 1) {
										cout << "Choose player you want to remove armies from: " << endl;
										for (int i = 0; i < playersTargeted.size(); i++) {
											cout << i + 1 << ": Player " << playersTargeted[i] + 1 << endl;
											}
											if (playerSelected > playersTargeted.size() && playerSelected < 1) {
												cin >> playerSelected;
												vector<int> playerArmiesToDestroy = vector<int>(0);
												playerArmiesToDestroy = players[playerSelected - 1].getArmyLocations(*Map::instance());
												int regionSelected = -1;
												if (players[currentPlayer].getIsNPC()) {
													regionSelected = random(1, playerArmiesToDestroy.size());
												}
												while (regionSelected > playerArmiesToDestroy.size() || regionSelected < 1) {
													cout << "Choose Player " << playerSelected << "'s country of armies to destroy" << endl;
													for (int i = 0; i < playerArmiesToDestroy.size(); i++) {
														cout << i + 1 << ": Country: " << playerArmiesToDestroy.at(i) << endl;
													}
													if (regionSelected > playerArmiesToDestroy.size() || regionSelected < 1) {
														cin >> regionSelected;
													}
												}
												cout << "Destroying player armies" << endl;
												players[currentPlayer].destroyArmy(Map::instance()->getCountries()[playerArmiesToDestroy[regionSelected - 1] - 1], players[playerSelected - 1]);
												innerCounter--;
												//playersTargeted = vector<int>(0);
												
											}
									}
								}
								else {
									cout << "There are no available armies to destroy!" << endl;
									innerCounter = 0;
								}
							}
						}
						innerCounter--;
					}
					numberOfActions -= 1;

				}

				else if (playerChoice == 2 && cardActionUsed != 2) {
					if (multipleChoices) {
						cardActionUsed = playerChoice;
					}
					int innerCounter = chosenCard.getNumA1();
					while (innerCounter > 0) {
						if (chosenCard.getAction2() == "build") {
							//Prompt player to build city
							//Looks for all countries that a player owns
							cin.clear();
							cin.ignore();
							int regionToBuildIn = -1;
							if (players[currentPlayer].getAvailableCities() > 0) {
								if (!players[currentPlayer].getIsNPC()) {
									cout << "Place your city!: " << endl;
								}


								if (players[currentPlayer].getArmyLocationsForCity(*Map::instance()).size() > 0) {
									if (players[currentPlayer].getArmyLocationsForCity(*Map::instance()).size() == 1)
										regionToBuildIn = 1;
									else
										regionToBuildIn = random(1, players[currentPlayer].getArmyLocationsForCity(*Map::instance()).size());
									while (regionToBuildIn > players[currentPlayer].getArmyLocationsForCity(*Map::instance()).size() || regionToBuildIn < 1) {
										cout << "Here are your options: " << endl;
										for (int playerCityOptions = 0; playerCityOptions < players[currentPlayer].getArmyLocationsForCity(*Map::instance()).size(); playerCityOptions++) {
											cout << playerCityOptions + 1 << ": Build in Country " << players[currentPlayer].getArmyLocationsForCity(*Map::instance())[playerCityOptions] << endl;
										}
										if (regionToBuildIn > players[currentPlayer].getArmyLocationsForCity(*Map::instance()).size() || regionToBuildIn < 1)
											cin >> regionToBuildIn;

									}
									if (!players[currentPlayer].getIsNPC())
										cout << "Building a city here: Country " << players[currentPlayer].getArmyLocationsForCity(*Map::instance())[regionToBuildIn - 1] << endl;
									Country countryToBuildCityIn = Map::instance()->getCountries()[players[currentPlayer].getArmyLocationsForCity(*Map::instance())[regionToBuildIn - 1] - 1];
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
						else if (chosenCard.getAction2() == "move") {
							while (innerCounter > 0) {
								cout << "You can move " << innerCounter << " armies" << endl;
								cout << "You have armies in the following countries: " << endl;
								//Loading valid players armies:
								if (players[currentPlayer].getArmyLocations(*Map::instance()).size() > 0) {
									int moveChoice = -1;
									if (players[currentPlayer].getIsNPC()) {
										moveChoice = random(1, players[currentPlayer].getArmyLocations(*Map::instance()).size());
									}
									else {
										while (moveChoice > players[currentPlayer].getArmyLocations(*Map::instance()).size() || moveChoice < 1) {
											for (int i = 0; i < players[currentPlayer].getArmyLocations(*Map::instance()).size(); i++) {
												cout << i + 1 << ": Country " << Map::instance()->getCountries()[players[currentPlayer].getArmyLocations(*Map::instance())[i] - 1].getCountryId() << endl;
											}
											if (moveChoice > players[currentPlayer].getArmyLocations(*Map::instance()).size() || moveChoice < 1) {
												cin >> moveChoice;
											}

										}
										cout << "Here are your adjacent countries you can move into from Country " << players[currentPlayer].getArmyLocations(*Map::instance())[moveChoice - 1] << endl;
									}
									int continentId = Map::instance()->getCountries()[players[currentPlayer].getArmyLocations(*Map::instance())[moveChoice - 1] - 1].getContinentId();
									vector<int> countriesOnSameContinent = vector<int>(0);
									for (int i = 0; i < Map::instance()->getCountries()[players[currentPlayer].getArmyLocations(*Map::instance())[moveChoice - 1] - 1].returnAdjacencies(GameMap).size(); i++) {
										if (Map::instance()->getCountries()[Map::instance()->getCountries()[players[currentPlayer].getArmyLocations(*Map::instance())[moveChoice - 1] - 1].returnAdjacencies(GameMap).at(i)].getContinentId() == continentId) {
											countriesOnSameContinent.push_back(Map::instance()->getCountries()[players[currentPlayer].getArmyLocations(*Map::instance())[moveChoice - 1] - 1].returnAdjacencies(GameMap).at(i));
										}
									}

									int countryDest = -1;
									if (players[currentPlayer].getIsNPC()) {
										countryDest = random(1, countriesOnSameContinent.size());
									}
									else {
										while (countryDest > countriesOnSameContinent.size() || countryDest < 1) {
											for (int i = 0; i < countriesOnSameContinent.size(); i++) {
												cout << i + 1 << ": Country " << countriesOnSameContinent[i] << endl;

											}

											if (countryDest > countriesOnSameContinent.size() || countryDest < 1)
												cin >> countryDest;
										}
									}


									players[currentPlayer].moveArmies(1, Map::instance()->getCountries()[players[currentPlayer].getArmyLocations(*Map::instance())[moveChoice - 1] - 1], Map::instance()->getCountries()[countriesOnSameContinent[countryDest - 1] - 1]);
									Map::instance()->setCountry(Map::instance()->getCountries());

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
								if (players[currentPlayer].getArmyLocations(*Map::instance()).size() > 0) {
									int moveChoice = -1;
									if (players[currentPlayer].getIsNPC()) {
										moveChoice = random(1, players[currentPlayer].getArmyLocations(*Map::instance()).size());
									}
									while (moveChoice > players[currentPlayer].getArmyLocations(*Map::instance()).size() || moveChoice < 1) {
										for (int i = 0; i < players[currentPlayer].getArmyLocations(*Map::instance()).size(); i++) {
											cout << i + 1 << ": Country " << Map::instance()->getCountries()[players[currentPlayer].getArmyLocations(*Map::instance())[i] - 1].getCountryId() << endl;
										}
										if (moveChoice > players[currentPlayer].getArmyLocations(*Map::instance()).size() || moveChoice < 1) {
											cin >> moveChoice;
										}

									}
									cout << "Here are your adjacent countries you can move into from Country " << players[currentPlayer].getArmyLocations(*Map::instance())[moveChoice - 1] << endl;
									int continentId = Map::instance()->getCountries()[players[currentPlayer].getArmyLocations(*Map::instance())[moveChoice - 1] - 1].getContinentId();


									int countryDest = -1;
									if (players[currentPlayer].getIsNPC()) {
										countryDest = random(1, Map::instance()->getCountries()[players[currentPlayer].getArmyLocations(*Map::instance())[moveChoice - 1] - 1].returnAdjacencies(GameMap).size());
									}
									while (countryDest > Map::instance()->getCountries()[players[currentPlayer].getArmyLocations(*Map::instance())[moveChoice - 1] - 1].returnAdjacencies(GameMap).size() || countryDest < 1) {
										for (int i = 0; i < Map::instance()->getCountries()[players[currentPlayer].getArmyLocations(*Map::instance())[moveChoice - 1] - 1].returnAdjacencies(GameMap).size(); i++) {
											cout << i + 1 << ": Country " << Map::instance()->getCountries()[players[currentPlayer].getArmyLocations(*Map::instance())[moveChoice - 1] - 1].returnAdjacencies(GameMap).at(i) << endl;
										}

										if (countryDest > Map::instance()->getCountries()[players[currentPlayer].getArmyLocations(*Map::instance())[moveChoice - 1] - 1].returnAdjacencies(GameMap).size() || countryDest < 1)
											cin >> countryDest;
									}

									players[currentPlayer].moveArmies(1, Map::instance()->getCountries()[players[currentPlayer].getArmyLocations(*Map::instance())[moveChoice - 1] - 1], Map::instance()->getCountries()[Map::instance()->getCountries()[players[currentPlayer].getArmyLocations(*Map::instance())[moveChoice - 1] - 1].returnAdjacencies(GameMap).at(countryDest - 1) - 1]);
									Map::instance()->setCountry(Map::instance()->getCountries());

									innerCounter--;
								}
								else {
									cout << "Sorry you have no armies available!" << endl;
								}
							}

						}//End PLACE
						else if (chosenCard.getAction2() == "place") {
							//Place armies. 
							while (innerCounter > 0) {
								cout << players[currentPlayer].getAvailableArmies() << " :Available Armies" << endl;
								if (players[currentPlayer].getAvailableArmies() > 0) {
									int spawnChoice = -1;
									if (players[currentPlayer].getIsNPC()) {
										spawnChoice = random(1, players[currentPlayer].getArmySpawnLocations(*Map::instance()).size());
									}
									else
										cout << "You may place " << innerCounter << " armies at the following locations: " << endl;
									while (spawnChoice > players[currentPlayer].getArmySpawnLocations(*Map::instance()).size() || spawnChoice < 1) {
										for (int i = 0; i < players[currentPlayer].getArmySpawnLocations(*Map::instance()).size(); i++) {
											//cout << i + 1 << ": Country " << Map::instance()->getCountries()[players[currentPlayer].getArmySpawnLocations(*Map::instance()).at(i)].getCountryId() << endl;
											cout << i + 1 << ": Country " << players[currentPlayer].getArmySpawnLocations(*Map::instance())[i] << endl;
										}

										if (spawnChoice > players[currentPlayer].getArmySpawnLocations(*Map::instance()).size() || spawnChoice < 1) {
											cin >> spawnChoice;
										}


									}

									Country updatedCountry = Map::instance()->getCountries()[players[currentPlayer].getArmySpawnLocations(*Map::instance())[spawnChoice - 1] - 1];
									players[currentPlayer].placeNewArmies(1, updatedCountry);

									innerCounter--;
								}
								else {
									cout << "You do not have anymore armies!" << endl;
									innerCounter = 0;
								}



							}

						}
						else if (chosenCard.getAction2() == "destroy") {

							while (innerCounter > 0) {
								//First getting all players
								players[currentPlayer].getPlayerID();
								vector<int> playersTargeted = vector<int>(0);
								for (int i = 0; i < players.size(); i++) {
									if (i != players[currentPlayer].getPlayerID() - 1 && players.at(i).getArmyLocations(*Map::instance()).size() > 0) {
										playersTargeted.push_back(i);
									}
								}

								int playerSelected = -1;
								if (players[currentPlayer].getIsNPC()) {
									playerSelected = random(1, playersTargeted.size());
								}
								if (playersTargeted.size() > 0) {
									while (playerSelected > playersTargeted.size() || playerSelected < 1) {
										cout << "Choose player you want to remove armies from: " << endl;
										for (int i = 0; i < playersTargeted.size(); i++) {
											cout << i + 1 << ": Player " << playersTargeted[i] + 1 << endl;
										}
										if (playerSelected > playersTargeted.size() && playerSelected < 1) {
											cin >> playerSelected;
											vector<int> playerArmiesToDestroy = vector<int>(0);
											playerArmiesToDestroy = players[playerSelected - 1].getArmyLocations(*Map::instance());
											int regionSelected = -1;
											if (players[currentPlayer].getIsNPC()) {
												regionSelected = random(1, playerArmiesToDestroy.size());
											}
											while (regionSelected > playerArmiesToDestroy.size() || regionSelected < 1) {
												cout << "Choose Player " << playerSelected << "'s country of armies to destroy" << endl;
												for (int i = 0; i < playerArmiesToDestroy.size(); i++) {
													cout << i + 1 << ": Country: " << playerArmiesToDestroy.at(i) << endl;
												}
												if (regionSelected > playerArmiesToDestroy.size() || regionSelected < 1) {
													cin >> regionSelected;
												}
											}
											cout << "Destroying player armies" << endl;
											players[currentPlayer].destroyArmy(Map::instance()->getCountries()[playerArmiesToDestroy[regionSelected - 1] - 1], players[playerSelected - 1]);
											innerCounter--;
											//playersTargeted = vector<int>(0);

										}
									}
								}
								else {
									cout << "There are no available armies to destroy!" << endl;
									innerCounter = 0;
								}
							}
						}
						innerCounter--;
					}
					numberOfActions -= 1;
					
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

	//:::::::::::::::::::::::::::::::::::PART 6::::::::::::::::::::::::::::::::::::::::::::::

	vector<int> scores;
	cout << "============================================================";
	cout << "\n\n======================= FINAL SCORES =======================\n\n";
	cout << "============================================================\n";

	for (int i = 0; i < players.size(); i++) //push to scores vector for winner computation
	{ 
	scores.push_back(players.at(i).computeScore(*Map::instance())); 
	//i0 = p1 score, i1 = p2 score, i2 = p3 score, etc
	}

	for (int i = 0; i < players.size(); i++) //display final results table
	{
		cout << "\nPLAYER " << i+1 << ": " << endl;
		cout << "Victory Points:		" << scores[i] << endl;
		cout << "Cards:			" << players.at(i).getHand().size() << endl;
		cout << "Coins:			" << players.at(i).getAvailableCoins() << endl;
	}

	declareWinner(scores, players);
	
}

const int random(int min, int max) { //range : [min, max)
	static bool first = true;
	if (first)
	{
		srand(time(NULL));
		first = false;
	}
	return min + rand() % ((max + 1) - min);
}
	
	//int winnerID = (getWinner(scores, players).getPlayerID()) + 1;

	/*try {
		cout << "\n\n\n\n CONGRATS PLAYER" << getWinner(scores, players).getPlayerID() << ". YOU WIN!!!";		
	}
	catch (string std) {
		cout << std;
	}*/
	
