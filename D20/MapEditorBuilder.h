//! @file 
//! @brief Header file for MapEditorBuilder.cpp
//!

#ifndef MAPEDITORBUILDER_H
#define MAPEDITORBUILDER_H

#include "MapBuilder.h"

/**
 * @class MapEditorBuilder
 * @brief Concrete builder class for editing Map objects.
 *
 * MapEditorBuilder extends the MapBuilder interface to provide functionality
 * for editing Map objects. It implements methods for resetting the builder state,
 * retrieving the constructed Map object, and reading map data from a file.
 * Instances of MapEditorBuilder are initialized with a filename, which is used
 * to read map data from a file during construction or editing.
 *
 * Design:
 * MapEditorBuilder follows the Builder design pattern, specializing in the construction
 * and editing of Map objects. It encapsulates logic for reading map data from a file and
 * updating the builder state accordingly. The class provides a convenient interface for
 * editing map objects while adhering to the common MapBuilder interface.
 *
 * Dependencies:
 * The class depends on the MapBuilder class for interface inheritance and utilizes <string>
 * for file-related operations.
 */
class MapEditorBuilder : public MapBuilder {
private:
    Map* map;
    string filename;

public:
    MapEditorBuilder(const string& filename);
    ~MapEditorBuilder();
    void reset() override;
    Map* getMap() const override;
    void readMapFromFile(const string& filename) override;
};

#endif // MAPEDITORBUILDER_H