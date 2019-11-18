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
	phases.push_back(o);
};
void Subject::Detach(GameObserver* o) {
	//_observers->remove(o);
	views.clear();
	phases.clear();
};
void Subject::Notify() {
	/*list<GameObserver *>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i)
		(*i)->Update();*/
	for (int i = 0; i < views.size(); i++)
		views[i]->Update();

	//By doing this, any of our phases should be updated when anything is changed in the Subject
	for (int i = 0; i < phases.size(); i++)
		phases[i]->Update();
};