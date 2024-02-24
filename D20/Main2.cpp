#include <iostream>
#include "Item.h"

int main() {
   
    Armor armor("Plate Armor");
    Shield shield("Wooden Shield");
    Weapon weapon("Long Sword");
    Boots boots("Leather Boots");
    Ring ring("Diamond Ring");
    Helmet helmet("Steel Helmet");

    std::cout << "Armor: " << armor.name << std::endl;
    auto armorEnhancement = armor.getEnhancement();
    std::cout << "Enhancement: " << enhancementToString(armorEnhancement.first) << ", Enhancement Number: " << armorEnhancement.second << std::endl << std::endl;

    std::cout << "Shield: " << shield.name << std::endl;
    auto shieldEnhancement = shield.getEnhancement();
    std::cout << "Enhancement: " << enhancementToString(shieldEnhancement.first) << ", Enhancement Number: " << shieldEnhancement.second << std::endl << std::endl;

    std::cout << "Weapon: " << weapon.name << std::endl;
    auto weaponEnhancement = weapon.getEnhancement();
    std::cout << "Enhancement: " << enhancementToString(weaponEnhancement.first) << ", Enhancement Number: " << weaponEnhancement.second << std::endl << std::endl;

    std::cout << "Ring: " << ring.name << std::endl;
    auto ringEnhancement = ring.getEnhancement();
    std::cout << "Enhancement: " << enhancementToString(ringEnhancement.first) << ", Enhancement Number: " << ringEnhancement.second << std::endl << std::endl;

    
    return 0;
}

