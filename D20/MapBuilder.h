// MapBuilder.h
#ifndef MAPBUILDER_H
#define MAPBUILDER_H

#include "Map.h"
#include <string>

class MapBuilder {
public:
    virtual ~MapBuilder() {}
    virtual void reset() = 0;
    virtual Map* getMap() const = 0;
    virtual void readMapFromFile(const std::string& filename) = 0;
};

#endif // MAPBUILDER_H