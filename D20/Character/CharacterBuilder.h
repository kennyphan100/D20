#pragma once
#pragma once
#ifndef CHARACTER_BUILDER_H
#define CHARACTER_BUILDER_H

#include "Character.h"

class CharacterBuilder {
protected:
    Character* character;
    Dice dice;

public:
    CharacterBuilder();
    virtual ~CharacterBuilder();
    virtual void buildAbilityScores() = 0;
    virtual void assignFighterType() = 0;
    virtual void assignLevel(int level) = 0;
    virtual Character* getCharacter();
    int roll4d6DropLowest();
    vector<int> generateAbilityScores();
};

class BullyFighterBuilder : public CharacterBuilder {
public:
    void buildAbilityScores() override;
    void assignFighterType() override;
    void assignLevel(int level) override;
};

class NimbleFighterBuilder : public CharacterBuilder {
public:
    void buildAbilityScores() override;
    void assignFighterType() override;
    void assignLevel(int level) override;
};

class TankFighterBuilder : public CharacterBuilder {
public:
    void buildAbilityScores() override;
    void assignFighterType() override;
    void assignLevel(int level) override;
};

#endif
