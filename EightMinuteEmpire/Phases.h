#pragma once
#include "GameObservers.h"
#include "Player.h"
#include "Card.h"

//This is a concrete observer
class Phases : public GameObserver {
public:
	Phases();
	Phases(Player* s);
	~Phases();
	void Update();
	void display();

	void setSubject(Player*);

private:
	Player *_subject;
};