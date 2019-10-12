#pragma once
#include "stdafx.h"
#ifndef Player_h
#define Player_h

#include <string>
#include "Country.h"
#include <vector>

using namespace std;
typedef boost::adjacency_list<listS, vecS, undirectedS> Graph;

class Player {
private:
	int playerID;
	int regionsOwned;
	vector<int> countriesOwned;



	int availableArmies;		//Armies in player's bank [should be 14 at game start]
	int availableCities;		//Cities in player's bank [should be 3 at game start]
	int availableCoins;					//Coins in player's bank [should be 8(5p), 9(4p), 11(3p), 14(2p) at game start]


	Bid *playerBid;
	//----TODO----//
	//Player needs to own a hand of cards

public:
	
	//----Wish List----//
	//void claimCountry();
	//void setCountriesOwned();
	
	void OLDdestroyCity(int cityLocationID, Player cityOwner);
	void destroyCity(Country& cityLocation, Player& cityOwner);

	//----Required Functions----//
	void PayCoin();
	void OLDplaceNewArmies(int num_Armies, int countryID);
	void placeNewArmies(int numArmies, Country& country);
	void OLDmoveArmies(int num_Armies, int originID, int destinationID);
	void moveArmies(int numArmies, Country& origin, Country& destination);
	void moveOverLand(int numArmies, Country& origin, Country& destination, Graph gameGraph);		//MoveArmies if we are adjacent on land
	void OLDbuildCity(int cityLocationID);
	void buildCity(Country& cityLocation);

	void destroyArmy(Country& armyLocation, Player armyOwner);


	vector<int> getCountriesOwned();
		

	

	//----Mutators & Accessors----//
	int getAvailableCities();
	void setAvailableCities(int x);

	void setPlayerID(int x);
	int getPlayerID();

	void setAvailableCoins(int x);

	int getAvailableArmies();
	void setAvailableArmies(int x);

	bool hasCityIn(Country& country);

	void setBid();
};







#endif