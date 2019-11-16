#include "stdafx.h"
#include <string>
#include <iostream>
#include "Map.h"
#include "Country.h"
#include "Player.h" 
#include "Card.h"
#include "Strategy.h"
#include <ostream>
#include <vector>
#include <string>
using namespace std;
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>
#include "Npc.h"
using namespace boost;

Npc::Npc() {
	Strategy* strategy = nullptr;
};

/*
Npc::Npc(Strategy* initStrategy) {
	this->strategy = initStrategy;
};

Npc::~Npc() {};

void Npc::setStrategy(Strategy* newStrategy) {
	this->strategy = newStrategy;
}
*/