#pragma once

#include <list>
#include "Observer.h"

using namespace std;

class Observer;

class Observable
{
public:
	virtual ~Observable();

	virtual void attach(Observer* o);
	virtual void detach(Observer* o);
	virtual void notify();

protected:
	Observable();

private:
	list<Observer*> *_observers;
};