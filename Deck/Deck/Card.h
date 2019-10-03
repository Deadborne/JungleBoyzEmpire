#pragma once
#include <string>

class Card {
	private:
		std::string good;
		int amount;
		std::string action1;
		std::string action2;
		std::string operate;

	public:
		Card();
		Card(std::string gd, int num, std::string act1, std::string act2, std::string op);
		Card(const Card &c);
		~Card();
		std::string getGood() const;
		int getGoodAmount() const;
		std::string getAction1() const;
		std::string getAction2() const;
		std::string getOperator() const;

};
