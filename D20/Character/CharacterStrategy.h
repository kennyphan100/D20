#ifndef CHARACTERSTRATEGY_H
#define CHARACTERSTRATEGY_H

class Character;
class Map;

enum class StrategyType {
    Player,
    Friendly,
    Aggressor
};

class CharacterStrategy {
public:
    virtual ~CharacterStrategy() {}
    virtual void move(Character& character, Map& map) = 0;
    virtual void moveGUI(Character& character, Map& map, int targetX, int targetY) = 0;
    virtual void attack(Character& character, Map& map) = 0;
    virtual void freeAction(Character& character, Map& map) = 0;
    virtual StrategyType getStrategyType() const = 0;
};

#endif // CHARACTERSTRATEGY_H
