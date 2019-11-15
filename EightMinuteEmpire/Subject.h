#pragma once
#include <list>
using namespace std;
class GameObserver;
class Subject {
public:
	virtual void Attach(GameObserver* o);
	virtual void Detach(GameObserver* o);
	virtual void Notify();
	Subject();
	~Subject();
private:
	list<GameObserver*> *_observers;
};