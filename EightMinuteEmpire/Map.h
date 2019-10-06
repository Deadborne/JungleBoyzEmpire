#pragma once
#include "stdafx.h"
#include <string>
#include <vector>
#include "Country.h"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>



class Map
{
private:
	int num;
	std::vector<Country> mappedCountries;
	int countrySize;
public:
	Map();
	Map(int n);
	int getNum();
	std::vector<std::string> split(std::string _stringToBeSplit, std::string _delimeter);
	void ReadMap(std::string _Filename);

	//WELTON
	std::vector<Country> getCountries();
};
