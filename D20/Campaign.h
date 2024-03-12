#pragma once
#ifndef CAMPAIGN_H
#define CAMPAIGN_H

#include "Map.h"
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Campaign {
private:
    string name;
    vector<string> maps;
    unordered_map<string, vector<string>> connections;

public:
    Campaign();

    Campaign(const string& name);

    void addMap(const string& mapName, const string& campaignDir);
    void removeMap(const string& mapName, const string& campaignDir);

    void connectMaps(const string& fromMap, const string& toMap);

    string getName() const;
    bool saveToFile(const string& filePath);
    bool loadFromFile(const string& filePath);
    void display() const;
};

#endif
