#pragma once

#include "stdafx.h"
#include "Player.h"

using namespace std;

void Player::setPlayerID(int x) {
	playerID = x;
}

int Player::getPlayerID() {
	return playerID;
}
