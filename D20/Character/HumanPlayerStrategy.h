#ifndef HUMANPLAYERSTRATEGY_H
#define HUMANPLAYERSTRATEGY_H

#include "CharacterStrategy.h"
#include "../Map/Map.h"


class HumanPlayerStrategy : public CharacterStrategy {
public:
    HumanPlayerStrategy();
    void move(Character& character, Map& map) override;
    void moveGUI(Character& character, Map& map, int targetX, int targetY, PlayGame& playGame) override;
    void moveGUI(Character& character, Map& map, PlayGame& playGame) override;
    void attack(Character& character, Map& map) override;
    void attackGUI(Character& character, Map& map, int targetX, int targetY, PlayGame& playGame) override;
    void attackGUI(Character& character, Map& map, PlayGame& playGame) override;
    void freeAction(Character& character, Map& map) override;
    StrategyType getStrategyType() const override;
};

#endif // HUMANPLAYERSTRATEGY_H
