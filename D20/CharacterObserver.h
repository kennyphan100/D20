#pragma once

#include "Observer.h"
#include "Character.h"

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