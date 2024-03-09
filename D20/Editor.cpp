#include "Editor.h"
#include <iostream>
#include <string>
#include "Character.h"
#include "Item.h"
#include "Map.h"
#include <cppunit/CompilerOutputter.h>
#include "CharacterObserver.h"
#include <filesystem>

using namespace std;

Editor::Editor() {
}

bool Editor::runEditor() {
    string choice;
    while(true) {
        cout << "===== Map Editor =====\n";
        cout << "1. Create New Map\n";
        cout << "2. Edit Current Map\n";
        cout << "3. Create Campaign\n";
        cout << "4. Edit Campaign\n";
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
            createCampaign();
        }
        else if (choice._Equal("4")) {
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
        string name, filePath;
        const string directoryPath = "./data/maps/";

        // User input name and check if duplicate exists in directory
        while (true) {
            cout << "Please enter the name of the map: ";
            getline(cin, name);
            filePath = directoryPath + name + ".txt";

            // Check if a file with the same name already exists
            if (filesystem::exists(filePath)) {
                cerr << "A map with this name already exists. Please choose a different name.\n";
            }
            else {
                break; // No duplicate found, proceed
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
            maps.push_back(myMap);

            // Construct the filename for the map, based on its name
            string filename = "./data/maps/" + name + ".txt"; // You can change the extension or naming convention as needed

            // Attempt to save the map to the specified file
            if (myMap.saveToFile(filename)) {
                cout << "Map '" << name << "' has been successfully saved to '" << filename << "'." << endl;
                int mapCount = countMapFiles("./data/maps/");
                cout << "The number of created maps is now: " << mapCount << "\n" << endl;
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
        string name = selectedMap->getName();
        cout << name << endl;
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
        string filename = "./data/maps/" + selectedMap->getName() + ".txt";

        if (selectedMap->saveToFile(filename)) {
            cout << "Map '" << selectedMap->getName() << "' has been successfully edited to '" << filename << "'.\n" << endl;
        }
        else {
            cerr << "Failed to edit the map '" << selectedMap->getName() << "' to a file.\n" << endl;
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
    string directoryPath = "./data/maps"; // The path to your maps directory
    int index = 1; // Start index from 1 for user-friendly numbering

    cout << "Available Maps:\n";

    try {
        // Iterate over the directory contents using std::filesystem directly
        for (const auto& entry : filesystem::directory_iterator(directoryPath)) {
            if (entry.is_regular_file()) { // Check if it's a file
                auto filePath = entry.path();
                auto extension = filePath.extension().string();

                // Check for .txt file extension
                if (extension == ".txt") {
                    // Print the file name without the extension, and file path if needed
                    cout << index++ << ": " << filePath.stem() << " (" << filePath << ")\n";
                }
            }
        }

        if (index == 1) { // If no .txt files were found
            cout << "No map files found in the directory.\n";
        }
    }
    catch (const filesystem::filesystem_error& e) {
        cerr << "Filesystem error: " << e.what() << '\n';
    }
    catch (const exception& e) {
        cerr << "General error: " << e.what() << '\n';
    }
}

Map* Editor::selectMap() {
    std::string directoryPath = "./data/maps"; // Adjust this path to your maps directory
    std::vector<std::string> mapFiles;

    // Read the directory and collect .txt files
    for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            mapFiles.push_back(entry.path().string());
        }
    }

    if (mapFiles.empty()) {
        std::cout << "No map files available.\n";
        return nullptr;
    }
    
    while (true) {
        displayAllMaps(); // Assuming displayAllMaps now takes mapFiles as a parameter
        int choice;
        std::cout << "\nEnter the number of the map you want to select: ";
        std::cin >> choice;
        // Clear the newline character after the number, and handle invalid input
        if (std::cin.fail()) {
            std::cin.clear(); // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard the line
            std::cout << "Invalid input. Please enter a number.\n";
            continue; // Skip the rest of the loop and prompt again
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Always clear the newline character

        if (choice > 0 && static_cast<size_t>(choice) <= mapFiles.size()) {
            // Assuming you have a way to load a map from a filename in your Map class
            // and that you manage memory for dynamically created maps (consider using smart pointers)
            Map* selectedMap = new Map();
            if (selectedMap->loadFromFile(mapFiles[choice - 1])) { // loadFromFile method to be implemented in Map
                selectedMap->display();
                return selectedMap;
            }
            else {
                delete selectedMap;
                std::cout << "Failed to load the selected map.\n";
                return nullptr;
            }
        }
        else {
            std::cout << "Invalid selection.\n";
            return nullptr;
        }
    }
}

int Editor::countMapFiles(const std::string& directoryPath) {
    using namespace std::filesystem;
    int fileCount = 0;
    for (const auto& entry : directory_iterator(directoryPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            ++fileCount;
        }
    }
    return fileCount;
}

// Implement other methods as needed
