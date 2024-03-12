//! @file 
//! @brief Header file for Observer.cpp
//!

#pragma once

#include "Observable.h"

class Observable;

/**
 * @class Observer
 * @brief Abstract class representing an observer of observable objects.
 *
 * Observer defines the interface for objects that observe changes in observable objects.
 * It declares a pure virtual method update, which is called by observable objects
 * to notify observers of changes in state. Concrete observer classes must implement
 * this method to define how they react to state changes in observed objects.
 *
 * Design:
 * Observer implements the Observer pattern, allowing objects to register as observers
 * of observable entities and react to changes in their state. It serves as a base class
 * for concrete observer implementations, providing a common interface for handling state updates.
 *
 * Dependencies:
 * The class depends on the Observable class for notifying observers of state changes.
 */
class Observer
{
public:
	virtual ~Observer();
	virtual void update(Observable* theChangeObservable) = 0;

protected:
	Observer();
};