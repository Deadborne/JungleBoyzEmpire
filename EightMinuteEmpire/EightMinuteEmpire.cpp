﻿// EightMinuteEmpire.cpp : Defines the entry point for the console application.
//
#pragma once

#include "stdafx.h"
#include <string>
#include <iostream>
#include "Map.h"
#include "Country.h"
#include "Player.h" 
#include <ostream>
//#include <vector>
using namespace std;
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
using namespace boost;


int main()
{

	//cout << "Hello World! What is your name? \n";
	string name;
	name = "John";
	//getline(cin, name);
	//cout << "Hello " << name << "!\n";
	cout << "Please Enter Map Name: ";//Wont display properly :\ 😀";
	getline(cin, name);
	Map m = Map(12);
	m.getNum();
	m.ReadMap(name);
	
	Country c = Country(12, 1);
	//m.getCountries();

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


	//Country d = Country(1, 1);
	//d.setOwner(1);

	//d.buildCity(3);



	//cout << "The owner of country 1 is " << d.getOwner();
	//cout << "\nDoes player 4 have a city in this country?: " << d.hasCity(3);
	//cout << "\nDoes player 2 have a city in this country?: " << d.hasCity(1);



	//Country America = Country(1, 1, { 1,0,0,2,0 });



	//cout << "Country ID " << America.getCountryId();
	//cout << "Country's Army Vector: ";
		
	//America.printArmies();


	//cout << America.getOwner();



	
	//Player p = Player();
	//p.getCountriesOwned();

	

	
	
	//let's test adjacencies



	
	//cout << "PlayerID: " << player1.getPlayerID() << "\n";
	////cout << player1.getAvailableCities();
	//	
	//vector<int> vec = player1.getCountriesOwned();
	//	//cout << vec.at(0) << vec.at(1);

	//for (int i = 0; i < vec.size(); i++) {
	//	cout << "Owns: " << vec.at(i);
	//}
	//	
	//cout << "Well aint that some shit: \n";
	//cout << "Country 1's ID: " << m.getCountries().at(0).getCountryId() 
	//	<< "\n"; //Gets ID of the country at index 0 of vector of countries
	//
	//int testID = m.getCountries().at(0).getCountryId();
	//vector<int> arTest = { 0,0,0,0,0 };
	////m.getCountries().at(0).setArmiesPerPlayer(arTest);

	//m.getCountries().at(0).printArmies();

	//cout << "..." << testID;
	//player1.placeNewArmies(3, testID);
	//m.getCountries().at(0).printArmies();
	////m.getCountries().at(0).printArmies();

	//cout << "TEST IN MAIN\n";


	//Country yeet = Country(1, 1, { 1,0,0,2,0 });
	//
	//cout << "\nYeet Test\n";
	//yeet.printArmies();
	//cout << "\n";
	//player1.NEWplaceNewArmies(5, yeet);
	//cout << "\n";
	//yeet.printArmies();




	//START OF ACTUAL DRIVER -- DO NOT DELETE PLEASE -- WILL MOVE
	Player player1 = Player();
	player1.setAvailableArmies(14);
	player1.setPlayerID(1);
	player1.setAvailableCities(3);

	Player player2 = Player();
	player2.setAvailableArmies(14);
	player2.setPlayerID(2);
	player2.setAvailableCities(3);

	Country c1 = m.getCountries().at(0);
	Country c2 = m.getCountries().at(1);

	cout << "=====Place new armies in a country=====\n";
	cout << "Armies in Country 1: \n";
	c1.printArmies();
	cout << "\n";

	player1.placeNewArmies(5, c1);
	cout << "\nPlayer 1 has placed 5 new armies in Country 1: \n";
	c1.printArmies();
	
	getline(cin, name);
	cout << "\n\n=====Move armies from Country 1 to Country 2=====\n";
	cout << "Player 1 has 0 armies in Country 2:\n";
	c2.printArmies();
	player1.moveArmies(2, c1, c2);
	cout << "\n     player 1 moving 2 armies from c1 to c2... \n";
	
	cout << "Armies now in Country 1:\n";
	c1.printArmies();
	cout << "\nArmies now in Country 2:\n";
	c2.printArmies();

	getline(cin, name);
	cout << "\n\n=====Add a city to Country 1=====\n";
	cout << "Player 1 has *" << c1.getCities().at(0) << "* cities in Country 1";
	cout << "\n     player 1 building city in c1...";
	player1.buildCity(c1);
	cout << "\nPlayer 1 now has *" << c1.getCities().at(0) << "* city in Country 1";
	
	getline(cin, name);
	cout << "\n\n=====Destroy another player's army=====\n";
	cout << "Recall Player 1 has 2 armies in Country 2:\n";
	c2.printArmies();
	cout << "\n      player 2 destroying one of Player 1's armies in Country 2...\n";
	player2.destroyArmy(c2, player1);
	cout << "Player 1 now has one fewer armies in Country 2:\n";
	c2.printArmies();

	getline(cin, name);
	cout << "\n\n=====Move Over Land=====\n";
	cout << "Recall Player 1 had 3 armies remaining in Country 1\n Let's move one to the adjacent Country, 2:\n";
	player1.moveOverLand(1, c1, c2, m.g);
	c2.printArmies();

	getline(cin, name);
	return 0;
}