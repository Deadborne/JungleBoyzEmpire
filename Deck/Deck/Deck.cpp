// Deck.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <vector>
#include "Card.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <iterator>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::shuffle;
using std::mt19937;
using std::random_device;
using std::to_string;

// shuffles deck randomely with different combinations in each file execution
vector<Card> shuffleDeck(vector<Card> d);
// draw a card from the deck and place it to the hand space
void draw(vector<Card> d, vector<Card> h);
// print deck of 
void printDeck(vector<Card> d);

int main()
{
    cout << "Hello World!\n";

	// Deck Object
	vector<Card> deck(42);
	// Hand Object with 6 face-up cards
	vector<Card> hand(6);

	int players = 0;
	cout << "Enter amount of Players: ";
	cin >> players;
	while (players < 2 || players > 5) {
		cout << "Invalid amount of players. Must be between 2 and 5: ";
		cin >> players;
	}
	cout << "You chose " << players << " players";


	// Fill deck with cards
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

	if (players == 5) {
		deck[38] = Card("anvil", 2, "move", 4, "", 0, "", true);
		deck[39] = Card("shard", 1, "place", 2, "", 0, "", true);
		deck[40] = Card("carrot", 1, "place", 4, "move", 2, "or", true);
		deck[41] = Card("coal", 1, "moveOver", 2, "", 0, "", true);
	}

	cout << "\n" << endl;

	// Move 6 front cards from Deck to Hand object
	for (int i = 0; i < hand.size(); i++) {
		hand[i] = deck[0];
		deck.erase(deck.begin());
		deck.size();
	}

	// Print shuffled deck
	printDeck(shuffleDeck(deck));
	// Print hand for display 
	printDeck(hand);

	return 0;

}

// Player draws card from top of deck and places at the hand space
void draw(vector<Card> d, vector<Card> h) {
	h[h.size()-1] = d[0];
}

// Shuffle deck method
vector<Card> shuffleDeck(vector<Card> d) {
	random_device rd;
	mt19937 g(rd());

	shuffle(d.begin(), d.end(), g);
	return d;
}

// Print cards from deck based on their good
void printDeck(vector<Card> d) {
	int j = 0;
	string str;
	for (auto& i : d) {
		str = "[" + to_string(j) + "] " + "Goods" + to_string(i.getGoodAmount()) + " " + i.getGood() + ", Action 1: " + i.getAction1() + "x" + to_string(i.getNumA1()) + ", Action 2: " + i.getAction2() + "x" + to_string(i.getNumA2()) + " 5-Player-Card: " + to_string(i.getIsFive());
		cout << str << endl;
		j++;
	}
}

void printCard(vector<Card> d, int i) {
	string str = "[" + to_string(i) + "] " + "Goods" + to_string(d[i].getGoodAmount()) + " " + d[i].getGood() + ", Action 1: " + d[i].getAction1() + "x" + to_string(d[i].getNumA1()) + ", Action 2: " + d[i].getAction2() + "x" + to_string(d[i].getNumA2()) + " 5-Player-Card: " + to_string(d[i].getIsFive());
	cout << str << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
