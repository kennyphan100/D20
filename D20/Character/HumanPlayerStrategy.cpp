#include "HumanPlayerStrategy.h"
#include "Character.h"
#include "../Dice/Dice.h"
#include "../Map/Map.h"
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include "../GUI/PlayGame.h"

using namespace std;

HumanPlayerStrategy::HumanPlayerStrategy()
{
}

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

void HumanPlayerStrategy::moveGUI(Character& character, Map& map, int targetX, int targetY, PlayGame& playGame) {
    auto [startX, startY] = map.getCharacterPosition(character);
    if (startX == -1 && startY == -1) {
        std::cerr << "Error: Character's position not found on the map.\n";
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
        map.visualizePath(path, character, playGame);
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

void HumanPlayerStrategy::moveGUI(Character& character, Map& map, PlayGame& playGame)
{
    // this function is not used
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

void HumanPlayerStrategy::attackGUI(Character& character, Map& map, int targetX, int targetY, PlayGame& playGame)
{
    Character* target = map.getCharacter(targetX, targetY);
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
        std::cout << "Hit! Target takes " << damageRoll << " damage.\n";
        target->takeDamage(damageRoll);

        if (target->hitPoints <= 0) {
            map.setCell(targetX, targetY, Cell::EMPTY);
            playGame.removeObject(playGame.objects, targetX, targetY);

            playGame.isAggressorDead = true;

            playGame.drawSelectedMapGrid(&map);
            playGame.drawSelectedMapGridStatic(map.getName());
        }

    }
    else {
        std::cout << "Miss! The attack did not hit the target.\n";
    }
}

void HumanPlayerStrategy::freeAction(Character& character, Map& map) {
    std::cout << "\nChoose a free action: \n1. Rest (recover health)\n2. Look around\n3. Speak\n4. Interact\nEnter choice: ";
    int choice;
    std::cin >> choice;

    ofstream logFile("./game_log.txt", ios::app);
    bool interacted = false;  // Declare before switch statement
    auto [charX, charY] = map.getCharacterPosition(character);  // Declare before switch statement

    switch (choice) {
    case 1:
        std::cout << "Resting... health recovered." << std::endl;
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
    case 4:
        std::cout << "Attempting to interact with nearby objects..." << std::endl;

        for (auto [dx, dy] : std::vector<std::pair<int, int>>{ {0, -1}, {1, 0}, {0, 1}, {-1, 0} }) {
            int nx = charX + dx, ny = charY + dy;
            if (map.getCell(nx, ny) == Cell::CHEST) {
                Item* item = Item::spawnRandomItem();
                character.addToInventory(item);
                std::cout << "Found and interacted with a chest! Obtained: " << item->getName() << std::endl;
                map.setCell(nx, ny, Cell::EMPTY);
                interacted = true;
                break;
            }
        }

        if (!interacted) {
            std::cout << "No interactable objects nearby." << std::endl;
        }

        if (interacted && logFile.is_open()) {
            time_t t = time(nullptr);
            tm tm;
            localtime_s(&tm, &t);
            char buffer[80];
            strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);
            string timestamp(buffer);
            logFile << "============ Character Interact ============" << endl;
            logFile << "Timestamp: " << timestamp << endl;
            logFile << "Character " << character.getName() << " interacted." << "\n";
            logFile << "\n";
            logFile.close();
        }
        break;
    default:
        std::cout << "Invalid choice." << std::endl;
        break;
    }

    if (logFile.is_open()) {
        logFile.close();
    }
}

StrategyType HumanPlayerStrategy::getStrategyType() const {
    return StrategyType::Player;
}
