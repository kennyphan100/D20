#include "Map.h"
#include <queue>
#include <iostream>

struct Point {
    int x;
    int y;

    Point(int x, int y) : x(x), y(y) {}

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

Map::Map(int width, int height) : width(width), height(height), grid(height, std::vector<Cell>(width, Cell::EMPTY)) {
    // The grid is initialized in the member initializer list
}

bool isTraversable(const std::vector<std::vector<Cell>>& grid, int x, int y) {
    return x >= 0 && x < grid[0].size() && y >= 0 && y < grid.size() &&
        (grid[y][x] != Cell::WALL && grid[y][x] != Cell::OCCUPIED);
}

void Map::setCell(int x, int y, Cell cellType) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        grid[y][x] = cellType;
    }
    // You may want to handle errors for out-of-bounds indices
}

// BFS to find a path from top-left to bottom-right
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
            }
        }
        std::cout << std::endl;
    }
}