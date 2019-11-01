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
	bool* _isStart;
	vector<int*> _armiesPerPlayer{ new int(0), new int(0), new int(0), new int(0), new int(0) };
	vector<bool*> _cities{ new bool (false), new bool(false), new bool(false), new bool(false), new bool(false) };

public:
	Country();
	Country(int* _countryId, int* _continentId);
	Country(int* _countryId, int* _continentId, bool* _isStart);
	Country(int* _countryId, int* _continentId, vector<int*> _armiesPerPlayer);
	Country(int* _countryId, int* _continentId, vector<int*> _armiesPerPlayer, bool* _isStart);

	int getCountryId();
	int getContinentId();
	int getOwner();

	void setCountryId(int* _countryId);
	void setContinentId(int* _continentId);
	void setStarterStatus(bool* _status);

	void buildCity(int _playerId);
	void setOwner();
	bool hasCity(int _playerId);
	bool isStartingCountry();

	vector<int*> getArmiesPerPlayer();
	void printArmies();

	vector<bool*> getCities();
	void setCities(vector<bool*> newCities);

	typedef boost::adjacency_list<listS, vecS, undirectedS> Graph;

	bool Country::isConnected(Graph _g, Country _c2);
	bool Country::isAdjacent(Graph _g, Country _c2);
	void showAdjacencies(Graph _g);
	vector<int> returnAdjacencies(Graph _g);

	void setArmiesPerPlayer(vector<int*> newArmies);
};
