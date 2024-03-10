#pragma once
#ifndef MAPCONNECTION_H
#define MAPCONNECTION_H

#include <string>

using namespace std;

/**
 * @brief Represents a connection between two maps in a campaign.
 *
 * This structure holds information about the connection from one map to another,
 * including the names of the source and destination maps and a description of the
 * connection point or condition (via).
 */
struct MapConnection {
    std::string fromMapName; ///< The name of the map from which the connection originates.
    std::string toMapName;   ///< The name of the map to which the connection leads.
    std::string via;         ///< A description of the connection point or condition.
};

#endif // MAPCONNECTION_H

