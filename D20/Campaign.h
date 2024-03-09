#pragma once
#ifndef CAMPAIGN_H
#define CAMPAIGN_H

#include "Map.h"
#include "MapConnection.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

class Campaign {
public:
    Campaign(const string name);

    /**
     * @brief Adds a map to the campaign.
     * @param mapName The name of the map to add.
     * @param map The map object to add.
     */
    void addMap(const string mapName, const Map map);

    /**
     * @brief Connects two maps within the campaign.
     * @param fromMapName The name of the starting map.
     * @param toMapName The name of the destination map.
     * @param via A description of the connection point or condition.
     */
    void connectMaps(const string fromMapName, const string toMapName, const string via);

    /**
     * @brief Checks if the campaign is valid based on certain criteria.
     * @return True if the campaign is valid, false otherwise.
     */
    bool verifyCampaign() const;

    /**
     * @brief Gets the campaign name.
     * @return The name of the campaign.
     */
    std::string getName() const;

    /**
     * @brief Displays the campaign information, including maps and connections.
     */
    void displayCampaignInfo() const;

private:
    string name; ///< Name of the campaign.
    vector<Map> maps; ///< Maps included in the campaign, keyed by their names.
    vector<MapConnection> connections; ///< Connections between maps in the campaign.
};

#endif