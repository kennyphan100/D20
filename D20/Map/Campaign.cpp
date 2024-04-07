//! @file 
//! @brief Implementation file for Campaign.h
//!

#include "Campaign.h"
#include "Map.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <filesystem>

using namespace std;

//! Constructor for Campaign class.
//! Initializes the campaign with the default name "Unnamed Campaign"
Campaign::Campaign() : name("Unnamed Campaign") {}

//! Constructor for Campaign class with a specified name.
//! @param newName The name of the campaign.
Campaign::Campaign(const string& newName) : name(newName) {}

//! Retrieves the name of the campaign.
//! @return The name of the campaign.
string Campaign::getName() const {
    return name;
}

//! Adds a map to the campaign.
//! @param mapName The name of the map to be added.
//! @param campaignDir The directory path of the campaign.
void Campaign::addMap(const string& mapName, const string& campaignDir) {
    filesystem::path dirPath(campaignDir);
    filesystem::path mapCopyFilePath = dirPath / "maps" / (mapName + ".txt");
    filesystem::path mapFilePath = "./data/maps/" + mapName + ".txt";

    if (find(maps.begin(), maps.end(), mapName) == maps.end()) {
        Map map;

        if (filesystem::exists(mapFilePath) && map.loadFromFile(mapFilePath.string())) {
            cout << "Loaded existing map: \"" << mapName << "\".\n";
        }
        else {
            cout << "New map created: \"" << mapName << "\".\n";
        }

        if (map.saveToFile(mapCopyFilePath.string())) {
            maps.push_back(mapName);
            cout << "Map \"" << mapName << "\" added and saved in the campaign \"" << name << "\".\n";
        }
        else {
            cerr << "Failed to save map \"" << mapName << "\".\n";
        }
    }
    else {
        cout << "Map \"" << mapName << "\" is already in the campaign \"" << name << "\".\n";
    }
}

//! Removes a map from the campaign.
//! @param mapName The name of the map to be removed.
//! @param campaignDir The directory path of the campaign.
void Campaign::removeMap(const string& mapName, const string& campaignDir) {
    filesystem::path dirPath(campaignDir);
    filesystem::path mapFilePath = dirPath / "maps" / (mapName + ".txt");

    auto it = find(maps.begin(), maps.end(), mapName);
    if (it != maps.end()) {
        maps.erase(it);
        cout << "Map \"" << mapName << "\" removed from the campaign \"" << name << "\".\n";

        try {
            if (filesystem::exists(mapFilePath) && filesystem::remove(mapFilePath)) {
                cout << "Map file for \"" << mapName << "\" deleted successfully.\n";
            }
            else {
                cout << "Map file for \"" << mapName << "\" was not found or couldn't be deleted.\n";
            }
        }
        catch (const filesystem::filesystem_error& e) {
            cerr << "Error deleting map file: " << e.what() << '\n';
        }
    }
    else {
        cout << "Map \"" << mapName << "\" is not in the campaign \"" << name << "\".\n";
    }
}

//! Connects two maps within the campaign.
//! @param fromMapName The name of the map from which the connection starts.
//! @param toMapName The name of the map to which the connection points.
void Campaign::connectMaps(const string& fromMapName, const string& toMapName) {
    if (find(maps.begin(), maps.end(), fromMapName) != maps.end() &&
        find(maps.begin(), maps.end(), toMapName) != maps.end()) {
        connections[fromMapName].push_back(toMapName);
        cout << "Connected \"" << fromMapName << "\" to \"" << toMapName << "\" within the campaign \"" << name << "\".\n";
    }
    else {
        cerr << "One or both maps are not in the campaign \"" << name << "\". Connection failed.\n";
    }
}

//! Saves the campaign data to a file.
//! @param filename The name of the file to save the campaign data.
//! @return True if the save operation was successful, false otherwise.
bool Campaign::saveToFile(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file \"" << filename << "\" for writing.\n";
        return false;
    }

    file << "Campaign Name: " << name << "\n";

    file << "Maps:\n";
    for (const auto& mapName : maps) {
        file << mapName << "\n";
    }
    file << "\n";

    file << "Connections:\n";
    for (const auto& [fromMap, toMaps] : connections) {
        for (const auto& toMap : toMaps) {
            file << fromMap << " -> " << toMap << "\n";
        }
    }

    file.close();
    return true;
}

//! Loads campaign data from a file.
//! @param filename The name of the file containing campaign data.
//! @return True if the load operation was successful, false otherwise.
bool Campaign::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return false;
    }

    string line2;
    if (getline(file, line2)) {
        string prefix = "Campaign Name: ";
        size_t prefixPosition = line2.find(prefix);
        if (prefixPosition != string::npos) {
            name = line2.substr(prefixPosition + prefix.length());
        }
    }

    string line;
    while (getline(file, line) && line != "Maps:") {} 

    while (getline(file, line) && line != "Connections:") { 
        if (!line.empty()) {
            maps.push_back(line);
        }
    }

    while (getline(file, line)) {
        if (!line.empty()) {
            istringstream iss(line);
            string from, arrow, to;
            if (iss >> from >> arrow >> to) { 
                connections[from].push_back(to);
            }
        }
    }
    return true;
}

//! Displays information about the campaign, including maps and connections.
void Campaign::display() const {
    cout << name << "\nMaps:\n";
    for (const auto& mapName : maps) {
        cout << "  " << mapName << "\n";
    }
    cout << "Connections:\n";
    for (const auto& [from, toList] : connections) {
        for (const auto& to : toList) {
            cout << "  " << from << " -> " << to << "\n";
        }
    }
}

//! Returns connection given a key
vector<string> Campaign::getConnectedMap(const string& mapKey) {
    auto it = connections.find(mapKey);
    if (it != connections.end()) {
        return it->second;
    }
    return {}; // Return empty vector if mapKey is not found
}



