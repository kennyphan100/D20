#include "FriendlyStrategy.h"
#include "Character.h"
#include "AggressorStrategy.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <thread>

using namespace std;

FriendlyStrategy::FriendlyStrategy() {
    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        seeded = true;
    }
}

void FriendlyStrategy::move(Character& character, Map& map) {
    auto [charX, charY] = map.getCharacterPosition(character);
    auto [targetX, targetY] = map.findClosestEnemyPosition(charX, charY);

    if (targetX == -1 && targetY == -1) {
        std::tie(targetX, targetY) = map.getPlayerPosition();
    }

    if (std::abs(targetX - charX) + std::abs(targetY - charY) == 1) {
        return;
    }

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
            continue;
        }

        for (auto [dx, dy] : std::vector<std::pair<int, int>>{ {1, 0}, {-1, 0}, {0, 1}, {0, -1} }) {
            int nx = x + dx, ny = y + dy;

            if (nx >= 0 && ny >= 0 && nx < map.getWidth() && ny < map.getHeight() &&
                map.isEmptyCell(nx, ny) && distance.count({ nx, ny }) == 0) {
                q.push({ nx, ny });
                distance[{nx, ny}] = steps + 1;
                prev[{nx, ny}] = { x, y };

                int distToTarget = std::abs(targetX - nx) + std::abs(targetY - ny);
                if (distToTarget < minDistance) {
                    minDistance = distToTarget;
                    bestCell = { nx, ny };
                }
            }
        }
    }

    std::list<std::pair<int, int>> path;
    for (std::pair<int, int> at = bestCell; at != std::pair<int, int>{-1, -1}; at = prev[at]) {
        path.push_front(at);
    }

    for (const auto& [nextX, nextY] : path) {
        if (distance[{nextX, nextY}] > 10) {
            break;
        }

        map.moveCharacter(charX, charY, nextX, nextY);
        charX = nextX;
        charY = nextY;

        map.displayWithNumbering();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    std::cout << "Friendly character moved towards the target.\n";
}

void FriendlyStrategy::moveGUI(Character& character, Map& map, int targetX, int targetY, PlayGame& playGame) {
    //auto [startX, startY] = map.getCharacterPosition(character);
    //if (startX == -1 && startY == -1) {
    //    std::cerr << "Error: Character's position not found on the map.\n";
    //    return;
    //}

    //std::vector<MapPoint> path = map.findShortestPath(startX, startY, targetX, targetY);

    //if (path.empty()) {
    //    std::cout << "Invalid move. Target is either unreachable or too far away.\n";
    //    return;
    //}

    //if (path.size() > 11) {
    //    std::cout << "Invalid move. Target is too far away.\n";
    //    return;
    //}

    //if (!path.empty() && path.size() <= 11) {
    //    map.visualizePath(path, character);
    //    std::cout << "Character moved to target position.\n";
    //}

    //std::ofstream logFile("./game_log.txt", std::ios::app);
    //if (logFile.is_open()) {
    //    logFile << "============ Character Move ============\n";
    //    logFile << "Character " << character.getName() << " moved from (" << startX << ", " << startY
    //        << ") to (" << targetX << ", " << targetY << ") covering a distance of "
    //        << path.size() - 1 << " units.\n\n";
    //    logFile.close();
    //}

    //map.displayWithNumbering();
}

void FriendlyStrategy::attack(Character& friendly, Map& map) {
    auto [friendlyX, friendlyY] = map.getCharacterPosition(friendly);

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;

            Character* target = map.getCharacter(friendlyX + dx, friendlyY + dy);
            if (target && target->getStrategyType() == StrategyType::Aggressor) {
                Dice dice;
                std::string attackRollFormula = "1d20";
                int rollResult = dice.rollDice(attackRollFormula);

                if (rollResult >= target->getArmorClass()) {
                    std::string damageRollFormula = "1d8";
                    int damageRoll = dice.rollDice(damageRollFormula);
                    target->takeDamage(damageRoll);

                    std::cout << "Friendly hit the target for " << damageRoll << " damage.\n";
                }
                else {
                    std::cout << "Friendly's attack missed the target.\n";
                }
                return;
            }
        }
    }
}

void FriendlyStrategy::freeAction(Character& character, Map& map) {
    int action = std::rand() % 3;
    ofstream logFile("./game_log.txt", ios::app);

    switch (action) {
    case 0:
        std::cout << "Friendly character heals an ally." << std::endl;
        if (logFile.is_open()) {
            time_t t = time(nullptr);
            tm tm;
            localtime_s(&tm, &t);
            char buffer[80];
            strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);
            string timestamp(buffer);
            logFile << "============ Character Free Action ============" << endl;
            logFile << "Timestamp: " << timestamp << endl;
            logFile << "Friendly character " << character.getName() << " heals an ally." << "\n";
            logFile << "\n";
            logFile.close();
        }
        break;
    case 1:
        std::cout << "Friendly character gives advice." << std::endl;
        if (logFile.is_open()) {
            time_t t = time(nullptr);
            tm tm;
            localtime_s(&tm, &t);
            char buffer[80];
            strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);
            string timestamp(buffer);
            logFile << "============ Character Free Action ============" << endl;
            logFile << "Timestamp: " << timestamp << endl;
            logFile << "Friendly character " << character.getName() << " gives advice." << "\n";
            logFile << "\n";
            logFile.close();
        }
        break;
    case 2:
        std::cout << "Friendly character scouts the area." << std::endl;
        if (logFile.is_open()) {
            time_t t = time(nullptr);
            tm tm;
            localtime_s(&tm, &t);
            char buffer[80];
            strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);
            string timestamp(buffer);
            logFile << "============ Character Free Action ============" << endl;
            logFile << "Timestamp: " << timestamp << endl;
            logFile << "Friendly character " << character.getName() << " scouts the area." << "\n";
            logFile << "\n";
            logFile.close();
        }
        break;
    default:
        std::cerr << "Unexpected action index." << std::endl;
    }
}

void FriendlyStrategy::switchToAggressor(Character& character) {
    std::cout << "Friendly character is now hostile." << std::endl;
    character.setStrategy(new AggressorStrategy());
}

StrategyType FriendlyStrategy::getStrategyType() const {
    return StrategyType::Friendly;
}