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
#include <cstdlib>


const int ModerateStrategy::getCard(vector<Card> deck, Player player) {
	int choice = 0;
	for (int i = 0; i < deck.size(); i++) {
		if (deck[i].getAction1() == "place" || deck[i].getAction2() == "place")
			choice = i;
		else if (deck[i].getAction1() == "move" || deck[i].getAction2() == "Move")
			choice = i;
		else if (deck[i].getAction1() == "moveOver" || deck[i].getAction2() == "moveOver")
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

const int ModerateStrategy::getChoice(Card card) {
	string str1 = card.getAction1();
	string str2 = card.getAction2();

	if (str2 == "")
		return 0;
	else {
		if (card.getOperator() == "or") {
			if (card.getAction1() == "place" || card.getAction1() == "move" || card.getAction1() == "moveOver")
				return 0;
			else if (card.getAction1() == "place" || card.getAction1() == "move" || card.getAction1() == "moveOver")
				return 1;
			else
				return 0;
		}
	}
}

const string ModerateStrategy::getAction(Card card, int choice) {
	if (choice == 0)
		return card.getAction1();
	else
		return card.getAction2();
}

/*
const int ModerateStrategy::random(int min, int max) { //range : [min, max) 
	static bool first = true;
	if (first)
	{
		srand(time(NULL));
		first = false;
	}
	return min + rand() % ((max + 1) - min);
}
*/