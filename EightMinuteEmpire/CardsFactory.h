#pragma once

#include "Card.h"

#include <string>

using namespace std;





class CardsFactory {

public:
	~CardsFactory();

	static Card* Create(string good, int goodAmount, string action1, int n1, string action2, int n2, string op, bool n5);
		//Based on the good that gets passed, pass that information to a constructor of individual classes that inherit from the Card superclass


private:
	CardsFactory();

};