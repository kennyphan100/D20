// Campaign.h
#include "Campaign.h"
#include "Map.h"
#include <algorithm> // For std::find_if and std::remove
#include <iostream>  // For std::cout and std::cerr
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <filesystem>

using namespace std;

Campaign::Campaign() : name("Unnamed Campaign") {}

// Constructor with name parameter
Campaign::Campaign(const std::string& newName) : name(newName) {
    // Here, you're simply initializing the name of the campaign.
    // The maps vector is automatically initialized to be empty.
    // The connections map is also initialized to be empty.
}

string Campaign::getName() const {
    return name;
}

//void Campaign::addMap(const std::string& mapName, const string& filename) {
//    // Check if the map is already in the campaign
//    if (std::find(maps.begin(), maps.end(), mapName) == maps.end()) {
//        maps.push_back(mapName); // Add the map if it's not already present
//        std::cout << "Map \"" << mapName << "\" added to the campaign \"" << name << "\".\n";
//    }
//    else {
//        std::cout << "Map \"" << mapName << "\" is already in the campaign \"" << name << "\".\n";
//    }
//}

void Campaign::addMap(const std::string& mapName, const std::string& campaignDir) {
    std::filesystem::path dirPath(campaignDir);
    std::filesystem::path mapCopyFilePath = dirPath / "maps" / (mapName + ".txt");
    std::filesystem::path mapFilePath = "./data/maps/" + mapName + ".txt";

    // Check if the map is already part of the campaign
    if (std::find(maps.begin(), maps.end(), mapName) == maps.end()) {
        Map map;

        if (std::filesystem::exists(mapFilePath) && map.loadFromFile(mapFilePath.string())) {
            std::cout << "Loaded existing map: \"" << mapName << "\".\n";
        }
        else {
            std::cout << "New map created: \"" << mapName << "\".\n";
        }

        if (map.saveToFile(mapCopyFilePath.string())) {
            maps.push_back(mapName);
            std::cout << "Map \"" << mapName << "\" added and saved in the campaign \"" << name << "\".\n";
        }
        else {
            std::cerr << "Failed to save map \"" << mapName << "\".\n";
        }
    }
    else {
        std::cout << "Map \"" << mapName << "\" is already in the campaign \"" << name << "\".\n";
    }
}

void Campaign::removeMap(const std::string& mapName, const std::string& campaignDir) {
    // Construct the full path for the map file in the campaign directory
    std::filesystem::path dirPath(campaignDir);
    std::filesystem::path mapFilePath = dirPath / "maps" / (mapName + ".txt");

    // Check if the map is part of the campaign
    auto it = std::find(maps.begin(), maps.end(), mapName);
    if (it != maps.end()) {
        // Remove the map name from the list
        maps.erase(it);
        std::cout << "Map \"" << mapName << "\" removed from the campaign \"" << name << "\".\n";

        // Optionally delete the map file from the filesystem
        try {
            if (std::filesystem::exists(mapFilePath) && std::filesystem::remove(mapFilePath)) {
                std::cout << "Map file for \"" << mapName << "\" deleted successfully.\n";
            }
            else {
                std::cout << "Map file for \"" << mapName << "\" was not found or couldn't be deleted.\n";
            }
        }
        catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "Error deleting map file: " << e.what() << '\n';
        }
    }
    else {
        std::cout << "Map \"" << mapName << "\" is not in the campaign \"" << name << "\".\n";
    }
}

// Connect Maps within Campaign
void Campaign::connectMaps(const std::string& fromMapName, const std::string& toMapName) {
    // Check if both maps exist in the campaign
    if (std::find(maps.begin(), maps.end(), fromMapName) != maps.end() &&
        std::find(maps.begin(), maps.end(), toMapName) != maps.end()) {
        // Add the connection
        connections[fromMapName].push_back(toMapName);
        std::cout << "Connected \"" << fromMapName << "\" to \"" << toMapName << "\" within the campaign \"" << name << "\".\n";
    }
    else {
        // If either map doesn't exist in the campaign, display an error message
        std::cerr << "One or both maps are not in the campaign \"" << name << "\". Connection failed.\n";
    }
}

// Get Connections of a Map
std::vector<std::string> Campaign::getConnections(const std::string& mapName) const {
    auto it = connections.find(mapName);
    if (it != connections.end()) {
        return it->second;  // Return the list of connections
    }
    else {
        return {};  // Return an empty vector if no connections found
    }
}

bool Campaign::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file \"" << filename << "\" for writing.\n";
        return false;
    }

    // Write campaign name and description
    file << "Campaign Name: " << name << "\n";

    // Write the list of maps
    file << "Maps:\n";
    for (const auto& mapName : maps) {
        file << mapName << "\n";
    }
    file << "\n"; // Extra newline to separate sections

    // Write connections
    file << "Connections:\n";
    for (const auto& [fromMap, toMaps] : connections) {
        for (const auto& toMap : toMaps) {
            file << fromMap << " -> " << toMap << "\n";
        }
    }

    file.close();
    return true; // Indicate successful saving
}

bool Campaign::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }

    //// Assuming the first line is the campaign name
    //std::getline(file, name);

    std::string line2;
    // Assuming the first line is the campaign name in the format "Campaign Name: XYZ"
    if (std::getline(file, line2)) {
        std::string prefix = "Campaign Name: ";
        size_t prefixPosition = line2.find(prefix);
        if (prefixPosition != std::string::npos) {
            // Remove the prefix to extract just the campaign name
            name = line2.substr(prefixPosition + prefix.length());
        }
    }

    // The second line is the campaign description

    // Read maps, assuming a delimiter like "Maps:" indicates the start
    std::string line;
    while (std::getline(file, line) && line != "Maps:") {} // Skip until maps section

    while (std::getline(file, line) && line != "Connections:") { // Now reading map names
        if (!line.empty()) {
            maps.push_back(line); // Add each map name to the vector
        }
    }

    // Reading connections, assuming format "Map1 -> Map2"
    while (std::getline(file, line)) {
        if (!line.empty()) {
            std::istringstream iss(line);
            std::string from, arrow, to;
            if (iss >> from >> arrow >> to) { // Parses "from -> to"
                connections[from].push_back(to); // Add the connection
            }
        }
    }

    return true; // Successfully loaded
}

void Campaign::display() const {
    std::cout << name << "\nMaps:\n";
    for (const auto& mapName : maps) {
        std::cout << "  " << mapName << "\n";
    }
    std::cout << "Connections:\n";
    for (const auto& [from, toList] : connections) {
        for (const auto& to : toList) {
            std::cout << "  " << from << " -> " << to << "\n";
        }
    }
}



