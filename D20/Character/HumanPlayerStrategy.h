#ifndef HUMANPLAYERSTRATEGY_H
#define HUMANPLAYERSTRATEGY_H

#include "CharacterStrategy.h"

class HumanPlayerStrategy : public CharacterStrategy {
public:
    void move(Character& character) override;
    void attack(Character& character) override;
    void freeAction(Character& character) override;
};

#endif // HUMANPLAYERSTRATEGY_H
