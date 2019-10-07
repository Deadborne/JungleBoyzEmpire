#pragma once

#include "stdafx.h"
#include "Player.h"
#include "Map.h"

using namespace std;


//----Mutators and Accessors----//

void Player::setPlayerID(int x) {
	playerID = x;
}

int Player::getPlayerID() {
	return playerID;
}

int Player::getAvailableCities() {
	return availableCities;
}

void Player::setAvailableCities(int x) {
	availableCities = x;
}


//----Required Functionality----//


//Pays single coin by deleting it from players bank (and from existence)
void Player::PayCoin() {
	availableCoins--;
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

	//As long as we arent trying to place more armies than we have available to us, 
	if ((availableArmies - num_Armies) >= 0) {

		//Get armiesPerPlayer vector for desired country
		vector<int> armies = m.getCountries().at(countryID).getArmiesPerPlayer();

		//Add however many armies player wants to the appropriate index
		armies.at(playerID - 1) += num_Armies;

		//Push those changes to the actual array of armies
		m.getCountries().at(countryID).setArmiesPerPlayer(armies);


	} else {
		//If the player has too few 
		cerr << "\nOperation blocked. You only have " << availableArmies << " armies available to you.";
	}

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
	m.getCountries().at(originID).setArmiesPerPlayer(originArmies);

	//Place them in their new destination country
	vector<int> destinationArmies = m.getCountries().at(destinationID).getArmiesPerPlayer();
	destinationArmies.at(playerID - 1) += num_Armies;
	m.getCountries().at(destinationID).setArmiesPerPlayer(destinationArmies);
}

//Builds a city in a country if the player has an army present and doesnt already have a city built there
void Player::buildCity(int cityLocationID) {
	Map m = Map();
	//Check that they have cities left
	if (availableCities != 0) {
		//Get the armies vector
		vector<int> armies = m.getCountries().at(cityLocationID).getArmiesPerPlayer();
		//If the player has an army in that country, they are allowed to build a city
		if (armies.at(playerID - 1) > 0) {
			vector<bool> cities = m.getCountries().at(cityLocationID).getCities();
			//Players are allowed only 1 city per country, so if they dont have a city present in that country:
			if (cities.at(playerID - 1) != true) {
				cities.at(playerID - 1) = true;
				m.getCountries().at(cityLocationID).setCities(cities);
				availableCities--;
			}

		}
	}
}

//Player.destroyArmy will take the location of the city and a player object for the city owner.
//From there, the city is removed from the country and deposited back into the owner's city bank
void Player::destroyArmy(int cityLocationID, Player cityOwner) {
	Map m = Map();
	//Get counry's city vector
	vector<bool> cities = m.getCountries().at(cityLocationID).getCities();

	//Get the city owner's ID
	int cityOwnerID = cityOwner.getPlayerID();

	//If cityOwner has a city in that country
	if (cities.at(cityOwnerID - 1) == true) {
		//then make sure that is no longer the case
		cities.at(cityOwnerID - 1) = false;

		//Push the changes to the country array
		m.getCountries().at(cityOwnerID).setCities(cities);
		
		//Add a city back to the player's city bank
		cityOwner.setAvailableCities(cityOwner.getAvailableCities() - 1);
	}


}



