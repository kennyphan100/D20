#pragma once
#ifndef LOGGEROBSERVABLE_H
#define LOGGEROBSERVABLE_H

#include "Observer.h"
#include "LoggerObserver.h"
#include <string>
#include <vector>

using namespace std;

class LoggerObservable {
    list<Observer*> *observers;
    LoggerObserver log;

public:
    void attachObserver(Observer* observer);
    void detachObserver(Observer* observer);
    void logEvent(const string& event);
    void printLog() const;
    void notifyObservers(const string& event);
};

#endif
