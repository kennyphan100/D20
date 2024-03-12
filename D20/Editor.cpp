#include "Editor.h"
#include "Character.h"
#include "Campaign.h"
#include "Item.h"
#include "Map.h"
#include "CharacterObserver.h"
#include <iostream>
#include <string>
#include <cppunit/CompilerOutputter.h>
#include <filesystem>
#include "MapObserver.h"

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
        cout << "9. Exit\n\n";
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
        cout << "\n" << endl;
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
            cout << "\nPlease enter the name of the map: ";
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

        MapObserver* mo = new MapObserver(&myMap);

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
            //myMap.display(); // TO BE REMOVED SINCE THE OBSERVER PATTERN CALLS THIS FUNCTION BY DEFAULT (in the setCell function above)
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
                cout << "The number of created maps is now: " << mapCount << endl;
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
        cout << "Map selection cancelled or invalid.\n" << "\n";
    }
}

void Editor::createCampaign() {
    std::string campaignName;
    std::filesystem::path dirPathCampaign, dirPathMapsInCampaign, infoFilePath;

    while (true) {
        std::cout << "Enter the name of the new campaign: ";
        std::getline(std::cin, campaignName);

        // Construct the directory path where the campaign's files will be stored
        dirPathCampaign = std::filesystem::current_path() / "data" / "campaigns" / campaignName;
        dirPathMapsInCampaign = std::filesystem::current_path() / "data" / "campaigns" / campaignName / "maps";

        // Check if a campaign with this name already exists by checking the directory existence
        if (std::filesystem::exists(dirPathCampaign)) {
            std::cerr << "A campaign with the name \"" << campaignName << "\" already exists. Please try a different name.\n";
            continue; // Prompt the user again
        }
        else {
            break; // The name is unique, exit the loop
        }
    }

    // Attempt to create the campaign directory
    if (!std::filesystem::create_directories(dirPathCampaign)) {
        std::cerr << "Failed to create directory for the campaign \"" << campaignName << "\".\n";
        return; // Stop if unable to create the directory
    }

    if (!std::filesystem::create_directories(dirPathMapsInCampaign)) {
        std::cerr << "Failed to create directory for the maps in \"" << campaignName << "\".\n";
        return; // Stop if unable to create the directory
    }

    // Construct the file path for the main campaign file within the directory
    infoFilePath = dirPathCampaign / (campaignName + ".txt");

    // Initialize the campaign object (assuming Campaign constructor doesn't require file path)
    Campaign newCampaign(campaignName);

    // Call saveToFile method of Campaign to save the campaign details into the directory
    if (newCampaign.saveToFile(infoFilePath.string())) {
        std::cout << "Campaign \"" << campaignName << "\" created and saved successfully.\n\n";
    }
    else {
        std::cerr << "Failed to save the campaign \"" << campaignName << "\".\n\n";
    }
}

void Editor::editCampaign() {
    Campaign* selectedCampaign = selectCampaign(); // Let the user select a campaign

    if (!selectedCampaign) {
        std::cout << "Campaign selection cancelled or invalid.\n";
        return;
    }

    bool editing = true;
    string campaignName = selectedCampaign->getName();
    while (editing) {
        std::cout << "\nEditing Campaign => " << campaignName << "\n";
        selectedCampaign->display();
        std::cout << "\n1. Add Map\n"
            << "2. Remove Map\n"
            << "3. Connect Maps\n"
            << "4. Save and Exit\n"
            << "Enter your choice: ";
        int choice;
        std::cin >> choice;

        // Clear input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
        case 1: {
            // Let the user add a map
            Map* newMap = selectMap(); // Assumes selectMap returns a new or existing map
            if (newMap) {
                selectedCampaign->addMap(newMap->getName(), "./data/campaigns/" + campaignName); // Assuming addMap takes the map name
                //selectedCampaign->display();
                //std::cout << "Map " << newMap->getName() << " added.\n";
            }
            break;
        }
        case 2: {
            Map* mapToRemove = selectMapInCampaign(selectedCampaign->getName(), ""); // Let the user select a map to remove
            if (mapToRemove) {
                selectedCampaign->removeMap(mapToRemove->getName(), "./data/campaigns/" + campaignName); // Assuming removeMap takes the map name
                //std::cout << "Map \"" << mapToRemove->getName() << "\" removed.\n";
            }
            else {
                std::cout << "Map selection cancelled or invalid.\n";
            }
            break;
        }
        case 3: {
            // Let the user select the "from" map
            Map* fromMap = selectMapInCampaign(selectedCampaign->getName(), "from");
            if (!fromMap) {
                std::cout << "Invalid selection for the 'from' map.\n";
                break;
            }

            // Let the user select the "to" map
            Map* toMap = selectMapInCampaign(selectedCampaign->getName(), "to");
            if (!toMap) {
                std::cout << "Invalid selection for the 'to' map.\n";
                break;
            }

            // Ensure that the fromMap and toMap are not the same
            if (fromMap->getName() == toMap->getName()) {
                std::cout << "The 'from' map and 'to' map cannot be the same. Please select different maps.\n";
            }
            else {
                // Proceed to connect the maps
                selectedCampaign->connectMaps(fromMap->getName(), toMap->getName());
                std::cout << "Maps successfully connected: " << fromMap->getName() << " -> " << toMap->getName() << "\n";
            }
            break;
        }
        case 4: {
            editing = false; // Exit the loop to save and exit
            break;
        }
        default: {
            std::cout << "Invalid choice. Please enter a valid option.\n";
            break;
        }
        }
    }

    // Save the campaign after making changes
    std::filesystem::path dirPath, infoFilePath;
    dirPath = std::filesystem::current_path() / "data" / "campaigns" / campaignName;
    infoFilePath = dirPath / (campaignName + ".txt");
    if (selectedCampaign->saveToFile(infoFilePath.string())) {
        std::cout << "Campaign \"" << campaignName << "\" has been successfully saved to \"" << infoFilePath << "\".\n";
    }
    else {
        std::cerr << "Failed to save the campaign \"" << campaignName << "\".\n";
    }

    delete selectedCampaign; // Assuming dynamic allocation in selectCampaign
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

void Editor::displayAllMapsInCampaign(const string& campaignName) {
    string directoryPath = "./data/campaigns/" + campaignName + "/maps"; // The path to your maps directory
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

void Editor::displayAllCampaigns() {
    std::string directoryPath = "./data/campaigns/";  // Adjust the path to your campaigns directory
    int index = 1;  // Start index from 1 for user-friendly numbering

std::cout << "Available Campaigns:\n";

try {
    // Iterate over the directory contents using std::filesystem directly
    for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
        if (entry.is_directory()) {  // Check if it's a directory
            auto dirPath = entry.path();
            // Print the directory name, which represents the campaign name
            std::cout << index++ << ": " << dirPath.filename() << "\n";
        }
    }

    if (index == 1) {  // If no directories were found
        std::cout << "No campaign directories found in the directory.\n";
    }
}
catch (const std::filesystem::filesystem_error& e) {
    std::cerr << "Filesystem error: " << e.what() << '\n';
}
catch (const std::exception& e) {
    std::cerr << "General error: " << e.what() << '\n';
}
}

Map* Editor::selectMap() {
    string directoryPath = "./data/maps"; // Adjust this path to your maps directory
    vector<string> mapFiles;

    // Read the directory and collect .txt files
    for (const auto& entry : filesystem::directory_iterator(directoryPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            mapFiles.push_back(entry.path().string());
        }
    }

    if (mapFiles.empty()) {
        cout << "No map files available.\n";
        return nullptr;
    }

    while (true) {
        displayAllMaps(); // Assuming displayAllMaps now takes mapFiles as a parameter
        int choice;
        cout << "\nEnter the number of the map you want to select: ";
        cin >> choice;
        // Clear the newline character after the number, and handle invalid input
        if (cin.fail()) {
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the line
            cout << "Invalid input. Please enter a number.\n";
            continue; // Skip the rest of the loop and prompt again
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Always clear the newline character

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
                cout << "Failed to load the selected map.\n";
                return nullptr;
            }
        }
        else {
            cout << "Invalid selection.\n";
            return nullptr;
        }
    }
}

Map* Editor::selectMapInCampaign(const string& campaignName, const string& call) {
    string directoryPath = "./data/campaigns/" + campaignName + "/maps"; // Adjust this path to your maps directory
    vector<string> mapFiles;

    // Read the directory and collect .txt files
    for (const auto& entry : filesystem::directory_iterator(directoryPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            mapFiles.push_back(entry.path().string());
        }
    }

    if (mapFiles.empty()) {
        cout << "No map files available.\n";
        return nullptr;
    }

    while (true) {
        displayAllMapsInCampaign(campaignName); // Assuming displayAllMaps now takes mapFiles as a parameter
        int choice;
        if (call._Equal("from")) {
            cout << "\nEnter the number of the first map you want to connect: ";
        }
        else if (call._Equal("to")) {
            cout << "\nEnter the number of the second map you want to connect: ";
        }
        else if (call.empty()) {
            cout << "\nEnter the number of the map you want to select: ";
        }
        cin >> choice;
        // Clear the newline character after the number, and handle invalid input
        if (cin.fail()) {
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the line
            cout << "Invalid input. Please enter a number.\n";
            continue; // Skip the rest of the loop and prompt again
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Always clear the newline character

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
                cout << "Failed to load the selected map.\n";
                return nullptr;
            }
        }
        else {
            cout << "Invalid selection.\n";
            return nullptr;
        }
    }
}

Campaign* Editor::selectCampaign() {
    std::string directoryPath = "./data/campaigns/"; // Path to your campaigns directory
    std::vector<std::filesystem::path> campaignDirectories;

    // Read the directory and collect campaign directories
    for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
        if (entry.is_directory()) {
            campaignDirectories.push_back(entry.path());
        }
    }

    if (campaignDirectories.empty()) {
        std::cout << "No campaign directories available.\n";
        return nullptr;
    }

    std::cout << "Available Campaigns:\n";
    for (size_t i = 0; i < campaignDirectories.size(); ++i) {
        std::cout << i + 1 << ": " << campaignDirectories[i].filename() << "\n";
    }

    int choice;
    std::cout << "\nEnter the number of the campaign you want to select: ";
    std::cin >> choice;
    if (std::cin.fail() || choice <= 0 || static_cast<size_t>(choice) > campaignDirectories.size()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number.\n";
        return nullptr;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the newline character

    // Construct the .txt file path inside the selected campaign directory
    std::filesystem::path selectedCampaignPath = campaignDirectories[choice - 1] / (campaignDirectories[choice - 1].filename().string() + ".txt");

    // Load the selected campaign
    Campaign* selectedCampaign = new Campaign(campaignDirectories[choice - 1].filename().string()); // Assuming Campaign constructor takes name
    if (!selectedCampaign->loadFromFile(selectedCampaignPath.string())) { // Assuming Campaign has loadFromFile that takes the full path
        delete selectedCampaign;
        std::cout << "Failed to load the selected campaign.\n";
        return nullptr;
    }

    return selectedCampaign;
}

int Editor::countMapFiles(const string& directoryPath) {
    using namespace filesystem;
    int fileCount = 0;
    for (const auto& entry : directory_iterator(directoryPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            ++fileCount;
        }
    }
    return fileCount;
}

// Implement other methods as needed
