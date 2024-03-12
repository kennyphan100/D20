// MapEditorBuilder.cpp
#include "MapEditorBuilder.h"
#include <fstream>
#include <sstream>

MapEditorBuilder::MapEditorBuilder(const std::string& filename) : filename(filename), map(nullptr) {
    readMapFromFile(this->filename);
}

MapEditorBuilder::~MapEditorBuilder() {
    delete map;
}

void MapEditorBuilder::reset() {
    delete map;
    map = nullptr;
}

Map* MapEditorBuilder::getMap() const {
    return map;
}

void MapEditorBuilder::readMapFromFile(const std::string& newFilename) {
    filename = newFilename;
    reset();

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open map file.");
    }

    int width, height;
    file >> width >> height;
    if (!file || width <= 0 || height <= 0) {
        throw std::runtime_error("Invalid map size in file: " + filename);
    }

    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    map = new Map(width, height, filename);

    std::string line;
    int y = 0;
    while (getline(file, line)) {
        for (int x = 0; x < line.length(); ++x) {
            switch (line[x]) {
            case 'W':
                map->setCell(x, y, Cell::WALL);
                break;
            case 'O':
                map->setCell(x, y, Cell::OCCUPIED);
                break;
            case 'S':
                map->setCell(x, y, Cell::START);
                break;
            case 'F':
                map->setCell(x, y, Cell::FINISH);
                break;
            case '_':
                map->setCell(x, y, Cell::EMPTY);
                break;
            case 'P':
                map->setCell(x, y, Cell::PLAYER);
                break;
            case 'D':
                map->setCell(x, y, Cell::DOOR);
                break;
            case 'C':
                map->setCell(x, y, Cell::CHEST);
                break;
            default:
                throw std::runtime_error("Unrecognized map symbol: " + std::string(1, line[x]));
            }
        }
        y++;
    }
}