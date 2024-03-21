//! @file 
//! @brief Header file for MapObserver.cpp
//!

#pragma once

#include "../Observer.h"
#include "Map.h"
#include <string>

/**
 * @class MapObserver
 * @brief Class for observing changes in a Map object.
 *
 * MapObserver provides functionality to observe and react to changes in a Map object.
 * It inherits from the Observer class and implements the update method to receive notifications
 * from the observed Map object. MapObserver instances are associated with specific Map objects,
 * allowing them to track changes and perform actions accordingly.
 *
 * Design:
 * MapObserver is designed to be associated with a single Map object, providing a means
 * to monitor its state changes. It implements the Observer interface to receive notifications
 * from the observed Map object. The class encapsulates a Map pointer and a name
 * identifier for convenience and clarity.
 *
 * Dependencies:
 * The class depends on the Observer interface and the Map class for functionality.
 */
class MapObserver : public Observer
{
public:
	virtual ~MapObserver();
	MapObserver(Map* c);

	virtual void update(Observable* o);
	virtual void log(Observable* o);

private:
	string name;
	Map* _subject;
};