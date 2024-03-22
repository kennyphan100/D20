#pragma once
#ifndef ITEM2_H
#define ITEM2_H

#include "../Character/Character.h"

class CharacterDecorator : public Character {
//protected:
//    
public:
    Character* character;
    CharacterDecorator(Character* character);
    virtual ~CharacterDecorator();
    //void display() override;
    void applyEnhancement(CharacterStat stat, int bonus) override;
    virtual std::string getDescription() const = 0;
};

class Item2 : public CharacterDecorator {
protected:
    string name;
    int enhancementBonus;
    CharacterStat enhancementType;
public:
    Item2(Character* character, string name, CharacterStat type, int bonus);
    std::string getDescription() const override;
    string getName() const;
    int getEnhancementBonus() const;
    CharacterStat getEnhancementType() const;
};

class Helmet2 : public Item2 {
public:
    Helmet2(Character* character, string name, CharacterStat type, int bonus);
    std::string getDescription() const override;
};

class Armor2 : public Item2 {
public:
    Armor2(Character* character, string name, CharacterStat type, int bonus);
    std::string getDescription() const override;
};

class Shield2 : public Item2 {
public:
    Shield2(Character* character, string name, CharacterStat type, int bonus);
    std::string getDescription() const override;
};

class Ring2 : public Item2 {
public:
    Ring2(Character* character, string name, CharacterStat type, int bonus);
    std::string getDescription() const override;
};

class Belt2 : public Item2 {
public:
    Belt2(Character* character, string name, CharacterStat type, int bonus);
    std::string getDescription() const override;
};

class Boots2 : public Item2 {
public:
    Boots2(Character* character, string name, CharacterStat type, int bonus);
    std::string getDescription() const override;
};

class Weapon2 : public Item2 {
public:
    Weapon2(Character* character, string name, CharacterStat type, int bonus);
    std::string getDescription() const override;
};

#endif // ITEM2_H
