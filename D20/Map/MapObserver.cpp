//! @file 
//! @brief Implementation file for MapObserver.h
//!

#include "MapObserver.h"

#include <iostream>

//! @brief Destructor for MapObserver.
//! Detaches itself from the subject and sets the subject pointer to null.
MapObserver::~MapObserver()
{
	_subject->detach(this);
	_subject = NULL;
}

//! @brief Constructor for MapObserver.
//! Attaches itself to the subject.
//! @param c The subject to observe.
MapObserver::MapObserver(Map* c)
{
	_subject = c;
	_subject->attach(this);
}

//! @brief Update method for MapObserver.
//! Updates the observer when notified by the subject.
//! @param o The observable object that triggered the update.
void MapObserver::update(Observable* o)
{
	if (_subject == o)
	{
		cout << "==================== Map Update ====================" << endl;
		_subject->display();
		cout << "\n";
	}
}
