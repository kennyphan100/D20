//! @file 
//! @brief Header file for MapBuilder.cpp
//!

#ifndef MAPBUILDER_H
#define MAPBUILDER_H

#include "Map.h"
#include <string>

/**
 * @class MapBuilder
 * @brief Abstract class for building Map objects.
 *
 * MapBuilder serves as an interface for building Map objects. It defines methods for resetting
 * the builder state, retrieving the constructed Map object, and reading map data from a file.
 * Concrete implementations of MapBuilder are responsible for constructing Map objects according
 * to specific requirements or formats, providing flexibility and extensibility in map creation.
 *
 * Design:
 * MapBuilder follows the Builder design pattern, allowing the construction of Map objects
 * to be separated from their representation. The class defines a common interface for all
 * map builders, ensuring consistency and interoperability between different implementations.
 * Concrete builders inherit from MapBuilder and provide specialized logic for map construction.
 *
 * Dependencies:
 * The class depends on the Map class for constructing Map objects and utilizes <string> for
 * file-related operations.
 */
class MapBuilder {
public:
    virtual ~MapBuilder() {}
    virtual void reset() = 0;
    virtual Map* getMap() const = 0;
    virtual void readMapFromFile(const string& filename) = 0;
};

#endif