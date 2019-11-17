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
		cout << "Player " << *playerID << " set birthdate in YYYYMMDD format: \n";
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

int Player::getFinalScore() {
	return *finalScore;
}

void Player::setFinalScore(int x) {
	finalScore = new int(x);
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
	*availableCoins -= *playerBid->getBidAmountPointer();
	//cout << "Available Coins: " << availableCoins << "\n";
}

void Player::setBid(int maxBid) {
	playerBid = new Bid();
	playerBid->setBid(*playerID, maxBid);
	*availableCoins -= *playerBid->getBidAmountPointer();
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
	
	//Check army availability. Can't place an army if theyre all already deployed

	if ((*availableArmies - numArmies) >= 0) {
		vector<int*> armies = country.getArmiesPerPlayer();

		int *extraArmies;
		extraArmies = new int(numArmies);

		//Change armies in player's slot
		*armies.at((*playerID) - 1) += *extraArmies;

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
	//Map m = Map();

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
	//Map m = Map();

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
	//Map m = Map();
	
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
				int cities = *availableCities;
				cities--;
				*availableCities = cities;
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
	//Map m = Map();

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
	//Map m = Map();

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
	//delete[] continentsOwned;
	delete hand;
	delete strategy;
}

//Check if a player is the owner of a particular country
bool Player::isCountryOwner(Country& country) {
	
	vector<int*> armies = country.getArmiesPerPlayer();

	int maxArmies = 0;
	int maxArmiesIndex = 0;
	maxArmies = *armies[0];
	//Get max armies and index of that value
	for (int i = 0; i < armies.size(); i++) {
		for (int j = i + 1; j < armies.size(); j++) {
			if (*armies[j] > maxArmies) {
				maxArmies = *armies[j];
				maxArmiesIndex = j;
			}
		}
	}
	
	
	int dupe = 0;

	//Count duplicates of max
	for (int i = 0; i < armies.size(); i++) {
		if (*armies.at(i) == maxArmies)
			dupe++;
	}
	if (dupe > 1) //duplicates present --> nobody owns it
		return false;
	else if (maxArmiesIndex == *playerID) //check that the max is at the same index as our current player.
		return true;
	else {
		return false;
	}	
	
}

//Get all the countries our current player owns, return a vector of countries
vector<Country> Player::getCountriesOwned(Map m) {
	
	vector<Country> ownedCountries;

	for (int i = 0; i < m.getCountries().size(); i++) {
		if (isCountryOwner(m.getCountries().at(i))) {
			ownedCountries.push_back(m.getCountries().at(i));
		}
	}

	return ownedCountries;
}

//Using the country data, determine which countries we have, if any
vector<int> Player::getContinentsOwned(Map m) {

	vector<int> continentsOwned;
	//For each continent that exists
	for (int i = 0; i < m.getContinents().size(); i++) {
		//Get # of countries in this continet
		vector<Country> countries = m.getCountries();
		int countriesInContinent = 0;

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
		int countriesOwnedInContinent = 0;

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
			continentsOwned.push_back(m.getContinents().at(i));
		}

	}
	
	//The variable will have been changed in the player's data members, but this function will also return that vector for ease of use
	return continentsOwned;
}
//Calulate all the points from the goods we have collected via cards
int Player::pointsFromCards() {
	//Get the player's hand
	vector<Card> hand = getHand();

	//Shitty way to store the number of goods
	int carrots = 0;
	int anvils = 0;
	int shards = 0;
	int coals = 0;
	int trees = 0;
	int wildcards = 0;


	//Loop through the hand and count goods of each type
	for (int i = 0; i < hand.size(); i++) {
		//Aight lets count trees
		if (hand.at(i).getGood() == "tree")
			carrots += hand.at(i).getGoodAmount();
		else if (hand.at(i).getGood() == "anvil")
			anvils += hand.at(i).getGoodAmount();
		else if (hand.at(i).getGood() == "shard")
			shards += hand.at(i).getGoodAmount();
		else if (hand.at(i).getGood() == "coal")
			coals += hand.at(i).getGoodAmount();
		else if (hand.at(i).getGood() == "carrot")
			carrots += hand.at(i).getGoodAmount();
		else if (hand.at(i).getGood() == "wildcard")
			wildcards += hand.at(i).getGoodAmount();
	}

	//Display current count for other cards, so as to make the right decision
	cout << "You currently have:"
		<< "\n\t- " << trees << " trees"
		<< "\n\t- " << anvils << " anvils"
		<< "\n\t- " << shards << " shards"
		<< "\n\t- " << coals << " coals"
		<< "\n\t- " << carrots << " carrots"
		;

	//If we have have any wildcards to handle
	if (wildcards > 0) {
		cout << "\n\nYou also have " << wildcards << " wildcards\n";
		cout << "As such, you may assign it to be either:"
			<< "\n\t- tree"
			<< "\n\t- anvil"
			<< "\n\t- shard"
			<< "\n\t- coal"
			<< "\n\t- carrot"
			;
		//Assign values to each of our wild cards
		for (int j = 1; j <= wildcards; j++) {
			string chosenGood;
			cout << "\n\nChoose a value for wildcard " << j << endl;
			cin >> chosenGood;

			//Add the chosen value
			if (chosenGood == "tree")
				trees++;
			else if (chosenGood == "anvil")
				anvils++;
			else if (chosenGood == "shard")
				shards++;
			else if (chosenGood == "coal")
				coals++;
			else if (chosenGood == "carrot")
				carrots++;
			else
				cout << "Good type unrecognized. Please enter either tree, anvil, shard, coal, or carrot.\n";
		}
	}

	//Now assign victory Points
	int vp = 0;

	//For trees:
	switch (trees) {
	case 2: vp++; break;
	case 3: vp++; break;
	case 4: vp += 2; break;
	case 5: vp += 3; break;
	case 6: vp += 5; break;
	case 7: vp += 5; break;
	default: break;
	}

	//For anvils
	switch (anvils) {
	case 2: vp++; break;
	case 3: vp++; break;
	case 4: vp += 2; break;
	case 5: vp += 2; break;
	case 6: vp += 3; break;
	case 7: vp += 5; break;
	case 8: vp += 5; break;
	default: break;
	}

	//For shards
	switch (shards) {
	case 1: vp++; break;
	case 2: vp += 2; break;
	case 3: vp += 3; break;
	case 4: vp += 5; break;
	case 5: vp += 5; break;
	case 6: vp += 5; break;
	case 7: vp += 5; break;
	case 8: vp += 5; break;
	default: break;
	}

	//For coals
	switch (coals) {
	case 2: vp++; break;
	case 3: vp += 2; break;
	case 4: vp += 3; break;
	case 5: vp += 5; break;
	case 6: vp += 5; break;
	case 7: vp += 5; break;
	case 8: vp += 5; break;
	default: break;
	}

	//For carrots
	switch (carrots) {
	case 3: vp++; break;
	case 4: vp++; break;
	case 5: vp += 2; break;
	case 6: vp += 2; break;
	case 7: vp += 3; break;
	case 8:
	case 9:
	case 10:
	case 11:
	case 12: vp += 5; break;
	default: break;
	}

	return vp;
}

//Compute the final score.
int Player::computeScore(Map m) {

	//Add the length of owned country vector, owned continent vector, and points from card goods
	
	return getCountriesOwned(m).size() + getContinentsOwned(m).size() + pointsFromCards();
}

int Player::andOrAction(int actionNum) {
	return actionNum;
}

void Player::ignore() {
	cout << "You have chosen to ignore your action!" << endl;
}

//returns a vector of country Ids where the player has at least one army.
std::vector<int> Player::getArmyLocations(Map m) {

	vector<Country> v = m.getCountries();
	vector<int> locations = {};

	int me = *playerID;

	for (int i = 0; i < v.size(); i++) {
		if ((*v[i].getArmiesPerPlayer()[me - 1]) > 0) {
			locations.push_back(v[i].getCountryId());
		}
	}
	return locations;
}
//returns a vector of country Ids where the player has at least one army.
std::vector<int> Player::getArmyLocationsForCity(Map m) {

	vector<Country> v = m.getCountries();
	vector<int> locations = {};
	int me = *playerID;

	for (int i = 0; i < v.size(); i++) {
		if ((*v[i].getArmiesPerPlayer()[me - 1]) > 0) {
			bool containsCity = false;
			for (int j = 0; j < v[i].getCities().size(); j++) {
				if (*v[i].getCities().at(j) == true) {
					containsCity = true;
				}
			}

			if (!containsCity) {
				locations.push_back(v[i].getCountryId());
			}

		}
	}
	return locations;
}

std::vector<int> Player::getArmySpawnLocations(Map m) {

	vector<Country> v = m.getCountries();
	vector<int> locations = {};
	int me = *playerID;
	for (int i = 0; i < v.size(); i++) {
		if (v[i].isStartingCountry() || *v[i].getCities()[me - 1]) {
			locations.push_back(v[i].getCountryId());
		}
	}
	return locations;
}

void Player::setGreedStrategy(GreedStrategy _strategy) {
	strategy = new GreedStrategy(_strategy);
}

void Player::setModerateStrategy(ModerateStrategy _strategy) {
	strategy = new ModerateStrategy(_strategy);
}

Strategy* Player::getStrategy() {
	return strategy;
}

void Player::setIsNPC(bool _isNPC) {
	isNPC = new bool(_isNPC);
}

bool Player::getIsNPC() {
	return *isNPC;
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




