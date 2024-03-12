//! @file 
//! @brief Header file for MapGameBuilder.cpp
//!

#ifndef MAPGAMEBUILDER_H
#define MAPGAMEBUILDER_H

#include "MapBuilder.h"
#include <string>

/**
 * @class MapGameBuilder
 * @brief Concrete builder class for constructing Map objects for games.
 *
 * MapGameBuilder extends the MapBuilder interface to specialize in constructing
 * Map objects tailored for games. It incorporates additional functionality to adapt
 * map contents based on the game level provided during initialization. The class
 * implements methods for resetting the builder state, retrieving the constructed Map object,
 * and reading map data from a file. Additionally, it provides a method to adapt map contents
 * to the specified game level, ensuring appropriate gameplay experience.
 *
 * Design:
 * MapGameBuilder adheres to the Builder design pattern, focusing on the construction
 * of Map objects optimized for games. It encapsulates logic for reading map data from a file,
 * adapting map contents based on the game level, and maintaining builder state. The class
 * provides a specialized interface for game-specific map building operations while leveraging
 * the common MapBuilder interface for consistency.
 *
 * Dependencies:
 * The class depends on the MapBuilder class for interface inheritance and utilizes <string>
 * for file-related operations.
 */
class MapGameBuilder : public MapBuilder {
private:
    Map* map;
    string filename;
    int gameLevel;

public:
    MapGameBuilder(const string& filename, int level);
    virtual ~MapGameBuilder();
    virtual void reset() override;
    virtual Map* getMap() const override;
    virtual void readMapFromFile(const string& filename) override;
    void adaptContentsToLevel();
};

#endif
