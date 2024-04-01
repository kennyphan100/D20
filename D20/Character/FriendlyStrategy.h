#ifndef FRIENDLYSTRATEGY_H
#define FRIENDLYSTRATEGY_H

#include "CharacterStrategy.h"
#include "../Map/Map.h"

class FriendlyStrategy : public CharacterStrategy {
public:
    FriendlyStrategy();
    void move(Character& character, Map& map) override;
    void attack(Character& character, Map& map) override;
    void freeAction(Character& character) override;
    void switchToAggressor(Character& character);
    StrategyType getStrategyType() const override;
};

#endif // FRIENDLYSTRATEGY_H
