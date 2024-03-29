#include "stdafx.h"
#include "Card.h"
#include <iostream>
using namespace std;

Card::Card() :
	good(""),
	amount(0),
	action1(""),
	num1(0),
	action2(""),
	num2(0),
	operate(""),
	isFive(false)
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
	good(gd),
	amount(num),
	action1(act1),
	num1(n1),
	action2(act2),
	num2(n2),
	operate(op),
	isFive(n5)
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

int Card::getNumA1() const {
	return num1;
}

std::string Card::getAction2() const {
	return action2;
}

int Card::getNumA2() const {
	return num2;
}

std::string Card::getOperator() const {
	return operate;
}

bool Card::getIsFive() const {
	return isFive;
}

string Card::printCard() {
	string str = "Goods: " + to_string(Card::getGoodAmount()) + " " + Card::getGood() + ", Action 1: " + Card::getAction1() + "x" + to_string(Card::getNumA1()) + ", Action 2: " + Card::getAction2() + "x" + to_string(Card::getNumA2());
	return str;
}

string Card::formatAction(std::string action, std::string number) {
	string formattedString = "";
	if (action == "build") {
		formattedString = "You can build one city in a region you occupy";
	}
	else if (action == "destroy") {
		formattedString = "You can destroy " + number + " opponent armies";
	}
	else if (action == "move") {
		formattedString = "You can move " + number + " of your own armies within their own respective continents";
	}
	else if (action == "moveOver") {
		formattedString = "You can move " + number + " of your own armies, even across continents";
	}
	else if (action == "place") {
		formattedString = "You can place " + number + " armies";
	}

	return formattedString;

}

//Factory Pattern -->
TreeCard::TreeCard(int goodAmount, string action1, int n1, string action2, int n2, string op, bool n5) :
	Card("tree", goodAmount, action1, n1, action2, n2, op, n5)
{}
TreeCard::~TreeCard() {}

AnvilCard::AnvilCard(int goodAmount, string action1, int n1, string action2, int n2, string op, bool n5) :
	Card("anvil", goodAmount, action1, n1, action2, n2, op, n5)

{}
AnvilCard::~AnvilCard() {}

CarrotCard::CarrotCard(int goodAmount, string action1, int n1, string action2, int n2, string op, bool n5) : 
	Card("carrot", goodAmount, action1, n1, action2, n2, op, n5)
{}
CarrotCard::~CarrotCard() {}

CoalCard::CoalCard(int goodAmount, string action1, int n1, string action2, int n2, string op, bool n5) :
	Card("coal", goodAmount, action1, n1, action2, n2, op, n5)
{}
CoalCard::~CoalCard() {}

ShardCard::ShardCard(int goodAmount, string action1, int n1, string action2, int n2, string op, bool n5) :
	Card("shard", goodAmount, action1, n1, action2, n2, op, n5)
{}
ShardCard::~ShardCard() {}

WildCard::WildCard(int goodAmount, string action1, int n1, string action2, int n2, string op, bool n5) :
	Card("wildcard", goodAmount, action1, n1, action2, n2, op, n5)
{}
WildCard::~WildCard() {}
