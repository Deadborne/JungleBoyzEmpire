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

	cout << "Hello World! What is your name? \n";
	string name;
	name = "rofl";
	getline(cin, name);
	cout << "Hello " << name << "!\n";
	cout << "Please Enter Map Name: ";//Wont display properly :\ 😀";
	getline(cin, name);
	Map m = Map(12);
	m.getNum();
	m.ReadMap(name);
	
	Country c = Country(12, 1);
	m.getCountries();

	//typedef boost::adjacency_list<listS, vecS, undirectedS> Graph;
	//Graph territories;
	//typedef adjacency_list< listS, vecS, directedS > digraph;
	//Graph continents;
	//typedef adjacency_list< listS, vecS, directedS > digraph;

	//// instantiate a digraph object with 8 vertices
	//Graph g(8);

	//// add some edges
	//add_edge(0, 1, g);
	//add_edge(1, 5, g);
	//add_edge(5, 6, g);
	//add_edge(2, 3, g);
	//add_edge(2, 4, g);
	//add_edge(3, 5, g);
	//add_edge(4, 5, g);
	//add_edge(5, 7, g);

	// represent graph in DOT format and send to cout
	//write_graphviz(cout, g);


	Country d = Country(1, 1);
	d.setOwner(1);

	d.buildCity(3);



	//cout << "The owner of country 1 is " << d.getOwner();
	//cout << "\nDoes player 4 have a city in this country?: " << d.hasCity(3);
	//cout << "\nDoes player 2 have a city in this country?: " << d.hasCity(1);



	Country America = Country(1, 1, { 1,0,0,2,0 });



	//cout << "Country ID " << America.getCountryId();
	//cout << "Country's Army Vector: ";
		
	//America.printArmies();


	//cout << America.getOwner();



	
	Player p = Player();
	//p.getCountriesOwned();

	
	vector<int> test = { 1,4,9,3,6,2 }; //Desire index should be 6
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
	
	
	//let's test adjacencies
	return 0;
}