#include "PlayGameMenu.h"
#include <filesystem>
#include "../Map/Editor.h"

namespace fs = std::filesystem;

PlayGameMenu::PlayGameMenu(sf::RenderWindow& window) : window(window), dropdownOpen(false), characterSelected(false), campaignSelected(false) {
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

    characterLabel.setFont(font);
    characterLabel.setString("Select Character");
    characterLabel.setCharacterSize(36);
    characterLabel.setFillColor(sf::Color::Black);
    characterLabel.setStyle(sf::Text::Bold | sf::Text::Underlined);
    characterLabel.setPosition(200, 70);

    campaignLabel.setFont(font);
    campaignLabel.setString("Select Campaign");
    campaignLabel.setCharacterSize(36);
    campaignLabel.setFillColor(sf::Color::Black);
    campaignLabel.setStyle(sf::Text::Bold | sf::Text::Underlined);
    campaignLabel.setPosition(700, 70);

    startGameButtonBackground.setSize(sf::Vector2f(250, 50));
    startGameButtonBackground.setFillColor(sf::Color::Black);
    startGameButtonBackground.setPosition((window.getSize().x / 2 - startGameButtonBackground.getLocalBounds().width / 2), 500);

    startGameButtonText.setFont(font);
    startGameButtonText.setString("Play Game");
    startGameButtonText.setCharacterSize(24);
    startGameButtonText.setFillColor(sf::Color::White);
    startGameButtonText.setPosition((window.getSize().x / 2 - startGameButtonText.getLocalBounds().width / 2), 510);

    alertText.setFont(font);
    alertText.setString("You must select a character and a campaign!");
    alertText.setCharacterSize(24);
    alertText.setStyle(sf::Text::Bold);
    alertText.setFillColor(sf::Color(128, 0, 0)); // Text color
    alertText.setPosition(window.getSize().x / 2 - alertText.getLocalBounds().width / 2, 450); // Adjust position as needed
}

void PlayGameMenu::handlePlayGameMenuClick(int mouseX, int mouseY, MenuState& currentState) {
    // Handle clicks on main menu
    if (isClickOnCharacterList(mouseX, mouseY)) {
        characterSelected = true;
        // Determine which character was clicked
        int characterIndex = static_cast<int>((mouseY - characterListStartPosition.y) / characterListItemSpacing);
        if (characterIndex >= 0 && static_cast<size_t>(characterIndex) < characterFiles.size()) {
            std::fill(characterSelection.begin(), characterSelection.end(), false);
            characterSelection[characterIndex] = true;

            for (size_t i = 0; i < characterSelection.size(); ++i) {
                if (characterSelection[i]) {
                    //selectedMaps.push_back(mapFiles[i]);
                    selectedCharacter = characterFiles[i];
                    //cout << selectedCharacter << endl;

                    //Editor* editor = new Editor();
                    //Character* loadedCharacter = editor->selectCharacterGUI(selectedCharacter);
                    ////loadedCharacter->display();

                    //character = loadedCharacter;


                }
            }
        }
    }
    else if (isClickOnCampaignList(mouseX, mouseY)) {
        campaignSelected = true;
        // Determine which campaign was clicked
        int campaignIndex = static_cast<int>((mouseY - campaignListStartPosition.y) / campaignListItemSpacing);
        if (campaignIndex >= 0 && static_cast<size_t>(campaignIndex) < campaignFiles.size()) {
            std::fill(campaignSelection.begin(), campaignSelection.end(), false);
            campaignSelection[campaignIndex] = true;

            for (size_t i = 0; i < campaignSelection.size(); ++i) {
                if (campaignSelection[i]) {
                    //selectedMaps.push_back(mapFiles[i]);
                    selectedCampaign = campaignFiles[i];
                }
            }
        }
    }
    else if (startGameButtonBackground.getGlobalBounds().contains(mouseX, mouseY))
    {
        currentState = PLAY_GAME;
    }
}

void PlayGameMenu::handleCharacterCreationClick(int mouseX, int mouseY) {
    // Handle clicks on character creation screen
}

void PlayGameMenu::handleTextInput(sf::Uint32 unicode) {
}

void PlayGameMenu::drawMainMenu(sf::RenderWindow& window) {
    // Draw main menu
}

void PlayGameMenu::drawPlayGameMenu() {
    window.draw(worldBackground);
    window.draw(backButton);
    window.draw(characterLabel);
    window.draw(campaignLabel);

    window.draw(startGameButtonBackground);
    window.draw(startGameButtonText);

    if (characterSelected == false or campaignSelected == false) {
        window.draw(alertText);
    }

    float currentYPosition = characterListStartPosition.y;

    loadCharacterFiles("./data/characters");
    characterSelection.resize(characterFiles.size(), false);
    for (size_t i = 0; i < characterFiles.size(); ++i) {
        sf::Text characterNameText;
        characterNameText.setFont(font);
        characterNameText.setString(characterFiles[i]);
        characterNameText.setCharacterSize(20);
        characterNameText.setFillColor(characterSelection[i] ? sf::Color::White : sf::Color::Black); // Highlight if selected
        characterNameText.setPosition(characterListStartPosition.x, currentYPosition);

        window.draw(characterNameText);

        currentYPosition += characterListItemSpacing;
    }

    float currentYPosition2 = campaignListStartPosition.y;

    loadCampaignFiles("./data/campaigns");
    campaignSelection.resize(campaignFiles.size(), false);
    for (size_t i = 0; i < campaignFiles.size(); ++i) {
        sf::Text campaignNameText;
        campaignNameText.setFont(font);
        campaignNameText.setString(campaignFiles[i]);
        campaignNameText.setCharacterSize(20);
        campaignNameText.setFillColor(campaignSelection[i] ? sf::Color::White : sf::Color::Black); // Highlight if selected
        campaignNameText.setPosition(campaignListStartPosition.x, currentYPosition2);

        window.draw(campaignNameText);

        currentYPosition2 += campaignListItemSpacing;
    }

}

bool PlayGameMenu::isClickOnCharacterList(int mouseX, int mouseY) {
    // Assuming you have a defined area for the map list
    sf::FloatRect characterListArea(characterListStartPosition.x, characterListStartPosition.y, 300, characterFiles.size() * characterListItemSpacing); // Example dimensions
    return characterListArea.contains(static_cast<float>(mouseX), static_cast<float>(mouseY));
}

bool PlayGameMenu::isClickOnCampaignList(int mouseX, int mouseY) {
    // Assuming you have a defined area for the map list
    sf::FloatRect campaignListArea(campaignListStartPosition.x, campaignListStartPosition.y, 300, campaignFiles.size() * campaignListItemSpacing); // Example dimensions
    return campaignListArea.contains(static_cast<float>(mouseX), static_cast<float>(mouseY));
}


void PlayGameMenu::loadCharacterFiles(const string& directoryPath) {
    characterFiles.clear(); // Clear existing entries
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        if (entry.is_regular_file()) {
            std::string filePath = entry.path().stem().string();
            // Optionally, filter only .txt files
            if (entry.path().extension() == ".txt") {
                characterFiles.push_back(filePath);
            }
        }
    }
}

void PlayGameMenu::loadCampaignFiles(const string& directoryPath) {
    campaignFiles.clear(); // Clear existing entries
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        if (fs::is_directory(entry.path())) {
            //std::cout << entry.path().filename().string() << std::endl;
            campaignFiles.push_back(entry.path().stem().string());
        }
    }
}
