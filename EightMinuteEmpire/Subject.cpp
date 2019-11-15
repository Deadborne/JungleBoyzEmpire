#include "Subject.h"
#include "GameObservers.h"
Subject::Subject() {
	_observers = new list<GameObserver*>;
}
Subject::~Subject() {
	delete _observers;
}
void Subject::Attach(GameObserver* o) {
	_observers->push_back(o);
};
void Subject::Detach(GameObserver* o) {
	_observers->remove(o);
};
void Subject::Notify() {
	list<GameObserver *>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i)
		(*i)->Update();
};