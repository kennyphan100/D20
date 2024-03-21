#ifndef FRIENDLYSTRATEGY_H
#define FRIENDLYSTRATEGY_H

#include "CharacterStrategy.h"

class FriendlyStrategy : public CharacterStrategy {
public:
    FriendlyStrategy();
    void move(Character& character) override;
    void attack(Character& character) override;
    void freeAction(Character& character) override;
    void switchToAggressor(Character& character);
};

#endif // FRIENDLYSTRATEGY_H
