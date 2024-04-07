#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class CampaignEdit {
public:
    CampaignEdit(sf::RenderWindow& window);

    void handleCampaignEditClick(int mouseX, int mouseY);
    void drawCampaignEdit();
    void loadMapFiles(const string& directoryPath, const string& campaignName);
    void loadCampaigns(const string& directoryPath);
    bool isClickOnMapList(int mouseX, int mouseY);
    bool isClickOnCampaignList(int mouseX, int mouseY);

    sf::Text titleLabel;
    sf::RectangleShape editCampaignButton;
    sf::Text editCampaignButtonText;
    sf::Text mapLabel;
    sf::Text campaignLabel;
    sf::Text alertText;

    sf::Vector2f mapListStartPosition{ 780, 130 }; // Starting position of the map list
    float mapListItemSpacing = 30.0f;
    vector<string> mapFiles;
    vector<bool> mapSelections;

    sf::Vector2f campaignListStartPosition{ 250, 130 }; // Starting position of the campaign list
    float campaignListItemSpacing = 30.0f;
    vector<string> campaignFiles;
    vector<bool> campaignSelections;
    std::vector<int> orders;

private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Texture worldBackgroundTex;
    sf::Sprite worldBackground;
    sf::Text backButton;

    string selectedCampaign;
    bool showSuccessfulAlert;
    bool showFailureAlert;
};

