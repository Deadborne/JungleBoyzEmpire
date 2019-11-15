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
using namespace std;
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>
using namespace boost;


class Strategy {
public:
	virtual const int getCard() = 0;
	virtual const int getChoice() = 0;
	virtual const int getAction(string str) = 0;
};

class GreedStrategy : Strategy {
public:
	const int getCard();
	const int getChoice();
	const int getAction(string str);
};

class ModerateStrategy : Strategy {
public:
	const int getCard();
	const int getChoice();
	const int getAction(string str);
};
