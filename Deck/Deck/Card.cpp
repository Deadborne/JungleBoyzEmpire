#include "Card.h"
#include <iostream>
using std::cout;
using std::endl;

Card::Card() {
	cout << "Card Default Constructed" << endl;
}

Card::Card(std::string gd, int am, std::string act1, std::string act2, std::string op) :
	good(gd),
	amount(am),
	action1(act1),
	action2(act2),
	operate(op)
{
	cout << "Card Constructed" << endl;
}

Card::Card(const Card &c) :
	good(c.good),
	amount(c.amount),
	action1(c.action1),
	action2(c.action2),
	operate(c.operate)
{
	cout << "Card Constructed and Copied" << endl;
}

Card::~Card() {
	cout << "Card Destructed" << endl;
}

inline std::string Card::getGood() const {
	return good;
}

inline int Card::getGoodAmount() const {
	return amount;
}

inline std::string Card::getAction1() const {
	return action1;
}

inline std::string Card::getAction2() const {
	return action2;
}

inline std::string Card::getOperator() const {
	return operate;
}