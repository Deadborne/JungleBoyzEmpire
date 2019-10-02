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
		Card(std::string mat, std::string act1, std::string act2);
		~Card();
		std::string getMaterial() const;
		std::string getAction1() const;
		std::string getAction2() const;

};
