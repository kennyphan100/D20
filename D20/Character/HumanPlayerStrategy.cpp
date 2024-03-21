#include "HumanPlayerStrategy.h"
#include "Character.h"
#include <iostream>
#include <string>

void HumanPlayerStrategy::move(Character& character) {
    std::cout << "Enter move direction (N, S, E, W): ";
    std::string direction;
    std::cin >> direction;
    std::cout << "Moving " << direction << std::endl;
}

void HumanPlayerStrategy::attack(Character& character) {
    std::cout << "Select target to attack (input target ID): ";
    int targetId;
    std::cin >> targetId;
    std::cout << "Attacking target ID " << targetId << std::endl;
}

void HumanPlayerStrategy::freeAction(Character& character) {
    std::cout << "Choose a free action: \n1. Rest (recover health)\n2. Look around\n3. Speak\nEnter choice: ";
    int choice;
    std::cin >> choice;
    switch (choice) {
    case 1:
        std::cout << "Resting... health recovered." << std::endl;
        // Implement health recovery
        break;
    case 2:
        std::cout << "Looking around the area..." << std::endl;
        // Implement the logic to describe the area or reveal certain elements
        break;
    case 3:
        std::cout << "Speaking to nearby characters..." << std::endl;
        // Implement interaction with NPCs or other characters
        break;
    default:
        std::cout << "Invalid choice." << std::endl;
        break;
    }
}
