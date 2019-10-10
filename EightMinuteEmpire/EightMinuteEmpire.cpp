// EightMinuteEmpire.cpp : Defines the entry point for the console application.
//
#pragma once

#include "stdafx.h"
#include <string>
#include <iostream>
#include "Map.h"
#include "Country.h"
#include "Player.h" 
#include <ostream>
using namespace std;
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
using namespace boost;


int main()
{

	int ctry = 1;
	int ctnt = 1;
	
	Country bamerica = Country(&ctry, &ctnt);
	cout << "Country ID " << bamerica.getCountryId() << endl;
	
	typedef boost::adjacency_list<listS, vecS, undirectedS> Graph;
	Graph territories;
	typedef adjacency_list< listS, vecS, directedS > digraph;
	Graph continents;
	typedef adjacency_list< listS, vecS, directedS > digraph;

	std::string in;

	Map m;
	cout << "Alright baby boi, what map do you want to read? (Proper format is M#) \n" << endl;
	getline(cin, in);
	Graph GameMap = (m.ReadMap(in));

	//m.getCountries();
	

	m.purge();
	
	//Desire index should be 6
	//vector<int>::iterator result;

	//result = max_element(test.begin(), test.end());
	//cout << "Max element at: " << std::distance(test.begin(), result) << '\n';
	//cout << "\nMax element is: " << *result;

	//
	//bool duplicatesExist = false;
	////TESTING
	//for (int i = 0; ((i < test.size()) && (duplicatesExist == false)); i++) {
	//	for (int j = i + 1; j < test.size(); j++) {
	//		if ((test.at(i) == test.at(j)) && (test.at(i) == *result)) {
	//			cout << "\nDuplicate value " << test.at(i)
	//				<< " at indices " << i << ", " << j << endl;
	//			duplicatesExist = true;
	//		}
	//	}
	//}

	//if (duplicatesExist == true) {
	//	cout << "Bitch yeh";
	//}else {
	//	cout << "Bitch nah";
	//}		
	

	return 0;
}