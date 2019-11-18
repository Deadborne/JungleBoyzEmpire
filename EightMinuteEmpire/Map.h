#pragma once
#include "stdafx.h"
#include <string>
#include <vector>
#include "Country.h"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include "Player.h"
typedef boost::adjacency_list<listS, vecS, undirectedS> Graph;


class Map
{

private:
	int* startingCountry;
	static Map* mapInstance;
	Map();

	vector<Player*> players;
public:
	
	std::vector<std::string> split(std::string _stringToBeSplit, std::string _delimeter);

	typedef boost::adjacency_list<listS, vecS, undirectedS> Graph;
	Graph ReadMap(std::string _Filename);
	void purge();
	std::vector<Country> getCountries();

	void showEverything();
	Country getStartingCountry();
	Country giveMeCountry(int id);

	vector<int> getContinents();
	void setCountry(std::vector<Country> countries);

	static Map* instance(); //lazy instantiation
	static void resetInstance();

	vector<Player*> getPlayers();
	void setPlayers(vector<Player*> x);

};
