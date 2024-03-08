//! @file 
//! @brief Implementation file for Map.h
//!

#include "Map.h"
#include <queue>
#include <iostream>

//! Represents a point in 2D space.
struct Point {
    int x;
    int y;

    Point(int x, int y) : x(x), y(y) {}

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

//! Constructor of Map class
//! @param width : The width of the Map to be created
//! @param height : The height of the Map to be created
//! @return new Map object
Map::Map(int width, int height, string name) : width(width), height(height), name(name), grid(height, std::vector<Cell>(width, Cell::EMPTY)) {
}

//! Checks if the map is traversable from the starting point to the ending point
//! A map is traversable if it's within the bounds of the grid and not a WALL or OCCUPIED cell blocks the passage.
//! @param grid The grid representing the map.
//! @param x The x-coordinate of the cell.
//! @param y The y-coordinate of the cell.
//! @return True if the cell is traversable, false otherwise.
bool isTraversable(const std::vector<std::vector<Cell>>& grid, int x, int y) {
    return x >= 0 && x < grid[0].size() && y >= 0 && y < grid.size() &&
        (grid[y][x] != Cell::WALL && grid[y][x] != Cell::OCCUPIED);
}

//! Checks if the given coordinates represent an empty cell in the map.
//! @param x The x-coordinate of the cell.
//! @param y The y-coordinate of the cell.
//! @return True if the cell is empty, false otherwise.
bool Map::isEmptyCell(int x, int y) {
    if (grid[y][x] != Cell::EMPTY) {
        return false;
    }
    return true;
}

//! Sets the type of a cell at the specified coordinates.
//! @param x The x-coordinate of the cell.
//! @param y The y-coordinate of the cell.
//! @param cellType The type of the cell to be set.
//! @throw std::out_of_range If the coordinates are out of bounds.
void Map::setCell(int x, int y, Cell cellType) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Cell coordinates are out of bounds.");
    }
    grid[y][x] = cellType;
}

//! Verifies if there exists a path from the top-left corner to the bottom-right corner of the map.
//! Uses Breadth First Search (BFS) algorithm to find the path.
//! @return True if a path exists, false otherwise.
bool Map::verifyMap() {
    std::queue<Point> q;
    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));

    // Starting point
    Point start(0, 0);
    // Ending point
    Point end(width - 1, height - 1);

    // Directions to move in the grid (up, down, left, right)
    std::vector<Point> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

    // Initialize BFS from the starting point
    q.push(start);
    visited[start.y][start.x] = true;

    // Perform BFS
    while (!q.empty()) {
        Point current = q.front();
        q.pop();

        // Check if we've reached the end
        if (current == end) {
            return true;
        }

        // Explore neighbors
        for (const auto& dir : directions) {
            int newX = current.x + dir.x;
            int newY = current.y + dir.y;

            if (isTraversable(grid, newX, newY) && !visited[newY][newX]) {
                visited[newY][newX] = true;
                q.emplace(newX, newY);
            }
        }
    }

    // If BFS completes without finding the end, there is no path
    return false;
}

//! Displays the map on the console.
//! Uses characters to represent different types of cells.
void Map::display() const {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            switch (grid[y][x]) {
            case Cell::EMPTY:
                std::cout << '_';
                break;
            case Cell::WALL:
                std::cout << '!';
                break;
            case Cell::OCCUPIED:
                std::cout << 'O';
                break;
            case Cell::START:
                std::cout << 'S';
                break;
            case Cell::FINISH:
                std::cout << 'F';
                break;
            }
        }
        std::cout << std::endl;
    }
}

int Map::getWidth() const {
    return width;
}

int Map::getHeight() const {
    return height;
}