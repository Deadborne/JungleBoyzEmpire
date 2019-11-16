#include "stdafx.h"
#include "Subject.h"
#include "GameObservers.h"
Subject::Subject() {

}
Subject::~Subject() {
	//delete _observers;
}
void Subject::Attach(GameObserver* o) {
	//_observers->push_back(o);
	views.push_back(o);
};
void Subject::Detach(GameObserver* o) {
	//_observers->remove(o);
	views.clear();
};
void Subject::Notify() {
	/*list<GameObserver *>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i)
		(*i)->Update();*/
	for (int i = 0; i < views.size(); i++)
		views[i]->Update();
};