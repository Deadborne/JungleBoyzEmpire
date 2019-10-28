#include <iostream>
#include <vector>
#include "Card.h"
using namespace std;

// Constructor
Hand::Hand() :
	cards(8)
{}

// Destructor
Hand::~Hand() {}

// Inserts card on hand space
void Hand::setHand(Card c) {
	Hand::cards.insert(cards.begin(), c);
}

std::vector<Card> Hand::getHand() const {
	return cards;
}

// Outputs hand space
void Hand::printHand() {
	int j = 0;
	string str = "";
	//for (auto& i : cards) {
	//	cout << "Print card: ";
	//	//i.printCard();
	//}
}
