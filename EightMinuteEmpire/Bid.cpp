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

int Bid::getBidAmount() {
	return *_bidAmount;
}
int* Bid::getBidAmountPointer() {
	return _bidAmount;
}

int Bid::getDate() {
	return *birthdate;
}

void Bid::setBid(int amount) {
	*_bidAmount = amount;
}

void Bid::setDate(int date) {
	*birthdate = date;
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

int Bid::calculateDate(std::vector<int> dateList) {
	cout << "Calculating Bids: ";
	int maxBid = 0;
	int maxBidIndex = -1;
	bool isFirstFindBid = false;
	bool isTied = false;
	maxBid = *max_element(dateList.begin(), dateList.end());

	//Looking for the index

	for (int i = 0; i < dateList.size(); i++) {
		if (maxBid == dateList.at(i)) {
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

