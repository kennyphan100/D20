#include "CampaignEdit.h"
#include "../Map/Map.h"
#include "../Map/Editor.h"
#include <filesystem>

namespace fs = std::filesystem;

CampaignEdit::CampaignEdit(sf::RenderWindow& window) : window(window), showSuccessfulAlert(false), showFailureAlert(false) {
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }

    if (!worldBackgroundTex.loadFromFile("./Images/mapbackground.jpg")) {
        cout << "ERROR: Game could not load background image" << "\n";
    }
    worldBackground.setScale(static_cast<float>(window.getSize().x) / worldBackgroundTex.getSize().x,
        static_cast<float>(window.getSize().y) / worldBackgroundTex.getSize().y);

    worldBackground.setTexture(worldBackgroundTex);

    backButton.setFont(font);
    backButton.setString("Go Back");
    backButton.setCharacterSize(24);
    backButton.setFillColor(sf::Color::Black);
    backButton.setPosition(25, 25);

    titleLabel.setFont(font);
    titleLabel.setString("Campaign Edit");
    titleLabel.setCharacterSize(40);
    titleLabel.setFillColor(sf::Color::Black);
    titleLabel.setStyle(sf::Text::Bold | sf::Text::Underlined);
    titleLabel.setPosition((window.getSize().x / 2 - titleLabel.getLocalBounds().width / 2), 25);

    editCampaignButton.setSize(sf::Vector2f(200, 50));
    editCampaignButton.setFillColor(sf::Color::Black);
    editCampaignButton.setPosition((window.getSize().x / 2 - editCampaignButton.getLocalBounds().width / 2), 550);

    editCampaignButtonText.setFont(font);
    editCampaignButtonText.setString("Save Campaign");
    editCampaignButtonText.setCharacterSize(24);
    editCampaignButtonText.setFillColor(sf::Color::White);
    editCampaignButtonText.setPosition((window.getSize().x / 2 - editCampaignButtonText.getLocalBounds().width / 2), 560);

    campaignLabel.setFont(font);
    campaignLabel.setString("Available Campaigns");
    campaignLabel.setCharacterSize(24);
    campaignLabel.setFillColor(sf::Color::Black);
    campaignLabel.setStyle(sf::Text::Underlined);
    campaignLabel.setPosition(250, 100);

    mapLabel.setFont(font);
    mapLabel.setString("Available Maps");
    mapLabel.setCharacterSize(24);
    mapLabel.setFillColor(sf::Color::Black);
    mapLabel.setStyle(sf::Text::Underlined);
    mapLabel.setPosition(780, 100);

    alertText.setFont(font);
    alertText.setString("Successfully edited campaign!");
    alertText.setCharacterSize(28);
    alertText.setFillColor(sf::Color::White); // Text color
    alertText.setPosition(window.getSize().x / 2 - alertText.getLocalBounds().width / 2, 620); // Adjust position as needed

}

void CampaignEdit::handleCampaignEditClick(int mouseX, int mouseY) {
    if (isClickOnCampaignList(mouseX, mouseY)) {
        // Determine which campaign was clicked
        int campaignIndex = static_cast<int>((mouseY - campaignListStartPosition.y) / campaignListItemSpacing);
        if (campaignIndex >= 0 && static_cast<size_t>(campaignIndex) < campaignFiles.size()) {
            std::fill(campaignSelections.begin(), campaignSelections.end(), false);
            campaignSelections[campaignIndex] = true;

            for (size_t i = 0; i < campaignSelections.size(); ++i) {
                if (campaignSelections[i]) {
                    selectedCampaign = campaignFiles[i];
                }
            }
            loadMapFiles("./data/campaigns", selectedCampaign);
        }
        showSuccessfulAlert = false;
    }
    else if (isClickOnMapList(mouseX, mouseY)) {
        // Determine which map was clicked
        int mapIndex = static_cast<int>((mouseY - mapListStartPosition.y) / mapListItemSpacing);
        if (mapIndex >= 0 && static_cast<size_t>(mapIndex) < mapFiles.size()) {
            // Toggle the selection state for the clicked map
            mapSelections[mapIndex] = !mapSelections[mapIndex];

            if (mapSelections[mapIndex]) {
                orders.push_back(mapIndex);
            }
            else {
                orders.pop_back();
            }
        }
    }
    else if (editCampaignButton.getGlobalBounds().contains(mouseX, mouseY)) {
        cout << "Editing campaign..." << endl;
        std::vector<std::string> selectedMaps;

        for (size_t i = 0; i < orders.size(); ++i) {

            selectedMaps.push_back(mapFiles[orders[i]]);
         
        }

        Editor* editor = new Editor();
        Campaign* campaignObject = editor->selectCampaignGUI(selectedCampaign);
        editor->editCampaignGUI(campaignObject, selectedMaps);

        showSuccessfulAlert = true;

    }
}

void CampaignEdit::drawCampaignEdit() {
    window.draw(worldBackground);
    window.draw(titleLabel);
    window.draw(backButton);
    window.draw(editCampaignButton);
    window.draw(editCampaignButtonText);
    window.draw(campaignLabel);
    window.draw(mapLabel);

    float currentMapYPosition = mapListStartPosition.y;
    float currentCampaignYPosition = campaignListStartPosition.y;

    loadCampaigns("./data/campaigns");
    campaignSelections.resize(campaignFiles.size(), false);
    mapSelections.resize(mapFiles.size(), false);

    for (size_t i = 0; i < campaignFiles.size(); ++i) {
        sf::Text campaignNameText;
        campaignNameText.setFont(font);
        campaignNameText.setString(to_string(i + 1) + ". " + campaignFiles[i]);
        campaignNameText.setCharacterSize(20);
        campaignNameText.setFillColor(campaignSelections[i] ? sf::Color::White : sf::Color::Black); // Highlight if selected
        campaignNameText.setPosition(campaignListStartPosition.x, currentCampaignYPosition);

        window.draw(campaignNameText);

        currentCampaignYPosition += campaignListItemSpacing;
    }

    if (!selectedCampaign.empty()) {
        for (size_t i = 0; i < mapFiles.size(); ++i) {
            sf::Text mapNameText;
            mapNameText.setFont(font);
            mapNameText.setString(to_string(i + 1) + ". " + mapFiles[i]);
            mapNameText.setCharacterSize(20);
            mapNameText.setFillColor(mapSelections[i] ? sf::Color::White : sf::Color::Black); // Highlight if selected
            mapNameText.setPosition(mapListStartPosition.x, currentMapYPosition);

            window.draw(mapNameText);

            currentMapYPosition += mapListItemSpacing;
        }
    }

    if (showSuccessfulAlert) {
        window.draw(alertText);
    }

}

void CampaignEdit::loadMapFiles(const string& directoryPath, const string& campaignName) {
    mapFiles.clear(); // Clear existing entries
    std::string campaignDirectoryPath = directoryPath + "/" + campaignName + "/maps";
    for (const auto& entry : fs::directory_iterator(campaignDirectoryPath)) {
        if (entry.is_regular_file()) {
            std::string filePath = entry.path().stem().string();
            // Optionally, filter only .txt files
            if (entry.path().extension() == ".txt") {
                mapFiles.push_back(filePath);
            }
        }
    }
}

void CampaignEdit::loadCampaigns(const std::string& directoryPath) {
    campaignFiles.clear(); // Clear existing entries

    // Iterate over all items in the directoryPath
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        // Check if the entry is a directory, which represents a campaign
        if (entry.is_directory()) {
            // Get the name of the campaign from the directory name
            std::string campaignName = entry.path().filename().string();
            // Add the campaign name to the vector of campaign names
            campaignFiles.push_back(campaignName);
        }
    }
}

bool CampaignEdit::isClickOnMapList(int mouseX, int mouseY) {
    // Assuming you have a defined area for the map list
    sf::FloatRect mapListArea(mapListStartPosition.x, mapListStartPosition.y, 300, mapFiles.size() * mapListItemSpacing); // Example dimensions
    return mapListArea.contains(static_cast<float>(mouseX), static_cast<float>(mouseY));
}

bool CampaignEdit::isClickOnCampaignList(int mouseX, int mouseY) {
    // Assuming you have a defined area for the map list
    sf::FloatRect campaignListArea(campaignListStartPosition.x, campaignListStartPosition.y, 300, campaignFiles.size() * campaignListItemSpacing); // Example dimensions
    return campaignListArea.contains(static_cast<float>(mouseX), static_cast<float>(mouseY));
}
