#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class PlayGameMenu {
public:
    enum ActiveInputField { NAME, LEVEL };

    PlayGameMenu(sf::RenderWindow& window);

    void handlePlayGameMenuClick(int mouseX, int mouseY);
    void handleCharacterCreationClick(int mouseX, int mouseY);
    void handleTextInput(sf::Uint32 unicode);
    void drawMainMenu(sf::RenderWindow& window);
    void drawPlayGameMenu();

    bool isClickOnCharacterList(int mouseX, int mouseY);
    void loadCharacterFiles(const string& directoryPath);

    bool isClickOnCampaignList(int mouseX, int mouseY);
    void loadCampaignFiles(const string& directoryPath);

    sf::Text characterLabel;

    sf::Text campaignLabel;

    sf::RectangleShape startGameButton;

    sf::Text startGameButtonText;

    sf::RectangleShape dropdownButton;

    sf::Text dropdownText;

    sf::Text alertText;

    sf::Vector2f characterListStartPosition{ 200, 130 };
    float characterListItemSpacing = 30.0f;
    vector<string> characterFiles;
    vector<bool> characterSelection;
    string selectedCharacter;

    sf::Vector2f campaignListStartPosition{ 700, 130 };
    float campaignListItemSpacing = 30.0f;
    vector<string> campaignFiles;
    vector<bool> campaignSelection;
    string selectedCampaign;

private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Texture worldBackgroundTex;
    sf::Sprite worldBackground;
    sf::Text backButton;

    bool dropdownOpen;
    bool showSuccessfulAlert;

    ActiveInputField activeField;
};
