//! @file 
//! @brief Main driver file to create and execute the different parts (Character, Map, Item, and Dice) and the test suite.
//!

#include "Dice.h"
#include <iostream>
#include "Character.h"
#include "Item.h"
#include "Map.h"
#include <cppunit/TestRunner.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include "CharacterObserver.h"
#include "MapObserver.h"
#include "Editor.h"

using namespace std;

//!  A free helper function for converting a string to lowercase.
//! @param str : text string
//! @return text string converted to lowercase
string toLowercase(const string& str) {
    string result = str;
    for (char& c : result) {
        c = tolower(c);
    }
    return result;
}

//! main() function. Entry point of the program
//! It does the following: 
//! 1. Create a character given the user's input for the desired level and class type
//! 2. Create a map given the user's input for the size and allow the placement of walls and other objects
//! 3. Create an item and an item container that can hold multiple items
//! 4. Roll a dice using the form xdy[+z]
//! 5. Run the test cases. 
//! 9. Exit the program.
int main() {
    Character* myCharacter;

    while (true) {
        cout << "============== D20 Game - Menu ==============" << endl;
        cout << "1. Character" << endl;
        cout << "2. Map" << endl;
        cout << "3. Item" << endl;
        cout << "4. Dice" << endl;
        cout << "5. Run Unit Tests" << endl;
        cout << "9. Exit \n" << endl;
        cout << "Please enter one of the number part: ";

        string part;
        cin >> part;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n";

        if (part == "9")
        {
            cout << "Terminating program. Bye bye!" << endl;
            exit(0);
        }

        if (part._Equal("1"))
        {
            string characterType;
            cout << "Enter the class of your desired character (e.g., Fighter): ";
            cin >> characterType;
            characterType = toLowercase(characterType);

            while (!characterType._Equal("fighter")) {
                cout << "This class does not exist yet. Try another class: ";
                cin >> characterType;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n";

            int level;
            while (true) {
                cout << "Enter the level of your desired character (e.g., 10): ";
                string input;
                getline(cin, input);
                stringstream ss(input);

                if (ss >> level && ss.eof()) {
                    if (level > 0) {
                        break;
                    }
                    else {
                        cout << "You must enter a value greater than 0.\n" << endl;
                    }
                }
                else {
                    cerr << "Input format must be a positive integer value.\n" << endl;
                }
                
            }
            cout << "\n";

            myCharacter = new Character(level, CharacterType::FIGHTER);

            cout << " ===== Successfully created a character with the following stats: ===== " << endl;
            myCharacter->printCharacter();

            cout << "\n===== TESTING CHARACTER OBSERVER: =====\n" << endl;

            CharacterObserver *co = new CharacterObserver(myCharacter);

            Armor diamondArmor("Diamond Armor");
            Shield ironShield("Iron Shield");
            Boots leatherBoots("Leather Boots");

            cout << "Equipping a piece of armor..." << endl;
            myCharacter->equipArmor(&diamondArmor);

            cout << "Equipping a piece of shield..." << endl;
            myCharacter->equipShield(&ironShield);

            cout << "Equipping a piece of boots..." << endl;
            myCharacter->equipBoots(&leatherBoots);

        }
        else if (part._Equal("2"))
        {
            Editor *editor = new Editor();

            while (true) {
                bool continueEditing = editor->runEditor();
                if (!continueEditing) {
                    break;
                }
            }

        }
        else if (part._Equal("3"))
        {
            Helmet helmet("Helmet");
            Armor armor("Armor");
            Shield shield("Shield");
            Ring ring("Ring");
            Belt belt("Belt");
            Boots boots("Boots");
            Weapon weapon("Weapon");

            cout << "Armor: " << armor.name << endl;
            auto armorEnhancement = armor.getEnhancement();
            cout << "Enhancement: " << enhancementToString(armorEnhancement.first) << ", Enhancement Bonus: " << armorEnhancement.second << endl << endl;

            cout << "Shield: " << shield.name << endl;
            auto shieldEnhancement = shield.getEnhancement();
            cout << "Enhancement: " << enhancementToString(shieldEnhancement.first) << ", Enhancement Bonus: " << shieldEnhancement.second << endl << endl;

            cout << "Weapon: " << weapon.name << endl;
            auto weaponEnhancement = weapon.getEnhancement();
            cout << "Enhancement: " << enhancementToString(weaponEnhancement.first) << ", Enhancement Bonus: " << weaponEnhancement.second << endl << endl;

            cout << "Ring: " << ring.name << endl;
            auto ringEnhancement = ring.getEnhancement();
            cout << "Enhancement: " << enhancementToString(ringEnhancement.first) << ", Enhancement Bonus: " << ringEnhancement.second << endl << endl;

            Backpack backpack("MyBackpack");
            backpack.addItem(&helmet);
            backpack.addItem(&armor);
            backpack.addItem(&shield);
            backpack.addItem(&ring);
            backpack.addItem(&belt);
            backpack.addItem(&boots);
            backpack.addItem(&weapon);

            backpack.displayItems();
        }
        else if (part._Equal("4"))
        {
            Dice dice;
            string input;

            cout << "Enter a dice roll expression (e.g., 3d6+5) : ";
            cin >> input;

            int result = dice.rollDice(input);

            while (result < 0) {
                if (result == -1) {
                   cout << "Invalid input format. Please use the xdy[+z] format." << endl;
                }
                else if (result == -2) {
                    cout << "Invalid dice type. Valid types are d4, d6, d8, d10, d12, d20, d100." << endl;
                }
                cout << "\n";
                cout << "Enter a new dice roll expression (e.g., 3d6+5) : ";
                cin >> input;
                result = dice.rollDice(input);
            }

            if (result >= 0) {
                cout << "Result of rolling " << input << ": " << result << endl;
            }
            cout << "\n";

        }
        else if (part._Equal("5"))
        {
            // Get the top level suite from the registry
            CppUnit::Test* suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();
            // Adds the test to the list of test to run
            CppUnit::TextUi::TestRunner runner;
            runner.addTest(suite);
            // Change the default outputter to a compiler error format outputter
            runner.setOutputter(new CppUnit::CompilerOutputter(&runner.result(), cerr));
            // Run the tests.
            bool wasSuccessful = runner.run();

            if (wasSuccessful) {
                cout << "All the tests passed!" << endl;
            }

        }
        else
        {
            cout << "Please enter a valid number.";
            cout << "\n";
        }
        cout << "\n";
    }
}