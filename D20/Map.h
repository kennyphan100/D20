//! @file 
//! @brief Header file for Map.cpp
//!

#pragma once
#ifndef MAP_H
#define MAP_H

#include <vector>
#include "Observable.h"

/**
 * @enum Cell
 * @brief Represents different types of cells that can exist in the map.
 *
 * This enumeration covers all possible types of cells within the map, each representing a different state or object.
 */
enum class Cell { START, FINISH, EMPTY, WALL, OCCUPIED, PLAYER, DOOR, CHEST };

/**
 * @class Map
 * @brief Class represents a customizable game map for strategic or adventure games.
 *
 * Game Rules:
 * The map is divided into cells which can be empty, walls, or occupied (by characters, opponents, or items).
 * Players can move through empty cells but not through walls or occupied cells.
 * Players can only go up, down, left or right.
 * The map must have a clear path between designated start and end points to be valid.
 *
 * Design:
 * Implemented as a 2D grid using a vector of vectors, facilitating dynamic map sizes and easy access to each cell.
 * Provides functionality to set the status of each cell and check the existence of a valid path.
 *
 * Libraries:
 * <vector> for storing the map grid due to its flexibility in handling dynamic 2D arrays.
 */
class Map : public Observable {
public:
    /**
     * @brief Constructor that creates a map with specified dimensions.
     * @param width Width of the map.
     * @param height Height of the map.
     */
    Map(int width, int height);

    /**
     * @brief Sets the type of a specific cell in the map.
     * @param x X-coordinate of the cell.
     * @param y Y-coordinate of the cell.
     * @param cellType The type of cell to set (START, EMPTY, etc.).
     */
    void setCell(int x, int y, Cell cellType);

    /**
     * @brief Checks if the specified cell is empty.
     * @param x X-coordinate of the cell.
     * @param y Y-coordinate of the cell.
     * @return True if the cell is empty, false otherwise.
     */
    bool isEmptyCell(int x, int y);

    /**
    * @brief Verifies the validity of the map, ensuring there is a path from start to finish.
    * @return True if the map is valid, false otherwise.
    */
    bool verifyMap();

    /**
     * @brief Displays the map to the console.
     */
    void display() const;

private:
    int width; ///< Width of the map.
    int height; ///< Height of the map.
    vector<vector<Cell>> grid; ///< 2D grid representing the map, containing cells of type Cell.
};

#endif