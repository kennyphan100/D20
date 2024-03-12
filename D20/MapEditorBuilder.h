// MapEditorBuilder.h
#ifndef MAPEDITORBUILDER_H
#define MAPEDITORBUILDER_H

#include "MapBuilder.h"

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