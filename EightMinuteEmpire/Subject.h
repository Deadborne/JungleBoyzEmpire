#pragma once

#include "GameObservers.h"
#include <list>
#include <vector>
using namespace std;

class Subject {
	vector <GameObserver*> views;
public:
	virtual void Attach(GameObserver* o); //ok
	virtual void Detach(GameObserver* o);
	virtual void Notify(); //ok
	Subject();
	~Subject();

	//list<GameObserver*> *_observers;
};