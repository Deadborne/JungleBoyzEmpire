#pragma once
#include <string>

class Card {
	private:
		bool isWildcard;
		std::string material;
		std::string action1;
		std::string action2;

	public:
		Card();
		Card(bool wildcard, std::string mat, std::string act1, std::string act2);
		~Card();
		bool isWild() { return isWildcard; }
		std::string getMaterial() const { return material; }
		std::string getAction1() const { return action1; }
		std::string getAction2() const { return action2; }




};
