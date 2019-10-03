#include "Card.h"
#include <iostream>
using std::cout;
using std::endl;

Card::Card() :
	good(""),
	amount(0),
	action1(""),
	action2(""),
	operate("")
{}

Card::Card(std::string gd, int am, std::string act1, std::string act2, std::string op) :
	good(gd),
	amount(am),
	action1(act1),
	action2(act2),
	operate(op)
{}

Card::Card(const Card &c) :
	good(c.good),
	amount(c.amount),
	action1(c.action1),
	action2(c.action2),
	operate(c.operate)
{}

Card::~Card() {}

std::string Card::getGood() const {
	return good;
}

int Card::getGoodAmount() const {
	return amount;
}

std::string Card::getAction1() const {
	return action1;
}

std::string Card::getAction2() const {
	return action2;
}

std::string Card::getOperator() const {
	return operate;
}
