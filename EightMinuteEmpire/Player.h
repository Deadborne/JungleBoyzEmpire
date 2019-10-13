#pragma once
#include "stdafx.h"
#include "Bid.h"
#ifndef Player_h
#define Player_h

#include <string>
#include "Country.h"
#include <vector>
#include <string>

using namespace std;
typedef boost::adjacency_list<listS, vecS, undirectedS> Graph;

class Player {
private:
	int* playerID;


	vector<int> continentsOwned;
	vector<int> countriesOwned;

	vector<string> HandOfCards = { "card1", "card2", "card3", "card4" };



	int *availableArmies;					//Armies in player's bank [should be 14 at game start]
	int *availableCities;					//Cities in player's bank [should be 3 at game start]
	int *availableCoins;					//Coins in player's bank [should be 8(5p), 9(4p), 11(3p), 14(2p) at game start]


	Bid *playerBid;

	
	//This is the member function for the Hand, once it is implemented and synced w/ my branch
	//Hand *hand;
	
	
	
	//----TODO----//
	//Player needs to own a hand of cards

public:
	
	//----Wish List----//
	//void claimCountry();
	//void setCountriesOwned();
	
	
	void destroyCity(Country& cityLocation, Player& cityOwner);
	vector<int> getCountriesOwned();

	//----Required Functions----//
	void PayCoin();
	void placeNewArmies(int numArmies, Country& country);
	void moveArmies(int numArmies, Country& origin, Country& destination);
	void moveOverLand(int numArmies, Country& origin, Country& destination, Graph gameGraph);
	void buildCity(Country& cityLocation);
	void destroyArmy(Country& armyLocation, Player armyOwner);

	//----Mutators & Accessors----//
	int getAvailableCities();
	void setAvailableCities(int x);
	
	void setPlayerID(int x);
	int getPlayerID();

	

	int getAvailableArmies();
	void setAvailableArmies(int x);

	int getAvailableCoins();
	void setAvailableCoins(int x);

	bool hasCityIn(Country& country);

	void setBid();
	Bid getBid();


};



#endif