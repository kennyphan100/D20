#pragma once

#include "Observable.h"

class Observable;

class Observer
{
public:
	virtual ~Observer();
	virtual void update(Observable* theChangeObservable) = 0;

protected:
	Observer();
};