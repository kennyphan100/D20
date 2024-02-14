#include "Character.h"
#include <iostream>
#include <cmath>

Character::Character(int level) : level(level), armor(nullptr) {
    generateAbilityScores();
    calculateModifiers();
    calculateHitPoints();
    calculateArmorClass();
    calculateAttackBonus();
    calculateDamageBonus();
}

void Character::generateAbilityScores() {
    for (int& score : abilityScores) {
        score = dice.rollDice("3d6");
    }
}

void Character::calculateModifiers() {
    for (int i = 0; i < 6; ++i) {
        abilityModifiers[i] = (abilityScores[i] - 10) / 2;
    }
}

void Character::calculateHitPoints() {
    int conMod = getAbilityModifier(2);
    hitPoints = 10 + conMod + (level - 1) * (5 + conMod);
}

void Character::calculateArmorClass() {
    int dexMod = getAbilityModifier(1);
    armorClass = 10 + dexMod;
    if (armor) armorClass += armor->armorBonus;
}

void Character::calculateAttackBonus() {
    int strMod = getAbilityModifier(0);
    attackBonus = level + strMod;
}

void Character::calculateDamageBonus() {
    int strMod = getAbilityModifier(0);
    damageBonus = strMod;
}

void Character::equipArmor(Armor* a) {
    armor = armor;
    calculateArmorClass();
}

void Character::equipShield(Shield* s) {
    shield = s;
}

void Character::equipWeapon(Weapon* w) {
    weapon = w;
    calculateAttackBonus();
    calculateDamageBonus();
}

void Character::equipBoots(Boots* b) {
    boots = b;
}

void Character::equipRing(Ring* r) {
    ring = r;
}

void Character::equipHelmet(Helmet* h) {
    helmet = h;
}

int Character::getAbilityScore(int index) const {
    return abilityScores[index];
}

int Character::getAbilityModifier(int index) const {
    return abilityModifiers[index];
}

int Character::getHitPoints() const {
    return hitPoints;
}

int Character::getArmorClass() const {
    return armorClass;
}

int Character::getAttackBonus() const {
    return attackBonus;
}

int Character::getDamageBonus() const {
    return damageBonus;
}

void Character::printCharacter() const {
    std::cout << "Level: " << level << "\n"
        << "HP: " << hitPoints << ", AC: " << armorClass << ", Attack Bonus: " << attackBonus << ", Damage Bonus: " << damageBonus << "\n"
        << "STR: " << abilityScores[0] << " (" << abilityModifiers[0] << "), "
        << "DEX: " << abilityScores[1] << " (" << abilityModifiers[1] << "), "
        << "CON: " << abilityScores[2] << " (" << abilityModifiers[2] << "), "
        << "INT: " << abilityScores[3] << " (" << abilityModifiers[3] << "), "
        << "WIS: " << abilityScores[4] << " (" << abilityModifiers[4] << "), "
        << "CHA: " << abilityScores[5] << " (" << abilityModifiers[5] << ")\n";
}