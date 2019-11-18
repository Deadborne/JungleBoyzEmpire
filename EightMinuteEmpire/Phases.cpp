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

void Phases::display() {
	cout << "\n-----PLAYER " << _subject->getPlayerID() << "'S TURN ";
	//we need to display 
}

void Phases::setSubject(Player *s) {
	_subject = s;
	_subject->Attach(this);
}