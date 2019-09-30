#include "Card.h"
#include <iostream>
using std::cout;
using std::endl;

Card::Card() : isWildcard(false) {
	cout << "Card Constructed" << endl;
}

Card::Card(bool wcard, std::string mat, std::string act1, std::string act2) :
	isWildcard(wcard),
	material(mat),
	action1(act1),
	action2(act2)

{
	cout << "Card Constructed" << endl;
}

Card::~Card() {
	cout << "Card Destructed" << endl;
}