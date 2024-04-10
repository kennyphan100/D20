#ifndef AGGRESSORSTRATEGY_H
#define AGGRESSORSTRATEGY_H

#include "CharacterStrategy.h"
#include "../Map/Map.h"

class AggressorStrategy : public CharacterStrategy {
public:
    AggressorStrategy();
    virtual void move(Character& character, Map& map) override;
    virtual void moveGUI(Character& character, Map& map, int targetX, int targetY, PlayGame& playGame) override;
    virtual void attack(Character& character, Map& map) override;
    virtual void freeAction(Character& character, Map& map) override;
    StrategyType getStrategyType() const override;
};

#endif // AGGRESSORSTRATEGY_H
