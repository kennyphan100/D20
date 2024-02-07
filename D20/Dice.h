#pragma once
#ifndef DICE_H
#define DICE_H

#include <string>
#include <random>

class Dice {
public:
    Dice();
    int rollDice(const std::string& input);

private:
    int rollSingleDice(int sides);
    std::mt19937 rng;
};

#endif