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

int main() {
    while (true) {
        cout << "Please enter the part of the game (press 0 to exit): ";
        string part;
        cin >> part;
        cout << "\n";

        if (part._Equal("0"))
        {
            std::exit(0);
        }
        else if (part._Equal("character"))
        {
        }
        else if (part._Equal("map"))
        {
            try {
                cout << "Please enter the dimensions of map (e.g., 10 10): ";
                int width;
                int height;
                string dummy;
                cin >> width >> height;
                cout << "\n";
                getline(cin, dummy);

                Map myMap(width, height);

                myMap.setCell(0, 0, Cell::START); // Start point
                myMap.setCell(width - 1, height - 1, Cell::FINISH); // End point

                while (true) {
                    string coordinatesInput;
                    cout << "Please enter the coordinates (width, height) for the placement of walls/characters (e.g., 1 2 W or 3 4 C) - Press Q to Stop: ";
                    getline(cin, coordinatesInput);

                    if (coordinatesInput == "q") {
                        myMap.display();
                        break;
                    }

                    int x, y;
                    char obstacle;
                    stringstream ss(coordinatesInput);

                    if (!(ss >> x >> y >> obstacle)) {
                        cerr << "Error: Input format is incorrect!" << endl;
                        continue;
                    }
                    cout << "width: " << width << endl;
                    cout << "height: " << height << endl;
                    cout << "x: " << x << endl;
                    cout << "y: " << y << endl;
                    cout << "obstacle: " << obstacle << endl;

                    if (x < 0 || x >= width || y < 0 || y >= height) {
                        cout << "Cell coordinates are out of bounds." << endl;
                        continue;
                    }

                    if (!(myMap.isEmptyCell(x, y))) {
                        cout << "Try again, this cell is occupied or has a wall." << endl;
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
                }

                // Verify the map to see if there is a path from start to end
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
            try {
                string input;

                cout << "Enter the dice roll expression (e.g., 3d6+5): ";
                cin >> input;

                int result = dice.rollDice(input);

                if (result != -1) {
                    cout << "Result of rolling " << input << ": " << result << endl;
                }
                cout << "\n";

                Character fighter(1);
                Armor leatherArmor("Leather Armor", 1);
                fighter.equipArmor(&leatherArmor);
                fighter.printCharacter();
            }
            catch (const exception& e) {
                cerr << e.what() << endl;
            }
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
            bool wasSucessful = runner.run();
            return wasSucessful;
            // Return error code 1 if the 
        }
        else
        {
            cout << "Please enter a valid part.";
            cout << "\n";
        }
        cout << "\n";
    }
}