#pragma once
#include "stdafx.h"
#include "Continent.h"
#include <vector>
#include <string>

using namespace std;

//int continentId;
//std::string continentName;
//int continentOwnedByPlayer;

Continent::Continent(int continentId) {
	_continentId = continentId;
	_continentName = "UnnamedContinent";
	_continentOwnedByPlayer = -1;
}

Continent::Continent(int continentId, std::string continentName) {
	_continentId = continentId;
	_continentName = continentName;
	_continentOwnedByPlayer = -1;		
}

//Tells you who the owner of the continent in, based off of the continent territories you pass in
void Continent::setOwnerOfContinent(int continentId, std::vector<int> countries) {
	int currMax = 0;
	//Loops through the vector and which players owns the territory for i
	for (int i = 0; i < countries.size(); i++) {
		if (countries[i] > currMax) {
			currMax = countries[i];
			_continentOwnedByPlayer = i;
		}
		//Means that it is tied
		else if (currMax == countries[i]) {
			currMax = countries[i];
			_continentOwnedByPlayer = -1;
			break;
		}
	}
}

