#pragma once
#include "stdafx.h"
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
using namespace boost;


using namespace std;
class Country
{
private:
	int _countryId;
	int _continentId;
	int _countryOwner = -1;
	bool _isStart = false;
	vector<int> _armiesPerPlayer{ 5,8,3,4,2 };
	vector<bool> _cities{ false, false, false, false, false };

public:
	Country();
	Country(int _countryId, int _continentId);
	Country(int _countryId, int _continentId, bool _isStart);
	Country(int _countryId, int _continentId, vector<int> _armiesPerPlayer);
	int getCountryId();
	int getOwner();
	void buildCity(int _playerId);
	void setOwner(int _countryId);
	bool hasCity(int _playerId);
	vector<int> getArmiesPerPlayer();
	void printArmies();
	vector<bool> getCities();
	void setCities(vector<bool> newCities);

	typedef boost::adjacency_list<listS, vecS, undirectedS> Graph;
	bool Country::isConnected(Graph _g, Country _c2);
	bool Country::isAdjacent(Graph _g, Country _c2);

	void setArmiesPerPlayer(vector<int> newArmies);
};
