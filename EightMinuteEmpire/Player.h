#pragma once
#include "stdafx.h"
#ifndef Player_h
#define Player_h

#include <string>
#include "Country.h"
#include <vector>

using namespace std;

class Player {
private:
	int playerID;
	int regionsOwned;
	vector<int> countriesOwned;

public:
	//void claimCountry();		//basically a setter


	//void PayCoin();
	void placeNewArmies(int num_Armies, int countryID);
	void moveArmies(int num_Armies, int originID, int destinationID);
	//void MoveOverLand();
	//void BuildCity();
	//void DestroyArmy();

	void getCountriesOwned();
		

	//void setCountriesOwned();


	void setPlayerID(int x);
	int getPlayerID();
};







#endif