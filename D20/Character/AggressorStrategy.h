#ifndef AGGRESSORSTRATEGY_H
#define AGGRESSORSTRATEGY_H

#include "CharacterStrategy.h"

class AggressorStrategy : public CharacterStrategy {
public:
    void move(Character& character) override;
    void attack(Character& character) override;
    void freeAction(Character& character) override;
};

#endif // AGGRESSORSTRATEGY_H
