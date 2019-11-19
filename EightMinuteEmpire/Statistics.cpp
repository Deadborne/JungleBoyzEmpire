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

	//Congratulate player on drawing their last card
	if (_subject->checkIfReachedHandLimit() == true) {

		_subject->setHandStatus(false); //just so we don't see this message again for the same player

		cout << "~~~~~~~~OH MY GOODNESS!~~~~~~~~~~" << endl;
		cout << "Player " << _subject->getPlayerID() << ", ";
		if (_subject->getPlayerID() == 0)
			cout << "you beautiful bastard, ";
		else if (_subject->getPlayerID() == 1)
			cout << "you mythical creature, ";
		else if (_subject->getPlayerID() == 2)
			cout << "you white lion of a human being, ";
		else if (_subject->getPlayerID() == 3)
			cout << "you delicate work of art, ";
		else if (_subject->getPlayerID() == 4)
			cout << "you majestic human unicorn, ";
		else if (_subject->getPlayerID() == 5)
			cout << "you wonderful golden child, ";
		cout << "you've completed a full hand!\n In any case, here's where things stand:" << endl;
	}
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
	cout << "\nCurrent points: " << endl;

	//prints out one "o" per point
	for (int i = 0; i < Map::instance()->getPlayers().size(); i++) {
		
		int points = Map::instance()->getPlayers()[i]->getCountriesOwned(*Map::instance()).size() + Map::instance()->getPlayers()[i]->getContinentsOwned(*Map::instance()).size();
		cout << "Player " << Map::instance()->getPlayers()[i]->getPlayerID() << " points: ";
		for (int j = 0; j < points; j++) {
			cout << "o";
		}
		cout << endl;
	}

	cout << "\n\n----END OF STATISTICS----\n"<< endl;
}

void Statistics::setSubject(Player *s) {
	_subject = s;
	_subject->Attach(this);
}
