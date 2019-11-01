#include "stdafx.h"
#include "Card.h"
#include <iostream>
#include <vector>
using namespace std;

Hand::Hand() :
	cards(0)
{}

Hand::~Hand() {}

std::vector<Card> Hand::getHand() const {
	return cards;
}

void Hand::printHand() {
	int j = 0;
	string str;
	for (auto& i : cards) {
		cout << "[" << j+1 << "] " << i.printCard() << endl;
		j++;
	}
}

// Inserts card on hand space
void Hand::setHand(Card c) {
	Hand::cards.insert(cards.begin(), c);
}


