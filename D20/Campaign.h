#pragma once
#ifndef CAMPAIGN_H
#define CAMPAIGN_H

#include "Map.h"
#include "MapConnection.h"
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Campaign {
private:
    string name;
    vector<string> maps; // List of maps in the campaign
    unordered_map<string, vector<string>> connections; // Store connections between maps

public:
    Campaign();

    Campaign(const string& name);

    // Map management
    void addMap(const string& mapName, const string& campaignDir);
    void removeMap(const string& mapName, const string& campaignDir);
    //vector<Map> getMaps() const;

    // Map connections
    void connectMaps(const string& fromMap, const string& toMap);
    vector<string> getConnections(const string& mapName) const;

    // Getters and setters
    string getName() const;
    //void setName(const string& newName);

    bool saveToFile(const string& filePath);
    bool loadFromFile(const std::string& filePath);

    void display() const;
    // Additional functionalities might include saving/loading campaigns, listing maps, etc.
};

#endif // CAMPAIGN_H
