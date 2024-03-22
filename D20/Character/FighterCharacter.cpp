#include "FighterCharacter.h"

#include <iostream>

FighterCharacter::FighterCharacter() : Character()
{
}

/**
 * @brief Constructs a new Character with a specified level and character type.
 * @param level The starting level of the character.
 * @param fighterType The class type of the character.* / "
 * @return character object
 */
FighterCharacter::FighterCharacter(int level, FighterType fighterType) : Character(level, fighterType) {
    generateAbilityScores();
    calculateAbilityModifiers();
    calculateHitPoints();
    calculateArmorClass();
    calculateAttackBonus();
    calculateDamageBonus();
}

FighterCharacter::FighterCharacter(int level, FighterType fighterType, CharacterStrategy* strategy) : Character(level, fighterType, strategy) {
    generateAbilityScores();
    calculateAbilityModifiers();
    calculateHitPoints();
    calculateArmorClass();
    calculateAttackBonus();
    calculateDamageBonus();
}

//void FighterCharacter::display() {
//    std::cout << "Basic Character\n";
//}

void FighterCharacter::applyEnhancement(CharacterStat stat, int bonus) {
    // Apply enhancement to character's statistics or other attributes

}

