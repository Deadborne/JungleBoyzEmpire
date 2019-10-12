#pragma once
#include "stdafx.h"
#include <string>
#include <vector>
#include "Country.h"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>



class Map
{

public:
	Map();
	std::vector<std::string> split(std::string _stringToBeSplit, std::string _delimeter);

	typedef boost::adjacency_list<listS, vecS, undirectedS> Graph;
	Graph ReadMap(std::string _Filename);
	void purge();
	std::vector<Country> getCountries();
};
