#pragma once
#ifndef MAP_H
#define MAP_H

#include <vector>

// Enum class for different types of cells in the map
enum class Cell { START, EMPTY, WALL, OCCUPIED , FINISH};

// Map class definition
class Map {
public:
    // Constructor to create a map with the given dimensions
    Map(int width, int height);

    // Method to set the type of a cell at a specific location
    void setCell(int x, int y, Cell cellType);

    bool isEmptyCell(int x, int y);

    // Method to verify the validity of the map
    bool verifyMap();

    void display() const;

private:
    int width, height; // Dimensions of the map
    std::vector<std::vector<Cell>> grid; // 2D grid representing the map
};

#endif // MAP_H