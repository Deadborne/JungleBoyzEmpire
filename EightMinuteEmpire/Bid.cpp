#include "stdafx.h"
#include "Bid.h"
#include <vector>
#include <algorithm>
#include <math.h>
#include <iostream>
#include <ostream>
#include <string>
using namespace std;

Bid::Bid() {
}

Bid::Bid(int bidAmount) {
	_bidAmount = new int(bidAmount);
}

Bid::~Bid() {
}

void Bid::setBid(int playerId) {
	bool validInput = false;
	while (!validInput) {
		cout << "Player " << playerId + 1 << " select bid amount between 0 and 8: \n";
		string inputValue = "0";

		try {
			getline(cin, inputValue);
			int playerBet = stoi(inputValue);

			if (playerBet >= 0 && playerBet <= 8) {
				_bidAmount = new int(playerBet);
				validInput = true;
			}

		}
		catch (exception e) {

		}
	}
}


//This is going to be the laziest C++ code, sorry :( 
int Bid::calculateBid(std::vector<int> bidList) {
	cout << "Calculating Bids: ";
	int maxBid = 0;
	int maxBidIndex = -1;
	bool isFirstFindBid = false;
	bool isTied = false;
	maxBid = *max_element(bidList.begin(), bidList.end());

	//Looking for the index

	for (int i = 0; i < bidList.size(); i++) {
		if (maxBid == bidList.at(i)) {
			if (isFirstFindBid) {
				isTied = true;
			}
			else {
				isFirstFindBid = true;
				maxBidIndex = i;
			}
		}		
	}

	if (isTied) {
		return -1;
	}
	else {
		return maxBidIndex;
	}
}