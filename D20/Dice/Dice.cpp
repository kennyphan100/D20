//! @file 
//! @brief Implementation file for Dice.h
//!

#include "Dice.h"
#include <regex>
#include <random>
#include <ctime>
#include <iostream>
#include <set>
#include <fstream>
#include <ctime>

using namespace std;

//! Constructor for Dice class.
//! @return new Dice object
Dice::Dice() {
    rng.seed(time(nullptr));
}

//! Rolls a single dice with the specified number of sides.
//! @param sides The number of sides of the dice.
//! @return The result of the dice roll.
int Dice::rollSingleDice(int sides) {
    uniform_int_distribution<int> dist(1, sides);
    return dist(rng);
}

//! Rolls a set of dice based on the input string.
//! The input string should be in the format "xdy+z", where x is the number of dice,
//! y is the type of dice (number of sides), and z (optional) is an additional modifier.
//! @param input The input string specifying the dice roll.
//! @return The total result of the dice roll.
int Dice::rollDice(const string& input) {
    regex dicePattern(R"((\d+)d(\d+)(\+\d+)?)");
    smatch matches;

    const set<int> validDiceSides = { 4, 6, 8, 10, 12, 20, 100 }; // Set of valid dice types

    if (regex_match(input, matches, dicePattern)) {
        int x = stoi(matches[1].str()); // Number of dice
        int y = stoi(matches[2].str()); // Type of dice
        int z = (matches[3].matched) ? stoi(matches[3].str().substr(1)) : 0; // Optional addition, default to 0

        // Validate the dice type
        if (validDiceSides.find(y) == validDiceSides.end()) {
            //std::cerr << "Invalid dice type. Valid types are d4, d6, d8, d10, d12, d20, d100." << std::endl;
            return -2;
        }

        int result = 0;
        for (int i = 0; i < x; ++i) {
            result += rollSingleDice(y);
        }

        result += z;
        ofstream logFile("./game_log.txt", ios::app);
        if (logFile.is_open()) {
            time_t t = time(nullptr);
            tm tm;
            localtime_s(&tm, &t);
            char buffer[80];
            strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);
            string timestamp(buffer);
            logFile << "============ Dice Roll ============" << endl;
            logFile << "Timestamp: " << timestamp << endl;
            logFile << "Roll dice of type " << input << ": " << result << "\n";
            logFile << "\n";
            logFile.close();
        }

        return result;
    }
    else {
        //std::cerr << "Invalid input format. Please use the xdy[+z] format." << std::endl;
        return -1;
    }
}