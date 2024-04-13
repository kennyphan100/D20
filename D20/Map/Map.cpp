//! @file 
//! @brief Implementation file for Map.h
//!

#include "Map.h"
#include <queue>
#include <iostream>
#include <fstream> 
#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include <filesystem>
#include "../Character/Character.h"
#include <ctime>
#include <chrono>
#include <thread>
#include <algorithm>
#include "../GUI/PlayGame.h"

using namespace std;

Map::Map() : width(0), height(0), name(" "), grid(0, vector<Cell>(0, Cell::EMPTY))
{
    reachedDoor = false;
}

//! Constructor of Map class
//! @param width : The width of the Map to be created
//! @param height : The height of the Map to be created
//! @return new Map object
Map::Map(int width, int height, string name) : width(width), height(height), name(name), grid(height, vector<Cell>(width, Cell::EMPTY))
{
    reachedDoor = false;
}

//! Checks if the map is traversable from the starting point to the ending point
//! A map is traversable if it's within the bounds of the grid and not a WALL or OCCUPIED cell blocks the passage.
//! @param grid The grid representing the map.
//! @param x The x-coordinate of the cell.
//! @param y The y-coordinate of the cell.
//! @return True if the cell is traversable, false otherwise.
bool isTraversable(const vector<vector<Cell>>& grid, int x, int y) {
    return x >= 0 && x < grid[0].size() && y >= 0 && y < grid.size() && (grid[y][x] != Cell::WALL && grid[y][x] != Cell::OCCUPIED);
}

//bool isTraversable(const vector<vector<Cell>>& grid, int x, int y, bool allowOccupiedStartEnd = false) {
//    if (x < 0 || x >= grid[0].size() || y < 0 || y >= grid.size()) return false;
//
//    Cell cell = grid[y][x];
//    return cell == Cell::EMPTY || (allowOccupiedStartEnd && (cell == Cell::OCCUPIED || cell == Cell::PLAYER));
//}

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
    queue<MapPoint> q;
    vector<vector<bool>> visited(height, vector<bool>(width, false));

    // Starting point
    MapPoint start(0, 0);
    // Ending point
    MapPoint end(width - 1, height - 1);

    // Directions to move in the grid (up, down, left, right)
    vector<MapPoint> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

    // Initialize BFS from the starting point
    q.push(start);
    visited[start.y][start.x] = true;

    // Perform BFS
    while (!q.empty()) {
        MapPoint current = q.front();
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
            case Cell::AGGRESSOR:
                cout << "A ";
                break;
            case Cell::FRIENDLY:
                cout << "F ";
                break;
            }
        }
        cout << endl;
    }
}
void Map::displayWithNumbering() const {
    // Display column numbers on top
    cout << "  ";
    cout << "\t";
    cout << "  ";
    for (int x = 0; x < getWidth(); ++x) {
        cout << x << " ";
    }
    cout << endl;

    for (int y = 0; y < getHeight(); ++y) {
        // Display row numbers on the left
        cout << "\t";
        cout << y << " ";

        for (int x = 0; x < getWidth(); ++x) {
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
            case Cell::AGGRESSOR:
                cout << "A ";
                break;
            case Cell::FRIENDLY:
                cout << "F ";
                break;
            }
        }
        cout << endl;
    }
    cout << "\n";
}

void Map::logMap(ostream& out) const {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            switch (grid[y][x]) {
            case Cell::EMPTY:
                out << "_ ";
                break;
            case Cell::WALL:
                out << "W ";
                break;
            case Cell::OCCUPIED:
                out << "O ";
                break;
            case Cell::START:
                out << "S ";
                break;
            case Cell::FINISH:
                out << "F ";
                break;
            case Cell::DOOR:
                out << "D ";
                break;
            case Cell::CHEST:
                out << "C ";
                break;
            case Cell::PLAYER:
                out << "P ";
                break;
            }
        }
        out << endl;
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

    ofstream logFile("./game_log.txt", ios::app);
    if (logFile.is_open()) {
        time_t t = time(nullptr);
        tm tm;
        localtime_s(&tm, &t);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);
        string timestamp(buffer);
        logFile << "============ Loaded Map ============" << endl;
        logFile << "Timestamp: " << timestamp << endl;
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                // Assuming Cell is an enum and grid is a 2D vector of Cells
                // Convert each cell type to an integer or a character
                switch (grid[y][x]) {
                case Cell::START:
                    logFile << "S ";  // Start
                    break;
                case Cell::FINISH:
                    logFile << "F ";  // Finish
                    break;
                case Cell::EMPTY:
                    logFile << "_ ";  // Empty
                    break;
                case Cell::WALL:
                    logFile << "W ";  // Wall
                    break;
                case Cell::OCCUPIED:
                    logFile << "O ";  // Occupied
                    break;
                case Cell::PLAYER:
                    logFile << "P ";  // Player
                    break;
                case Cell::DOOR:
                    logFile << "D ";  // Door
                    break;
                case Cell::CHEST:
                    logFile << "C ";  // Chest
                    break;
                default:
                    logFile << "X ";  // Unknown or other types
                }
            }
            logFile << endl;  // Newline after each row
        }
        logFile << "\n";
        logFile.close();
    }

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

vector<vector<Cell>> Map::getGrid() const
{
    return grid;
}

void Map::placeCharacter(int x, int y, Character* character) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Character coordinates are out of bounds.");
    }
    if (grid[y][x] != Cell::EMPTY) {
        throw std::logic_error("Cannot place a character on a non-empty cell.");
    }
    if (character->getStrategyType() == StrategyType::Aggressor) {
        grid[y][x] = Cell::AGGRESSOR;
    }
    else if (character->getStrategyType() == StrategyType::Friendly) {
        grid[y][x] = Cell::FRIENDLY;
    }
    else {
        grid[y][x] = Cell::PLAYER;
    }
    characters[{x, y}] = character;
}

Character* Map::getCharacter(int x, int y) const {
    auto it = characters.find({ x, y });
    if (it != characters.end()) {
        return it->second;
    }
    return nullptr;
}

void Map::removeCharacter(int x, int y) {
    grid[y][x] = Cell::EMPTY;
    characters.erase({ x, y });
}

bool Map::moveCharacter(int fromX, int fromY, int toX, int toY) {
    auto it = characters.find({ fromX, fromY });
    if (it == characters.end()) {
        std::cerr << "No character at the starting position." << std::endl;
        return false;
    }

    if (toX < 0 || toX >= width || toY < 0 || toY >= height) {
        std::cerr << "Target position is out of bounds." << std::endl;
        return false;
    }

    bool isMovingToDoor = (grid[toY][toX] == Cell::DOOR);

    if (!(grid[toY][toX] == Cell::EMPTY || isMovingToDoor)) {
        std::cerr << "Target position is blocked." << std::endl;
        return false;
    }

    Character* character = it->second;
    characters.erase(it);
    characters[{toX, toY}] = character;

    setCell(fromX, fromY, Cell::EMPTY);

    if (character->getStrategyType() == StrategyType::Aggressor) {
        setCell(toX, toY, Cell::AGGRESSOR);
    }
    else if (character->getStrategyType() == StrategyType::Friendly) {
        setCell(toX, toY, Cell::FRIENDLY);
    }
    else {
        setCell(toX, toY, Cell::PLAYER);
    }

    if (isMovingToDoor) {
        reachedDoor = true;
        std::cout << "The player has reached a door. Saving game..." << std::endl;
        std::cout << "The player has reached a door. Saving game..." << std::endl;
        //character->saveToFile("./data/characters/auto_save_character.txt");
        character->saveToFile("./data/characters/" + character->getName() + ".txt");
    }

    return true;
}

std::vector<MapPoint> Map::findShortestPath(int startX, int startY, int endX, int endY) {
    std::vector<std::vector<int>> distances(height, std::vector<int>(width, std::numeric_limits<int>::max()));
    distances[startY][startX] = 0;

    std::queue<MapPoint> q;
    q.push({ startX, startY });

    std::map<MapPoint, MapPoint> prev;
    prev[{startX, startY}] = { -1, -1 };

    std::vector<MapPoint> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

    while (!q.empty()) {
        MapPoint current = q.front();
        q.pop();

        if ((current.x == endX && current.y == endY && (grid[endY][endX] == Cell::DOOR || grid[endY][endX] == Cell::EMPTY)) ||
            (current.x == endX && current.y == endY)) {
            break;
        }

        for (const auto& dir : directions) {
            int nx = current.x + dir.x;
            int ny = current.y + dir.y;

            if (nx >= 0 && nx < width && ny >= 0 && ny < height &&
                (grid[ny][nx] == Cell::EMPTY || grid[ny][nx] == Cell::DOOR) && distances[ny][nx] == std::numeric_limits<int>::max()) {
                distances[ny][nx] = distances[current.y][current.x] + 1;
                q.push({ nx, ny });
                prev[{nx, ny}] = current;
            }
        }
    }

    std::vector<MapPoint> path;
    if (prev.find({ endX, endY }) != prev.end()) {
        for (MapPoint at(endX, endY); at != MapPoint(-1, -1); at = prev[at]) {
            path.push_back(at);
        }
        std::reverse(path.begin(), path.end());
    }

    return path;
}

std::pair<int, int> Map::getCharacterPosition(Character& character) {
    for (const auto& entry : characters) {
        const auto& position = entry.first;
        Character* storedCharacter = entry.second;
        if (storedCharacter == &character) {
            return std::make_pair(position.first, position.second);
        }
    }
    return std::make_pair(-1, -1);
}

std::pair<int, int> Map::findClosestEnemyPosition(int charX, int charY) {
    std::pair<int, int> closestEnemyPos = { -1, -1 };
    int minDistance = std::numeric_limits<int>::max();

    for (const auto& entry : characters) {
        const auto& position = entry.first;
        Character* character = entry.second;

        //if (character && character->getStrategyType() == StrategyType::Aggressor) {
        if (character->getName() == "Hellfire") {
            int distance = std::abs(charX - position.first) + std::abs(charY - position.second);
            if (distance < minDistance) {
                minDistance = distance;
                closestEnemyPos = position;
            }
        }
    }

    return closestEnemyPos;
}

std::pair<int, int> Map::getPlayerPosition() const {
    for (const auto& entry : characters) {
        const auto& position = entry.first;
        Character* character = entry.second;

        if (character && character->getStrategyType() == StrategyType::Player) {
            return position;
        }
    }

    return std::make_pair(-1, -1);
}

std::pair<int, int> Map::findClosestAllyPosition(int charX, int charY, const Character& askingCharacter) {
    std::pair<int, int> closestAllyPos = { -1, -1 };
    int minDistance = std::numeric_limits<int>::max();

    for (const auto& entry : characters) {
        const auto& position = entry.first;
        Character* potentialAlly = entry.second;

        if (potentialAlly != &askingCharacter) {
            int distance = std::abs(charX - position.first) + std::abs(charY - position.second);
            if (distance < minDistance) {
                minDistance = distance;
                closestAllyPos = position;
            }
        }
    }

    return closestAllyPos;
}

void Map::visualizePath(const std::vector<MapPoint>& path) {
    for (const auto& p : path) {
        setCell(p.x, p.y, Cell::PATH);
        displayWithNumbering();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        setCell(p.x, p.y, Cell::EMPTY);
    }
}

void Map::visualizePath(const std::vector<MapPoint>& path, Character& character) {
    for (size_t i = 1; i < path.size(); ++i) {
        MapPoint from = path[i - 1];
        MapPoint to = path[i];

        this->moveCharacter(from.x, from.y, to.x, to.y);

        this->displayWithNumbering();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void Map::visualizePath(const std::vector<MapPoint>& path, Character& character, PlayGame& playGame) {
    for (size_t i = 1; i < path.size(); ++i) {
        MapPoint from = path[i - 1];
        MapPoint to = path[i];

        this->moveCharacter(from.x, from.y, to.x, to.y);

        this->displayWithNumbering();

        playGame.characterPositionX = to.x;
        playGame.characterPositionY = to.y;
        playGame.drawSelectedMapGrid(this);

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

bool Map::isPlayerAtDoor() {
    return reachedDoor;
}
