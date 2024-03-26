//! @file 
//! @brief Header file for Map.cpp
//!

#pragma once
#ifndef MAP_H
#define MAP_H

#include <vector>
#include <iostream>
#include <map>
#include "../Observable.h"
#include "../Character/Character.h"

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
class Map : public Observable{
public:
    Map();
    /**
     * @brief Constructor that creates a map with specified dimensions.
     * @param width Width of the map.
     * @param height Height of the map.
     */
    Map(int width, int height, string name);

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

    /**
     * @brief Getter for the map's width.
     * @return The width of the map.
     */
    int getWidth() const;

    /**
     * @brief Getter for the map's height.
     * @return The height of the map.
     */
    int getHeight() const;

    /**
     * @brief Getter for the cell's type.
     * @param x The x position.
     * @param y The y position.
     */
    Cell getCell(int x, int y) const;

    string getName() const;

    void setName(string newName);

    bool saveToFile(const string& filename);

    bool loadFromFile(const string& filename);

    Cell charToCellType(char c);

    void placeCharacter(int x, int y, Character* character);

    Character* getCharacter(int x, int y) const;

    void removeCharacter(int x, int y);

    bool moveCharacter(int fromX, int fromY, int toX, int toY);

    /**
     * @brief BFS Pathfinding function
     * @param startX The starting x position.
     * @param startY The starting y position.
     * @param endX The ending x position.
     * @param endY The ending y position.
     * @return The travel distance. -1 If no path found.
     */
    int findShortestPath(int startX, int startY, int endX, int endY);

private:
    int width; ///< Width of the map.
    int height; ///< Height of the map.
    string name; ///< Name of the map.
    vector<vector<Cell>> grid; ///< 2D grid representing the map, containing cells of type Cell.
    map<pair<int, int>, Character*> characters; ///< 2D map containing the pointers to the Characters on the map.
};

#endif