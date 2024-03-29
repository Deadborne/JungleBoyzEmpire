#include "stdafx.h"
#include "Bid.h"
#include "Map.h"
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

int Bid::getBidAmount() {
	return *_bidAmount;
}
int* Bid::getBidAmountPointer() {
	return _bidAmount;
}

int Bid::getDate() {
	return *birthdate;
}

void Bid::setBid(int playerId) {
	bool validInput = false;
	while (!validInput) {
		cout << "Player " << playerId << " select bid amount between 0 and 8: \n";
		string inputValue = "0";

		try {
			getline(cin, inputValue);
			int playerBet = stoi(inputValue);

			if (playerBet >= 0 && playerBet <= 8) {
				_bidAmount = new int(playerBet);
				validInput = true;
			}

		}
		catch (std::exception e) {
			cout << "Invalid bid amount. Try again: ";
		}
	}
}

void Bid::setBid(int playerId, int maxBid) {
	bool validInput = false;
	while (!validInput) {
		cout << "Player " << playerId << " select bid amount between 0 and " << maxBid << ": \n";
		string inputValue = "0";

		try {
			getline(cin, inputValue);
			int playerBet = stoi(inputValue);

			if (playerBet >= 0 && playerBet <= maxBid) {
				_bidAmount = new int(playerBet);
				validInput = true;
			}

		}
		catch (std::exception e) {
			cout << "Invalid bid amount. Try again: ";
		}
	}
}



void Bid::setDate(int playerId) {
	bool validInput = false;
	while (!validInput) {
		cout << "Player " << playerId << " set birthdate in YYYYMMDD format: \n";
		string inputValue = "0";

		try {
			getline(cin, inputValue);
			int playerDate = stoi(inputValue);

			if (playerDate > 0) {
				birthdate = new int(playerDate);
				validInput = true;
			}

		}
		catch (std::exception e) {
			cout << "Invalid bid amount. Try again: ";
		}
	}
}


//This is going to be the laziest C++ code, sorry :( 
int Bid::calculateBid(std::vector<int> bidList) {
	cout << "Calculating Bids: " << endl;
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

int Bid::calculateDate(std::vector<int> dateList) {
	cout << "Finding youngest player: " << endl;
	int maxBid = 0;
	int maxBidIndex = -1;
	bool isFirstFindBid = false;
	bool isTied = false;
	//maxBid = *max_element(dateList.begin(), dateList.end());

	//Looking for the index

	int maxDate = -1;
	int maxDateIndex = -1;

	for (int i = 0; i < dateList.size(); i++) {
		if (dateList[i] > maxDate) {
			maxDate = dateList[i];
			maxDateIndex = i;
			isTied = false;
		}
		else if (dateList[i] == maxDate) {
			cout << dateList[i];
			isTied = true;
		}
	}

	if (isTied) {
		cout << "TWINS!? I give up. Player 1 will have to start!" << endl;
		return 0;
	}

	else
		return maxDateIndex;
}

