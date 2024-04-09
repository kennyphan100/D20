//! @file 
//! @brief Header file for Campaign.cpp
//!

#pragma once
#ifndef CAMPAIGN_H
#define CAMPAIGN_H

#include "Map.h"
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

/**
 * @class Campaign
 * @brief Class for managing a campaign consisting of multiple maps.
 *
 * This class provides functionality to organize and manage a campaign, which is composed of multiple maps
 * interconnected through various connections. It allows users to add and remove maps from the campaign,
 * establish connections between maps, save the campaign data to a file, load campaign data from a file,
 * and display information about the campaign.
 *
 * Design:
 * The Campaign class utilizes a vector to store the names of maps within the campaign and an unordered_map
 * to represent connections between maps. Each map is identified by a unique name, and connections are
 * represented as pairs of map names. The design facilitates efficient management of map data and connections,
 * enabling seamless navigation within the campaign.
 *
 * Libraries:
 * <vector> is utilized for dynamic storage of map names within the campaign.
 * <unordered_map> is employed to efficiently store and manage map connections using map names as keys.
 */
class Campaign {
private:
    string name;
    vector<string> maps;

public:
    Campaign();
    unordered_map<string, vector<string>> connections;
    vector<string> connectionsOrdered;

    Campaign(const string& name);

    void addMap(const string& mapName, const string& campaignDir);
    void removeMap(const string& mapName, const string& campaignDir);

    void connectMaps(const string& fromMap, const string& toMap);
    vector<string> getConnectedMap(const string& mapKey);
    void connectSequentialMaps(const vector<string>& selectedMaps);
    string getFirstMap();
    string getAllMaps();
    pair<list<string>, string> getMapsAndConnections();

    string getName() const;
    bool saveToFile(const string& filePath, const vector<string>& selectedMaps = vector<string>());
    bool loadFromFile(const string& filePath);
    void display() const;
    void display2() const;
};

#endif
