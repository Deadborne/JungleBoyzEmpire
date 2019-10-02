#include "Card.h"
#include <iostream>
using std::cout;
using std::endl;

Card::Card() : {
	cout << "Card Constructed" << endl;
}

Card::Card(std::string mat, std::string act1, std::string act2) :
	material(mat),
	action1(act1),
	action2(act2)

{
	cout << "Card Constructed" << endl;
}

Card::~Card() {
	cout << "Card Destructed" << endl;
}

inline std::string Card::getMaterial() const {
	return material;
}

inline std::string Card::getAction1() const {
	return action1;
}

inline std::string Card::getAction2() const {
	return action2;
}