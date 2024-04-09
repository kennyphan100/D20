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
#include <set>
#include <unordered_set>

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
bool Campaign::saveToFile(const string& filename, const vector<string>& selectedMaps) {
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
    
    if (!selectedMaps.empty()) {
        file << "\n";
        file << "Connections Ordered:\n";
        for (auto mapName : selectedMaps) {
            file << mapName << "\n";
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

    while (getline(file, line) && line != "Connections Ordered:") {
        if (!line.empty()) {
            istringstream iss(line);
            string from, arrow, to;
            if (iss >> from >> arrow >> to) { 
                connections[from].push_back(to);
            }
        }
    }

    while (getline(file, line)) {
        if (!line.empty()) {
            connectionsOrdered.push_back(line);
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

void Campaign::display2() const {
    for (const auto& pair : connections) {
        // 'pair.first' is the key (a string)
        // 'pair.second' is the value (a vector<string>)
        std::cout << pair.first << " is connected to: ";
        for (const auto& connectedNode : pair.second) {
            // 'connectedNode' is each string in the vector<string>
            std::cout << connectedNode << " ";
        }
        std::cout << std::endl; // Newline for readability
    }
}

void Campaign::connectSequentialMaps(const std::vector<std::string>& selectedMaps) {
    for (auto i = 0; i < selectedMaps.size(); i++) {
        connectionsOrdered.push_back(selectedMaps[i]);
    }

    for (size_t i = 0; i < selectedMaps.size() - 1; ++i) {
        const auto& fromMapName = selectedMaps[i];
        const auto& toMapName = selectedMaps[i + 1];

        // Check if both maps exist in the campaign
        if (find(maps.begin(), maps.end(), fromMapName) != maps.end() &&
            find(maps.begin(), maps.end(), toMapName) != maps.end()) {

            // Add the connection only if it doesn't already exist
            if (find(connections[fromMapName].begin(), connections[fromMapName].end(), toMapName) == connections[fromMapName].end()) {
                connections[fromMapName].push_back(toMapName);
                cout << "Connected \"" << fromMapName << "\" to \"" << toMapName << "\" within the campaign \"" << name << "\".\n";
            }
        }
        else {
            cerr << "One or both maps named \"" << fromMapName << "\" and \"" << toMapName << "\" are not in the campaign \"" << name << "\". Connection failed.\n";
        }
    }
}

string Campaign::getFirstMap()
{
    auto it = connections.begin();
    if (it != connections.end()) {
        const auto& firstKey = it->first;
        const auto& firstVector = it->second;

        if (!firstVector.empty()) {
            const auto& firstElementOfVector = firstVector[0];
            cout << firstKey << endl;
            cout << firstElementOfVector << endl;
            return "\"" + firstKey + "\": \"" + firstElementOfVector + "\"";
        }
        else {
            return "The vector associated with the first key is empty.";
        }
    }
    else {
        return "The map is empty.";
    }
}

string Campaign::getAllMaps() {
    if (connections.empty()) {
        return "The map is empty.";
    }

    string result;
    for (const auto& pair : connections) {
        const auto& mapName = pair.first;
        const auto& connectedMaps = pair.second;

        result += mapName + " is connected to: ";
        if (!connectedMaps.empty()) {
            for (const auto& connectedMap : connectedMaps) {
                result += connectedMap + ", ";
            }
            // Remove the last ", " from the string
            result.pop_back(); // Removes the last space
            result.pop_back(); // Removes the last comma
        }
        else {
            result += "No connections";
        }
        result += ".\n"; // Add a newline for readability
    }
    return result;
}

pair<list<string>, string> Campaign::getMapsAndConnections() {
    set<string> uniqueMapNames; // Use a set to track unique names
    list<string> mapNames; // This will be our ordered list of unique map names
    string connectionsSummary;

    if (connections.empty()) {
        return make_pair(mapNames, "The map is empty.");
    }

    // First, add all source maps to the set of unique names
    for (const auto& pair : connections) {
        uniqueMapNames.insert(pair.first);
        for (const auto& connectedMap : pair.second) {
            uniqueMapNames.insert(connectedMap); // Also add destination maps
        }
    }

    // Now that we have all unique names, add them to the list for ordered access
    for (const auto& name : uniqueMapNames) {
        mapNames.push_back(name);
    }

    // Compile connections into a summary string
    for (const auto& pair : connections) {
        connectionsSummary += pair.first + " is connected to: ";
        for (const auto& connectedMap : pair.second) {
            connectionsSummary += connectedMap + ", ";
        }
        // Remove the trailing comma and space
        connectionsSummary.pop_back();
        connectionsSummary.pop_back();
        connectionsSummary += ".\n";
    }

    return make_pair(mapNames, connectionsSummary);

}

//! Returns connection given a key
vector<string> Campaign::getConnectedMap(const string& mapKey) {
    auto it = connections.find(mapKey);
    if (it != connections.end()) {
        return it->second;
    }
    return {}; // Return empty vector if mapKey is not found
}
