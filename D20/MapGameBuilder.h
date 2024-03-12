#ifndef MAPGAMEBUILDER_H
#define MAPGAMEBUILDER_H

#include "MapBuilder.h"
#include <string>

class MapGameBuilder : public MapBuilder {
private:
    Map* map;
    std::string filename;
    int gameLevel;

public:
    MapGameBuilder(const std::string& filename, int level);
    virtual ~MapGameBuilder();
    virtual void reset() override;
    virtual Map* getMap() const override;
    virtual void readMapFromFile(const std::string& filename) override;
    void adaptContentsToLevel();
};

#endif // MAPGAMEBUILDER_H
