#include "stdafx.h"
#include "CardsFactory.h"


CardsFactory::CardsFactory() {}

CardsFactory::~CardsFactory() {}

Card* CardsFactory::Create(string good, int goodAmount, string action1, int n1, string action2, int n2, string op, bool n5) {

	if (good == "tree")
		return new TreeCard(goodAmount, action1, n1, action2, n2, op, n5);
	else if (good == "anvil")
		return new AnvilCard(goodAmount, action1, n1, action2, n2, op, n5);
	else if (good == "carrot")
		return new CarrotCard(goodAmount, action1, n1, action2, n2, op, n5);
	else if (good == "coal")
		return new CoalCard(goodAmount, action1, n1, action2, n2, op, n5);
	else if (good == "shard")
		return new ShardCard(goodAmount, action1, n1, action2, n2, op, n5);
	else if (good == "wildcard")
		return new WildCard(goodAmount, action1, n1, action2, n2, op, n5);
	
		

	
}


