#include "MapGameBuilder.h"
#include <fstream>
#include <limits>
#include <stdexcept>

MapGameBuilder::MapGameBuilder(const string& filename, int level)
    : filename(filename), gameLevel(level), map(nullptr) {
    readMapFromFile(filename);
    adaptContentsToLevel();
}

MapGameBuilder::~MapGameBuilder() {
    delete map;
}

void MapGameBuilder::reset() {
    delete map;
    map = nullptr;
}

Map* MapGameBuilder::getMap() const {
    return map;
}

void MapGameBuilder::readMapFromFile(const string& newFilename) {
    filename = newFilename;
    reset();

    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Could not open map file.");
    }

    int width, height;
    file >> width >> height;
    if (!file || width <= 0 || height <= 0) {
        throw runtime_error("Invalid map size in file: " + filename);
    }

    file.ignore(numeric_limits<streamsize>::max(), '\n');

    map = new Map(width, height, filename);

    string line;
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
                throw runtime_error("Unrecognized map symbol: " + string(1, line[x]));
            }
        }
        y++;
    }
}

void MapGameBuilder::adaptContentsToLevel() {
    /* Placeholder logic 
    for (Character& character : map->getCharacters()) {
        character.setLevel(gameLevel);
    }
    */
}
