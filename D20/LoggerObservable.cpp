#include "LoggerObservable.h"

using namespace std;

void LoggerObservable::attachObserver(Observer* observer) {
    observers->push_back(observer);
}

void LoggerObservable::detachObserver(Observer* observer) {
    observers->remove(observer);
}

void LoggerObservable::logEvent(const std::string& event) {
    log.addEntry(event);
    notifyObservers(event);
}

void LoggerObservable::notifyObservers(const std::string& event) {
    list<Observer*>::iterator i;
    for (i = observers->begin(); i != observers->end(); ++i)
    {
        //(*i)->update(this);
    }
}

void LoggerObservable::printLog() const {
    log.printLog();
}