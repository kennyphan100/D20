#include "FriendlyStrategy.h"
#include "Character.h"
#include "AggressorStrategy.h"
#include <iostream>

// Assuming Character has methods to get/set its position and to check for attacks

void FriendlyStrategy::move(Character& character) {
    std::cout << "Friendly character is moving towards the player..." << std::endl;
}

void FriendlyStrategy::attack(Character& character) {
    std::cout << "Friendly character does not want to fight." << std::endl;
}

void FriendlyStrategy::freeAction(Character& character) {
    int action = std::rand() % 3;

    switch (action) {
    case 0:
        std::cout << "Friendly character heals an ally." << std::endl;
        break;
    case 1:
        std::cout << "Friendly character gives advice." << std::endl;
        break;
    case 2:
        std::cout << "Friendly character scouts the area." << std::endl;
        break;
    default:
        std::cerr << "Unexpected action index." << std::endl;
    }
}

void FriendlyStrategy::switchToAggressor(Character& character) {
    std::cout << "Friendly character is now hostile." << std::endl;
    character.setStrategy(new AggressorStrategy());
}
