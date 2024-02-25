//! @file 
//! @brief Header file for Dice.cpp
//!

#pragma once
#ifndef DICE_H
#define DICE_H

#include <string>
#include <random>

using namespace std;

/** 
 * @class Dice
 * @brief This class is used for simulating dice rolls.
 * 
 * Game Rules:
 * This class adheres to tabletop gaming conventions using dice types d4, d6, d8, d10, d12, d20, and d100.
 * It allows rolling multiple dice of one kind, optionally adding a constant value to the sum of these rolls.
 * The notation used is xdy+z where:
 * - x is the number of dice
 * - y is the type of dice
 * - z is an optional modifier added to the total result.
 *
 * Design:
 * The class parses input strings conforming to the dice notation, then computes the roll totals using a pseudo-random number generator.
 *
 * Libraries:
 * Utilizes <random> from the C++ Standard Library for generating dice outcomes, chosen for its efficiency and standardization.
 * The class utilizes <string> from the C++ Standard Library for managing and manipulating string data, crucial for parsing dice roll expressions and handling text-based commands.
 */
class Dice {
public:
    /**
     * @brief Constructs a new Dice object.
     *
     * Initializes a random number generator used for rolling dice.
     */
    Dice();

    /**
     * @brief Rolls dice based on the input string.
     *
     * Interprets an input string (e.g., "3d6+5") and returns the result of the dice roll.
     * @param input The dice roll expression to interpret and roll.
     * @return The result of the dice roll.
     */
    int rollDice(const string& input);

private:
    /**
     * @brief Rolls a single dice of the specified number of sides.
     *
     * @param sides The number of sides on the dice.
     * @return The result of the dice roll.
     */
    int rollSingleDice(int sides);

    mt19937 rng; ///< The random number generator used for rolling dice.
};

#endif