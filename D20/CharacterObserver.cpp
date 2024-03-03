#include "CharacterObserver.h"

#include <iostream>

CharacterObserver::~CharacterObserver()
{
	_subject->detach(this);
	_subject = NULL;
}

CharacterObserver::CharacterObserver(Character* c)
{
	_subject = c;
	_subject->attach(this);
	name = "View " + to_string(serial);
	++serial;
}

void CharacterObserver::update(Observable* o)
{
	if (_subject == o)
	{
		cout << "====================Update " + name + "====================" << endl;
		_subject->printCharacter();
	}
}

int CharacterObserver::serial = 0;