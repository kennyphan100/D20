#include "PlayGame.h"
#include <filesystem>
#include "../Map/Editor.h"

namespace fs = std::filesystem;

PlayGame::PlayGame(sf::RenderWindow& window) : window(window), dropdownOpen(false), showSuccessfulAlert(false) {
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }

    if (!worldBackgroundTex.loadFromFile("./Images/mapbackground.jpg")) {
        cout << "ERROR: Game could not load background image" << "\n";
    }
    worldBackground.setScale(static_cast<float>(window.getSize().x) / worldBackgroundTex.getSize().x,
        static_cast<float>(window.getSize().y) / worldBackgroundTex.getSize().y);

    worldBackground.setTexture(worldBackgroundTex);

    if (!characterTexture.loadFromFile("./Images/player_icon.png")) {
        // Handle error if texture loading fails
        cout << "ERROR: Game could not load icon" << "\n";
    }

    if (!wallTexture.loadFromFile("./Images/wall_icon.png")) {
        // Handle error if texture loading fails
        cout << "ERROR: Game could not load icon" << "\n";
    }

    if (!chestTexture.loadFromFile("./Images/treasure_icon.png")) {
        // Handle error if texture loading fails
        cout << "ERROR: Game could not load icon" << "\n";
    }

    if (!doorTexture.loadFromFile("./Images/door_icon.png")) {
        // Handle error if texture loading fails
        cout << "ERROR: Game could not load icon" << "\n";
    }

    backButton.setFont(font);
    backButton.setString("Go Back");
    backButton.setCharacterSize(24);
    backButton.setFillColor(sf::Color::Black);
    backButton.setPosition(25, 25);

    campaignLabel.setFont(font);
    campaignLabel.setString("Campaign:");
    campaignLabel.setCharacterSize(24);
    campaignLabel.setFillColor(sf::Color::Black);
    campaignLabel.setStyle(sf::Text::Underlined);
    campaignLabel.setPosition(20, 85);

    campaignNameLabel.setFont(font);
    campaignNameLabel.setString("");
    campaignNameLabel.setCharacterSize(24);
    campaignNameLabel.setFillColor(sf::Color::Black);
    campaignNameLabel.setPosition(165, 85);

    mapNameLabel.setFont(font);
    mapNameLabel.setString("");
    mapNameLabel.setCharacterSize(36);
    mapNameLabel.setFillColor(sf::Color::Black);
    mapNameLabel.setStyle(sf::Text::Bold | sf::Text::Underlined);
    mapNameLabel.setPosition((window.getSize().x / 2 - mapNameLabel.getLocalBounds().width / 2) - 120, 20);

    winLabel.setFont(font);
    winLabel.setString("You have reached the end of the campaign. YOU WIN!");
    winLabel.setCharacterSize(22);
    winLabel.setFillColor(sf::Color(50, 200, 50));
    winLabel.setStyle(sf::Text::Bold);
    winLabel.setPosition((window.getSize().x / 2 - winLabel.getLocalBounds().width / 2), 600);

    alertText.setFont(font);
    alertText.setString("You must select a character and a campaign!");
    alertText.setCharacterSize(24);
    alertText.setStyle(sf::Text::Bold);
    alertText.setFillColor(sf::Color::White); // Text color
    alertText.setPosition(window.getSize().x / 2 - alertText.getLocalBounds().width / 2, 570); // Adjust position as needed

    activeField = ActiveInputField::LEVEL;

    GRID_WIDTH = 10;
    GRID_HEIGHT = 10;

    const float INVENTORY_OFFSET_X = 900;
    const float INVENTORY_OFFSET_Y = 150;

    inventoryText.setFont(font); // Assuming 'font' is the font loaded in your constructor
    inventoryText.setString("Inventory Panel");
    inventoryText.setCharacterSize(24);
    inventoryText.setFillColor(sf::Color::Black);
    inventoryText.setPosition(INVENTORY_OFFSET_X, INVENTORY_OFFSET_Y - 40);
    window.draw(inventoryText);

}

void PlayGame::drawInventoryGrid(sf::RenderWindow& window) {
    sf::Color gridColor = sf::Color::Black; // Change grid color to black
    float lineThickness = 2.0f; // Adjust thickness as desired

    const int INVENTORY_GRID_WIDTH = 5;
    const int INVENTORY_GRID_HEIGHT = 5;
    const int INVENTORY_CELL_SIZE = 50; 
    const float INVENTORY_OFFSET_X = 900; 
    const float INVENTORY_OFFSET_Y = 150; 

    const float UNEQUIP_BUTTON_OFFSET_X = 900; // Same X offset as the inventory
    const float UNEQUIP_BUTTON_OFFSET_Y = INVENTORY_OFFSET_Y + (INVENTORY_GRID_HEIGHT * INVENTORY_CELL_SIZE) + 20; // Place it below the inventory
    const float UNEQUIP_BUTTON_WIDTH = 170;
    const float UNEQUIP_BUTTON_HEIGHT = 30;


    // Create the unequip helmet button
    sf::RectangleShape unequipHelmetButton(sf::Vector2f(UNEQUIP_BUTTON_WIDTH, UNEQUIP_BUTTON_HEIGHT));
    unequipHelmetButton.setPosition(UNEQUIP_BUTTON_OFFSET_X, UNEQUIP_BUTTON_OFFSET_Y);
    unequipHelmetButton.setFillColor(sf::Color::Black); // Adjust color as needed

    // Text for the button
    sf::Text buttonText("Unequip Helmet", font, 18);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(UNEQUIP_BUTTON_OFFSET_X, UNEQUIP_BUTTON_OFFSET_Y); // Adjust text position within the button

    // Draw the button and text
    window.draw(unequipHelmetButton);
    window.draw(buttonText);

    sf::RectangleShape unequipArmorButton(sf::Vector2f(UNEQUIP_BUTTON_WIDTH, UNEQUIP_BUTTON_HEIGHT));
    unequipArmorButton.setPosition(UNEQUIP_BUTTON_OFFSET_X, UNEQUIP_BUTTON_OFFSET_Y + UNEQUIP_BUTTON_HEIGHT + 5); // Place it below the helmet button
    unequipArmorButton.setFillColor(sf::Color::Black); // Adjust color as needed

    // Text for the button
    sf::Text armorButtonText("Unequip Armor", font, 18);
    armorButtonText.setFillColor(sf::Color::White);
    armorButtonText.setPosition(UNEQUIP_BUTTON_OFFSET_X, UNEQUIP_BUTTON_OFFSET_Y + UNEQUIP_BUTTON_HEIGHT + 5); // Adjust text position within the button

    // Draw the button and text
    window.draw(unequipArmorButton);
    window.draw(armorButtonText);

    sf::RectangleShape unequipShieldButton(sf::Vector2f(UNEQUIP_BUTTON_WIDTH, UNEQUIP_BUTTON_HEIGHT));
    unequipShieldButton.setPosition(UNEQUIP_BUTTON_OFFSET_X, UNEQUIP_BUTTON_OFFSET_Y + (UNEQUIP_BUTTON_HEIGHT + 5) * 2); // Place it below the armor button
    unequipShieldButton.setFillColor(sf::Color::Black); // Adjust color as needed

    // Text for the button
    sf::Text shieldButtonText("Unequip Shield", font, 18);
    shieldButtonText.setFillColor(sf::Color::White);
    shieldButtonText.setPosition(UNEQUIP_BUTTON_OFFSET_X, UNEQUIP_BUTTON_OFFSET_Y + (UNEQUIP_BUTTON_HEIGHT + 5) * 2); // Adjust text position within the button

    // Draw the button and text
    window.draw(unequipShieldButton);
    window.draw(shieldButtonText);

    sf::RectangleShape unequipRingButton(sf::Vector2f(UNEQUIP_BUTTON_WIDTH, UNEQUIP_BUTTON_HEIGHT));
    unequipRingButton.setPosition(UNEQUIP_BUTTON_OFFSET_X, UNEQUIP_BUTTON_OFFSET_Y + (UNEQUIP_BUTTON_HEIGHT + 5) * 3); // Place it below the shield button
    unequipRingButton.setFillColor(sf::Color::Black); // Adjust color as needed

    // Text for the button
    sf::Text ringButtonText("Unequip Ring", font, 18);
    ringButtonText.setFillColor(sf::Color::White);
    ringButtonText.setPosition(UNEQUIP_BUTTON_OFFSET_X, UNEQUIP_BUTTON_OFFSET_Y + (UNEQUIP_BUTTON_HEIGHT + 5) * 3); // Adjust text position within the button

    // Draw the button and text
    window.draw(unequipRingButton);
    window.draw(ringButtonText);

    sf::RectangleShape unequipBeltButton(sf::Vector2f(UNEQUIP_BUTTON_WIDTH, UNEQUIP_BUTTON_HEIGHT));
    unequipBeltButton.setPosition(UNEQUIP_BUTTON_OFFSET_X + UNEQUIP_BUTTON_WIDTH + 5, UNEQUIP_BUTTON_OFFSET_Y); // Place it to the right of the helmet button
    unequipBeltButton.setFillColor(sf::Color::Black); // Adjust color as needed

    // Text for the button
    sf::Text beltButtonText("Unequip Belt", font, 18);
    beltButtonText.setFillColor(sf::Color::White);
    beltButtonText.setPosition(UNEQUIP_BUTTON_OFFSET_X + UNEQUIP_BUTTON_WIDTH + 5, UNEQUIP_BUTTON_OFFSET_Y); // Adjust text position within the button

    // Draw the button and text
    window.draw(unequipBeltButton);
    window.draw(beltButtonText);

    sf::RectangleShape unequipWeaponButton(sf::Vector2f(UNEQUIP_BUTTON_WIDTH, UNEQUIP_BUTTON_HEIGHT));
    unequipWeaponButton.setPosition(UNEQUIP_BUTTON_OFFSET_X + UNEQUIP_BUTTON_WIDTH + 5, UNEQUIP_BUTTON_OFFSET_Y + UNEQUIP_BUTTON_HEIGHT + 5); // Place it under the belt button
    unequipWeaponButton.setFillColor(sf::Color::Black); // Adjust color as needed

    // Text for the button
    sf::Text weaponButtonText("Unequip Weapon", font, 18);
    weaponButtonText.setFillColor(sf::Color::White);
    weaponButtonText.setPosition(UNEQUIP_BUTTON_OFFSET_X + UNEQUIP_BUTTON_WIDTH + 5, UNEQUIP_BUTTON_OFFSET_Y + UNEQUIP_BUTTON_HEIGHT + 5); // Adjust text position within the button

    // Draw the button and text
    window.draw(unequipWeaponButton);
    window.draw(weaponButtonText);

    sf::RectangleShape unequipBootsButton(sf::Vector2f(UNEQUIP_BUTTON_WIDTH, UNEQUIP_BUTTON_HEIGHT));
    unequipBootsButton.setPosition(UNEQUIP_BUTTON_OFFSET_X + UNEQUIP_BUTTON_WIDTH + 5, UNEQUIP_BUTTON_OFFSET_Y + (UNEQUIP_BUTTON_HEIGHT + 5) * 2); // Place it under the weapon button
    unequipBootsButton.setFillColor(sf::Color::Black); // Adjust color as needed

    // Text for the button
    sf::Text bootsButtonText("Unequip Boots", font, 18);
    bootsButtonText.setFillColor(sf::Color::White);
    bootsButtonText.setPosition(UNEQUIP_BUTTON_OFFSET_X + UNEQUIP_BUTTON_WIDTH + 5, UNEQUIP_BUTTON_OFFSET_Y + (UNEQUIP_BUTTON_HEIGHT + 5) * 2); // Adjust text position within the button

    // Draw the button and text
    window.draw(unequipBootsButton);
    window.draw(bootsButtonText);

    sf::RectangleShape equipButton(sf::Vector2f(UNEQUIP_BUTTON_WIDTH, UNEQUIP_BUTTON_HEIGHT));
    equipButton.setPosition(UNEQUIP_BUTTON_OFFSET_X + UNEQUIP_BUTTON_WIDTH + 5, UNEQUIP_BUTTON_OFFSET_Y + (UNEQUIP_BUTTON_HEIGHT + 5) * 3); // Place it under the boots button
    equipButton.setFillColor(sf::Color::Green); // Adjust color as needed

    // Text for the button
    sf::Text equipButtonText("Equip", font, 18);
    equipButtonText.setFillColor(sf::Color::White);
    equipButtonText.setPosition(UNEQUIP_BUTTON_OFFSET_X + UNEQUIP_BUTTON_WIDTH + 5, UNEQUIP_BUTTON_OFFSET_Y + (UNEQUIP_BUTTON_HEIGHT + 5) * 3); // Adjust text position within the button

    // Draw the button and text
    window.draw(equipButton);
    window.draw(equipButtonText);

    // Draw vertical grid lines
    for (int i = 0; i <= INVENTORY_GRID_WIDTH; ++i) {
        sf::RectangleShape verticalLine(sf::Vector2f(lineThickness, INVENTORY_GRID_HEIGHT * INVENTORY_CELL_SIZE));
        verticalLine.setPosition(INVENTORY_OFFSET_X + i * INVENTORY_CELL_SIZE - lineThickness / 2.0f, INVENTORY_OFFSET_Y);
        verticalLine.setFillColor(gridColor);
        window.draw(verticalLine);
    }

    for (int j = 0; j <= INVENTORY_GRID_HEIGHT; ++j) {
        sf::RectangleShape horizontalLine(sf::Vector2f(INVENTORY_GRID_WIDTH * INVENTORY_CELL_SIZE, lineThickness));
        horizontalLine.setPosition(INVENTORY_OFFSET_X, INVENTORY_OFFSET_Y + j * INVENTORY_CELL_SIZE - lineThickness / 2.0f);
        horizontalLine.setFillColor(gridColor);
        window.draw(horizontalLine);
    }


    const std::string itemFolderPath = "./data/items/";
    int itemIndex = 0;

    for (const auto& entry : fs::directory_iterator(itemFolderPath)) {
        if (entry.is_regular_file()) { 
            std::string itemName = entry.path().stem().string(); 

            if (itemName.find("Helmet") != std::string::npos) {
                sf::Texture helmetTexture;
                if (helmetTexture.loadFromFile("./Images/helmet_game_icon.png")) {
                    sf::Sprite helmetSprite(helmetTexture);
                    const float cellSize = 50.0f; 
                    const float scale = cellSize / helmetTexture.getSize().x; 

                    helmetSprite.setScale(scale, scale);
                    helmetSprite.setPosition(INVENTORY_OFFSET_X + itemIndex % INVENTORY_GRID_WIDTH * INVENTORY_CELL_SIZE,
                        INVENTORY_OFFSET_Y + itemIndex / INVENTORY_GRID_WIDTH * INVENTORY_CELL_SIZE);
                    window.draw(helmetSprite);

                    itemIndex++;
                }
                else {
                    std::cerr << "Failed to load helmet texture." << std::endl;
                }
            }

            if (itemName.find("Armor") != std::string::npos) {
                sf::Texture armorTexture;
                if (armorTexture.loadFromFile("./Images/armor_game_icon.png")) {
                    sf::Sprite armorSprite(armorTexture);
                    const float cellSize = 50.0f; 
                    const float scale = cellSize / armorTexture.getSize().x; 

                    armorSprite.setScale(scale, scale);
                    armorSprite.setPosition(INVENTORY_OFFSET_X + itemIndex % INVENTORY_GRID_WIDTH * INVENTORY_CELL_SIZE,
                        INVENTORY_OFFSET_Y + itemIndex / INVENTORY_GRID_WIDTH * INVENTORY_CELL_SIZE);
                    window.draw(armorSprite);

                    itemIndex++;
                }
                else {
                    std::cerr << "Failed to load armor texture." << std::endl;
                }
            }

            if (itemName.find("Shield") != std::string::npos) {
                sf::Texture shieldTexture;
                if (shieldTexture.loadFromFile("./Images/shield_game_icon.png")) {
                    sf::Sprite shieldSprite(shieldTexture);
                    const float cellSize = 50.0f; 
                    const float scale = cellSize / shieldTexture.getSize().x; 

                    shieldSprite.setScale(scale, scale);
                    shieldSprite.setPosition(INVENTORY_OFFSET_X + itemIndex % INVENTORY_GRID_WIDTH * INVENTORY_CELL_SIZE,
                        INVENTORY_OFFSET_Y + itemIndex / INVENTORY_GRID_WIDTH * INVENTORY_CELL_SIZE);
                    window.draw(shieldSprite);

                    itemIndex++;
                }
                else {
                    std::cerr << "Failed to load shield texture." << std::endl;
                }
            }

            if (itemName.find("Sword") != std::string::npos) {
                sf::Texture swordTexture;
                if (swordTexture.loadFromFile("./sword_game_icon.png")) {
                    sf::Sprite swordSprite(swordTexture);
                    const float cellSize = 50.0f; 
                    const float scale = cellSize / swordTexture.getSize().x; 

                    swordSprite.setScale(scale, scale);
                    swordSprite.setPosition(INVENTORY_OFFSET_X + itemIndex % INVENTORY_GRID_WIDTH * INVENTORY_CELL_SIZE,
                        INVENTORY_OFFSET_Y + itemIndex / INVENTORY_GRID_WIDTH * INVENTORY_CELL_SIZE);
                    window.draw(swordSprite);

                    itemIndex++;
                }
                else {
                    std::cerr << "Failed to load sword texture." << std::endl;
                }
            }

            if (itemName.find("Boots") != std::string::npos) {
                sf::Texture bootsTexture;
                if (bootsTexture.loadFromFile("./Images/boots_game_icon.png")) {
                    sf::Sprite bootsSprite(bootsTexture);
                    const float cellSize = 50.0f; 
                    const float scale = cellSize / bootsTexture.getSize().x; 

                    bootsSprite.setScale(scale, scale);
                    bootsSprite.setPosition(INVENTORY_OFFSET_X + itemIndex % INVENTORY_GRID_WIDTH * INVENTORY_CELL_SIZE,
                        INVENTORY_OFFSET_Y + itemIndex / INVENTORY_GRID_WIDTH * INVENTORY_CELL_SIZE);
                    window.draw(bootsSprite);

                    itemIndex++;
                }
                else {
                    std::cerr << "Failed to load boots texture." << std::endl;
                }
            }

            if (itemName.find("Ring") != std::string::npos) {
                sf::Texture ringTexture;
                if (ringTexture.loadFromFile("./Images/ring_game_icon.png")) {
                    sf::Sprite ringSprite(ringTexture);
                    const float cellSize = 50.0f; 
                    const float scale = cellSize / ringTexture.getSize().x; 

                    ringSprite.setScale(scale, scale);
                    ringSprite.setPosition(INVENTORY_OFFSET_X + itemIndex % INVENTORY_GRID_WIDTH * INVENTORY_CELL_SIZE,
                        INVENTORY_OFFSET_Y + itemIndex / INVENTORY_GRID_WIDTH * INVENTORY_CELL_SIZE);
                    window.draw(ringSprite);

                    itemIndex++;
                }
                else {
                    std::cerr << "Failed to load ring texture." << std::endl;
                }
            }

            if (itemName.find("Belt") != std::string::npos) {
                sf::Texture beltTexture;
                if (beltTexture.loadFromFile("./Images/belt_game_icon.png")) {
                    sf::Sprite beltSprite(beltTexture);
                    const float cellSize = 50.0f; 
                    const float scale = cellSize / beltTexture.getSize().x; 

                    beltSprite.setScale(scale, scale);
                    beltSprite.setPosition(INVENTORY_OFFSET_X + itemIndex % INVENTORY_GRID_WIDTH * INVENTORY_CELL_SIZE,
                        INVENTORY_OFFSET_Y + itemIndex / INVENTORY_GRID_WIDTH * INVENTORY_CELL_SIZE);
                    window.draw(beltSprite);

                    itemIndex++;
                }
                else {
                    std::cerr << "Failed to load belt texture." << std::endl;
                }
            }
        }
    }
}

void PlayGame::drawGrid(sf::RenderWindow& window) {
    sf::Color gridColor = sf::Color::Black; // Change grid color to black
    float lineThickness = 3.0f; // Adjust thickness as desired

    // Draw vertical grid lines
    for (int i = 0; i <= GRID_WIDTH; ++i) {
        sf::RectangleShape verticalLine(sf::Vector2f(lineThickness, GRID_HEIGHT * CELL_SIZE));
        verticalLine.setPosition(GRID_OFFSET_X + i * CELL_SIZE - lineThickness / 2.0f, GRID_OFFSET_Y);
        verticalLine.setFillColor(gridColor);
        window.draw(verticalLine);
    }

    // Draw horizontal grid lines
    for (int j = 0; j <= GRID_HEIGHT; ++j) {
        sf::RectangleShape horizontalLine(sf::Vector2f(GRID_WIDTH * CELL_SIZE, lineThickness));
        horizontalLine.setPosition(GRID_OFFSET_X, GRID_OFFSET_Y + j * CELL_SIZE - lineThickness / 2.0f);
        horizontalLine.setFillColor(gridColor);
        window.draw(horizontalLine);
    }
}

void PlayGame::drawSelectedMapGrid(string selectedMap)
{
    objects.clear();

    Editor* editor = new Editor();
    Map* loadedMap = editor->selectMapGUI(selectedMap);

    GRID_WIDTH = loadedMap->getWidth();
    GRID_HEIGHT = loadedMap->getHeight();

    objects.push_back({ characterPositionX, characterPositionY, ObjectType::Character });

    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            switch (loadedMap->getGrid()[y][x]) {
            case Cell::WALL:
                objects.push_back({ x, y, ObjectType::Wall });
                break;
            case Cell::DOOR:
                objects.push_back({ x, y, ObjectType::Door });
                break;
            case Cell::CHEST:
                objects.push_back({ x, y, ObjectType::Chest });
                break;
            }
        }
    }
}

void PlayGame::handlePlayGameClick(int mouseX, int mouseY, Character* character, Campaign* campaign, string& mapName, vector<string>& listOfMaps) {
    // Handle clicks on cell
    if (mouseX >= GRID_OFFSET_X && mouseX < GRID_OFFSET_X + GRID_WIDTH * CELL_SIZE && mouseY >= GRID_OFFSET_Y && mouseY < GRID_OFFSET_Y + GRID_HEIGHT * CELL_SIZE) {
        // Inside the grid
        int gridX = (mouseX - GRID_OFFSET_X) / CELL_SIZE;
        int gridY = (mouseY - GRID_OFFSET_Y) / CELL_SIZE;

        // Check if targeted cell is occupied, if not move character to new position
        if (!isXYInObjects(gridX, gridY)) {
            characterPositionX = gridX;
            characterPositionY = gridY;
            //drawSelectedMapGrid(selectedMapName);
            //character->performMove(*map);
            //character->performMoveGUI(*map, gridX, gridY);
        }
        else if (XYPositionIsChest(gridX, gridY)) {
            cout << "opening chests..." << endl;
        }
        else if (XYPositionIsDoor(gridX, gridY)) {
            currentMapIndex += 1;

            // Check if its the last map
            if (currentMapIndex >= listOfMaps.size()) {
                wonTheGame = true;
            }
            else {
                mapName = listOfMaps[currentMapIndex];
                characterPositionX = 0;
                characterPositionY = 0;
            }
        }

    }

}

void PlayGame::handleCharacterCreationClick(int mouseX, int mouseY) {
    // Handle clicks on character creation screen
}

void PlayGame::handleTextInput(sf::Uint32 unicode) {
}

void PlayGame::drawMainMenu(sf::RenderWindow& window) {
    // Draw main menu
}

void PlayGame::drawPlayGame(string mapName, string campaignName) {
    mapNameLabel.setString(mapName);
    campaignNameLabel.setString(campaignName);

    window.draw(worldBackground);
    window.draw(backButton);
    window.draw(campaignLabel);
    window.draw(campaignNameLabel);
    window.draw(mapNameLabel);

    drawGrid(window);
    drawSelectedMapGrid(mapName);
    drawInventoryGrid(window);
    window.draw(inventoryText);

    // Draw objects
    for (const auto& obj : objects) {
        sf::Sprite objectSprite;
        objectSprite.setPosition(GRID_OFFSET_X + obj.x * CELL_SIZE, GRID_OFFSET_Y + obj.y * CELL_SIZE);
        objectSprite.setScale(static_cast<float>(CELL_SIZE) / wallTexture.getSize().x, static_cast<float>(CELL_SIZE) / wallTexture.getSize().y);
        switch (obj.type) {
        case ObjectType::Wall:
            objectSprite.setTexture(wallTexture);
            break;
        case ObjectType::Chest:
            objectSprite.setTexture(chestTexture);
            break;
        case ObjectType::Door:
            objectSprite.setTexture(doorTexture);
            break;
        case ObjectType::Character:
            objectSprite.setTexture(characterTexture);
            break;
        default:
            break;
        }
        window.draw(objectSprite);
    }

    if (showSuccessfulAlert) {
        window.draw(alertText);
    }

    if (wonTheGame) {
        window.draw(winLabel);
    }
    
}

// Checks if a given cell (x,y) is occupied by a wall
bool PlayGame::isXYInObjects(int x, int y) {
    for (const auto& obj : objects) {
        if (obj.x == x && obj.y == y && (obj.type == ObjectType::Wall or obj.type == ObjectType::Chest or obj.type == ObjectType::Door)) {
            return true; // Found the coordinates in the list of objects
        }
    }
    return false; // Did not find the coordinates in the list of objects
}

// Checks if a given cell (x,y) is occupied by a chest
bool PlayGame::XYPositionIsChest(int x, int y) {
    for (const auto& obj : objects) {
        if (obj.x == x && obj.y == y && (obj.type == ObjectType::Chest)) {
            return true;
        }
    }
    return false;
}

// Checks if a given cell (x,y) is occupied by a door
bool PlayGame::XYPositionIsDoor(int x, int y) {
    for (const auto& obj : objects) {
        if (obj.x == x && obj.y == y && (obj.type == ObjectType::Door)) {
            return true;
        }
    }
    return false;
}
