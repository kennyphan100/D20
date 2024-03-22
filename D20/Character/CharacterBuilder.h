#pragma once
#pragma once
#ifndef CHARACTER_BUILDER_H
#define CHARACTER_BUILDER_H

#include "Character.h"
#include "FighterCharacter.h"

using namespace std;

class CharacterBuilder : public Observable {
protected:
    Character* character;
    Dice dice;

public:
    CharacterBuilder();
    virtual ~CharacterBuilder();
    virtual void buildAbilityScores() = 0;
    virtual void assignFighterType() = 0;
    virtual void assignLevel(int level) = 0;
    void assignName(string name);
    bool saveToFile(const string& filename);
    virtual Character* getCharacter();
    int roll4d6DropLowest();
    vector<int> generateAbilityScores();
    virtual void logCharacter(ostream& out) = 0;
};

class BullyFighterBuilder : public CharacterBuilder {
public:
    void buildAbilityScores() override;
    void assignFighterType() override;
    void assignLevel(int level) override;
    void logCharacter(ostream& out) override;
};

class NimbleFighterBuilder : public CharacterBuilder {
public:
    void buildAbilityScores() override;
    void assignFighterType() override;
    void assignLevel(int level) override;
    void logCharacter(ostream& out) override;
};

class TankFighterBuilder : public CharacterBuilder {
public:
    void buildAbilityScores() override;
    void assignFighterType() override;
    void assignLevel(int level) override;
    void logCharacter(ostream& out) override;
};

#endif
