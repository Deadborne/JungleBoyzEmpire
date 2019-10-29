#include "stdafx.h"
#include "Card.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <iterator>
#include <stdlib.h>
using namespace std;

Deck::Deck() : deck(42), space(6), players(2) {
	initializeDeck(players),
		shuffleDeck(),
		initializeSpace();
};

Deck::Deck(int num) : deck(42), space(6), players(num) {
	initializeDeck(players),
		shuffleDeck(),
		initializeSpace();
};

Deck::~Deck() {}

Deck::Deck(const Deck& d) :
	players(d.players),
	deck(d.deck)
{}

// Created deck object with 42 cards
void Deck::initializeDeck(int players) {
	cout << "DECK SIZE: " << deck.size() << endl;
	cout << "SPACE SIZE: " << space.size() << endl;
	deck[0] = Card("tree", 1, "move", 3, "", 0, "", false);
	deck[1] = Card("anvil", 1, "place", 3, "", 0, "", false);
	deck[2] = Card("anvil", 1, "place", 3, "move", 3, "or", false);
	deck[3] = Card("wildcard", 1, "moveOver", 2, "", 0, "", false);
	deck[4] = Card("tree", 1, "moveOver", 4, "", 0, "", false);
	deck[5] = Card("anvil", 1, "moveOver", 3, "", 0, "", false);
	deck[6] = Card("wildcard", 1, "place", 2, "", 0, "", false);
	deck[7] = Card("coal", 1, "place", 2, "", 0, "", false);
	deck[8] = Card("shard", 1, "place", 2, "", 0, "", false);
	deck[9] = Card("coal", 1, "place", 3, "", 0, "", false);
	deck[10] = Card("anvil", 1, "place", 3, "", 0, "", false);
	deck[11] = Card("carrot", 2, "place", 3, "", 0, "", false);
	deck[12] = Card("coal", 1, "place", 2, "build", 1, "or", false);
	deck[13] = Card("anvil", 1, "build", 1, "", 0, "", false);
	deck[14] = Card("carrot", 1, "build", 1, "", 0, "", false);
	deck[15] = Card("carrot", 1, "build", 1, "", 0, "", false);
	deck[16] = Card("tree", 1, "build", 1, "", 0, "", false);
	deck[17] = Card("tree", 1, "build", 1, "", 0, "", false);
	deck[18] = Card("shard", 1, "place", 2, "", 0, "", false);
	deck[19] = Card("carrot", 1, "destroy", 1, "place", 1, "and", false);
	deck[20] = Card("shard", 1, "move", 2, "", 0, "", false);
	deck[21] = Card("tree", 1, "destroy", 1, "build", 1, "or", false);
	deck[22] = Card("anvil", 1, "move", 4, "", 0, "", false);
	deck[23] = Card("anvil", 1, "place", 3, "move", 4, "or", false);
	deck[24] = Card("anvil", 1, "place", 3, "move", 4, "or", false);
	deck[25] = Card("carrot", 1, "moveOver", 3, "", 0, "", false);
	deck[26] = Card("tree", 1, "moveOver", 3, "", 0, "", false);
	deck[27] = Card("coal", 1, "moveOver", 3, "", 0, "", false);
	deck[28] = Card("carrot", 2, "move", 4, "", 0, "", false);
	deck[29] = Card("advil", 1, "move", 5, "", 0, "", false);
	deck[30] = Card("coal", 1, "moveOver", 2, "", 0, "", false);
	deck[31] = Card("wildcard", 1, "moveOver", 3, "", 0, "", false);
	deck[32] = Card("carrot", 1, "move", 5, "", 0, "", false);
	deck[33] = Card("coal", 1, "move", 2, "", 0, "", false);
	deck[34] = Card("tree", 1, "place", 2, "move", 3, "or", false);
	deck[35] = Card("carrot", 1, "move", 4, "", 0, "", false);
	deck[36] = Card("carrot", 1, "place", 3, "", 0, "", false);
	deck[37] = Card("shard", 1, "place", 1, "", 0, "", false);

	if (players == 5) { // only insert these cards if the amount of players is 5
		deck[38] = Card("anvil", 2, "move", 4, "", 0, "", true);
		deck[39] = Card("shard", 1, "place", 2, "", 0, "", true);
		deck[40] = Card("carrot", 1, "place", 4, "move", 2, "or", true);
		deck[41] = Card("coal", 1, "moveOver", 2, "", 0, "", true);
	}
}

void Deck::initializeSpace() {
	for (int i = 0; i < space.size(); i++) {
		space[i] = deck[0];
		deck.erase(deck.begin());
		deck.size();
	}
}

// Shuffle deck method
void Deck::shuffleDeck() {
	random_device rd;
	mt19937 g(rd());

	shuffle(Deck::deck.begin(), Deck::deck.end(), g);
}

void Deck::printDeck() {
	int j = 0;
	cout << "TEST" << endl;
	for (auto& i : space) {
		i.printCard();
	}
}

std::vector<Card> Deck::getDeck() {
	return deck;
}

std::vector<Card> Deck::getSpace() {
	return space;
}

Card Deck::draw(int i) {
	Card card = space[i];
	space.erase(space.begin() + i);
	return card;
}