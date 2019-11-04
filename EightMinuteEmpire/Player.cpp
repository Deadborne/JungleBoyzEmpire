#pragma once

#include "stdafx.h"
#include "Player.h"
#include "Map.h"


using namespace std;


//----Mutators and Accessors----//

void Player::setPlayerID(int x) {
	playerID = new int(x);
}

void Player::setBirthday() {
	bool validInput = false;
	while (!validInput) {
		cout << "Player " << *playerID + 1 << " set birthdate in YYYYMMDD format: \n";
		string inputValue = "0";

		getline(cin, inputValue);
		int playerDate = stoi(inputValue);

		if (playerDate > 9999999 && playerDate < 20200000) {
			birthday = new int(playerDate);
			validInput = true;
		}
		else {
			cin.clear();
			cin.ignore();
		}

	}
}

int Player::getPlayerID() {
	return *playerID;
}

int Player::getBirthday() {
	return *birthday;
}

int Player::getAvailableCities() {
	return *availableCities;
}

void Player::setAvailableCities(int x) {
	availableCities = new int(x);
}

void Player::setAvailableCoins(int x) {
	availableCoins = new int(x);
}

int Player::getAvailableArmies() {
	return *availableArmies;
}

void Player::setAvailableArmies(int x) {
	availableArmies = new int(x);
}

int Player::getAvailableCoins() {
	return *availableCoins;
}

void Player::initializeHand() {
	hand = new Hand();
}

vector<Card> Player::getHand() {
	return hand->getHand();
}

void Player::setHand(vector<Card> v) {
	hand->swapHand(v);
}

void Player::printHand() {
	hand->printHand();
}

//Bid functionality
void Player::setBid() {
	playerBid = new Bid();
	playerBid->setBid(*playerID);
	availableCoins -= *playerBid->getBidAmountPointer();
	//cout << "Available Coins: " << availableCoins << "\n";
}

Bid Player::getBid() {
	return *playerBid;
}


//----Required Functionality----//

//Pays single coin by deleting it from players bank (and from existence)
void Player::PayCoin() {
	setAvailableCoins(getAvailableCoins()-1);
}
//Pays multiple coins
void Player::PayCoin(int numCoins) {
	setAvailableCoins(getAvailableCoins() - numCoins);
}

//This function will allow you to place any given number of new armies in any country
//As such, it ignores game rules:
//	1. Each player can place 3 new armies in the starting country at game start
//	2. Number of armies player can place is determined by the card he/she has drawn
//	3. Player can only place new armies in countries where they own a city 
void Player::placeNewArmies(int numArmies, Country& country) {
	//Map m = Map();

	//Check that the country is either the starting country or one where the player owns a city
	//Add following validation later
	//if ((country.isStartingCountry())||(hasCityIn(country)  == true)){}
	
	//Check army availability. Can't place an army if theyre all already deployed

	if ((*availableArmies - numArmies) >= 0) {
		vector<int*> armies = country.getArmiesPerPlayer();

		int *extraArmies;
		extraArmies = new int(numArmies);

		//Change armies in player's slot
		*armies.at((*playerID) /*- 1*/) += *extraArmies;

		//Push to country object
		country.setArmiesPerPlayer(armies);

		delete extraArmies;

	}else {
		//If the player has too few armies
		cerr << "\nOperation blocked. You only have " << *availableArmies << " armies available to you.";
	}
}

//Takes a number of armies, an origin country and a destination country. Subtracts armies from
//the origin and places them in the destination
void Player::moveArmies(int numArmies, Country& origin, Country& destination) {
	Map m = Map();

	//Build some temporary vectors to hold armies in each country
	vector<int*> originArmies = origin.getArmiesPerPlayer();
	vector<int*> destinationArmies = destination.getArmiesPerPlayer();

	//Avoid moving more armies than exist in the vector 
	if (*originArmies.at(*playerID - 1) >= numArmies) {

		//int *movedArmies;
		//movedArmies = new int(numArmies);
		
		//Move from origin
		*originArmies.at(*playerID - 1) -= numArmies;
		origin.setArmiesPerPlayer(originArmies);

		//Move to destination
		*destinationArmies.at(*playerID - 1) += numArmies;
		destination.setArmiesPerPlayer(destinationArmies);

	}
	else {
		cout << "\nThere are only " << *originArmies.at(*playerID - 1)
			<< " armies in Country " << origin.getCountryId()
			<< ". You cannot move more than that.";
	}
}

//Same as regular moveArmies, but first we check that our 2 countries exist on the same continent.
//If all is well, proceed as planned with moveArmies
void Player::moveOverLand(int numArmies, Country& origin, Country& destination, Graph gameGraph) {
	if (origin.isAdjacent(gameGraph, destination)) {
		cout << "\nCountries are adjacent. Movement approved.\n";
		moveArmies(numArmies, origin, destination);
	}
	else {
		cout << "The origin and destination countrie are not adjacent on land";
	}
}

//Allows a player to destroy an army of some other player. Finds the armyOwner's armies in armyLocation
//and decrements armies in that index
void Player::destroyArmy(Country& armyLocation, Player armyOwner) {
	Map m = Map();

	//temporary army vector for country's armies
	vector<int*> armies = armyLocation.getArmiesPerPlayer();

	//Player ID of the armyOwner (player whose army will be destoryed)
	int armyOwnerID = armyOwner.getPlayerID();

	//As long as the armyOwner has armies in the specified country, we are good to go
	if (*armies.at(armyOwnerID - 1) > 0) {
		
		//decrement the number of armies in the given country for the given player
		*armies.at(armyOwnerID - 1) -= 1;

		//push to country
		armyLocation.setArmiesPerPlayer(armies);

		//add the destroyed army back to the player's bank
		armyOwner.setAvailableArmies(armyOwner.getAvailableArmies() + 1);
	}
	else {
		cout << "\nPlayer " << armyOwnerID << " has no armies in Country " 
			<< armyLocation.getCountryId() + 1 <<".\n";
	}
}

//Allows a player to build a city in a given country, provided that:
//1. They have cities available in their bank
//2. They have an army deployed in the country
//3. They don't have a city already built in that country
void Player::buildCity(Country& cityLocation) {
	Map m = Map();
	
	//1
	if (availableCities > 0) {
		vector<int*> armies = cityLocation.getArmiesPerPlayer();
		//2
		if (armies.at(*playerID - 1) > 0) {
			vector<bool*> cities = cityLocation.getCities();
			//3
			if (*cities.at(*playerID - 1) != true) {
				*cities.at(*playerID - 1) = true;
				cityLocation.setCities(cities);
				*availableCities--;
			}
			else {
				cout << "\nCity already exists in country. Build one somewhere else.";
			}
		}
		else {
			cout << "\nCountry unoccupied. City cannot be built.";
		}
	}
	else {
		cout << "\nResources depleated. City cannot be built.";
	}
}

//Not required, but lets us destroy a city in the same manner we destroy an army
void Player::destroyCity(Country& cityLocation, Player& cityOwner) {
	Map m = Map();

	vector<bool*> cities = cityLocation.getCities();

	int cityOwnerID = cityOwner.getPlayerID();

	//Make sure there's a city to destroy
	if (*cities.at(cityOwnerID - 1) == true) {
		*cities.at(cityOwnerID - 1) = false;

		//In the country, set the city vector equal o the cities vector we have made in here
		cityLocation.setCities(cities);

		//Add that city back to the player's availableCities
		cityOwner.setAvailableCities(cityOwner.getAvailableCities() + 1);
	}

}

//Tells us if a player has a city in some given country
bool Player::hasCityIn(Country& country) {
	Map m = Map();

	//Get the cities for that country
	vector<bool*> cities = country.getCities();

	//If the player has a city logged in the counry's city vector
	if (*cities.at(*playerID - 1) == true) {
		return true;
	}
	else {
		return false;
	}
}

//returns a vector of country Ids where the player has at least one army.
vector<int> Player::armyLocations(Map m) {

	vector<Country> v = m.getCountries();
	vector<int> locations = {};

	int me = *playerID;

	for (int i = 0; i < v.size(); i++) {
		if ((*v[i].getArmiesPerPlayer()[me]) > 0) {
			locations.push_back(v[i].getCountryId());
		}
	}
	return locations;
}

Player::~Player() {
	delete[] availableArmies;
	delete[] playerBid;
	delete[] continentsOwned;
	delete[] countriesOwned;
	delete hand;
}

bool Player::isCountryOwner(Country& country) {
	
	vector<int*> armies = country.getArmiesPerPlayer();

	int indexOfMax = std::distance(armies.begin(), max_element(armies.begin(), armies.end()));

	if (find(armies.begin() + indexOfMax + 1, armies.end(), *max_element(armies.begin(), armies.end())) != armies.end()) {
		return false;
	}
	else if (indexOfMax == *playerID - 1)	//Is this playerID shit correct??
		return true;
}

vector<Country> Player::getCountriesOwned(Map m) {
	//Cut the searchable arrays down from all countries to just the ones where he player has troops stationed
	vector<int> armyLocs = armyLocations(m);

	for (int i = 0; i < armyLocs.size(); i++) {
		//Get the first country where the player has at least 1 army present
		Country country = m.getCountries().at(armyLocs.at(i));

		if (isCountryOwner(country)) {
			countriesOwned->push_back(country);
		}
	}

	return *countriesOwned;
	
}


vector<int> Player::getContinentsOwned(Map m) {

	//For each continent that exists
	for (int i = 0; i < m.getContinents().size(); i++) {
		//Get # of countries in this continet
		vector<Country> countries = m.getCountries();

		int countriesInContinent;

		//COUNT TOTAL COUNTRIES IN A CONTINENT
		//For every country
		for (int j = 0; j < countries.size(); j++) {
			//if that country's continent matches our current continent then we need to count it
			if (countries.at(j).getContinentId() == m.getContinents().at(i)) {
				//increment some variable, which will track the number of countries in a continent
				countriesInContinent++;
			}
		}

		//COUNT # COUNTRIES OWNED FROM THAT SAME CONTINENT
		int countriesOwnedInContinent;

		//For each country we OWN
		for (int k = 0; k < getCountriesOwned(m).size(); k++) {
			//if that country's continent mateches our current continent,
			if (getCountriesOwned(m).at(k).getContinentId() == m.getContinents().at(i)) {
				countriesOwnedInContinent++;
			}
		}

		//COMPARE THE 2 VALUES
		if (countriesInContinent == countriesOwnedInContinent) {
			//Then add the current continent to those that we own, adding its ID to a vector.
			continentsOwned->push_back(m.getContinents().at(i));
		}

	}
	
	//The variable will have been changed in the player's data members, but this function will also return that vector for ease of use
	return *continentsOwned;

}



//FUNTIONALITY NOT REQUIRED --- TO BE IMPLEMENTED IN A2//

////For future implementation, this function will scan countries, determine the owner
////and pass the country ID to its respective owner's countriesOwned vector
//vector<int> Player::getCountriesOwned() {
//	Map m = Map();				//Start the map
//	vector<Country> allCountries = m.getCountries();
//	
//	//This is where we will store countries owned by a player 
//	vector<int> countriesOwned;	
//
//	//Take the vector of country objects
//	//Loop through countries
//	for (int i = 0; i < allCountries.size(); i++) {
//		//Get the army vector for each country
//		vector<int> armies = allCountries.at(i).getArmiesPerPlayer();
//		//Get the largest element in the vector
//		vector<int>::iterator maxElement = max_element(armies.begin(), armies.end());
//		bool duplicatesExist = false;
//
//		
//		//-----THIS PART OF THE FUNCTION HAS NOT BEEN TESTED-----//
//		//Does our matrix have duplicates? Does it therefore have an owner?
//		for (int i = 0; (i < armies.size() && (duplicatesExist== false)); i++) {
//			for (int j = i + 1; j < armies.size(); j++) {
//
//				//If there are duplicates in the array and one of them is equal to 
//				if ((armies.at(i) == armies.at(j)) && (armies.at(i) == *maxElement)) {
//					duplicatesExist = true;
//				}
//			}
//		}
//		
//		//if the maxElement has a duplicate 
//		if (duplicatesExist == false) {
//			//Position of largest value
//			int ownerIndex = std::distance(armies.begin(), maxElement);
//
//			//If the playerID is the same as the index with the most armies
//			if (*playerID == ownerIndex + 1) {
//				//Then add that country to the player's owned countries
//				countriesOwned.push_back(allCountries.at(i).getCountryId());
//			}
//		}
//	}
//
//	return countriesOwned;
//}




