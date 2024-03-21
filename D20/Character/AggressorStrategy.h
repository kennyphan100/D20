#ifndef AGGRESSORSTRATEGY_H
#define AGGRESSORSTRATEGY_H

#include "CharacterStrategy.h"

class AggressorStrategy : public CharacterStrategy {
public:
    AggressorStrategy();
    virtual void move(Character& character) override;
    virtual void attack(Character& character) override;
    virtual void freeAction(Character& character) override;
};

#endif // AGGRESSORSTRATEGY_H
