#include "FriendlyStrategy.h"
#include "Character.h"
#include "AggressorStrategy.h"
#include <iostream>
#include <fstream>
#include <ctime>

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

    int targetX = -1, targetY = -1;

    std::tie(targetX, targetY) = map.findClosestEnemyPosition(charX, charY);

    if (targetX == -1 && targetY == -1) {
        std::tie(targetX, targetY) = map.getPlayerPosition();
    }

    if (targetX != -1 && targetY != -1) {
        int dirX = targetX - charX, dirY = targetY - charY;
        if (abs(dirX) > abs(dirY)) {
            dirX = (dirX > 0) ? 1 : -1;
            dirY = 0;
        }
        else {
            dirY = (dirY > 0) ? 1 : -1;
            dirX = 0;
        }

        if (map.isEmptyCell(charX + dirX, charY + dirY)) {
            map.moveCharacter(charX, charY, charX + dirX, charY + dirY);
            std::cout << "Friendly character " << character.getName() << " moves towards target." << std::endl;

            std::ofstream logFile("./game_log.txt", std::ios::app);
            if (logFile.is_open()) {
                logFile << "============ Character Move ============\n";
                logFile << "Friendly character " << character.getName() << " moved towards (" << targetX << ", " << targetY << ").\n\n";
                logFile.close();
            }
        }
        else {
            std::cout << "Friendly character " << character.getName() << " cannot move towards target due to an obstacle." << std::endl;
        }
    }
    else {
        std::cout << "No valid target found for friendly character to move towards." << std::endl;
    }
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

void FriendlyStrategy::freeAction(Character& character) {
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
    return StrategyType::Player;
}