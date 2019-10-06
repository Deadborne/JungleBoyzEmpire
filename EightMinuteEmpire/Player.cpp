#pragma once

#include "stdafx.h"
#include "Player.h"
#include "Map.h"

using namespace std;

void Player::setPlayerID(int x) {
	playerID = x;
}

int Player::getPlayerID() {
	return playerID;
}


void Player::getCountriesOwned() {
	Map m = Map();				//Start the map
	vector<Country> allCountries = m.getCountries();			//
	
	vector<int> countriesOwned;	//This is where we will store countries owned by a player 

	//Take the vector of country objects
	//Loop through countries
	for (int i = 0; i <= allCountries.size(); i++) {
		//Get the army vector for each country
		vector<int> armies = allCountries.at(i).getArmiesPerPlayer();
		vector<int>::iterator maxElement = max_element(armies.begin(), armies.end());
		
		//Position of largest value
		int ownerIndex = std::distance(armies.begin(), maxElement);

		//If the playerID is the same as the index with the most armies
		if (playerID == ownerIndex + 1) {
			//Then add that country to the player's owned countries
			countriesOwned.push_back(allCountries.at(i).getCountryId());

		}







	}


		//getArmiesPerPlayer vector
			
			//ownerIndex = Get the index of the largest value 
			//if (getPlayerID == ownerIndex)
				//Add countryID to countriesOwned vector

	/*for (int i = 0; i <=  ) {
		
	}*/



	
}