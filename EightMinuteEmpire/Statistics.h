#pragma once
#include "GameObservers.h"
#include "Player.h"

//This is a concrete observer.
class Statistics : public GameObserver
{
public:
	Statistics();
	Statistics(Player* s); //s for subject, of course!
	~Statistics();
	void Update();
	void display();

	void setSubject(Player*);

private:
	Player *_subject;
};