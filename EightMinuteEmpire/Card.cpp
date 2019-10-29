#include "Card.h"
#include <iostream>
using namespace std;

Card::Card() :
	good(new string("")),
	amount(new int(0)),
	action1(new string("")),
	num1(new int(0)),
	action2(new string("")),
	num2(new int(0)),
	operate(new string("")),
	isFive(new bool(false))
{}

// gd = good string
// num = amount of good (1 or 2)
// act1 = string of action1
// n1 = amount of blocks used for action1
// act = string of action2
// n2 = amount of blocks used for action2
// op = operator "and" or "or" or "" for cards with two actions
// n5 = boolean that checks whether card is placed on deck
Card::Card(std::string gd, int num, std::string act1, int n1, std::string act2, int n2, std::string op, bool n5) :
	good(&gd),
	amount(&num),
	action1(&act1),
	num1(&n1),
	action2(&act2),
	num2(&n2),
	operate(&op),
	isFive(&n5)
{}

// Copy Constructor
Card::Card(const Card &c) :
	good(c.good),
	amount(c.amount),
	action1(c.action1),
	num1(c.num1),
	action2(c.action2),
	num2(c.num2),
	operate(c.operate),
	isFive(c.isFive)
{}

// Card Destructor
Card::~Card() {
	good = NULL;
	amount = NULL;
	action1 = NULL;
	num1 = NULL;
	num2 = NULL;
	operate = NULL;
	isFive = NULL;
}

void Card::printCard() {
	cout << "Goods: " << *good << " x " << *amount << " " << *good << ", Action 1: " << *action1 + "x" << *num1 << ", Action 2: " << *action2 << "x" << *num2 << " 5-Player-Card: " << *isFive << endl;
}
