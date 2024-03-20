#pragma once
#ifndef CHARACTER_ACTION_STRATEGY_H
#define CHARACTER_ACTION_STRATEGY_H

class Character;

// Strategy interface
class CharacterActionStrategy {
public:
    virtual void performMove(Character& character) = 0;
    virtual void performAttack(Character& character) = 0;
    virtual void performFreeActions(Character& character) = 0;
};

#endif // CHARACTER_ACTION_STRATEGY_H
