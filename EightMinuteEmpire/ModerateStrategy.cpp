#include "stdafx.h"
#include <string>
#include <iostream>
#include "Map.h"
#include "Country.h"
#include "Player.h"
#include "Npc.h" 
#include "Card.h"
#include "Strategy.h"
#include <ostream>
#include <vector>
using namespace std;
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>
using namespace boost;


const int ModerateStrategy::getCard(vector<Card> deck) {
	return 0;
}

const int ModerateStrategy::getChoice(Card card) {
	string str1 = card.getAction1();
	string str2 = card.getAction2();

	if (str2 == "")
		return 0;
	else {
		if (card.getOperator() == "or") {
			if (card.getAction1() == "destroy" || card.getAction1() == "build" || card.getAction1() == "moveOver" || card.getAction1() == "place")
				return 0;
			else
				return 1;
		}
	}
}

const string ModerateStrategy::getAction(Card card, int choice) {
	if (choice == 0)
		return card.getAction1();
	else
		return card.getAction2();
}

//const int ModerateStraegy::getMove()