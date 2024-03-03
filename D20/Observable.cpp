#include "Observable.h"

using namespace std;

Observable::Observable()
{
	_observers = new list<Observer*>;
}

Observable::~Observable()
{
	delete _observers;
}

// Attach an observer to the Subject_
void Observable::attach(Observer* o)
{
	_observers->push_back(o);
}

// Detach an observer from the Subject_
void Observable::detach(Observer* o)
{
	_observers->remove(o);
}

// Notify all observers upon stage change
void Observable::notify()
{
	list<Observer*>::iterator i;
	for (i = _observers->begin(); i != _observers->end(); ++i)
	{
		(*i)->update(this);
	}
}