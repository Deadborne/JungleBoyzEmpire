#pragma once

#include "GameObservers.h"
#include <list>
#include <vector>
using namespace std;

class Subject {
	vector <GameObserver*> views;
	vector <GameObserver*> phases;
public:
	virtual void Attach(GameObserver* o); //ok
	virtual void Detach(GameObserver* o);
	virtual void Notify(); //ok
	virtual void NotifyPhase();
	Subject();
	~Subject();

	//list<GameObserver*> *_observers;
};