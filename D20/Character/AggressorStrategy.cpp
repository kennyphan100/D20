#include "AggressorStrategy.h"
#include "Character.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

AggressorStrategy::AggressorStrategy() {
    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        seeded = true;
    }
}

void AggressorStrategy::move(Character& character) {
    std::cout << "Aggressor moves towards the player..." << std::endl;
}

void AggressorStrategy::attack(Character& character) {
    // Attack logic...
    std::cout << "Aggressor attacks the player!" << std::endl;
}

void AggressorStrategy::freeAction(Character& character) {
    int action = std::rand() % 3;

    switch (action) {
    case 0:
        std::cout << "Aggressor sharpens its weapons, increasing attack power." << std::endl;
        break;
    case 1:
        std::cout << "Aggressor taunts the player, potentially affecting player's decisions." << std::endl;
        break;
    case 2:
        std::cout << "Aggressor scouts for vulnerabilities, increasing its next attack's accuracy." << std::endl;
        break;
    default:
        std::cerr << "Invalid action selected." << std::endl;
        break;
    }
}
