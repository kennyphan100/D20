#include "CharacterObserver.h"

#include <iostream>

CharacterObserver::CharacterObserver(Character& c)
{
	_subject = &c;
	_subject->attach(this);
	name = "View " + std::to_string(serial);
	++serial;
}


CharacterObserver::~CharacterObserver()
{
	_subject->detach(this);
	_subject = NULL;
}

void CharacterObserver::update(Observable* o)
{
	if (_subject == o)
	{
		std::cout << "****************Update " + name + "****************" << std::endl;
		_subject->printCharacter();
	}
}

int CharacterObserver::serial = 0;