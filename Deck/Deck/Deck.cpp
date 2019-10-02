// Deck.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <vector>
#include "Card.h"
#include <iostream>
using std::cout;
using std::endl;
using std::string;
using std::vector;

int main()
{
    std::cout << "Hello World!\n";

	// Deck Object
	vector<Card> deck;
	vector<Card> hand;

	Card c1("coal", "Spawn 5", "Move 2");
	deck[0] = c1;
	Card c2("wildcard", "Move 2", "");
	deck[1] = c2;

}

// Player draws card from top of deck and places at the hand space
Card draw(vector<Card> d, vector<Card> h) {
	h[h.size()-1] = d[0];
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
