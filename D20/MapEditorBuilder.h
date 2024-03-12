// MapEditorBuilder.h
#ifndef MAPEDITORBUILDER_H
#define MAPEDITORBUILDER_H

#include "MapBuilder.h"

class MapEditorBuilder : public MapBuilder {
private:
    Map* map;
    std::string filename;

public:
    MapEditorBuilder(const std::string& filename);
    ~MapEditorBuilder();
    void reset() override;
    Map* getMap() const override;
    void readMapFromFile(const std::string& filename) override;
};

#endif // MAPEDITORBUILDER_H