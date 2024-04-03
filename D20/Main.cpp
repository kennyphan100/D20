//! @file 
//! @brief Main driver file to create and execute the different parts (Character, Map, Item, and Dice) and the test suite.
//!

#include "Dice/Dice.h"
#include <iostream>
#include <filesystem>
#include "Character/Character.h"
#include "Item/Item.h"
#include "Item/Item2.h"
#include "Map/Map.h"
#include <cppunit/TestRunner.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include "Character/CharacterObserver.h"
#include "Map/MapObserver.h"
#include "Map/Editor.h"
#include "Character/CharacterDirector.h"
#include "Character/CharacterUtils.h"
#include "Character/FriendlyStrategy.h"
#include "Character/HumanPlayerStrategy.h"
#include "Character/AggressorStrategy.h"

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

//! main() function. Entry point of the program.
//! It does the following: 
//! 1. Create a character given the user's input for the desired level and class type
//! 2. Create a map given the user's input for the size and allow the placement of walls and other objects
//! 3. Create an item and an item container that can hold multiple items
//! 4. Roll a dice using the form xdy[+z]
//! 5. Run the test cases. 
//! 9. Exit the program.
int mainX() {
    Character* myCharacter;
    CharacterDirector director;
    Character* newCharacter;
    CharacterBuilder* characterBuilder;

    while (true) {
        cout << "============== D20 Game - Menu ==============" << endl;
        cout << "1. Character" << endl;
        cout << "2. Map" << endl;
        cout << "3. Item" << endl;
        cout << "4. Dice" << endl;
        cout << "5. Run Unit Tests" << endl;
        cout << "6. Play Game" << endl;
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
            string fighterType;
            cout << "Enter the desired type of fighter for your character (Bully/Nimble/Tank): ";
            cin >> fighterType;
            fighterType = toLowercase(fighterType);

            while (!fighterType._Equal("bully") && !fighterType._Equal("nimble") && !fighterType._Equal("tank")) {
                cout << "This class does not exist yet. Try another class: ";
                cin >> fighterType;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n";

            string name, filePath;
            const string directoryPath = "./data/characters/";
            while (true) {
                cout << "Please enter the name of the character: ";
                getline(cin, name);
                filePath = directoryPath + name + ".txt";

                if (filesystem::exists(filePath)) {
                    cerr << "A character with this name already exists. Please choose a different name.\n" << endl;
                }
                else {
                    break;
                }
            }

            int level;
            while (true) {
                cout << "Enter the level of your desired character (e.g., 1): ";
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

            if (fighterType._Equal("bully")) {
                characterBuilder = new BullyFighterBuilder;
            }
            else if (fighterType._Equal("nimble")) {
                characterBuilder = new NimbleFighterBuilder;
            }
            else {
                characterBuilder = new TankFighterBuilder;
            }

            CharacterObserver* co = new CharacterObserver(characterBuilder);

            director.setBuilder(characterBuilder);
            newCharacter = director.buildCharacter(level, name);
            /*CharacterObserver* co = new CharacterObserver(newCharacter);*/
            
            cout << " ===== Successfully created a new character with the following stats: ===== " << endl;
            newCharacter->printCharacter();
            
            //myCharacter->printCharacter();

            //cout << "\n===== TESTING CHARACTER OBSERVER: =====\n" << endl;

            //CharacterObserver *co1 = new CharacterObserver(newCharacter);

            //Armor diamondArmor("Diamond Armor");
            //Shield ironShield("Iron Shield");
            //Boots leatherBoots("Leather Boots");

            //cout << "Equipping a piece of armor..." << endl;
            //newCharacter->equipArmor(&diamondArmor);

            //cout << "Equipping a piece of shield..." << endl;
            //myCharacter->equipShield(&ironShield);

            //cout << "Equipping a piece of boots..." << endl;
            //myCharacter->equipBoots(&leatherBoots);

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
            //Character* fighterCharacter = new FighterCharacter(10, FighterType::TANK);
            //fighterCharacter->setName("TestCharacter");
            //fighterCharacter->display();

            //cout << "\n";
            //cout << "========================\n" << endl;

            //cout << "=== List of items that you can equip (write the negative to unequip) ===\n"
            //    << "1. Helmet - Name: Iron Helmet, Enchantment: Intelligence, Bonus: +1\n"
            //    << "2. Armor - Name: Diamond Helmet, Enchantment: Armor class, Bonus: +5\n"
            //    << "3. Shield - Name: Diamond Shield, Enchantment: Armor class, Bonus: +5\n"
            //    << "4. Ring - Name: Silver Ring, Enchantment: Strength, Bonus: +3\n"
            //    << "5. Belt - Name: Iron Belt, Enchantment: Constitution, Bonus: +2\n"
            //    << "6. Boots - Name: Leather Boots, Enchantment: Dexterity, Bonus: +1\n"
            //    << "7. Weapon - Name: Gold Sword, Enchantment: Attack bonus, Bonus: +4\n";

            //cout << "\n";
            //cout << "========================\n" << endl;

            //int itemOption;
            //while (true) {
            //    cout << "Choose an option to equip (enter 0 to exit): ";
            //    string input;
            //    getline(cin, input);
            //    stringstream ss(input);

            //    if (ss >> itemOption && ss.eof()) {
            //        if ((-8 < itemOption < 8 && itemOption != 0)) {
            //            if (itemOption == 1) {
            //                fighterCharacter = new Helmet2(fighterCharacter, "Iron Helmet", CharacterStat::Intelligence, 1);
            //            }
            //            else if (itemOption == 2) {
            //                fighterCharacter = new Armor2(fighterCharacter, "Diamond Helmet", CharacterStat::ArmorClass, 5);
            //            }
            //            else if (itemOption == 3) {
            //                fighterCharacter = new Shield2(fighterCharacter, "Diamond Shield", CharacterStat::ArmorClass, 5);
            //            }
            //            else if (itemOption == 4) {
            //                fighterCharacter = new Ring2(fighterCharacter, "Silver Ring", CharacterStat::Strength, 3);
            //            }
            //            else if (itemOption == 5) {
            //                fighterCharacter = new Belt2(fighterCharacter, "Iron Belt", CharacterStat::Constitution, 2);
            //            }
            //            else if (itemOption == 6) {
            //                fighterCharacter = new Boots2(fighterCharacter, "Leather Boots", CharacterStat::Dexterity, 1);
            //            }
            //            else if (itemOption == 7) {
            //                fighterCharacter = new Weapon2(fighterCharacter, "Gold Sword", CharacterStat::Strength, 4);
            //            }
            //            else if (itemOption == -1) {
            //                fighterCharacter = new Helmet2(fighterCharacter, "---", CharacterStat::NoEffect, 0);
            //            }
            //            else if (itemOption == -2) {
            //                fighterCharacter = new Armor2(fighterCharacter, "---", CharacterStat::NoEffect, 0);
            //            }
            //            else if (itemOption == -3) {
            //                fighterCharacter = new Shield2(fighterCharacter, "---", CharacterStat::NoEffect, 0);
            //            }
            //            else if (itemOption == -4) {
            //                fighterCharacter = new Ring2(fighterCharacter, "---", CharacterStat::NoEffect, 0);
            //            }
            //            else if (itemOption == -5) {
            //                fighterCharacter = new Belt2(fighterCharacter, "---", CharacterStat::NoEffect, 0);
            //            }
            //            else if (itemOption == -6) {
            //                fighterCharacter = new Boots2(fighterCharacter, "---", CharacterStat::NoEffect, 0);
            //            }
            //            else if (itemOption == -7) {
            //                fighterCharacter = new Weapon2(fighterCharacter, "---", CharacterStat::NoEffect, 0);
            //            }

            //            cout << "\n" << endl;
            //            fighterCharacter->display();
            //            cout << "\n" << endl;

            //        }
            //        else {
            //            break;
            //            cout << "Terminating.\n" << endl;
            //        }
            //    }
            //    else {
            //        cerr << "Input format must be a positive integer value.\n" << endl;
            //    }
            //}

            //fighterCharacter = new Helmet2(fighterCharacter, "Iron Helmet", CharacterStat::Strength, 2);
            //fighterCharacter->display();


            //Helmet2* helmet = CharacterUtils::findHelmet(fighterCharacter);
            //cout << helmet->getEnhancementBonus() << endl;

            // ===============================================================

            Helmet newHelmet("Diamond Helmet", EnhancementType::Strength, 5);

            string filename = "./data/items/" + newHelmet.getName() + ".txt";

            if (newHelmet.saveToFile(filename, "Helmet")) {
                cout << "Item '" << newHelmet.getName() << "' has been successfully saved to '" << filename << "'." << endl;
            }
            else {
                cerr << "Failed to save the item '" << newHelmet.getName() << "' to a file.\n" << endl;
            }

            //Helmet helmet("Helmet");
            //Armor armor("Armor");
            //Shield shield("Shield");
            //Ring ring("Ring");
            //Belt belt("Belt");
            //Boots boots("Boots");
            //Weapon weapon("Weapon");

            //cout << "Armor: " << armor.getName() << endl;
            //auto armorEnhancement = armor.getEnhancement();
            //cout << "Enhancement: " << enhancementToString(armorEnhancement.first) << ", Enhancement Bonus: " << armorEnhancement.second << endl << endl;

            //cout << "Shield: " << shield.getName() << endl;
            //auto shieldEnhancement = shield.getEnhancement();
            //cout << "Enhancement: " << enhancementToString(shieldEnhancement.first) << ", Enhancement Bonus: " << shieldEnhancement.second << endl << endl;

            //cout << "Weapon: " << weapon.getName() << endl;
            //auto weaponEnhancement = weapon.getEnhancement();
            //cout << "Enhancement: " << enhancementToString(weaponEnhancement.first) << ", Enhancement Bonus: " << weaponEnhancement.second << endl << endl;

            //cout << "Ring: " << ring.getName() << endl;
            //auto ringEnhancement = ring.getEnhancement();
            //cout << "Enhancement: " << enhancementToString(ringEnhancement.first) << ", Enhancement Bonus: " << ringEnhancement.second << endl << endl;

            //Backpack backpack("MyBackpack");
            //backpack.addItem(&helmet);
            //backpack.addItem(&armor);
            //backpack.addItem(&shield);
            //backpack.addItem(&ring);
            //backpack.addItem(&belt);
            //backpack.addItem(&boots);
            //backpack.addItem(&weapon);

            //backpack.displayItems();
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
        else if (part._Equal("6"))
        {
            FriendlyStrategy fs;
            AggressorStrategy as;
            HumanPlayerStrategy hps;
            FighterCharacter myCharacter(1, FighterType::NIMBLE, &hps);
            FighterCharacter enemyCharacter(1, FighterType::BULLY, &as);

            Editor* editor = new Editor();

            Map* chosenMap = editor->selectMap();

            chosenMap->placeCharacter(0, 0, &myCharacter);
            chosenMap->placeCharacter(4, 6, &enemyCharacter);

            chosenMap->display();

            string actionChoice;

            while (true) {
                cout << "============== Actions ==============" << endl;
                cout << "1. Move" << endl;
                cout << "2. Attack" << endl;
                cout << "3. Free action" << endl;
                cout << "9. Exit \n" << endl;

                cout << "Please enter the number of the action: ";
                cin >> actionChoice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\n";

                if (actionChoice == "1") {
                    myCharacter.performMove(*chosenMap);
                }
                else if (actionChoice == "2") {
                    myCharacter.performAttack(*chosenMap);
                }
                else if (actionChoice == "3") {
                    myCharacter.performFreeActions();
                }
                else if (actionChoice == "9") {
                    break;
                }

                cout << "\n";
                chosenMap->display();

                cout << "Enemy's turn to move: ";
                enemyCharacter.performMove(*chosenMap);

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