#include "CampaignCreation.h"
#include "../Map/Campaign.h"
#include "../Map/Editor.h"
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

CampaignCreation::CampaignCreation(sf::RenderWindow& window) : window(window), showSuccessfulAlert(false), showFailureAlert(false) {
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }

    backButton.setFont(font);
    backButton.setString("Go Back");
    backButton.setCharacterSize(24);
    backButton.setFillColor(sf::Color::Black);
    backButton.setPosition(25, 25);

    nameLabel.setFont(font);
    nameLabel.setString("Name:");
    nameLabel.setCharacterSize(24);
    nameLabel.setFillColor(sf::Color::Black);
    nameLabel.setPosition(50, 100);

    nameValue.setFont(font);
    nameValue.setString("");
    nameValue.setCharacterSize(24);
    nameValue.setFillColor(sf::Color::Black);
    nameValue.setPosition(nameInputBackground.getPosition().x + 160, 100);

    mapLabel.setFont(font);
    mapLabel.setString("Available Maps");
    mapLabel.setCharacterSize(24);
    mapLabel.setFillColor(sf::Color::Black);
    mapLabel.setPosition(50, 170);

    nameInputBackground.setSize(sf::Vector2f(200, 40));
    nameInputBackground.setFillColor(sf::Color::White);
    nameInputBackground.setPosition(150, 95);

    createCampaignButton.setSize(sf::Vector2f(245, 50));
    createCampaignButton.setFillColor(sf::Color::Black);
    createCampaignButton.setPosition(735, 500);

    createCampaignButtonText.setFont(font);
    createCampaignButtonText.setString("Create Campaign");
    createCampaignButtonText.setCharacterSize(24);
    createCampaignButtonText.setFillColor(sf::Color::White);
    createCampaignButtonText.setPosition(750, 510);

    alertTextSuccess.setFont(font);
    alertTextSuccess.setString("Successfully created campaign " + inputName + " !");
    alertTextSuccess.setCharacterSize(24);
    alertTextSuccess.setFillColor(sf::Color::Black); // Text color
    alertTextSuccess.setPosition(window.getSize().x / 2 - alertTextSuccess.getLocalBounds().width / 2, 500); // Adjust position as needed

    alertTextFailure.setFont(font);
    alertTextFailure.setString("The campaign with the name " + inputName + " already exists!");
    alertTextFailure.setCharacterSize(24);
    alertTextFailure.setFillColor(sf::Color::Black); // Text color
    alertTextFailure.setPosition(window.getSize().x / 2 - alertTextFailure.getLocalBounds().width / 2, 500); // Adjust position as needed

}

void CampaignCreation::handleMainMenuClick(int mouseX, int mouseY) {
    // Handle clicks on main menu
}

void CampaignCreation::handleCampaignCreationClick(int mouseX, int mouseY) {
    try {
        showSuccessfulAlert, showFailureAlert = false, false;
        sf::Vector2f mousePosF(static_cast<float>(mouseX), static_cast<float>(mouseY));
        if (nameInputBackground.getGlobalBounds().contains(mousePosF)) {
            activeField = NAME;
        }
        else if (isClickOnMapList(mouseX, mouseY)) {
            // Determine which map was clicked
            int mapIndex = static_cast<int>((mouseY - mapListStartPosition.y) / mapListItemSpacing);
            if (mapIndex >= 0 && static_cast<size_t>(mapIndex) < mapFiles.size()) {
                // Toggle the selection state for the clicked map
                mapSelections[mapIndex] = !mapSelections[mapIndex];
            }
        }
        else if (createCampaignButton.getGlobalBounds().contains(mouseX, mouseY)) {
            std::cout << "creating campaign..." << std::endl;
            cout << inputName << endl;
            std::vector<std::string> selectedMaps;
            for (size_t i = 0; i < mapSelections.size(); ++i) {
                if (mapSelections[i]) {
                    selectedMaps.push_back(mapFiles[i]);
                }
            }
            Editor* editor = new Editor();
            editor->createCampaignGUI(inputName, selectedMaps);
            showSuccessfulAlert = true;
        }
    }
    catch (const exception& e) {
        showFailureAlert = true;
        cerr << "A campaign with this name already exists. Please choose a different name." << endl;
    }
}

void CampaignCreation::handleTextInput(sf::Uint32 unicode) {
    if (activeField == NAME) {
        // Handle name input (similar to character creation)
        if (isPrintableAscii(unicode)) {
            if (unicode == 8 && inputName.size() > 0) { // Backspace pressed
                inputName.pop_back();
            }
            else if (unicode != 8) {
                inputName += static_cast<char>(unicode);
            }
            nameValue.setString(inputName);
        }
    }
}

void CampaignCreation::drawMainMenu(sf::RenderWindow& window) {
    // Draw main menu
}

void CampaignCreation::drawCampaignCreation() {
    // Draw character creation screen
    window.draw(nameInputBackground);
    window.draw(nameValue);
    window.draw(nameLabel);
    window.draw(mapLabel);

    window.draw(createCampaignButton);
    window.draw(createCampaignButtonText);
    window.draw(backButton);

    float currentYPosition = mapListStartPosition.y;

    //cout << currentYPosition << endl;
    loadMapFiles("./data/maps");
    mapSelections.resize(mapFiles.size(), false);
    //for (const auto& mapFileName : mapFiles) {
    //    sf::Text mapNameText;
    //    mapNameText.setFont(font); // Assuming `font` is accessible
    //    mapNameText.setString(mapFileName); // You might want to format or trim the filename
    //    mapNameText.setCharacterSize(20); // Choose an appropriate size
    //    mapNameText.setFillColor(sf::Color::Black);
    //    mapNameText.setPosition(mapListStartPosition.x, currentYPosition);
    //    window.draw(mapNameText);

    //    currentYPosition += mapListItemSpacing; // Move down for the next item
    //}

    for (size_t i = 0; i < mapFiles.size(); ++i) {
        sf::Text mapNameText;
        mapNameText.setFont(font);
        mapNameText.setString(mapFiles[i]);
        mapNameText.setCharacterSize(20);
        mapNameText.setFillColor(mapSelections[i] ? sf::Color::Red : sf::Color::Black); // Highlight if selected
        mapNameText.setPosition(mapListStartPosition.x, currentYPosition);

        window.draw(mapNameText);

        currentYPosition += mapListItemSpacing;
    }

    if (showFailureAlert) {
        window.draw(alertTextFailure);
    }
    else if (showSuccessfulAlert) {
        window.draw(alertTextSuccess);
    }
}

bool CampaignCreation::isPrintableAscii(sf::Uint32 unicode) {
    // Function to check if the unicode is a printable ASCII character
    return (unicode >= 32 && unicode <= 126) || unicode == 8;
}

CampaignCreation::ActiveInputField CampaignCreation::getActiveField() const
{
    return activeField;
}

void CampaignCreation::loadMapFiles(const string& directoryPath) {
    mapFiles.clear(); // Clear existing entries
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        if (entry.is_regular_file()) {
            std::string filePath = entry.path().stem().string();
            // Optionally, filter only .txt files
            if (entry.path().extension() == ".txt") {
                mapFiles.push_back(filePath);
            }
        }
    }
}

bool CampaignCreation::isClickOnMapList(int mouseX, int mouseY) {
    // Assuming you have a defined area for the map list
    sf::FloatRect mapListArea(mapListStartPosition.x, mapListStartPosition.y, 300, mapFiles.size() * mapListItemSpacing); // Example dimensions
    return mapListArea.contains(static_cast<float>(mouseX), static_cast<float>(mouseY));
}


