#ifndef MAPGAMEBUILDER_H
#define MAPGAMEBUILDER_H

#include "MapBuilder.h"
#include <string>

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
