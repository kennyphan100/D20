//! @file 
//! @brief Header file for Character.cpp
//!

#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include "Dice.h"
#include "Item.h"
#include <memory>
#include <array>
#include <random>
#include "Observable.h"

using namespace std;

enum class CharacterType { FIGHTER, SORCERER, MONK, PALADIN, BARD, BARBARIAN };

/**
 * @class Character
 * @brief Class for generating player characters in a d20 system.
 *
 * Game rules: d20 system focusing on fighter characters.
 * - Ability scores are generated randomly.
 * - Hit points are based on constitution modifier and character level.
 * - Armor class is influenced by the dexterity modifier.
 * - Attack bonus is derived from level and strength/dexterity modifiers.
 * - Damage bonus is based on the strength modifier.
 *
 * Design:
 * This implementation is designed to create characters specifically for the fighter class,
 * following d20 game rules. The character's abilities and combat statistics are generated based on their level
 * and class, incorporating randomness for ability scores and derived attributes such as hit points, armor class,
 * attack bonus, and damage bonus. The design allows for a character to be equipped with specific items,
 * including armor, shields, weapons, boots, rings, and helmets, to influence their combat statistics.
 *
 * Libraries:
 * <array> is chosen for its performance benefits over dynamic containers for fixed-size data.
 * <random> provides a robust solution for randomness, essential for role-playing game mechanics.
 */ 
class Character : public Observable {
protected:
    int level;
    CharacterType characterType;
    std::array<int, 6> abilityScores; // STR, DEX, CON, INT, WIS, CHA
    std::array<int, 6> abilityModifiers;
    int hitPoints;
    int armorClass;
    int attackBonus;
    int damageBonus;
    Dice dice;

    Armor* armor;
    Shield* shield;
    Weapon* weapon;
    Boots* boots;
    Ring* ring;
    Helmet* helmet;

    Backpack* backpack;

public:
    Character(int level, CharacterType characterType);

    void generateAbilityScores();
    void calculateAbilityModifiers();
    void calculateHitPoints();
    void calculateArmorClass();
    void calculateAttackBonus();
    void calculateDamageBonus();

    void equipArmor(Armor* a);
    void equipShield(Shield* s);
    void equipWeapon(Weapon* w);
    void equipBoots(Boots* b);
    void equipRing(Ring* r);
    void equipHelmet(Helmet* h);

    int getLevel() const;
    CharacterType getCharacterType() const;
    int getAbilityScore(int index) const;
    int getAbilityModifier(int index) const;
    int getHitPoints() const;
    int getArmorClass() const;
    int getAttackBonus() const;
    int getDamageBonus() const;

    void printCharacter() const;

};

string characterTypeToString(CharacterType characterType);

#endif