#pragma once
#ifndef HUMAN_PLAYER_STRATEGY_H
#define HUMAN_PLAYER_STRATEGY_H

#include "CharacterActionStrategy.h"

class HumanPlayerStrategy : public CharacterActionStrategy {
public:
    void performMove(Character& character) override;
    void performAttack(Character& character) override;
    void performFreeActions(Character& character) override;
};

#endif // HUMAN_PLAYER_STRATEGY_H
