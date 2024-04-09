#ifndef FRIENDLYSTRATEGY_H
#define FRIENDLYSTRATEGY_H

#include "CharacterStrategy.h"
#include "../Map/Map.h"

class FriendlyStrategy : public CharacterStrategy {
public:
    FriendlyStrategy();
    void move(Character& character, Map& map) override;
    virtual void moveGUI(Character& character, Map& map, int targetX, int targetY) override;
    void attack(Character& character, Map& map) override;
    void freeAction(Character& character, Map& map) override;
    void switchToAggressor(Character& character);
    StrategyType getStrategyType() const override;
};

#endif // FRIENDLYSTRATEGY_H
