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
#include "Strategy.h"
using namespace std;
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>
using namespace boost;

class Npc : Player {
private:
	Strategy* strategy;
public:
	Npc() {};
	Npc(Strategy* initStrategy) {};
	void setStrategy(Strategy* newStrategy);
};
