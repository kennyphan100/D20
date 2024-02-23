#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include "Dice.h"
#include "Item.h"
#include <memory>
#include <array>
#include <random>

class Character {
protected:
    int level;
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

public:
    Character(int level);

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

    int getAbilityScore(int index) const;
    int getAbilityModifier(int index) const;
    int getHitPoints() const;
    int getArmorClass() const;
    int getAttackBonus() const;
    int getDamageBonus() const;

    void printCharacter() const;
};

#endif