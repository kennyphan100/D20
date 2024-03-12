//! @file 
//! @brief Implementation file for Map.h
//!

#include "Map.h"
#include <queue>
#include <iostream>
#include <fstream> 
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>

using namespace std;

//! Represents a point in 2D space.
struct Point {
    int x;
    int y;

    Point(int x, int y) : x(x), y(y) {}

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

Map::Map() : width(0), height(0), name(" "), grid(0, vector<Cell>(0, Cell::EMPTY))
{
}

//! Constructor of Map class
//! @param width : The width of the Map to be created
//! @param height : The height of the Map to be created
//! @return new Map object
Map::Map(int width, int height, string name) : width(width), height(height), name(name), grid(height, vector<Cell>(width, Cell::EMPTY))
{
}

//! Checks if the map is traversable from the starting point to the ending point
//! A map is traversable if it's within the bounds of the grid and not a WALL or OCCUPIED cell blocks the passage.
//! @param grid The grid representing the map.
//! @param x The x-coordinate of the cell.
//! @param y The y-coordinate of the cell.
//! @return True if the cell is traversable, false otherwise.
bool isTraversable(const vector<vector<Cell>>& grid, int x, int y) {
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
//! @throw out_of_range If the coordinates are out of bounds.
void Map::setCell(int x, int y, Cell cellType) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw out_of_range("Cell coordinates are out of bounds.");
    }
    grid[y][x] = cellType;
    notify();
}

//! Verifies if there exists a path from the top-left corner to the bottom-right corner of the map.
//! Uses Breadth First Search (BFS) algorithm to find the path.
//! @return True if a path exists, false otherwise.
bool Map::verifyMap() {
    queue<Point> q;
    vector<vector<bool>> visited(height, vector<bool>(width, false));

    // Starting point
    Point start(0, 0);
    // Ending point
    Point end(width - 1, height - 1);

    // Directions to move in the grid (up, down, left, right)
    vector<Point> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

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
                cout << "_ ";
                break;
            case Cell::WALL:
                cout << "W ";
                break;
            case Cell::OCCUPIED:
                cout << "O ";
                break;
            case Cell::START:
                cout << "S ";
                break;
            case Cell::FINISH:
                cout << "F ";
                break;
            case Cell::DOOR:
                cout << "D ";
                break;
            case Cell::CHEST:
                cout << "C ";
                break;
            case Cell::PLAYER:
                cout << "P ";
                break;
            }
        }
        cout << endl;
    }
}

//! Gets the width of the map.
//! @return The width of the map.
int Map::getWidth() const {
    return width;
}

//! Gets the height of the map.
//! @return The height of the map.
int Map::getHeight() const {
    return height;
}

//! Gets the cell type.
//! @return The type of the cell.
Cell Map::getCell(int x, int y) const {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return grid[y][x];
    }
    else {
        throw out_of_range("Cell coordinates are out of bounds.");
    }
}

string Map::getName() const {
    return name;
}

bool Map::saveToFile(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file '" << filename << "' for writing.\n";
        return false;
    }

    // Write the map dimensions first (optional but useful for loading)
    file << width << " " << height << endl;

    // Loop through each cell of the map and write its type to the file
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Assuming Cell is an enum and grid is a 2D vector of Cells
            // Convert each cell type to an integer or a character
            switch (grid[y][x]) {
            case Cell::START:
                file << "S ";  // Start
                break;
            case Cell::FINISH:
                file << "F ";  // Finish
                break;
            case Cell::EMPTY:
                file << "_ ";  // Empty
                break;
            case Cell::WALL:
                file << "W ";  // Wall
                break;
            case Cell::OCCUPIED:
                file << "O ";  // Occupied
                break;
            case Cell::PLAYER:
                file << "P ";  // Player
                break;
            case Cell::DOOR:
                file << "D ";  // Door
                break;
            case Cell::CHEST:
                file << "C ";  // Chest
                break;
            default:
                file << "X ";  // Unknown or other types
            }
        }
        file << endl;  // Newline after each row
    }

    file.close();
    return true;  // Return true to indicate successful saving
}

bool Map::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return false;
    }

    filesystem::path filePath(filename);
    setName(filePath.stem().string());

    int width, height;
    file >> width >> height;
    file.ignore(numeric_limits<streamsize>::max(), '\n'); // Skip to the next line

    // Optional: Check if width and height read successfully
    if (file.fail()) {
        cerr << "Error reading map dimensions." << endl;
        return false;
    }

    vector<vector<Cell>> tempGrid(height, vector<Cell>(width, Cell::EMPTY)); // Create a temporary grid

    string line;
    for (int y = 0; y < height && getline(file, line); ++y) {
        istringstream lineStream(line);
        for (int x = 0; x < width; ++x) {
            char cellTypeChar;
            if (!(lineStream >> cellTypeChar)) {
                cerr << "Error reading map at (" << x << ", " << y << ")." << endl;
                return false; // Error handling
            }

            // Convert the character to a Cell enum value
            // This assumes you have a method or logic to translate characters to Cell values
            Cell cellType = charToCellType(cellTypeChar);
            tempGrid[y][x] = cellType;
        }
    }

    this->width = width; // Update the map's dimensions
    this->height = height;
    this->grid = tempGrid; // Update the map's grid

    return true;
}

Cell Map::charToCellType(char c) {
    switch (c) {
    case 'S': return Cell::START;
    case 'F': return Cell::FINISH;
    case 'E': return Cell::EMPTY;
    case 'W': return Cell::WALL;
    case 'O': return Cell::OCCUPIED; // Assuming 'O' represents an occupied cell
    case 'P': return Cell::PLAYER;   // Assuming 'P' represents a player
    case 'D': return Cell::DOOR;     // Assuming 'D' represents a door
    case 'C': return Cell::CHEST;    // Assuming 'C' represents a chest
    default:  return Cell::EMPTY;    // Default case if character does not match
    }
}

void Map::setName(string newName) {
    name = newName;
}