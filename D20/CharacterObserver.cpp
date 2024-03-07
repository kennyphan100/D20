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
}

void CharacterObserver::update(Observable* o)
{
	if (_subject == o)
	{
		cout << "==================== Character Update ====================" << endl;
		_subject->printCharacter();
		cout << "\n";
	}
}
