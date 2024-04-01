#include "AggressorStrategy.h"
#include "Character.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

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

    int targetX = -1, targetY = -1;

    std::tie(targetX, targetY) = map.findClosestAllyPosition(charX, charY, character);

    if (targetX == -1 && targetY == -1) {
        std::tie(targetX, targetY) = map.getPlayerPosition();
    }

    if (targetX != -1 && targetY != -1) {
        int dirX = targetX - charX, dirY = targetY - charY;
        if (std::abs(dirX) > std::abs(dirY)) {
            dirX = (dirX > 0) ? 1 : -1;
            dirY = 0;
        }
        else {
            dirY = (dirY > 0) ? 1 : -1;
            dirX = 0;
        }

        if (map.isEmptyCell(charX + dirX, charY + dirY)) {
            map.moveCharacter(charX, charY, charX + dirX, charY + dirY);
            std::cout << "Aggressor character " << character.getName() << " moves towards ally/player." << std::endl;
        }
        else {
            std::cout << "Aggressor character " << character.getName() << " cannot move towards ally/player due to an obstacle." << std::endl;
        }
    }
    else {
        std::cout << "No valid ally/player found for aggressor character to move towards." << std::endl;
    }
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
                    target->takeDamage(damageRoll);

                    std::cout << "Aggressor hit the target for " << damageRoll << " damage.\n";
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
    return StrategyType::Player;
}