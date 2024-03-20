#pragma once
#ifndef AGGRESSOR_STRATEGY_H
#define AGGRESSOR_STRATEGY_H

#include "CharacterActionStrategy.h"

class AggressorStrategy : public CharacterActionStrategy {
public:
    void performMove(Character& character) override;
    void performAttack(Character& character) override;
    void performFreeActions(Character& character) override;
};

#endif // AGGRESSOR_STRATEGY_H
