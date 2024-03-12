//! @file 
//! @brief Implementation file for MapEditorBuilder.h
//!

#include "MapEditorBuilder.h"
#include <fstream>
#include <sstream>

//! @file MapEditorBuilder.h
//! @brief Constructor for MapEditorBuilder.
//! Initializes a MapEditorBuilder object with the specified filename and reads the map from the file.
//! @param filename The name of the file containing the map.
MapEditorBuilder::MapEditorBuilder(const string& filename) : filename(filename), map(nullptr) {
    readMapFromFile(this->filename);
}

//! @brief Destructor for MapEditorBuilder.
//! Deallocates memory for the map.
MapEditorBuilder::~MapEditorBuilder() {
    delete map;
}

//! @brief Reset the MapEditorBuilder.
//! Deallocates memory for the current map and sets it to nullptr.
void MapEditorBuilder::reset() {
    delete map;
    map = nullptr;
}

//! @brief Get the map.
//! Returns a pointer to the map.
//! @return A pointer to the map.
Map* MapEditorBuilder::getMap() const {
    return map;
}

//! @brief Read a map from file.
//! Reads a map from the specified file, parses it, and creates a map object.
//! @param newFilename The name of the file containing the map.
void MapEditorBuilder::readMapFromFile(const string& newFilename) {
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