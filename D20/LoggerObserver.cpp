#include "LoggerObserver.h"
#include <iostream>

using namespace std;

void LoggerObserver::addEntry(const string& entry) {
    entries.push_back(entry);
}

void LoggerObserver::printLog() const {
    cout << "Unified Log:" << endl;
    for (const auto& entry : entries) {
        cout << entry << endl;
    }
}