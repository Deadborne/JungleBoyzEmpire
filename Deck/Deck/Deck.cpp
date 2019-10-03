// Deck.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <time.h>
#include <vector>
#include "Card.h"
#include <iostream>
#include <algorithm>
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::random_shuffle;

void shuffleDeck(vector<Card> d);
void draw(vector<Card> d, vector<Card> h);
void printDeck(vector<Card> d);

int main()
{
    cout << "Hello World!\n";

	// Deck Object
	vector<Card> deck(42);
	// Hand Object with face-up cards
	vector<Card> hand(6);

	deck[0] = Card("shard", 1, "move 2", "", "");
	deck[1] = Card("anvil", 1, "place 3", "move 3", "or");
	deck[2] = Card("anvil", 2, "move 4", "", "");
	deck[3] = Card("anvil", 1, "move 4", "", "");
	deck[4] = Card("tree", 1, "move 6", "", "");
	deck[5] = Card("tree", 1, "move 3", "", "");
	deck[6] = Card("anvil", 1, "place 3", "", "");
	deck[7] = Card("shard", 1, "place 2", "", "");
	deck[8] = Card("wildcard", 1, "moveOver 2", "", "");
	deck[9] = Card("tree", 1, "moveOver 4", "", "");
	deck[10] = Card("anvil", 1, "moveOver 3", "", "");
	deck[11] = Card("wildcard", 1, "place 2", "", "");
	deck[12] = Card("coal", 1, "place 2", "", "");
	deck[13] = Card("shard", 1, "place 2", "", "");
	deck[14] = Card("coal", 1, "place 3", "", "");
	deck[15] = Card("anvil", 1, "place 3", "", "");
	deck[16] = Card("carrot", 2, "place 3", "", "");
	deck[17] = Card("coal", 1, "place 2", "build", "or");
	deck[18] = Card("anvil", 1, "build", "", "");
	deck[19] = Card("carrot", 1, "build", "", "");
	deck[20] = Card("carrot", 1, "build", "", "");
	deck[21] = Card("tree", 1, "build", "", "");
	deck[22] = Card("tree", 1, "build", "", "");
	deck[23] = Card("shard", 1, "place 2", "", "");
	deck[24] = Card("carrot", 1, "destroy", "place 1", "and");
	deck[24] = Card("carrot", 1, "place 4", "move 2", "or");
	deck[25] = Card("tree", 1, "destroy", "build", "or");
	deck[26] = Card("coal", 1, "moveOver 2", "", "");


	// shuffles deck before game
	shuffleDeck(deck);
	printDeck(deck);

	return 0;

}

// Player draws card from top of deck and places at the hand space
void draw(vector<Card> d, vector<Card> h) {
	h[h.size()-1] = d[0];
}

// Shuffle deck method
void shuffleDeck(vector<Card> d) {
	srand(unsigned(time(NULL)));
	random_shuffle(d.begin(), d.end());
}

// Print cards from deck based on their good
void printDeck(vector<Card> d) {
	for (auto& i : d)
		cout << "Goods: " << i.getGoodAmount() << " " << i.getGood() << endl;
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
