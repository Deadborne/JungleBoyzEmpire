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
	vector<Country> allCountries = m.getCountries();
	
	//This is where we will store countries owned by a player 
	vector<int> countriesOwned;	

	//Take the vector of country objects
	//Loop through countries
	for (int i = 0; i <= allCountries.size(); i++) {
		//Get the army vector for each country
		vector<int> armies = allCountries.at(i).getArmiesPerPlayer();
		//Get the largest element in the vector
		vector<int>::iterator maxElement = max_element(armies.begin(), armies.end());
		bool duplicatesExist = false;

		
		//-----THIS PART OF THE FUNCTION HAS NOT BEEN TESTED-----//
		//Does our matrix have duplicates? Does it therefore have an owner?
		for (int i = 0; i < (armies.size() && (duplicatesExist== false)); i++) {
			for (int j = i + 1; j < armies.size(); j++) {

				//If there are duplicates in the array and one of them is equal to 
				if ((armies.at(i) == armies.at(j)) && (armies.at(i) == *maxElement)) {
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


//This function will allow you to place any given number of new armies in any country
//As such, it ignores game rules:
//	1. Each player can place 3 new armies in the starting country at game start
//	2. Number of armies player can place is determined by the card he/she has drawn
//	3. Player can only place new armies in countries where they own a city 
void Player::placeNewArmies(int num_Armies, int countryID) {
	Map m = Map();		

	//Get armiesPerPlayer vector for desired country
	vector<int> armies = m.getCountries().at(countryID).getArmiesPerPlayer();

	//Add however many armies player wants to the appropriate index
	armies.at(playerID - 1) += num_Armies;

	//FOR REFERENCE
	//Player ID correspondance with army vector: 
	//			{0, 1, 2, 0, 0}
	//			 ^  ^  ^  ^  ^
	//			 P1 P2 P3 P4 P5
	//This assumes implementation doesn't have a player ID '0'

	
}

//Takes an originID and destinationID to represent origin and destination countries respectively
//Subtracts an army from one country and adds one to another
//Ignores game rules for qualifying army movements
void Player::moveArmies(int num_Armies, int originID, int destinationID) {
	Map m = Map();

	//Pull armies from origin country
	vector<int> originArmies = m.getCountries().at(originID).getArmiesPerPlayer();
	originArmies.at(playerID - 1) -= num_Armies;

	//Place them in their new destination country
	vector<int> destinationArmies = m.getCountries().at(destinationID).getArmiesPerPlayer();
	destinationArmies.at(playerID - 1) += num_Armies;
	

}

