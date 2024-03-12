//! @file 
//! @brief Implementation file for Observable.h
//!

#include "Observable.h"

using namespace std;

//! @brief Constructor for Observable.
//! Initializes the list of observers.
Observable::Observable()
{
	_observers = new list<Observer*>;
}

//! @brief Destructor for Observable.
//! Deallocates memory for the list of observers.
Observable::~Observable()
{
	delete _observers;
}

//! @brief Attach an observer to the Observable.
//! Adds an observer to the list of observers.
//! @param o The observer to attach.
void Observable::attach(Observer* o)
{
	_observers->push_back(o);
}

//! @brief Detach an observer from the Observable.
//! Removes an observer from the list of observers.
//! @param o The observer to detach.
void Observable::detach(Observer* o)
{
	_observers->remove(o);
}

//! @brief Notify all observers.
//! Notifies all observers about a change in the observable object.
void Observable::notify()
{
	list<Observer*>::iterator i;
	for (i = _observers->begin(); i != _observers->end(); ++i)
	{
		(*i)->update(this);
	}
}