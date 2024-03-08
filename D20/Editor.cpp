#include "Editor.h"
#include <iostream>
#include <string>
#include "Character.h"
#include "Item.h"
#include "Map.h"
#include <cppunit/CompilerOutputter.h>
#include "CharacterObserver.h"


using namespace std;

Editor::Editor() {
}

bool Editor::runEditor() {
    string choice;
    while(true) {
        cout << "===== Map Editor =====\n";
        cout << "1. Create New Map\n";
        cout << "2. Edit Current Map\n";
        cout << "3. Display Current Map\n";
        cout << "4. Create Campaign\n";
        cout << "5. Edit Campaign\n";
        cout << "9. Exit\n";
        cout << "Select an option: ";

        getline(cin, choice);
        stringstream ss(choice);

        if (choice._Equal("1")) {
            createMap();
        }
        else if (choice._Equal("2")) {
            editMap();
        }
        else if (choice._Equal("3")) {
            createMap();
        }
        else if (choice._Equal("4")) {
            createCampaign();
        }
        else if (choice._Equal("5")) {
            editCampaign();
        }
        else if (choice._Equal("9")) {
            return false;
        }
        else {
            cerr << "Invalid input. Please enter a valid option.\n" << endl;
            continue;
        }
        return true;
    }
}

void Editor::createMap() {
    try {
        int width;
        int height;
        string name;

        while (true) {
            cout << "Please enter the name of the map: ";
            getline(cin, name);
            stringstream ss(name);
            if (maps.find(name) != maps.end()) {
                cerr << "A map with the name \"" << name << "\" already exists. Please choose a different name.\n";
            }
            else {
                break;
            }
        }

        while (true) {
            cout << "Please enter the dimensions of map (e.g., 10 10): ";
            string dimensions;
            getline(cin, dimensions);
            stringstream ss2(dimensions);

            if (!(ss2 >> width >> height)) {
                cerr << "Input format is incorrect! \n" << endl;
                continue;
            }
            break;
        }

        Map myMap(width, height, name);
        cout << "\n";

        myMap.setCell(0, 0, Cell::START); // Start point
        myMap.setCell(width - 1, height - 1, Cell::FINISH); // End point

        while (true) {
            string coordinatesInput;
            cout << "Please enter the coordinates (width, height) for the placement of walls/players/chests (e.g., 1 2 W or 3 4 P or 1 2 C) - enter Q when done: ";
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

            if (obstacle != 'W' && obstacle != 'C' && obstacle != 'P' && obstacle != 'D') {
                cout << "Invalid obstacle. Must be 'W', 'C', 'P', or 'D'. \n" << endl;
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
            case 'P':
                myMap.setCell(x, y, Cell::PLAYER);
                break;
            case 'C':
                myMap.setCell(x, y, Cell::CHEST);
                break;
            case 'D':
                myMap.setCell(x, y, Cell::DOOR);
                break;
            }
            myMap.display();
            cout << "\n";

        }
        // Verify the map to see if there is a path from start to finish
        if (myMap.verifyMap()) {
            cout << "\nA path exists from start to finish." << endl;
            maps.insert(make_pair(name, myMap)); // THIS CRASHES THE PROGRAM
            cout << "The number of created maps is now: " << maps.size() << endl;

            // Construct the filename for the map, based on its name
            string filename = "./data/" + name + ".txt"; // You can change the extension or naming convention as needed

            // Attempt to save the map to the specified file
            if (myMap.saveToFile(filename)) {
                cout << "Map '" << name << "' has been successfully saved to '" << filename << "'.\n" << endl;
            }
            else {
                cerr << "Failed to save the map '" << name << "' to a file.\n" << endl;
            }
        }
        else {
            cout << "\nNo path exists from start to finish. Map not saved." << endl;
        }
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
    }
}

void Editor::editMap() {
    Map* selectedMap = selectMap(); // Let the user select a map
    if (selectedMap) {
        // Perform editing operations on the selected map
        // For example, changing its name, updating specific cells, etc.
        int width = selectedMap->getWidth();
        int height = selectedMap->getHeight();
        while (true) {
            string coordinatesInput;
            cout << "Please enter the coordinates (width, height) for the placement of walls/players/chests (e.g., 1 2 W or 3 4 P or 1 2 C) - enter Q when done: ";
            getline(cin, coordinatesInput);

            if (coordinatesInput == "q") {
                selectedMap->display();
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

            if (obstacle != 'W' && obstacle != 'C' && obstacle != 'P' && obstacle != 'D') {
                cout << "Invalid obstacle. Must be 'W', 'C', 'P', or 'D'. \n" << endl;
                continue;
            }

            if (x < 0 || x >= width || y < 0 || y >= height) {
                cout << "Cell coordinates are out of bounds. \n" << endl;
                continue;
            }

            if (!(selectedMap->isEmptyCell(x, y))) {
                cout << "Try again, this cell is occupied or has a wall. \n" << endl;
                continue;
            }

            switch (obstacle) {
            case 'W':
                selectedMap->setCell(x, y, Cell::WALL);
                break;
            case 'P':
                selectedMap->setCell(x, y, Cell::PLAYER);
                break;
            case 'C':
                selectedMap->setCell(x, y, Cell::CHEST);
                break;
            case 'D':
                selectedMap->setCell(x, y, Cell::DOOR);
                break;
            }
            selectedMap->display();
            cout << "\n";
        }
        string filename = "./data/" + selectedMap->getName() + ".txt";

        if (selectedMap->saveToFile(filename)) {
            cout << "Map '" << selectedMap->getName() << "' has been successfully saved to '" << filename << "'.\n" << endl;
        }
        else {
            cerr << "Failed to save the map '" << selectedMap->getName() << "' to a file.\n" << endl;
        }
    }
    else {
        std::cout << "Map selection cancelled or invalid.\n" << "\n";
    }
}

void Editor::createCampaign() {
    // Placeholder for campaign creation logic
    std::cout << "Campaign creation not implemented yet.\n";
}

void Editor::editCampaign() {
    // Placeholder for campaign editing logic
    std::cout << "Campaign editing not implemented yet.\n";
}

void Editor::displayCurrentMap() {
    //currentMap.display();
    std::cout << "Display map not implemented yet.\n";
}

void Editor::displayAllMaps() {
    int index = 1; // Start index from 1 for user-friendly numbering
    std::cout << "Available Maps:\n";
    for (const auto& pair : maps) {
        std::cout << index++ << ": " << pair.first << " (Width: " << pair.second.getWidth() << ", Height: " << pair.second.getHeight() << ")\n";
    }
}

Map* Editor::selectMap() {
    if (maps.empty()) {
        std::cout << "No maps available.\n";
        return nullptr; // No maps to select
    }

    displayAllMaps(); // Display all maps for the user to choose

    int choice;
    std::cout << "Enter the number of the map you want to select: ";
    std::cin >> choice;
    std::cin.ignore(); // Clear the newline character after the number

    // Check if the choice is valid
    if (choice > 0 && choice <= maps.size()) {
        auto it = maps.begin();
        std::advance(it, choice - 1); // Move iterator to the chosen map
        return &(it->second); // Return a pointer to the chosen map
    }
    else {
        std::cout << "Invalid selection.\n";
        return nullptr; // Invalid selection
    }
}

// Implement other methods as needed
