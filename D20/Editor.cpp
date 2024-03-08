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

void Editor::runEditor() {
    int choice = 0;
    do {
        std::cout << "\nMap Editor\n";
        std::cout << "1. Create New Map\n";
        std::cout << "2. Edit Current Map\n";
        std::cout << "3. Display Current Map\n";
        std::cout << "4. Create Campaign\n";
        std::cout << "5. Edit Campaign\n";
        std::cout << "9. Exit\n";
        std::cout << "Select an option: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            createMap();
            break;
        case 2:
            editMap();
            break;
        case 3:
            displayCurrentMap();
            break;
        case 4:
            createCampaign();
            break;
        case 5:
            editCampaign();
            break;
        case 9:
            std::cout << "Exiting editor...\n";
            break;
        default:
            std::cout << "Invalid option. Please try again.\n";
        }
    } while (choice != 9);
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

            if (!(ss >> name)) {
                cerr << "Input format is incorrect! \n" << endl;
                continue;
            }

            //Check if name exists here

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
        maps.insert({ name, myMap });
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
    }
    else {
        std::cout << "Map selection cancelled or invalid.\n";
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

//void Editor::displayCurrentMap() {
//    currentMap.display();
//}

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
