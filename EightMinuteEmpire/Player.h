#pragma once
#include "stdafx.h"
#include "Bid.h"
#ifndef Player_h
#define Player_h
#include "Bid.h"
#include "Card.h"
#include <string>
#include "Country.h"
#include "Continent.h"
#include "Map.h"
#include "Subject.h"
#include "Strategy.h"
#include <vector>
#include <string>
#include <algorithm>
class Map;

using namespace std;
typedef boost::adjacency_list<listS, vecS, undirectedS> Graph;

class Player : public Subject {
private:
	int* playerID;
	int* birthday;
	Hand *hand;

	//The following vectors are dummies for future use
	//vector<int>* continentsOwned;

	int *availableArmies;					//Armies in player's bank [should be 14 at game start]
	int *availableCities;					//Cities in player's bank [should be 3 at game start]
	int *availableCoins;					//Coins in player's bank [should be 8(5p), 9(4p), 11(3p), 14(2p) at game start]


	Bid *playerBid;
	bool *reachedHandLimit = new bool(false);
	Strategy* strategy;
	bool *isNPC;
	int* finalScore;
	
public:
	vector<int> getArmyLocations(Map m);
	vector<int> getArmyLocationsForCity(Map m);

	vector<int> getArmySpawnLocations(Map m);
	
	//--- Bidding --- //

	~Player();
	
	void destroyCity(Country& cityLocation, Player& cityOwner);
	//vector<int> getCountriesOwned();

	//----Required Functions----//
	void PayCoin();
	void PayCoin(int numCoins);
	void placeNewArmies(int numArmies, Country& country);
	void moveArmies(int numArmies, Country& origin, Country& destination);
	void moveOverLand(int numArmies, Country& origin, Country& destination, Graph gameGraph);
	void buildCity(Country& cityLocation);
	void destroyArmy(Country& armyLocation, Player armyOwner);

	bool isContinentOwner(int continentID, Map m);
	bool isCountryOwner(Country& country);

	vector<Country> getCountriesOwned(Map m);

	vector<int> getContinentsOwned(Map m);

	int pointsFromCards();

	int computeScore(Map m);


	//----Mutators & Accessors----//
	int getAvailableCities();
	void setAvailableCities(int x);
	
	void setPlayerID(int x);
	int getPlayerID();

	void setBirthday();
	int getBirthday();

	int getAvailableArmies();
	void setAvailableArmies(int x);

	int getAvailableCoins();
	void setAvailableCoins(int x);

	vector<Card> getHand();
	void setHand(vector<Card> v);

	void initializeHand();
	void printHand();

	bool hasCityIn(Country& country);
	vector<int> armyLocations(Map m);

	int getFinalScore();
	void setFinalScore(int x);

	void setBid();
	void setBid(int maxBid);
	Bid getBid();

	void setHandStatus(bool s);
	bool checkIfReachedHandLimit();


	int andOrAction(int actionNumber);
	void ignore();

	void setGreedStrategy(GreedStrategy _startegy);
	void setModerateStrategy(ModerateStrategy _startegy);
	Strategy* getStrategy();

	
	


	void setIsNPC(bool isNPC);
	bool getIsNPC();

	



};



#endif