#include "AggressorStrategy.h"
#include "Character.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <queue>
#include <chrono>
#include <thread>

using namespace std;

AggressorStrategy::AggressorStrategy() {
    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        seeded = true;
    }
}

void AggressorStrategy::move(Character& character, Map& map) {
    auto [charX, charY] = map.getCharacterPosition(character);
    auto [targetX, targetY] = map.findClosestAllyPosition(charX, charY, character);

    // If no ally is found, target the player's position
    if (targetX == -1 && targetY == -1) {
        std::tie(targetX, targetY) = map.getPlayerPosition();
    }

    // Don't move if the target is already adjacent
    if (std::abs(targetX - charX) <= 1 && std::abs(targetY - charY) <= 1) {
        return;
    }

    // Perform BFS to find the best cell within 10 moves
    std::queue<std::pair<int, int>> q;
    std::map<std::pair<int, int>, int> distance;
    std::map<std::pair<int, int>, std::pair<int, int>> prev;

    q.push({ charX, charY });
    distance[{charX, charY}] = 0;
    prev[{charX, charY}] = { -1, -1 };

    std::pair<int, int> bestCell = { charX, charY };
    int minDistance = std::numeric_limits<int>::max();

    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        int steps = distance[{x, y}];

        if (steps >= 10) {
            continue; // Skip any further processing if we've reached 10 steps
        }

        for (auto [dx, dy] : std::vector<std::pair<int, int>>{ {1, 0}, {-1, 0}, {0, 1}, {0, -1} }) {
            int nx = x + dx, ny = y + dy;

            // Bounds and obstacle checking
            if (nx < 0 || ny < 0 || nx >= map.getWidth() || ny >= map.getHeight() || !map.isEmptyCell(nx, ny) || distance.count({ nx, ny })) {
                continue; // Skip if out of bounds, not empty, or already visited
            }

            q.push({ nx, ny });
            distance[{nx, ny}] = steps + 1;
            prev[{nx, ny}] = { x, y };

            // If this is a cell closer to the target than any we've found so far, mark it as the best
            int distToTarget = std::abs(targetX - nx) + std::abs(targetY - ny);
            if (distToTarget < minDistance) {
                minDistance = distToTarget;
                bestCell = { nx, ny };
            }
        }
    }

    // Move along the path to the best cell found
    std::list<std::pair<int, int>> path;
    for (std::pair<int, int> at = bestCell; at != std::pair<int, int>{-1, -1}; at = prev[at]) {
        path.push_front(at); // Construct the path in reverse
    }

    // Iterate through the path and move the aggressor
    for (const auto& [nextX, nextY] : path) {
        if (distance[{nextX, nextY}] > 10) {
            break; // Stop if we're about to exceed 10 moves
        }

        map.moveCharacter(charX, charY, nextX, nextY);
        charX = nextX;
        charY = nextY;

        // Display the map with numbering after each move
        map.displayWithNumbering();
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Wait for half a second
    }

    std::cout << "Aggressor character moved towards the target.\n";
}

void AggressorStrategy::attack(Character& aggressor, Map& map) {
    auto [aggressorX, aggressorY] = map.getCharacterPosition(aggressor);

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;

            Character* target = map.getCharacter(aggressorX + dx, aggressorY + dy);
            if (target && (target->getStrategyType() == StrategyType::Friendly ||
                target->getStrategyType() == StrategyType::Player)) {
                Dice dice;
                std::string attackRollFormula = "1d20";
                int rollResult = dice.rollDice(attackRollFormula);

                if (rollResult >= target->getArmorClass()) {
                    std::string damageRollFormula = "1d8";
                    int damageRoll = dice.rollDice(damageRollFormula);
                    std::cout << "Aggressor hit the target for " << damageRoll << " damage.\n";
                    target->takeDamage(damageRoll);
                }
                else {
                    std::cout << "Aggressor's attack missed the target.\n";
                }
                return;
            }
        }
    }
}

void AggressorStrategy::freeAction(Character& character) {
    int action = std::rand() % 3;
    ofstream logFile("./game_log.txt", ios::app);

    switch (action) {
    case 0:
        std::cout << "Aggressor sharpens its weapons, increasing attack power." << std::endl;
        if (logFile.is_open()) {
            time_t t = time(nullptr);
            tm tm;
            localtime_s(&tm, &t);
            char buffer[80];
            strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);
            string timestamp(buffer);
            logFile << "============ Character Free Action ============" << endl;
            logFile << "Timestamp: " << timestamp << endl;
            logFile << "Aggressor " << character.getName() << " sharpens its weapons, increasing attack power." << "\n";
            logFile << "\n";
            logFile.close();
        }
        break;
    case 1:
        std::cout << "Aggressor taunts the player, potentially affecting player's decisions." << std::endl;
        if (logFile.is_open()) {
            time_t t = time(nullptr);
            tm tm;
            localtime_s(&tm, &t);
            char buffer[80];
            strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);
            string timestamp(buffer);
            logFile << "============ Character Free Action ============" << endl;
            logFile << "Timestamp: " << timestamp << endl;
            logFile << "Aggressor " << character.getName() << " taunts the player, potentially affecting player's decisions." << "\n";
            logFile << "\n";
            logFile.close();
        }
        break;
    case 2:
        std::cout << "Aggressor scouts for vulnerabilities, increasing its next attack's accuracy." << std::endl;
        if (logFile.is_open()) {
            time_t t = time(nullptr);
            tm tm;
            localtime_s(&tm, &t);
            char buffer[80];
            strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);
            string timestamp(buffer);
            logFile << "============ Character Free Action ============" << endl;
            logFile << "Timestamp: " << timestamp << endl;
            logFile << "Aggressor " << character.getName() << " scouts for vulnerabilities, increasing its next attack's accuracy." << "\n";
            logFile << "\n";
            logFile.close();
        }
        break;
    default:
        std::cerr << "Invalid action selected." << std::endl;
        break;
    }
}

StrategyType AggressorStrategy::getStrategyType() const {
    return StrategyType::Aggressor;
}