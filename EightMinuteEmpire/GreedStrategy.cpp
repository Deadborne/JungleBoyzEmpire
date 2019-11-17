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

const int GreedStrategy::getCard(vector<Card> deck, Player player) {
	int choice = 0;
	for (int i = 0; i < deck.size(); i++) {
		if (deck[i].getAction1() == "destroy" || deck[i].getAction2() == "destroy")
			choice = i;
		else if (deck[i].getAction1() == "build" || deck[i].getAction2() == "build")
			choice = i;
		else if (deck[i].getAction1() == "moveOver" || deck[i].getAction2() == "moveOver")
			choice = i;
		else if (deck[i].getAction1() == "place" || deck[i].getAction2() == "place")
			choice = i;
		else
			continue;
	}

	if (choice == 0)
		return choice;
	else if (choice == 1 || choice == 2) {
		if (player.getAvailableCoins() > 0) {
			player.PayCoin();
			return choice;
		}
		else
			return 0;
	}
	else if (choice == 3 || choice == 4) {
		if (player.getAvailableCoins() > 1) {
			player.PayCoin(2);
			return choice;
		}
		else
			return 0;
	}
	else if (choice == 5) {
		if (player.getAvailableCoins() > 2) {
			player.PayCoin(3);
			return choice;
		}
		else
			return 0;
	}
	return 0;
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
			else if (card.getAction2() == "destroy" || card.getAction2() == "build" || card.getAction2() == "moveOver" || card.getAction2() == "place")
				return 1;
			else
				return 0;
		}
	}
}

const string GreedStrategy::getAction(Card card, int actionChoice) {
	if (actionChoice == 0)
		return card.getAction1();
	else
		return card.getAction2();
}