#ifndef HUMANPLAYERSTRATEGY_H
#define HUMANPLAYERSTRATEGY_H

#include "CharacterStrategy.h"
#include "../Map/Map.h"

class HumanPlayerStrategy : public CharacterStrategy {
public:

    void move(Character& character, Map& map) override;
    void moveGUI(Character& character, Map& map, int targetX, int targetY) override;
    void attack(Character& character, Map& map) override;
    void freeAction(Character& character, Map& map) override;
    StrategyType getStrategyType() const override;
};

#endif // HUMANPLAYERSTRATEGY_H
