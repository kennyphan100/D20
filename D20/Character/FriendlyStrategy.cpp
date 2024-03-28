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

void FriendlyStrategy::move(Character& character) {
    std::cout << "Friendly character is moving towards the player..." << std::endl;
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
        logFile << "Friendly character " << character.getName() << " moved." << "\n";
        logFile << "\n";
        logFile.close();
    }
}

void FriendlyStrategy::attack(Character& character) {
    std::cout << "Friendly character does not want to fight." << std::endl;
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
        logFile << "Friendly character " << character.getName() << " does not want to fight." << "\n";
        logFile << "\n";
        logFile.close();
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
