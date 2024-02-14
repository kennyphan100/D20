#include "Dice.h"
#include <iostream>
#include "Character.h"
#include "Item.h"
using namespace std;

int main() {
    Dice dice;
    try {
        string input;

        while (true) {
            cout << "Enter the dice roll expression (e.g., 3d6+5): ";
            cin >> input;

            if (input == "q") { return 0; }

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
    }
    return 0;
}
