#include "stdafx.h"

#include "Statistics.h"
#include "Player.h"
#include <iostream>
using std::cout;
using std::endl;

Statistics::Statistics() {};

Statistics::Statistics(Player* s)
{
	_subject = s;
	_subject->Attach(this);
}

Statistics::~Statistics() {
	_subject->Detach(this);
}

void Statistics::Update() {
	display();
}

//The meat of the observer - show points, who controls what
void Statistics::display() {

	cout << "\n-----GAME STATISTICS:----\n" << endl;
	//print out every country owned by the player
	cout << "Player " << _subject->getPlayerID() << " has dominion over these Regions: [ ";
	for (int i = 0; i < _subject->getCountriesOwned(*Map::instance()).size(); i++) {
		cout << _subject->getCountriesOwned(*Map::instance()).at(i).getCountryId() << " "; //Print the country ID of each country owned
	}
	cout << "]" << endl;

	//print out every continent owned by the player
	cout << "Player " << _subject->getPlayerID() << " has dominion over these Continents: [ ";
	for (int i = 0; i < _subject->getContinentsOwned(*Map::instance()).size(); i++) {
		cout << _subject->getContinentsOwned(*Map::instance()).at(i) << " "; //Print the Continent ID of each Continent Owned
	}
	cout << "]" << endl;

	//print out every city owned by the player
	cout << "Player " << _subject->getPlayerID() << " has built a City in these Regions: [ ";
	for (int i = 0; i < _subject->getArmySpawnLocations(*Map::instance()).size(); i++) {
		cout << _subject->getArmySpawnLocations(*Map::instance()).at(i) << " "; //Print the country ID of each country with a city
	}
	cout << "]" << endl;

	//Bar Graph!
	cout << "Current points: ";
	int points = _subject->getContinentsOwned(*Map::instance()).size() + _subject->getCountriesOwned(*Map::instance()).size();
	for (int i = 0; i < points; i++) {
		cout << "o";
	}
	cout << "\n\n----END OF STATISTICS----\n"<< endl;
}

void Statistics::setSubject(Player *s) {
	_subject = s;
	_subject->Attach(this);
}
