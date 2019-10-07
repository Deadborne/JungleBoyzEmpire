#pragma once
#include "stdafx.h"
#include "Country.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//default constructor
Country::Country() {

}

//constructor, takes countryID and continentId
Country::Country(int countryId, int continentId) : _countryId(countryId), _continentId(continentId)
{
}
//constructor, takes countryID, continentId, and a boolean for starting country or not
Country::Country(int countryId, int continentId, bool isStart) : _countryId(countryId), _continentId(continentId), _isStart(isStart)
{
}

Country::Country(int countryId, int continentId, vector<int> armiesPerPlayer) : _countryId(countryId), _continentId(continentId), _armiesPerPlayer(armiesPerPlayer)
{
}


//----Mutators & Accessors----//

//Returns vector of cities for a given country
vector<bool> Country::getCities() {
	return _cities;
}

//Allows us to set the city vector for a given country
void Country::setCities(vector<bool> newCities) {
	_cities = newCities;
}

//returns the ID of the country
int Country::getCountryId(){
	return _countryId;
};

//Public accessor for armiesPerPlayer - W
vector<int> Country::getArmiesPerPlayer() {
	return _armiesPerPlayer;

}

//Setter for armiesPerPlayer
void Country::setArmiesPerPlayer(vector<int> newArmies) {
	_armiesPerPlayer = newArmies;
}



//----Other Functionality----//

//returns the owner of the country
void Country::setOwner(int countryId)
{
	int currMax = 0, owner = -1;

	for (int i = 0; i < Country::_armiesPerPlayer.size(); i++) 
	{
		if (_armiesPerPlayer[i] > currMax)
		{
			owner = i;
			currMax = _armiesPerPlayer[i];
		}
		else if (_armiesPerPlayer[i] == currMax)
		{
			owner = -1;
			break;
		}
	}
	_countryOwner = owner;
}

//builds a city in this country for the player being passed.
void Country::buildCity(int playerId)			//Is this fn redundant with player version? Should we delete?
{
	_cities[playerId] = true;
}

//tells you who the owner of the country is
int Country::getOwner() //check redundancy of this function
{
	return _countryOwner;
}

//checks if the player being passed as a param has a city in this country
bool Country::hasCity(int playerId) {
	if (_cities[playerId] == true)
		return true;
	else 
		return false;
}


//Prints the armies in the country from which this function is called - W
void Country::printArmies() {
	for (int i = 0; i < _armiesPerPlayer.size(); i++) {
		cout << _armiesPerPlayer.at(i) << " ";
	}

}






