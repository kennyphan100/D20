#pragma once
#ifndef FIGHTER_CHARACTER_H
#define FIGHTER_CHARACTER_H

#include "character.h"

class FighterCharacter : public Character {
public:
    FighterCharacter();
    FighterCharacter(int level, FighterType fighterType);
    //void display() override;
    void applyEnhancement(CharacterStat stat, int bonus) override;
};

#endif // FIGHTER_CHARACTER_H
