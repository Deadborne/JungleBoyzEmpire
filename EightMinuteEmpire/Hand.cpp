#include "stdafx.h"
#include "Card.h"
#include <iostream>
#include <vector>
using namespace std;

Hand::Hand() :
	cards()
{}

Hand::~Hand() {}

std::vector<Card> Hand::getHand() const {
	return cards;
}

void Hand::printHand() {
	int j = 0;
	string str;
	if (cards.size() == 0) {
		cout << "Your hand is empty." << endl;
	}
	else {
		for (auto& i : cards) {
			cout << "[" << j + 1 << "] " << i.printCard() << endl;
			j++;
		}
	}
}

// Inserts card on hand space
void Hand::setHand(Card c) {
	Card *insertedCard;
	insertedCard = new Card(c);
	cards.push_back(*insertedCard);
	cout << "Top card is now: " << cards[0].printCard() << endl;
}


void Hand::swapHand(vector<Card> v) {
	cards = v;
}