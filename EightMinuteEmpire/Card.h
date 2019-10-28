#pragma once
#include "stdafx.h"
#include <string>

class Card {
private:
	std::string good;
	int amount;
	std::string action1;
	int num1;
	std::string action2;
	int num2;
	std::string operate;
	bool isFive;

public:
	Card();
	Card(std::string gd, int num, std::string act1, int n1, std::string act2, int n2, std::string op, bool n5);
	Card(const Card& c);
	~Card();
	std::string getGood() const;
	int getGoodAmount() const;
	std::string getAction1() const;
	int getNumA1() const;
	std::string getAction2() const;
	int getNumA2() const;
	std::string getOperator() const;
	bool getIsFive() const;
};