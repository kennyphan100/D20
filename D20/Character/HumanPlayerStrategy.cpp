#include "HumanPlayerStrategy.h"
#include "Character.h"
#include "../Dice/Dice.h"
#include "../Map/Map.h"
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

void HumanPlayerStrategy::move(Character& character, Map& map) {
    auto [startX, startY] = map.getCharacterPosition(character);
    if (startX == -1 && startY == -1) {
        std::cerr << "Error: Character's position not found on the map.\n";
        return;
    }

    std::cout << "Current position: (" << startX << ", " << startY << ")\n";
    std::cout << "Enter target position coordinates (x y): ";
    int targetX, targetY;
    std::cin >> targetX >> targetY;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Invalid input. Please enter numerical coordinates.\n";
        return;
    }

    std::vector<MapPoint> path = map.findShortestPath(startX, startY, targetX, targetY);

    if (path.empty()) {
        std::cout << "Invalid move. Target is either unreachable or too far away.\n";
        return;
    }

    if (path.size() > 11) {
        std::cout << "Invalid move. Target is too far away.\n";
        return;
    }

    if (!path.empty() && path.size() <= 11) {
        map.visualizePath(path, character);
        std::cout << "Character moved to target position.\n";
    }

    std::ofstream logFile("./game_log.txt", std::ios::app);
    if (logFile.is_open()) {
        logFile << "============ Character Move ============\n";
        logFile << "Character " << character.getName() << " moved from (" << startX << ", " << startY
            << ") to (" << targetX << ", " << targetY << ") covering a distance of "
            << path.size() - 1 << " units.\n\n";
        logFile.close();
    }

    map.displayWithNumbering();
}

void HumanPlayerStrategy::attack(Character& attacker, Map& map) {
    std::cout << "\nEnter the position of the target to attack (x y): ";
    int x, y;
    std::cin >> x >> y;

    Character* target = map.getCharacter(x, y);
    if (!target) {
        std::cout << "No target found at the given position.\n";
        return;
    }

    Dice dice;
    std::string attackRoll = "1d20";
    int rollResult = dice.rollDice(attackRoll);

    std::ofstream logFile("./game_log.txt", std::ios::app);
    if (logFile.is_open()) {
        logFile << "============ Character Attack ============" << endl;
        //logFile << "Character " << character.getName() << " attack " << targetId << "." << "\n";
        logFile << "\n";
        logFile.close();
    }

    if (rollResult >= target->getArmorClass()) {
        int damageRoll = dice.rollDice("1d8");
        target->takeDamage(damageRoll);
        std::cout << "Hit! Target takes " << damageRoll << " damage.\n";
    }
    else {
        std::cout << "Miss! The attack did not hit the target.\n";
    }
}


void HumanPlayerStrategy::freeAction(Character& character) {
    std::cout << "\nChoose a free action: \n1. Rest (recover health)\n2. Look around\n3. Speak\nEnter choice: ";
    int choice;
    std::cin >> choice;
    ofstream logFile("./game_log.txt", ios::app);

    switch (choice) {
    case 1:
        std::cout << "Resting... health recovered." << std::endl;
        // Implement health recovery
        if (logFile.is_open()) {
            time_t t = time(nullptr);
            tm tm;
            localtime_s(&tm, &t);
            char buffer[80];
            strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);
            string timestamp(buffer);
            logFile << "============ Character Rest ============" << endl;
            logFile << "Timestamp: " << timestamp << endl;
            logFile << "Character " << character.getName() << " rest." << "\n";
            logFile << "\n";
            logFile.close();
        }
        break;
    case 2:
        std::cout << "Looking around the area..." << std::endl;
        // Implement the logic to describe the area or reveal certain elements
        if (logFile.is_open()) {
            time_t t = time(nullptr);
            tm tm;
            localtime_s(&tm, &t);
            char buffer[80];
            strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);
            string timestamp(buffer);
            logFile << "============ Character Look ============" << endl;
            logFile << "Timestamp: " << timestamp << endl;
            logFile << "Character " << character.getName() << " look." << "\n";
            logFile << "\n";
            logFile.close();
        }
        break;
    case 3:
        std::cout << "Speaking to nearby characters..." << std::endl;
        // Implement interaction with NPCs or other characters
        if (logFile.is_open()) {
            time_t t = time(nullptr);
            tm tm;
            localtime_s(&tm, &t);
            char buffer[80];
            strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);
            string timestamp(buffer);
            logFile << "============ Character Speak ============" << endl;
            logFile << "Timestamp: " << timestamp << endl;
            logFile << "Character " << character.getName() << " speak." << "\n";
            logFile << "\n";
            logFile.close();
        }
        break;
    default:
        std::cout << "Invalid choice." << std::endl;
        break;
    }
}

StrategyType HumanPlayerStrategy::getStrategyType() const {
    return StrategyType::Player;
}
