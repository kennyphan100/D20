#include "Dice.h"
#include <regex>
#include <random>
#include <ctime>
#include <iostream>
#include <set>

Dice::Dice() {
    rng.seed(time(nullptr));
}

int Dice::rollSingleDice(int sides) {
    std::uniform_int_distribution<int> dist(1, sides);
    return dist(rng);
}

int Dice::rollDice(const std::string& input) {
    std::regex dicePattern(R"((\d+)d(\d+)(\+\d+)?)");
    std::smatch matches;

    const std::set<int> validDiceSides = { 4, 6, 8, 10, 12, 20, 100 }; // Set of valid dice types

    if (std::regex_match(input, matches, dicePattern)) {
        int x = std::stoi(matches[1].str()); // Number of dice
        int y = std::stoi(matches[2].str()); // Type of dice
        int z = (matches[3].matched) ? std::stoi(matches[3].str().substr(1)) : 0; // Optional addition, default to 0

        // Validate the dice type
        if (validDiceSides.find(y) == validDiceSides.end()) {
            std::cerr << "Invalid dice type. Valid types are d4, d6, d8, d10, d12, d20, d100." << std::endl;
            return -1;
        }

        int result = 0;
        for (int i = 0; i < x; ++i) {
            result += rollSingleDice(y);
        }

        result += z;
        return result;
    }
    else {
        std::cerr << "Invalid input format. Please use the xdy[+z] format." << std::endl;
        return -1;
    }
}