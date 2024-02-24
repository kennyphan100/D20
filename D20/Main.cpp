#include "Dice.h"
#include <iostream>
#include "Character.h"
#include "Item.h"
#include "Map.h"
#include <cppunit/TestRunner.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

using namespace std;

string toLowercase(const string& str) {
    string result = str;
    for (char& c : result) {
        c = tolower(c);
    }
    return result;
}

int main() {
    while (true) {
        cout << "==================================================================================================" << endl;
        cout << "Please enter a part of the game to test (Character, Map, Item, Dice, or Test) - (enter Q to quit): ";
        string part;
        cin >> part;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\n";

        part = toLowercase(part);

        if (part == "q")
        {
            cout << "Terminating program." << endl;
            exit(0);
        }

        if (part._Equal("character"))
        {
            Character fighter(1);
            Armor leatherArmor("Leather Armor", 1);
            fighter.equipArmor(&leatherArmor);
            fighter.printCharacter();
        }
        else if (part._Equal("map"))
        {
            try {
                int width;
                int height;
                while (true) {
                    cout << "Please enter the dimensions of map (e.g., 10 10): ";
                    string dimensions;
                    getline(cin, dimensions);
                    stringstream ss(dimensions);

                    if (!(ss >> width >> height)) {
                        cerr << "Input format is incorrect! \n" << endl;
                        continue;
                    }
                    break;
                }

                Map myMap(width, height);
                cout << "\n";

                myMap.setCell(0, 0, Cell::START); // Start point
                myMap.setCell(width - 1, height - 1, Cell::FINISH); // End point

                while (true) {
                    string coordinatesInput;
                    cout << "Please enter the coordinates (width, height) for the placement of walls/characters (e.g., 1 2 W or 3 4 C) - enter Q to quit: ";
                    getline(cin, coordinatesInput);

                    if (coordinatesInput == "q") {
                        myMap.display();
                        break;
                    }

                    int x, y;
                    char obstacle;
                    stringstream ss(coordinatesInput);

                    if (!(ss >> x >> y >> obstacle)) {
                        cerr << "Input format is incorrect! \n" << endl;
                        continue;
                    }
                    obstacle = toupper(obstacle);

                    if (obstacle != 'W' && obstacle != 'C') {
                        cout << "Invalid obstacle. Must be 'W' or 'C'. \n" << endl;
                        continue;
                    }

                    if (x < 0 || x >= width || y < 0 || y >= height) {
                        cout << "Cell coordinates are out of bounds. \n" << endl;
                        continue;
                    }

                    if (!(myMap.isEmptyCell(x, y))) {
                        cout << "Try again, this cell is occupied or has a wall. \n" << endl;
                        continue;
                    }

                    switch (obstacle) {
                        case 'W':
                            myMap.setCell(x, y, Cell::WALL);
                            break;
                        case 'C':
                            myMap.setCell(x, y, Cell::OCCUPIED);
                            break;
                    }
                    myMap.display();
                    cout << "\n";
                }

                // Verify the map to see if there is a path from start to finish
                if (myMap.verifyMap()) {
                    std::cout << "A path exists from start to finish." << std::endl;
                }
                else {
                    std::cout << "No path exists from start to finish." << std::endl;
                }
            }
            catch (const exception& e) {
                cerr << e.what() << endl;
            }
        }
        else if (part._Equal("item"))
        {
        }
        else if (part._Equal("dice"))
        {
            Dice dice;
            string input;

            cout << "Enter a dice roll expression (e.g., 3d6+5) : ";
            cin >> input;

            int result = dice.rollDice(input);

            while (result < 0) {
                if (result == -1) {
                   cout << "Invalid input format. Please use the xdy[+z] format." << std::endl;
                }
                else if (result == -2) {
                    cout << "Invalid dice type. Valid types are d4, d6, d8, d10, d12, d20, d100." << std::endl;
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
        else if (part._Equal("test"))
        {
            // Get the top level suite from the registry
            CppUnit::Test* suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();
            // Adds the test to the list of test to run
            CppUnit::TextUi::TestRunner runner;
            runner.addTest(suite);
            // Change the default outputter to a compiler error format outputter
            runner.setOutputter(new CppUnit::CompilerOutputter(&runner.result(),
                std::cerr));
            // Run the tests.
            bool wasSuccessful = runner.run();

            if (wasSuccessful) {
                cout << "All the tests passed!" << endl;
            }

            return wasSuccessful;
        }
        else
        {
            cout << "Please enter a valid part.";
            cout << "\n";
        }
        cout << "\n";
    }
}