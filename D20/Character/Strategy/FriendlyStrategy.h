#pragma once
#ifndef FRIENDLY_STRATEGY_H
#define FRIENDLY_STRATEGY_H

#include "CharacterActionStrategy.h"

class FriendlyStrategy : public CharacterActionStrategy {
public:
    void performMove(Character& character) override;
    void performAttack(Character& character) override;
    void performFreeActions(Character& character) override;
};

#endif // FRIENDLY_STRATEGY_H
