//! @file 
//! @brief Header file for CharacterObserver.cpp
//!

#pragma once

#include "Observer.h"
#include "Character.h"

/**
 * @class CharacterObserver
 * @brief Class for observing changes in a Character object.
 *
 * This class provides functionality to observe and react to changes in a Character object.
 * It inherits from the Observer class and implements the update method to receive notifications
 * from the observed Character object. CharacterObserver instances are associated with specific
 * Character objects, allowing them to track changes and perform actions accordingly.
 *
 * Design:
 * CharacterObserver is designed to be associated with a single Character object, providing a means
 * to monitor its state changes. It implements the Observer interface to receive notifications
 * from the observed Character object. The class encapsulates a Character pointer and a name
 * identifier for convenience and clarity.
 *
 * Dependencies:
 * The class depends on the Observer interface and the Character class for functionality.
 */
class CharacterObserver : public Observer
{
public:
	virtual ~CharacterObserver();
	CharacterObserver(Character* c);

	virtual void update(Observable* o);

private:
	string name;
	Character* _subject;
};