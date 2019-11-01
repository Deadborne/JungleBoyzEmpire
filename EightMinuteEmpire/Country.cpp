#pragma once
#include "stdafx.h"
#include "Country.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
using namespace boost;

//default constructor
Country::Country() 
{
}
//constructor, takes countryID and continentId
Country::Country(int* countryId, int* continentId) : _countryId(countryId), _continentId(continentId), _isStart(false)
{
}
//constructor, takes countryID, continentId, and a boolean for starting country or not
Country::Country(int* countryId, int* continentId, bool* isStart) : _countryId(countryId), _continentId(continentId), _isStart(isStart)
{
}
//constructor, takes countryID, continentId, and the armies vector
Country::Country(int* countryId, int* continentId, vector<int*> armiesPerPlayer) : _countryId(countryId), _continentId(continentId), _armiesPerPlayer(armiesPerPlayer),_isStart(false)
{
}
//constructor, takes countryID, continentId, the armies vector and whether it's a starting country or not
Country::Country(int* countryId, int* continentId, vector<int*> armiesPerPlayer, bool* isStart) : _countryId(countryId), _continentId(continentId), _armiesPerPlayer(armiesPerPlayer), _isStart(isStart)
{
}

//----Mutators & Accessors----//

//Returns vector of cities for a given country
vector<bool*> Country::getCities() {
	return _cities;
}

//Allows us to set the city vector for a given country
void Country::setCities(vector<bool*> newCities) {
	_cities = newCities;
}

//returns the ID of the country
int Country::getCountryId(){
	return  *_countryId;
};

//returns the ID of the continent
int Country::getContinentId() {
	return  *_continentId;
};

//Public accessor for armiesPerPlayer
vector<int*> Country::getArmiesPerPlayer() {
	return _armiesPerPlayer;
}

//Setter for armiesPerPlayer
void Country::setArmiesPerPlayer(vector<int*> newArmies) {
	_armiesPerPlayer = newArmies;
}

//Checks if the country is the starting city
bool Country::isStartingCountry() {
	return _isStart;
}


//----Other Functionality----//

//sets the owner of the country
void Country::setOwner()
{
	int currMax = 0;
	int *owner;
	owner = new int(-1);

	for (int i = 0; i < Country::_armiesPerPlayer.size(); i++) 
	{
		if (*_armiesPerPlayer[i] > currMax)
		{
			*owner = i+1;
			currMax = *_armiesPerPlayer[i];
		}
		else if (*_armiesPerPlayer[i] == currMax)
		{
			*owner = -1;
			break;
		}
	}
	_countryOwner = owner;
}

//sets the country ID
void Country::setCountryId(int* countryId) {
	_countryId = countryId;
}

//sets the continent ID
void Country::setContinentId(int* continentId) {
	_continentId = continentId;
}

//sets whether this is the starting country or not
void Country::setStarterStatus(bool* status) {
	_isStart = status;
}

//builds a city in this country for the player being passed.
void Country::buildCity(int playerId)
{
	*_cities[playerId] = true;
}

//tells you who the owner of the country is
int Country::getOwner() 
{
	return *_countryOwner;
}

//checks if the player being passed as a param has a city in this country
bool Country::hasCity(int playerId) {
	if (*_cities[playerId] == true)
		return true;
	else 
		return false;
}


//Prints the armies in the country from which this function is called - W
void Country::printArmies() {
	for (int i = 0; i < _armiesPerPlayer.size(); i++) {
		cout << *_armiesPerPlayer.at(i) << " ";
	}
	/*vector<int*>::iterator iter;
	for (iter = _armiesPerPlayer.begin(); iter != _armiesPerPlayer.end(); ++iter)
		std::cout << **iter;*/
}

//tells you if two countries are connected (whether over land or sea)
typedef boost::adjacency_list<listS, vecS, undirectedS> Graph;
bool Country::isConnected(Graph g, Country c2) {

	//stuff we need
	vector<int> checker = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	typedef boost::graph_traits<Graph>::adjacency_iterator AdjacencyIterator;
	AdjacencyIterator ai, a_end;
	auto vertex_idMap = get(boost::vertex_index, g);
	int baditerator = 0;
	bool confirm = false;

	//store adjacencies in checker vector
	for (boost::tie(ai, a_end) = adjacent_vertices(*_countryId, g); ai != a_end; ++ai) {
		int e;
		e = vertex_idMap[*ai];
		checker[baditerator] = e;
		baditerator++;
	}

	//checker is now a vector of all adjacencies. Now we check if c2 is within that vector.
	for (int i = 0; i < 11; i++) {
		if (checker[i] != *c2._countryId)
			confirm = false;
		else {
			confirm = true;
			break;
		}
	}
	return confirm;
}

//tells you if two countries are connected over land only
bool Country::isAdjacent(Graph g, Country c2) {

	//stuff we need
	vector<int> checker = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	typedef boost::graph_traits<Graph>::adjacency_iterator AdjacencyIterator;
	AdjacencyIterator ai, a_end;
	auto vertex_idMap = get(boost::vertex_index, g);
	int baditerator = 0;
	bool confirm = false;

	//store adjacencies in checker vector
	for (boost::tie(ai, a_end) = adjacent_vertices(*_countryId, g); ai != a_end; ++ai) {
		int e;
		e = vertex_idMap[*ai];
		checker[baditerator] = e;
		baditerator++;
	}

	//checker is now a vector of all adjacencies. Now we check if c2 is within that vector.
	for (int i = 0; i < 11; i++) {
		if ((checker[i] != *c2._countryId) && (_continentId != c2._continentId))
			confirm = false;
		else {
			confirm = true;
			break;
		}
	}
	return confirm;
}

//prints a country's adjacencies
void Country::showAdjacencies(Graph g) {

	//stuff we need
	vector<int> checker = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	typedef boost::graph_traits<Graph>::adjacency_iterator AdjacencyIterator;
	AdjacencyIterator ai, a_end;
	auto vertex_idMap = get(boost::vertex_index, g);
	int baditerator = 0;
	bool confirm = false;

	//store adjacencies in checker vector
	for (boost::tie(ai, a_end) = adjacent_vertices(*_countryId, g); ai != a_end; ++ai) {
		int e;
		e = vertex_idMap[*ai];
		checker[baditerator] = e;
		baditerator++;
	}

	//sort the adjacencies, and don't show duplicates
	sort(checker.begin(), checker.end());
	checker.erase(unique(checker.begin(), checker.end()), checker.end());

	//show adjacencies, and don't show -1 or redundant info
	for (int i = 0; i < checker.size(); i++) {
		if (i != 0)
			cout << " ";
		if (checker[i] != -1)
			cout << checker[i];
	}
}

//returns the country's adjacencies as a vector of countryID's
vector<int> Country::returnAdjacencies(Graph g) {

	//stuff we need
	vector<int> checker = {};
	typedef boost::graph_traits<Graph>::adjacency_iterator AdjacencyIterator;
	AdjacencyIterator ai, a_end;
	auto vertex_idMap = get(boost::vertex_index, g);
	bool confirm = false;

	//store adjacencies in checker vector
	for (boost::tie(ai, a_end) = adjacent_vertices(*_countryId, g); ai != a_end; ++ai) {
		int e;
		e = vertex_idMap[*ai];
		checker.push_back(e);
	}

	//sort the adjacencies, and don't show duplicates
	sort(checker.begin(), checker.end());
	checker.erase(unique(checker.begin(), checker.end()), checker.end());
	return checker;
}



