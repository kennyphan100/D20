#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class CampaignCreation {
public:
    enum ActiveInputField { CREATE, NAME };
    CampaignCreation(sf::RenderWindow& window);

    void handleMainMenuClick(int mouseX, int mouseY);
    void handleCampaignCreationClick(int mouseX, int mouseY);
    void handleTextInput(sf::Uint32 unicode);
    void drawMainMenu(sf::RenderWindow& window);
    void drawCampaignCreation();
    bool isPrintableAscii(sf::Uint32 unicode);
    ActiveInputField getActiveField() const;

    sf::Text nameLabel;
    sf::Text nameValue;
    sf::RectangleShape nameInputBackground;
    sf::Text mapLabel;
    sf::RectangleShape createCampaignButton;
    sf::Text createCampaignButtonText;
    sf::Text alertTextSuccess;
    sf::Text alertTextFailure;

private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text backButton;
    bool showSuccessfulAlert;
    bool showFailureAlert;
    string inputName;
    ActiveInputField activeField;
    sf::Vector2f mapListStartPosition{ 50, 200 }; // Starting position of the map list
    float mapListItemSpacing = 30.0f;
    vector<string> mapFiles;
    vector<bool> mapSelections;

    void loadMapFiles(const string& directoryPath);
    bool isClickOnMapList(int mouseX, int mouseY);
};


