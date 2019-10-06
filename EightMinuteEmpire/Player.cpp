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
	Map m = Map();
	m.getCountries();
	vector<int> countriesOwned;

	//for (int i = 0; i <= ) {}



	
}