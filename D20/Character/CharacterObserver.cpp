//! @file 
//! @brief Implementation file for CharacterObserver.h
//!

#include "CharacterObserver.h"

#include <iostream>

//! Destructor for CharacterObserver class.
//! Detaches the observer from the subject and sets the subject pointer to null.
CharacterObserver::~CharacterObserver()
{
	_subject->detach(this);
	_subject = NULL;
}

//! Constructor for CharacterObserver class.
//! Attaches the observer to the specified character subject.
//! @param c Pointer to the character subject to observe.
CharacterObserver::CharacterObserver(Character* c)
{
	_subject = c;
	_subject->attach(this);
}

//! Update method called when the observed subject notifies the observer.
//! Prints the updated character information.
//! @param o Pointer to the observable subject.
void CharacterObserver::update(Observable* o)
{
	if (_subject == o)
	{
		cout << "==================== Character Update ====================" << endl;
		_subject->printCharacter();
		cout << "\n";
	}
}
