#include "stdafx.h"

#include "Phases.h"
#include "Player.h"

#include <iostream>

using namespace std;

Phases::Phases() {};

Phases::Phases(Player* s) {
	_subject = s;
	_subject->Attach(this);
}

Phases::~Phases() {
	_subject->Detach(this);
}

void Phases::Update() {
	display();
}


//So sorry for this function - out of time
void Phases::display() {
	
	//Heres what we just pulled
	Card lastCard = _subject->getHand().back();
	//Now lets talk about the card we just pulled
	cout << "Player " << _subject->getPlayerID() << ": pulled a card. They are entitled to ";
	
	//If there's only 1 action on the card
	if (lastCard.getOperator() == "") {
		//check what it is
		if (lastCard.getAction1() == "place")
			cout << "place " << lastCard.getNumA1() << " new army/armies on the board.\n\n";
		else if (lastCard.getAction1() == "move")
			cout << "move " << lastCard.getNumA1() << " army/armies over land.\n\n";
		else if (lastCard.getAction1() == "moveOver")
			cout << "move " << lastCard.getNumA1() << " army/armies over land or sea.\n/n";
		else if (lastCard.getAction1() == "build")
			cout << "build 1 city.";
	}
	else if (lastCard.getOperator() == "and") {
		cout << " both ";
		//do this
		if (lastCard.getAction1() == "place")
			cout << "place " << lastCard.getNumA1() << " new army/armies on the board ";
		else if (lastCard.getAction1() == "move")
			cout << "move " << lastCard.getNumA1() << " army/armies over land ";
		else if (lastCard.getAction1() == "moveOver")
			cout << "move " << lastCard.getNumA1() << " army/armies over land or sea ";
		else if (lastCard.getAction1() == "build")
			cout << "build 1 city, ";
		
		//and this
		cout << "and ";
		
		if (lastCard.getAction2() == "place")
			cout << "place " << lastCard.getNumA2() << " new army/armies on the board.\n\n";
		else if (lastCard.getAction2() == "move")
			cout << "move " << lastCard.getNumA2() << " army/armies over land.\n\n";
		else if (lastCard.getAction2() == "moveOver")
			cout << "move " << lastCard.getNumA2() << " army/armies over land or sea.\n\n";
		else if (lastCard.getAction2() == "build")
			cout << "build 1 city.";
	}
	else if (lastCard.getOperator() == "or") {
		cout << " either ";
		
		//do this
		if (lastCard.getAction1() == "place")
			cout << "place " << lastCard.getNumA1() << " new army/armies on the board ";
		else if (lastCard.getAction1() == "move")
			cout << "move " << lastCard.getNumA1() << " army/armies over land ";
		else if (lastCard.getAction1() == "moveOver")
			cout << "move " << lastCard.getNumA1() << " army/armies over land or sea ";
		else if (lastCard.getAction1() == "build")
			cout << "build 1 city, ";

		//and this
		cout << "or ";

		if (lastCard.getAction2() == "place")
			cout << "place " << lastCard.getNumA2() << " new army/armies on the board.\n\n";
		else if (lastCard.getAction2() == "move")
			cout << "move " << lastCard.getNumA2() << " army/armies over land.\n\n";
		else if (lastCard.getAction2() == "moveOver")
			cout << "move " << lastCard.getNumA2() << " army/armies over land or sea.\n\n";
		else if (lastCard.getAction2() == "build")
			cout << "build 1 city.";
	}
		
	

}

void Phases::setSubject(Player *s) {
	_subject = s;
	_subject->Attach(this);
}