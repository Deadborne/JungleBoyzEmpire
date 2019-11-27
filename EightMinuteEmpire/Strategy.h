#pragma once

#include "stdafx.h"
#include <string>
#include <iostream>
#include "Map.h"
#include "Country.h"
#include "Player.h" 
#include "Card.h"
#include <ostream>
#include <vector>
#include <string>
using namespace std;
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>
using namespace boost;


class Strategy {
public:
	virtual const int getCard(vector<Card> deck, int coins) = 0; // return the index of the card chosen in the card space
	virtual const int getChoice(Card card) = 0; // return 0 for choosing action1 and return 1 for action 2
	virtual const string getAction(Card card, int actionChoice) = NULL; // return the action chosen in a form of string
};

class GreedStrategy : public Strategy {
public:
	const int getCard(vector<Card> deck, int coins);
	const int getChoice(Card card);
	const string getAction(Card card, int actionChoice);
};

class ModerateStrategy : public Strategy {
public:
	const int getCard(vector<Card> deck, int coins);
	const int getChoice(Card card);
	const string getAction(Card card, int actionChoice);
};
