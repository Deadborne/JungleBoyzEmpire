// EightMinuteEmpire.cpp : Defines the entry point for the console application.
//
#pragma once

#include "stdafx.h"
#include <string>

#include <iostream>
#include "Map.h"
#include "Country.h"
using namespace std;
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
using namespace boost;


int main()
{

#include<iostream>
using namespace std;

int main()
{
	cout << "Hello World! What is your name? \n";
	string name;

	getline(cin, name);
	cout << "Hello " << name << "!\n";
	cout << "Please press enter to close the console :D";
	getline(cin, name);
	Map m = Map(12);
	m.getNum();
	Country c = Country(12, 1);
	c.getId();

	typedef boost::adjacency_list<listS, vecS, undirectedS> Graph;
	Graph territories;
	typedef adjacency_list< listS, vecS, directedS > digraph;
	Graph continents;
	typedef adjacency_list< listS, vecS, directedS > digraph;

	// instantiate a digraph object with 8 vertices
	Graph g(8);

	// add some edges
	add_edge(0, 1, g);
	add_edge(1, 5, g);
	add_edge(5, 6, g);
	add_edge(2, 3, g);
	add_edge(2, 4, g);
	add_edge(3, 5, g);
	add_edge(4, 5, g);
	add_edge(5, 7, g);

	// represent graph in DOT format and send to cout
	write_graphviz(cout, g);

	
	Country d = Country(1, 1);
	d.setOwner(1);

	d.buildCity(3);



	cout << "The owner of country 1 is " << d.getOwner();
	cout << "\nDoes player 4 have a city in this country?: " << d.hasCity(3);
	cout << "\nDoes player 2 have a city in this country?: " << d.hasCity(1);
	getline(cin, name);



    return 0;
}


