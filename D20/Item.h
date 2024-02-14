#pragma once
#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
public:
    std::string name;
    Item(std::string name) : name(name) {}
    virtual ~Item() = default;
};

class Armor : public Item {
public:
    int armorBonus;
    Armor(std::string name, int armorBonus) : Item(name), armorBonus(armorBonus) {}
};

class Shield : public Item {
public:
    int armorBonus;
    Shield(std::string name, int armorBonus) : Item(name), armorBonus(armorBonus) {}
};

class Weapon : public Item {
public:
    int attackBonus;
    Weapon(std::string name, int attackBonus) : Item(name), attackBonus(attackBonus) {}
};

class Boots : public Item {
public:
    int dexBonus;
    Boots(std::string name, int dexBonus) : Item(name), dexBonus(dexBonus) {}
};

class Ring : public Item {
public:
    int bonus;
    Ring(std::string name, int bonus) : Item(name), bonus(bonus) {}
};

class Helmet : public Item {
public:
    int bonus;
    Helmet(std::string name, int bonus) : Item(name), bonus(bonus) {}
};

#endif