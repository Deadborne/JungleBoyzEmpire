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
		//Get the larg
		vector<int>::iterator maxElement = max_element(armies.begin(), armies.end());
		
		bool duplicatesExist = false;

		
		//THIS FOR LOOP IS BROKEN
		//Having issues getting the actual max element so we can check if duplicates match the max, meaning nobody owns this country.
		//Does our matrix have duplicates? Does it therefore have an owner?
		for (int i = 0; i < (armies.size() && (duplicatesExist== false)); i++) {
			for (int j = i + 1; j < armies.size(); j++) {

				//If there are duplicates in the array and one of them is equal to 
				if (    (armies.at(i) == armies.at(j) ) && ( armies.at(i) == (*max_element(armies.begin(), armies.end()))    )) {
					duplicatesExist = true;
				}

			}

		}
	
		
		//if the maxElement has a duplicate 
		if (duplicatesExist == false) {
			//Position of largest value
			int ownerIndex = std::distance(armies.begin(), maxElement);

			//If the playerID is the same as the index with the most armies
			if (playerID == ownerIndex + 1) {
				//Then add that country to the player's owned countries
				countriesOwned.push_back(allCountries.at(i).getCountryId());
			}
		}


		

	}


	


	
}