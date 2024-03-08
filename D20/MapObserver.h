#pragma once

#include "Observer.h"
#include "Map.h"
#include <string>

class MapObserver : public Observer
{
public:
	virtual ~MapObserver();
	MapObserver(Map* c);

	virtual void update(Observable* o);

private:
	string name;
	Map* _subject;
};