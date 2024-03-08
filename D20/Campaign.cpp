// Campaign.h
#ifndef CAMPAIGN_H
#define CAMPAIGN_H

#include "Map.h"
#include "MapConnection.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

class Campaign {
public:
    Campaign(const std::string& name) : name(name) {}

    void addMap(const std::string& mapName, const Map& map) {
        maps[mapName] = map;
    }

    void connectMaps(const std::string& fromMapName, const std::string& toMapName, const std::string& via) {
        connections.push_back({ fromMapName, toMapName, via });
    }

    bool verifyCampaign() const {
        // Simplified: Just checks if there's at least one map and one connection
        return !maps.empty() && !connections.empty();
    }

    void displayCampaignInfo() const {
        cout << "Campaign: " << name << std::endl;
        for (const auto& conn : connections) {
            cout << "From: " << conn.fromMapName << " To: " << conn.toMapName << " Via: " << conn.via << std::endl;
        }
    }

private:
    std::string name;
    std::map<std::string, Map> maps;
    std::vector<MapConnection> connections;
};

#endif
