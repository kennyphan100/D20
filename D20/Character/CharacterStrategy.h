#ifndef CHARACTERSTRATEGY_H
#define CHARACTERSTRATEGY_H

class Character;

class CharacterStrategy {
public:
    virtual ~CharacterStrategy() {}
    virtual void move(Character& character) = 0;
    virtual void attack(Character& character) = 0;
    virtual void freeAction(Character& character) = 0;
};

#endif // CHARACTERSTRATEGY_H
