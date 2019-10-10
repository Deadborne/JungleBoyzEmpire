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
	int cid;
	int* _countryId;
	int* _continentId;
	int* _countryOwner;
	bool* _isStart = false;
	vector<int> _armiesPerPlayer{ 3,1,3,5,4 };
	vector<bool> _cities{ false, false, false, false, false };

public:
	Country();
	Country(int* _countryId, int* _continentId);
	Country(int* _countryId, int* _continentId, bool* _isStart);
	Country(int* _countryId, int* _continentId, vector<int> _armiesPerPlayer);
	Country(int* _countryId, int* _continentId, vector<int> _armiesPerPlayer, bool* _isStart);

	int getCountryId();
	int getContinentId();
	int getOwner();

	void setCountryId(int* _countryId);
	void setContinentId(int* _continentId);
	void setStarterStatus(bool* _status);

	void buildCity(int _playerId);
	void setOwner(int _countryId);
	bool hasCity(int _playerId);

	vector<int> getArmiesPerPlayer();
	void printArmies();

	vector<bool> getCities();
	void setCities(vector<bool> newCities);

	typedef boost::adjacency_list<listS, vecS, undirectedS> Graph;

	//todo
	bool Country::isConnected(Graph _g, Country _c2);
	bool Country::isAdjacent(Graph _g, Country _c2);

	void setArmiesPerPlayer(vector<int> newArmies);
};
