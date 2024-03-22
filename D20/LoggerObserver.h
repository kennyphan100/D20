#pragma once
#ifndef LOGGEROBSERVER_H
#define LOGGEROBSERVER_H

#include <vector>
#include <string>

using namespace std;

class LoggerObserver {
    vector<string> entries;

public:
    void addEntry(const string& entry);
    void printLog() const;
};

#endif