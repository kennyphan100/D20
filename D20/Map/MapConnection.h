//! @file 
//! @brief Header file for MapConnection.h
//!

#pragma once
#ifndef MAPCONNECTION_H
#define MAPCONNECTION_H

#include <string>

using namespace std;

/**
 * @struct MapConnection
 * @brief Structure representing a connection between maps.
 *
 * MapConnection encapsulates information about a connection between two maps,
 * including the names of the origin and destination maps and a description
 * of the connection point or condition. It provides a convenient way to
 * store and access data related to map connections within a system.
 *
 * Design:
 * MapConnection serves as a lightweight data structure for representing map connections.
 * It consists of three string members: fromMapName, toMapName, and via, which respectively
 * store the names of the origin and destination maps, and a description of the connection.
 * The design aims for simplicity and clarity, facilitating straightforward usage and manipulation
 * of map connection data in various contexts.
 *
 * Dependencies:
 * The structure relies on <string> for string-related operations and namespace std for string usage.
 */
struct MapConnection {
    std::string fromMapName; ///< The name of the map from which the connection originates.
    std::string toMapName;   ///< The name of the map to which the connection leads.
    std::string via;         ///< A description of the connection point or condition.
};

#endif // MAPCONNECTION_H

