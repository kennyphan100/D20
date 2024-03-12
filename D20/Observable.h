//! @file 
//! @brief Header file for Observable.cpp
//!

#pragma once

#include <list>
#include "Observer.h"

using namespace std;

class Observer;

/**
 * @class Observable
 * @brief Abstract class representing an observable object.
 *
 * Observable serves as a base class for objects that can be observed by Observer instances.
 * It defines methods for attaching, detaching, and notifying observers of changes in state.
 * Concrete classes inheriting from Observable can implement specific functionality for
 * managing observers and notifying them of relevant changes.
 *
 * Design:
 * Observable implements the Observable pattern, allowing other objects (observers) to register
 * interest in changes to its state. It maintains a list of registered observers and provides
 * methods for managing this list and notifying observers of state changes. The class is designed
 * to be inherited by concrete classes representing observable entities in a system.
 *
 * Dependencies:
 * The class depends on the Observer class for observer registration and notification and
 * utilizes <list> for managing the list of observers.
 */
class Observable
{
public:
	virtual ~Observable();

	virtual void attach(Observer* o);
	virtual void detach(Observer* o);
	virtual void notify();

protected:
	Observable();

private:
	list<Observer*> *_observers;
};