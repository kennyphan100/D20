//! @file 
//! @brief Implementation file for Character.h
//!

#include "Character.h"
#include <iostream>
#include <cmath>

using namespace std;

/**
 * @brief Constructs a new Character with a specified level and character type.
 * @param level The starting level of the character.
 * @param fighterType The class type of the character.* / "
 * @return character object
 */
Character::Character(int level, FighterType fighterType) : level(level), fighterType(fighterType), armor(nullptr) {
    generateAbilityScores();
    calculateAbilityModifiers();
    calculateHitPoints();
    calculateArmorClass();
    calculateAttackBonus();
    calculateDamageBonus();
}

//! Generates ability scores for the character by rolling 3d6 for each score.
void Character::generateAbilityScores() {
    for (int& score : abilityScores) {
        score = dice.rollDice("3d6");
    }
}

//! Calculates ability modifiers based on the ability scores.
void Character::calculateAbilityModifiers() {
    for (int i = 0; i < 6; ++i) {
        abilityModifiers[i] = (abilityScores[i] - 10) / 2;
    }
}

//! Calculates hit points for the character based on level and constitution modifier.
void Character::calculateHitPoints() {
    int conMod = getAbilityModifier(2);
    hitPoints = 10 + conMod + (level - 1) * (5 + conMod);
}

//! Calculates armor class for the character based on dexterity modifier.
void Character::calculateArmorClass() {
    int dexMod = getAbilityModifier(1);
    armorClass = 10 + dexMod;
    //if (armor) armorClass += armor->armorBonus;
}

//! Calculates attack bonus for the character based on level and strength modifier.
void Character::calculateAttackBonus() {
    int strMod = getAbilityModifier(0);
    attackBonus = level + strMod;
}

//! Calculates damage bonus for the character based on strength modifier.
void Character::calculateDamageBonus() {
    int strMod = getAbilityModifier(0);
    damageBonus = strMod;
}

//! Equips armor to the character.
//! @param a Pointer to the armor object to be equipped.
void Character::equipArmor(Armor* a) {
    armor = a;
    calculateArmorClass();
    notify();
}

//! Equips a shield to the character.
//! @param s Pointer to the shield object to be equipped.
void Character::equipShield(Shield* s) {
    shield = s;
    notify();
}

//! Equips a weapon to the character.
//! @param w Pointer to the weapon object to be equipped.
void Character::equipWeapon(Weapon* w) {
    weapon = w;
    calculateAttackBonus();
    calculateDamageBonus();
    notify();
}

//! Equips boots to the character.
//! @param b Pointer to the boots object to be equipped.
void Character::equipBoots(Boots* b) {
    boots = b;
    notify();
}

//! Equips a ring to the character.
//! @param r Pointer to the ring object to be equipped.
void Character::equipRing(Ring* r) {
    ring = r;
    notify();
}

//! Equips a helmet to the character.
//! @param h Pointer to the helmet object to be equipped.
void Character::equipHelmet(Helmet* h) {
    helmet = h;
    notify();
}

Armor* Character::getArmor() const
{
    if (armor != nullptr) {
        return armor; 
    }
    else {
        return NULL;
    }
}

Shield* Character::getShield() const
{
    if (shield != nullptr) {
        return shield;
    }
    else {
        return NULL;
    }
}

Weapon* Character::getWeapon() const
{
    if (weapon != nullptr) {
        return weapon;
    }
    else {
        return NULL;
    }
}

Boots* Character::getBoots() const
{
    if (boots != nullptr) {
        return boots;
    }
    else {
        return NULL;
    }
}

Ring* Character::getRing() const
{
    if (ring != nullptr) {
        return ring;
    }
    else {
        return NULL;
    }
}

Helmet* Character::getHelmet() const
{
    if (helmet != nullptr) {
        return helmet;
    }
    else {
        return NULL;
    }
}

//! Retrieves the level of the character.
//! @return The level of the character.
int Character::getLevel() const {
    return level;
}

//! Retrieves the character type of the character.
//! @return The character type of the character.
FighterType Character::getFighterType() const {
    return fighterType;
}

//! Retrieves the ability score at the specified index.
//! @param index The index of the ability score to retrieve.
//! @return The ability score at the specified index.
int Character::getAbilityScore(int index) const {
    return abilityScores[index];
}

//! Retrieves the ability modifier at the specified index.
//! @param index The index of the ability modifier to retrieve.
//! @return The ability modifier at the specified index.
int Character::getAbilityModifier(int index) const {
    return abilityModifiers[index];
}

//! Retrieves the hit points of the character.
//! @return The hit points of the character.
int Character::getHitPoints() const {
    return hitPoints;
}

//! Retrieves the armor class of the character.
//! @return The armor class of the character.
int Character::getArmorClass() const {
    return armorClass;
}

//! Retrieves the attack bonus of the character.
//! @return The attack bonus of the character.
int Character::getAttackBonus() const {
    return attackBonus;
}

//! Retrieves the damage bonus of the character.
//! @return The damage bonus of the character.
int Character::getDamageBonus() const {
    return damageBonus;
}

void Character::levelUp()
{
    this->level += 1;

    int diceValue = dice.rollDice("1d10");
    this->hitPoints += diceValue;

    int constitutionModifier = abilityScores[2];
    this->hitPoints += constitutionModifier;

    this->attackBonus += 1;

    int numberOfAttacksPerRound = floor(getLevel() / 5);

    this->nbOfAttacksPerRound = numberOfAttacksPerRound;
}

//! Prints information about the character.
void Character::printCharacter() const {
    cout << "Class: " << fighterTypeToString(getFighterType()) << "\n"
        << "Level: " << level << "\n"
        << "HP: " << hitPoints << ", AC: " << armorClass << ", Attack Bonus: " << attackBonus << ", Damage Bonus: " << damageBonus << "\n"
        << "STR: " << abilityScores[0] << " (" << abilityModifiers[0] << "), "
        << "DEX: " << abilityScores[1] << " (" << abilityModifiers[1] << "), "
        << "CON: " << abilityScores[2] << " (" << abilityModifiers[2] << "), "
        << "INT: " << abilityScores[3] << " (" << abilityModifiers[3] << "), "
        << "WIS: " << abilityScores[4] << " (" << abilityModifiers[4] << "), "
        << "CHA: " << abilityScores[5] << " (" << abilityModifiers[5] << ")\n";

    cout << "Equipped Armor: " << (getArmor() ? getArmor()->name : "---") << endl;
    cout << "Equipped Shield: " << (getShield() ? getShield()->name : "---") << endl;
    cout << "Equipped Weapon: " << (getWeapon() ? getWeapon()->name : "---") << endl;
    cout << "Equipped Boots: " << (getBoots() ? getBoots()->name : "---") << endl;
    cout << "Equipped Ring: " << (getRing() ? getRing()->name : "---") << endl;
    cout << "Equipped Helmet: " << (getHelmet() ? getHelmet()->name : "---") << endl;

}

//! Converts a character type enum value to its string representation.
//! @param characterType The character type enum value.
//! @return The string representation of the character type.
string characterTypeToString(CharacterType characterType) {
    switch (characterType) {
    case CharacterType::FIGHTER: return "FIGHTER";
    case CharacterType::SORCERER: return "SORCERER";
    case CharacterType::MONK: return "MONK";
    case CharacterType::PALADIN: return"PALADIN";
    case CharacterType::BARD: return "BARD";
    case CharacterType::BARBARIAN: return "BARBARIAN";
    default: return "Unknown CharacterType";
    }
}

//! Converts a fighter type enum value to its string representation.
//! @param fighterType The character type enum value.
//! @return The string representation of the fighter type.
string fighterTypeToString(FighterType fighterType) {
    switch (fighterType) {
    case FighterType::BULLY: return "BULLY";
    case FighterType::NIMBLE: return "NIMBLE";
    case FighterType::TANK: return "TANK";
    default: return "Unknown FighterType";
    }
}