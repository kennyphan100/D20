//! @file 
//! @brief Implementation file for Editor.h
//!

#include "Editor.h"
#include "../Character/Character.h"
#include "Campaign.h"
#include "../Item/Item.h"
#include "Map.h"
#include "../Character/CharacterObserver.h"
#include <iostream>
#include <string>
#include <cppunit/CompilerOutputter.h>
#include <filesystem>
#include "MapObserver.h"
#include "../GUI/MapEdit.h"

using namespace std;

//! Constructor for Editor class.
Editor::Editor() {
}

//! @brief Run the map editor.
//! 
//! This function provides a menu-driven interface for creating, editing maps, creating and editing campaigns, and exiting the editor.
//! 
//! @return False if the user chooses to exit the editor, true otherwise.
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

//! @brief Creates a new map.
//! 
//! This function guides the user through the process of creating a new map, setting
void Editor::createMap() {
    try {
        int width;
        int height;
        string name, filePath;
        const string directoryPath = "./data/maps/";

        while (true) {
            cout << "\nPlease enter the name of the map: ";
            getline(cin, name);
            filePath = directoryPath + name + ".txt";

            if (filesystem::exists(filePath)) {
                cerr << "A map with this name already exists. Please choose a different name.\n";
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

        MapObserver* mo = new MapObserver(&myMap);

        myMap.setCell(0, 0, Cell::START);
        myMap.setCell(width - 1, height - 1, Cell::FINISH);

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

        if (myMap.verifyMap()) {
            cout << "\nA path exists from start to finish." << endl;
            maps.push_back(myMap);

            string filename = "./data/maps/" + name + ".txt";

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

//! @brief Edits an existing map.
//! 
//! This function allows the user to select an existing map and edit its contents by 
void Editor::editMap() {
    Map* selectedMap = selectMap();
    if (selectedMap) {
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

//! @brief Create a new campaign.
//! 
//! This function prompts the user to enter the name of a new campaign, creates the necessary directories,
//! and saves campaign information to a file.
void Editor::createCampaign() {
    string campaignName;
    filesystem::path dirPathCampaign, dirPathMapsInCampaign, infoFilePath;

    while (true) {
        cout << "Enter the name of the new campaign: ";
        getline(cin, campaignName);

        dirPathCampaign = filesystem::current_path() / "data" / "campaigns" / campaignName;
        dirPathMapsInCampaign = filesystem::current_path() / "data" / "campaigns" / campaignName / "maps";

        if (filesystem::exists(dirPathCampaign)) {
            cerr << "A campaign with the name \"" << campaignName << "\" already exists. Please try a different name.\n";
            continue; 
        }
        else {
            break;
        }
    }

    if (!filesystem::create_directories(dirPathCampaign)) {
        cerr << "Failed to create directory for the campaign \"" << campaignName << "\".\n";
        return;
    }

    if (!filesystem::create_directories(dirPathMapsInCampaign)) {
        cerr << "Failed to create directory for the maps in \"" << campaignName << "\".\n";
        return;
    }

    infoFilePath = dirPathCampaign / (campaignName + ".txt");

    Campaign newCampaign(campaignName);

    if (newCampaign.saveToFile(infoFilePath.string())) {
        cout << "Campaign \"" << campaignName << "\" created and saved successfully.\n\n";
    }
    else {
        cerr << "Failed to save the campaign \"" << campaignName << "\".\n\n";
    }
}

//! @brief Edit an existing campaign.
//! 
//! This function allows the user to edit an existing campaign by adding or removing maps, connecting maps,
//! and saving the changes.
void Editor::editCampaign() {
    Campaign* selectedCampaign = selectCampaign();

    if (!selectedCampaign) {
        cout << "Campaign selection cancelled or invalid.\n";
        return;
    }

    bool editing = true;
    string campaignName = selectedCampaign->getName();
    while (editing) {
        cout << "\nEditing Campaign => " << campaignName << "\n";
        selectedCampaign->display();
        cout << "\n1. Add Map\n"
            << "2. Remove Map\n"
            << "3. Connect Maps\n"
            << "4. Save and Exit\n"
            << "Enter your choice: ";
        int choice;
        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1: {
            Map* newMap = selectMap();
            if (newMap) {
                selectedCampaign->addMap(newMap->getName(), "./data/campaigns/" + campaignName);
            }
            break;
        }
        case 2: {
            Map* mapToRemove = selectMapInCampaign(selectedCampaign->getName(), "");
            if (mapToRemove) {
                selectedCampaign->removeMap(mapToRemove->getName(), "./data/campaigns/" + campaignName);
            }
            else {
                cout << "Map selection cancelled or invalid.\n";
            }
            break;
        }
        case 3: {
            Map* fromMap = selectMapInCampaign(selectedCampaign->getName(), "from");
            if (!fromMap) {
                cout << "Invalid selection for the 'from' map.\n";
                break;
            }

            Map* toMap = selectMapInCampaign(selectedCampaign->getName(), "to");
            if (!toMap) {
                cout << "Invalid selection for the 'to' map.\n";
                break;
            }

            if (fromMap->getName() == toMap->getName()) {
                cout << "The 'from' map and 'to' map cannot be the same. Please select different maps.\n";
            }
            else {
                selectedCampaign->connectMaps(fromMap->getName(), toMap->getName());
                cout << "Maps successfully connected: " << fromMap->getName() << " -> " << toMap->getName() << "\n";
            }
            break;
        }
        case 4: {
            editing = false;
            break;
        }
        default: {
            cout << "Invalid choice. Please enter a valid option.\n";
            break;
        }
        }
    }

    filesystem::path dirPath, infoFilePath;
    dirPath = filesystem::current_path() / "data" / "campaigns" / campaignName;
    infoFilePath = dirPath / (campaignName + ".txt");
    if (selectedCampaign->saveToFile(infoFilePath.string())) {
        cout << "Campaign \"" << campaignName << "\" has been successfully saved to \"" << infoFilePath << "\".\n";
    }
    else {
        cerr << "Failed to save the campaign \"" << campaignName << "\".\n";
    }

    delete selectedCampaign;
}

//! @brief Display all available maps.
//! 
//! This function lists all map files present in the maps directory.
void Editor::displayAllMaps() {
    string directoryPath = "./data/maps";
    int index = 1;

    cout << "Available Maps:\n";

    try {
        for (const auto& entry : filesystem::directory_iterator(directoryPath)) {
            if (entry.is_regular_file()) {
                auto filePath = entry.path();
                auto extension = filePath.extension().string();

                if (extension == ".txt") {
                    cout << index++ << ": " << filePath.stem() << " (" << filePath << ")\n";
                }
            }
        }

        if (index == 1) {
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

//! @brief Display all maps in a specific campaign.
//! 
//! This function lists all map files present in the specified campaign's maps directory.
//! 
//! @param campaignName The name of the campaign.
void Editor::displayAllMapsInCampaign(const string& campaignName) {
    string directoryPath = "./data/campaigns/" + campaignName + "/maps"; 
    int index = 1; 

    cout << "Available Maps:\n";

    try {
        for (const auto& entry : filesystem::directory_iterator(directoryPath)) {
            if (entry.is_regular_file()) {
                auto filePath = entry.path();
                auto extension = filePath.extension().string();

                if (extension == ".txt") {
                    cout << index++ << ": " << filePath.stem() << " (" << filePath << ")\n";
                }
            }
        }

        if (index == 1) {
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

//! @brief Display all available campaigns.
//! 
//! This function lists all campaign directories present in the campaigns directory
void Editor::displayAllCampaigns() {
    string directoryPath = "./data/campaigns/";  
    int index = 1; 

cout << "Available Campaigns:\n";

try {
    for (const auto& entry : filesystem::directory_iterator(directoryPath)) {
        if (entry.is_directory()) {
            auto dirPath = entry.path();
            cout << index++ << ": " << dirPath.filename() << "\n";
        }
    }

    if (index == 1) {
        cout << "No campaign directories found in the directory.\n";
    }
}
catch (const filesystem::filesystem_error& e) {
    cerr << "Filesystem error: " << e.what() << '\n';
}
catch (const exception& e) {
    cerr << "General error: " << e.what() << '\n';
}
}

//! @brief Select a map from the available maps.
//! 
//! This function prompts the user to select a map from the available maps and loads the selected map.
//! 
//! @return A pointer to the selected map.
Map* Editor::selectMap() {
    string directoryPath = "./data/maps";
    vector<string> mapFiles;

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
        displayAllMaps();
        int choice;
        cout << "\nEnter the number of the map you want to select: ";
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice > 0 && static_cast<size_t>(choice) <= mapFiles.size()) {
            Map* selectedMap = new Map();
            if (selectedMap->loadFromFile(mapFiles[choice - 1])) {
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

Map* Editor::selectMapGUI(string mapName) {
    string directoryPath = "./data/maps";
    vector<string> mapFiles;

    for (const auto& entry : filesystem::directory_iterator(directoryPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            mapFiles.push_back(entry.path().string());
        }
    }

    if (mapFiles.empty()) {
        cout << "No map files available.\n";
        return nullptr;
    }

    displayAllMaps();

    Map* selectedMap = new Map();
    if (selectedMap->loadFromFile("./data/maps/" + mapName + ".txt")) {
        selectedMap->display();
        return selectedMap;
    }
    else {
        delete selectedMap;
        cout << "Failed to load the selected map.\n";
        return nullptr;
    }
    
}

//! @brief Select a map from a specific campaign.
//! 
//! This function prompts the user to select a map from the maps directory of the specified campaign
//! and loads the selected map.
//! 
//! @param campaignName The name of the campaign.
//! @param call A string indicating whether the selection is for 'from' or 'to' map in case of connecting maps.
//! @return A pointer to the selected map.
Map* Editor::selectMapInCampaign(const string& campaignName, const string& call) {
    string directoryPath = "./data/campaigns/" + campaignName + "/maps";
    vector<string> mapFiles;

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
        displayAllMapsInCampaign(campaignName);
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

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice > 0 && static_cast<size_t>(choice) <= mapFiles.size()) {
            Map* selectedMap = new Map();
            if (selectedMap->loadFromFile(mapFiles[choice - 1])) {
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

//! @brief Select a campaign to edit.
//! 
//! This function prompts the user to select a campaign from the available campaigns and loads the selected campaign.
//! 
//! @return A pointer to the selected campaign
Campaign* Editor::selectCampaign() {
    string directoryPath = "./data/campaigns/";
    vector<filesystem::path> campaignDirectories;

    for (const auto& entry : filesystem::directory_iterator(directoryPath)) {
        if (entry.is_directory()) {
            campaignDirectories.push_back(entry.path());
        }
    }

    if (campaignDirectories.empty()) {
        cout << "No campaign directories available.\n";
        return nullptr;
    }

    cout << "Available Campaigns:\n";
    for (size_t i = 0; i < campaignDirectories.size(); ++i) {
        cout << i + 1 << ": " << campaignDirectories[i].filename() << "\n";
    }

    int choice;
    cout << "\nEnter the number of the campaign you want to select: ";
    cin >> choice;
    if (cin.fail() || choice <= 0 || static_cast<size_t>(choice) > campaignDirectories.size()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number.\n";
        return nullptr;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    filesystem::path selectedCampaignPath = campaignDirectories[choice - 1] / (campaignDirectories[choice - 1].filename().string() + ".txt");

    Campaign* selectedCampaign = new Campaign(campaignDirectories[choice - 1].filename().string()); 
    if (!selectedCampaign->loadFromFile(selectedCampaignPath.string())) {
        delete selectedCampaign;
        cout << "Failed to load the selected campaign.\n";
        return nullptr;
    }

    return selectedCampaign;
}

//! @brief Count the number of map files in a directory.
//! 
//! This function counts the number of map files present in the specified directory.
//! 
//! @param directoryPath The path to the directory containing map files.
//! @return The count of map files.
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

void Editor::createMapGUI(string name, int width, int height) {
    string filePath;
    const string directoryPath = "./data/maps/";
    filePath = directoryPath + name + ".txt";
    if (filesystem::exists(filePath)) {
        throw std::runtime_error("A map with this name already exists. Please choose a different name.");
    }

    Map myMap(width, height, name);
    cout << "\n";

    MapObserver* mo = new MapObserver(&myMap);

    myMap.setCell(0, 0, Cell::START);
    myMap.setCell(width - 1, height - 1, Cell::FINISH);

    if (myMap.saveToFile(filePath)) {
        cout << "Map '" << name << "' has been successfully saved to '" << filePath << "'." << endl;
        int mapCount = countMapFiles("./data/maps/");
        cout << "The number of created maps is now: " << mapCount << endl;
    }
    else {
        cerr << "Failed to save the map '" << name << "' to a file.\n" << endl;
    }
}

void Editor::createCampaignGUI(string campaignName, std::vector<std::string> selectedMaps) {
    filesystem::path dirPathCampaign, dirPathMapsInCampaign, infoFilePath;

    dirPathCampaign = filesystem::current_path() / "data" / "campaigns" / campaignName;
    dirPathMapsInCampaign = filesystem::current_path() / "data" / "campaigns" / campaignName / "maps";

    if (filesystem::exists(dirPathCampaign)) {
        throw std::runtime_error("A campaign with this name already exists. Please choose a different name.");
    }

    if (!filesystem::create_directories(dirPathCampaign)) {
        cerr << "Failed to create directory for the campaign \"" << campaignName << "\".\n";
        return;
    }

    if (!filesystem::create_directories(dirPathMapsInCampaign)) {
        cerr << "Failed to create directory for the maps in \"" << campaignName << "\".\n";
        return;
    }

    infoFilePath = dirPathCampaign / (campaignName + ".txt");

    Campaign newCampaign(campaignName);

    if (newCampaign.saveToFile(infoFilePath.string())) {
        cout << "Campaign \"" << campaignName << "\" created and saved successfully.\n\n";
    }
    else {
        cerr << "Failed to save the campaign \"" << campaignName << "\".\n\n";
    }

    for (size_t i = 0; i < selectedMaps.size(); ++i) {
        cout << selectedMaps[i] << endl;
        newCampaign.addMap(selectedMaps[i], dirPathCampaign.string());
    }

    if (newCampaign.saveToFile(infoFilePath.string())) {
        cout << "Campaign \"" << campaignName << "\" created and saved successfully.\n\n";
    }
    else {
        cerr << "Failed to save the campaign \"" << campaignName << "\".\n\n";
    }
}

void Editor::editMapGUI(Map* selectedMap)
{
    if (selectedMap) {
        int width = selectedMap->getWidth();
        int height = selectedMap->getHeight();
        string name = selectedMap->getName();

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

