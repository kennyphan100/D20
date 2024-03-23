#include "HumanPlayerStrategy.h"
#include "Character.h"
#include <iostream>
#include <string>
#include <fstream>

void HumanPlayerStrategy::move(Character& character) {
    std::cout << "Enter move direction (N, S, E, W): ";
    std::string direction;
    std::cin >> direction;
    std::cout << "Moving " << direction << std::endl;
    ofstream logFile("./game_log.txt", ios::app);
    if (logFile.is_open()) {
        logFile << "============ Character Move ============" << endl;
        logFile << "Character " << character.getName() << " moved " << direction << "." << "\n";
        logFile << "\n";
        logFile.close();
    }
}

void HumanPlayerStrategy::attack(Character& character) {
    std::cout << "\nSelect target to attack (input target ID): ";
    int targetId;
    std::cin >> targetId;
    std::cout << "Attacking target ID " << targetId << std::endl;
    ofstream logFile("./game_log.txt", ios::app);
    if (logFile.is_open()) {
        logFile << "============ Character Attack ============" << endl;
        logFile << "Character " << character.getName() << " attack " << targetId << "." << "\n";
        logFile << "\n";
        logFile.close();
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
            logFile << "============ Character Rest ============" << endl;
            logFile << "Character " << character.getName() << " rest." << "\n";
            logFile << "\n";
            logFile.close();
        }
        break;
    case 2:
        std::cout << "Looking around the area..." << std::endl;
        // Implement the logic to describe the area or reveal certain elements
        if (logFile.is_open()) {
            logFile << "============ Character Look ============" << endl;
            logFile << "Character " << character.getName() << " look." << "\n";
            logFile << "\n";
            logFile.close();
        }
        break;
    case 3:
        std::cout << "Speaking to nearby characters..." << std::endl;
        // Implement interaction with NPCs or other characters
        if (logFile.is_open()) {
            logFile << "============ Character Speak ============" << endl;
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
