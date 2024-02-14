#include "Dice.h"
#include <iostream>
#include "Character.h"
#include "Item.h"
#include "Map.h"
using namespace std;

int main() {
  /*  Dice dice;
    try {
        string input;

        while (true) {
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

    }
    catch (const exception& e) {
        cerr << e.what() << endl;
    }*/

    // Create a 10x10 map
    Map myMap(10, 10);

    // Set some walls in the map
    myMap.setCell(1, 0, Cell::WALL);
    myMap.setCell(1, 2, Cell::WALL);
    myMap.setCell(1, 3, Cell::WALL);
    myMap.setCell(1, 4, Cell::WALL);
    myMap.setCell(1, 5, Cell::WALL);
    myMap.setCell(1, 6, Cell::WALL);
    myMap.setCell(1, 7, Cell::WALL);
    myMap.setCell(1, 8, Cell::WALL);
    myMap.setCell(1, 9, Cell::WALL);
    myMap.setCell(1, 100, Cell::WALL);
    // ... You can add more walls or obstacles as needed

    // Set the start and end points as EMPTY to ensure they are traversable
    myMap.setCell(0, 0, Cell::EMPTY); // Start point
    myMap.setCell(9, 9, Cell::EMPTY); // End point

    // Verify the map to see if there is a path from start to end
    if (myMap.verifyMap()) {
        std::cout << "A path exists from start to end." << std::endl;
    }
    else {
        std::cout << "No path exists from start to end." << std::endl;
    }

    std::cout << "Map after verification:" << std::endl;
    myMap.display();

    return 0;
}