#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "MenuState.h"
#include "Object.h"
#include "../Character/Character.h"

using namespace std;

class PlayGame {
public:
    enum ActiveInputField { NAME, LEVEL };

    PlayGame(sf::RenderWindow& window);

    void handlePlayGameClick(int mouseX, int mouseY, Character* character);
    void handleCharacterCreationClick(int mouseX, int mouseY);
    void handleTextInput(sf::Uint32 unicode);
    void drawMainMenu(sf::RenderWindow& window);
    void drawPlayGame();

    void drawGrid(sf::RenderWindow& window);
    void drawSelectedMapGrid(string selectedMap);

    std::vector<Object> objects;

    sf::Text titleLabel;
    sf::RectangleShape dropdownButton;
    sf::Text dropdownText;
    sf::Text alertText;

    sf::RectangleShape startGameButtonBackground;
    sf::Text startGameButtonText;

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

    int GRID_WIDTH = 10;
    int GRID_HEIGHT = 10;

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
