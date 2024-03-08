#include "MapObserver.h"

#include <iostream>

MapObserver::~MapObserver()
{
	_subject->detach(this);
	_subject = NULL;
}

MapObserver::MapObserver(Map* c)
{
	_subject = c;
	_subject->attach(this);
}

void MapObserver::update(Observable* o)
{
	if (_subject == o)
	{
		cout << "==================== Map Update ====================" << endl;
		_subject->display();
		cout << "\n";
	}
}
