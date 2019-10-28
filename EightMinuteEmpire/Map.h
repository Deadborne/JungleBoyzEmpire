#pragma once
#include "stdafx.h"
#include <string>
#include <vector>
#include "Country.h"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
typedef boost::adjacency_list<listS, vecS, undirectedS> Graph;


class Map
{
private:
	int num;
public:
	Map();
	Map(int n);
	int getNum();
	std::vector<std::string> split(std::string _stringToBeSplit, std::string _delimeter);
	void ReadMap(std::string _Filename);

	//WELTON
	std::vector<Country> getCountries();

	Graph g;
};
