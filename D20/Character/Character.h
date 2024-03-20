//! @file 
//! @brief Header file for Character.cpp
//!

#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include "../Dice/Dice.h"
#include "../Item/Item.h"
#include <memory>
#include <array>
#include <random>
#include "../Observable.h"
#include "Strategy/CharacterActionStrategy.h"

using namespace std;

enum class CharacterType { FIGHTER, SORCERER, MONK, PALADIN, BARD, BARBARIAN };

enum class FighterType { BULLY, NIMBLE, TANK };

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
public:
    int level;
    FighterType fighterType;
    array<int, 6> abilityScores; // STR, DEX, CON, INT, WIS, CHA
    array<int, 6> abilityModifiers;
    int hitPoints;
    int armorClass;
    int attackBonus;
    int damageBonus;
    int nbOfAttacksPerRound;
    Dice dice;

    void setStrategy(CharacterActionStrategy* strategy);
    void performActions();
    void performMove();
    void performAttack();
    void performFreeActions();

    Armor* armor;
    Shield* shield;
    Weapon* weapon;
    Boots* boots;
    Ring* ring;
    Helmet* helmet;

    Backpack* backpack;

    Character(int level, FighterType fighterType);
    Character(int level, FighterType fighterType, CharacterActionStrategy* strategy);

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

    Armor* getArmor() const;
    Shield* getShield() const;
    Weapon* getWeapon() const;
    Boots* getBoots() const;
    Ring* getRing() const;
    Helmet* getHelmet() const;

    int getLevel() const;
    //CharacterType getCharacterType() const;
    FighterType getFighterType() const;
    int getAbilityScore(int index) const;
    int getAbilityModifier(int index) const;
    int getHitPoints() const;
    int getArmorClass() const;
    int getAttackBonus() const;
    int getDamageBonus() const;

    void levelUp();
    void printCharacter() const;
private:
    CharacterActionStrategy* actionStrategy;

};

string fighterTypeToString(FighterType fighterType);

#endif