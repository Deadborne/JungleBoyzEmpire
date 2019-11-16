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
using namespace boost;

const int GreedStrategy::getCard(vector<Card> deck) {
	for (int i = 0; i < deck.size(); i++) {
		if (deck[i].getAction1() == "destroy" || deck[i].getAction2() == "destroy")
			return i;
		else if (deck[i].getAction1() == "build" || deck[i].getAction2() == "build")
			return i;
		else if (deck[i].getAction1() == "moveOver" || deck[i].getAction2() == "moveOver")
			return i;
		else if (deck[i].getAction1() == "place" || deck[i].getAction2() == "place")
			return i;
		else
			return i;
	}
}

const int GreedStrategy::getChoice(Card card) {
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

const string GreedStrategy::getAction(Card card, int choice) {
	if (choice == 0)
		return card.getAction1();
	else
		return card.getAction2();
}