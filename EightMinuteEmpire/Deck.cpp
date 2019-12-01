#include "stdafx.h"
#include "Card.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <iterator>
#include <stdlib.h>

#include "CardsFactory.h"

using namespace std;

Deck::Deck() : deck(38), space(6), players(5) {
	initializeDeck(5),
	shuffleDeck(),
	initializeSpace();
};

Deck::Deck(int num) : deck(38), space(6), players(num) {
	initializeDeck(num),
	shuffleDeck(),
	initializeSpace();
};

Deck::~Deck() {};

// Created deck object with 42 cards
void Deck::initializeDeck(int players) {
	cout << "DECK SIZE: " << deck.size() << endl;
	cout << "FRONT CARDS SIZE: " << space.size() << endl;

	vector<Card*> ptrCard;
	ptrCard.resize(38);
	
	ptrCard[0] = CardsFactory::Create("tree", 1, "move", 3, "", 0, "", false);
	ptrCard[1] = CardsFactory::Create("anvil", 1, "place", 3, "", 0, "", false);
	ptrCard[2] = CardsFactory::Create("anvil", 1, "place", 3, "move", 3, "or", false);
	ptrCard[3] = CardsFactory::Create("wildcard", 1, "moveOver", 2, "", 0, "", false);
	ptrCard[4] = CardsFactory::Create("tree", 1, "moveOver", 4, "", 0, "", false);
	ptrCard[5] = CardsFactory::Create("anvil", 1, "moveOver", 3, "", 0, "", false);
	ptrCard[6] = CardsFactory::Create("wildcard", 1, "place", 2, "", 0, "", false);
	ptrCard[7] = CardsFactory::Create("coal", 1, "place", 2, "", 0, "", false);
	ptrCard[8] = CardsFactory::Create("shard", 1, "place", 2, "", 0, "", false);
	ptrCard[9] = CardsFactory::Create("coal", 1, "place", 3, "", 0, "", false);
	ptrCard[10] = CardsFactory::Create("anvil", 1, "place", 3, "", 0, "", false);
	ptrCard[11] = CardsFactory::Create("carrot", 2, "place", 3, "", 0, "", false);
	ptrCard[12] = CardsFactory::Create("coal", 1, "place", 2, "build", 1, "or", false);
	ptrCard[13] = CardsFactory::Create("anvil", 1, "build", 1, "", 0, "", false);
	ptrCard[14] = CardsFactory::Create("carrot", 1, "build", 1, "", 0, "", false);
	ptrCard[15] = CardsFactory::Create("carrot", 1, "build", 1, "", 0, "", false);
	ptrCard[16] = CardsFactory::Create("tree", 1, "build", 1, "", 0, "", false);
	ptrCard[17] = CardsFactory::Create("tree", 1, "build", 1, "", 0, "", false);
	ptrCard[18] = CardsFactory::Create("shard", 1, "place", 2, "", 0, "", false);
	ptrCard[19] = CardsFactory::Create("carrot", 1, "destroy", 1, "place", 1, "and", false);
	ptrCard[20] = CardsFactory::Create("shard", 1, "move", 2, "", 0, "", false);
	ptrCard[21] = CardsFactory::Create("tree", 1, "destroy", 1, "build", 1, "or", false);
	ptrCard[22] = CardsFactory::Create("anvil", 1, "move", 4, "", 0, "", false);
	ptrCard[23] = CardsFactory::Create("anvil", 1, "place", 3, "move", 4, "or", false);
	ptrCard[24] = CardsFactory::Create("anvil", 1, "place", 3, "move", 4, "or", false);
	ptrCard[25] = CardsFactory::Create("carrot", 1, "moveOver", 3, "", 0, "", false);
	ptrCard[26] = CardsFactory::Create("tree", 1, "moveOver", 3, "", 0, "", false);
	ptrCard[27] = CardsFactory::Create("coal", 1, "moveOver", 3, "", 0, "", false);
	ptrCard[28] = CardsFactory::Create("carrot", 2, "move", 4, "", 0, "", false);
	ptrCard[29] = CardsFactory::Create("anvil", 1, "move", 5, "", 0, "", false);
	ptrCard[30] = CardsFactory::Create("coal", 1, "moveOver", 2, "", 0, "", false);
	ptrCard[31] = CardsFactory::Create("wildcard", 1, "moveOver", 3, "", 0, "", false);
	ptrCard[32] = CardsFactory::Create("carrot", 1, "move", 5, "", 0, "", false);
	ptrCard[33] = CardsFactory::Create("coal", 1, "move", 2, "", 0, "", false);
	ptrCard[34] = CardsFactory::Create("tree", 1, "place", 2, "move", 3, "or", false);
	ptrCard[35] = CardsFactory::Create("carrot", 1, "move", 4, "", 0, "", false);
	ptrCard[36] = CardsFactory::Create("carrot", 1, "place", 3, "", 0, "", false);
	ptrCard[37] = CardsFactory::Create("shard", 1, "place", 1, "", 0, "", false);
	
	//deck[0] =  Card("tree",		1,	"move",			3,	"",			0,	"",		false);
	//deck[1] =  Card("anvil",	1,	"place",		3,	"",			0,	"",		false);
	//deck[2] =  Card("anvil",	1,	"place",		3,	"move",		3,	"or",	false);
	//deck[3] =  Card("wildcard", 1,	"moveOver",		2,	"",			0,	"",		false);
	//deck[4] =  Card("tree",		1,	"moveOver",		4,	"",			0,	"",		false);
	//deck[5] =  Card("anvil",	1,	"moveOver",		3,	"",			0,	"",		false);
	//deck[6] =  Card("wildcard", 1,	"place",		2,	"",			0,	"",		false);
	//deck[7] =  Card("coal",		1,	"place",		2,	"",			0,	"",		false);
	//deck[8] =  Card("shard",	1,	"place",		2,	"",			0,	"",		false);
	//deck[9] =  Card("coal",		1,	"place",		3,	"",			0,	"",		false);
	//deck[10] = Card("anvil",	1,	"place",		3,	"",			0,	"",		false);
	//deck[11] = Card("carrot",	2,	"place",		3,	"",			0,	"",		false);
	//deck[12] = Card("coal",		1,	"place",		2,	"build",	1,	"or",	false);
	//deck[13] = Card("anvil",	1,	"build",		1,	"",			0,	"",		false);
	//deck[14] = Card("carrot",	1,	"build",		1,	"",			0,	"",		false);
	//deck[15] = Card("carrot",	1,	"build",		1,	"",			0,	"",		false);
	//deck[16] = Card("tree",		1,	"build",		1,	"",			0,	"",		false);
	//deck[17] = Card("tree",		1,	"build",		1,	"",			0,	"",		false);
	//deck[18] = Card("shard",	1,	"place",		2,	"",			0,	"",		false);
	//deck[19] = Card("carrot",	1,	"destroy",		1,	"place",	1,	"and",	false);
	//deck[20] = Card("shard",	1,	"move",			2,	"",			0,	"",		false);
	//deck[21] = Card("tree",		1,	"destroy",		1,	"build",	1,	"or",	false);
	//deck[22] = Card("anvil",	1,	"move",			4,	"",			0,	"",		false);
	//deck[23] = Card("anvil",	1,	"place",		3,	"move",		4,	"or",	false);
	//deck[24] = Card("anvil",	1,	"place",		3,	"move",		4,	"or",	false);
	//deck[25] = Card("carrot",	1,	"moveOver",		3,	"",			0,	"",		false);
	//deck[26] = Card("tree",		1,	"moveOver",		3,	"",			0,	"",		false);
	//deck[27] = Card("coal",		1,	"moveOver",		3,	"",			0,	"",		false);
	//deck[28] = Card("carrot",	2,	"move",			4,	"",			0,	"",		false);
	//deck[29] = Card("anvil",	1,	"move",			5,	"",			0,	"",		false);
	//deck[30] = Card("coal",		1,	"moveOver",		2,	"",			0,	"",		false);
	//deck[31] = Card("wildcard", 1,	"moveOver",		3,	"",			0,	"",		false);
	//deck[32] = Card("carrot",	1,	"move",			5,	"",			0,	"",		false);
	//deck[33] = Card("coal",		1,	"move",			2,	"",			0,	"",		false);
	//deck[34] = Card("tree",		1,	"place",		2,	"move",		3,	"or",	false);
	//deck[35] = Card("carrot",	1,	"move",			4,	"",			0,	"",		false);
	//deck[36] = Card("carrot",	1,	"place",		3,	"",			0,	"",		false);
	//deck[37] = Card("shard",	1,	"place",		1,	"",			0,	"",		false);


	if (players == 5) { // only insert these cards if the amount of players is 5
		ptrCard.push_back(CardsFactory::Create("anvil",	2,	"move",		4,	"",			0,	"",		true));
		ptrCard.push_back(CardsFactory::Create("shard",	1,	"place",	2,	"",			0,	"",		true));
		ptrCard.push_back(CardsFactory::Create("carrot",	1,	"place",	4,	"move",		2,	"or",	true));
		ptrCard.push_back(CardsFactory::Create("coal",		1,	"moveOver",	2,	"",			0,	"",		true));
	}

	//Copy contents of ptrCards into the actual deck

	for (int i = 0; i < ptrCard.size(); i++) {
		deck[i] = *ptrCard.at(i);
		ptrCard.at(i)->printCard();
	}

	//printDeckWhole();

	//deck.shrink_to_fit();
}

void Deck::initializeSpace() {
	for (int i = 0; i < space.size(); i++) {
		space[i] = deck[0];
		deck.erase(deck.begin());
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
	for (auto& i : space) {
		cout << "[" << j+1 << "] " << i.printCard() << endl;
		j++;
	}
	cout << "Card 1: Free, Card 2: 1 Coin, Card 3: 1 Coin, Card 4: 2 Coins, Card 5: 2 Coins, Card 6: 3 Coins." << endl;
}

void Deck::printDeckWhole() {
	int j = 0;
	for (auto& i : deck) {
		cout << "[" << j + 1 << "] " << i.printCard() << endl;
		j++;
	}
	cout << "Card 1: Free, Card 2: 1 Coin, Card 3: 1 Coin, Card 4: 2 Coins, Card 5: 2 Coins, Card 6: 3 Coins." << endl;
}

std::vector<Card> Deck::getDeck() const {
	return deck;
}

std::vector<Card> Deck::getSpace() const {
	return space;
}

int Deck::getDeckSize() const {
	return deck.size();
}

void Deck::draw() {
	if (!space.empty()) {
		Card card = deck[0];
		deck.erase(deck.begin());
		space.push_back(card);
	}
	else
		cout << "Card Space is full. Can't add card from deck." << endl;
}

void Deck::eraseBack() {
	space.pop_back();
}

void Deck::removeCard(int i) {
	space.erase(space.begin() + i - 1);
}