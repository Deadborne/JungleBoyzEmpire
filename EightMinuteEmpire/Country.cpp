#pragma once
#include "stdafx.h"
#include "Country.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//constructor, takes countryID and continentId
Country::Country(int countryId, int continentId) : _countryId(countryId), _continentId(continentId)
{
}
//returns the ID of the country
int Country::getId()
{
	return _countryId;
};

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
void Country::buildCity(int playerId) 
{
	_cities[playerId] = true;
}

//tells you who the owner of the country is
int Country::getOwner()
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
