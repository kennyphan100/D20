#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "MenuState.h"
#include "Object.h"
#include "../Character/Character.h"
#include "../Character/FighterCharacter.h"
#include "../Map/Campaign.h"

using namespace std;

class PlayGame {
public:
    enum ActiveInputField { NAME, LEVEL };

    PlayGame(sf::RenderWindow& window);

    void handlePlayGameClick(int mouseX, int mouseY, Character* character, Campaign* campaign, Map*& map, string& mapName, vector<string>& listOfMaps, FighterCharacter*& aggresorCharacter);
    void handleCharacterCreationClick(int mouseX, int mouseY);
    void handleTextInput(sf::Uint32 unicode);
    void drawMainMenu(sf::RenderWindow& window);
    void drawPlayGame(string mapName, string campaignName);
    void drawObjects(std::vector<Object> objects2);
    void drawObjectsStatic(std::vector<Object> objects2);

    void handleAggressorTurn(Character* character, Map*& map);

    void drawGrid(sf::RenderWindow& window);
    void drawSelectedMapGrid(string selectedMap);
    void drawSelectedMapGrid(Map* selectedMap);
    void drawSelectedMapGridStatic(string selectedMap);

    bool isXYInObjects(int x, int y);
    bool XYPositionIsChest(int x, int y);
    bool XYPositionIsAggressor(int x, int y);
    bool XYPositionIsDoor(int x, int y);
    void removeObject(std::vector<Object>& objects, int x, int y);

    std::vector<Object> objects;


    sf::Text inventoryText;
    void drawInventoryGrid(sf::RenderWindow& window);
    void drawInventoryTitle(sf::RenderWindow& window);

    int characterPositionX = 0;
    int characterPositionY = 0;

    int aggressorPositionX = 8;
    int aggressorPositionY = 8;
    bool isAggressorDead = false;

    ObjectType selectedObjectType = ObjectType::None;
    sf::Texture characterTexture;
    sf::Texture aggressorTexture;
    sf::Texture wallTexture;
    sf::Texture chestTexture;
    sf::Texture doorTexture;

    sf::Text campaignLabel;
    sf::Text campaignNameLabel;
    sf::Text mapNameLabel;
    sf::Text winLabel;
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

    string selectedMap;

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
    bool wonTheGame = false;
    int currentMapIndex = 0;
    int numberOfMapsInCampaign = 0;

    ActiveInputField activeField;
};
