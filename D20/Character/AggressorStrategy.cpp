#include "AggressorStrategy.h"
#include "Character.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <ctime>

using namespace std;

AggressorStrategy::AggressorStrategy() {
    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        seeded = true;
    }
}

void AggressorStrategy::move(Character& character) {
    std::cout << "Aggressor moves towards the player..." << std::endl;
    ofstream logFile("./game_log.txt", ios::app);
    if (logFile.is_open()) {
        time_t t = time(nullptr);
        tm tm;
        localtime_s(&tm, &t);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);
        string timestamp(buffer);
        logFile << "============ Character Move ============" << endl;
        logFile << "Timestamp: " << timestamp << endl;
        logFile << "Aggressor " << character.getName() << " moved." << "\n";
        logFile << "\n";
        logFile.close();
    }
}

void AggressorStrategy::attack(Character& character) {
    // Attack logic...
    std::cout << "Aggressor attacks the player!" << std::endl;
    ofstream logFile("./game_log.txt", ios::app);
    if (logFile.is_open()) {
        time_t t = time(nullptr);
        tm tm;
        localtime_s(&tm, &t);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);
        string timestamp(buffer);
        logFile << "============ Character Attack ============" << endl;
        logFile << "Timestamp: " << timestamp << endl;
        logFile << "Aggressor " << character.getName() << " attacked." << "\n";
        logFile << "\n";
        logFile.close();
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
