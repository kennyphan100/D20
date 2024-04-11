#include "PlayGame.h"
#include <filesystem>
#include "../Map/Editor.h"
#include "../Character/HumanPlayerStrategy.h"

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
    drawObjects(objects);
}

void PlayGame::drawSelectedMapGrid(Map* selectedMap)
{
    objects.clear();

    GRID_WIDTH = selectedMap->getWidth();
    GRID_HEIGHT = selectedMap->getHeight();

    objects.push_back({ characterPositionX, characterPositionY, ObjectType::Character });

    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            switch (selectedMap->getGrid()[y][x]) {
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
    drawObjects(objects);
}

void PlayGame::drawSelectedMapGridStatic(string selectedMap)
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
    drawObjectsStatic(objects);
}


void PlayGame::handlePlayGameClick(int mouseX, int mouseY, Character* character, Campaign* campaign, Map*& map, string& mapName, vector<string>& listOfMaps) {
    // Handle clicks on cell
    if (mouseX >= GRID_OFFSET_X && mouseX < GRID_OFFSET_X + GRID_WIDTH * CELL_SIZE && mouseY >= GRID_OFFSET_Y && mouseY < GRID_OFFSET_Y + GRID_HEIGHT * CELL_SIZE) {
        // Inside the grid
        int gridX = (mouseX - GRID_OFFSET_X) / CELL_SIZE;
        int gridY = (mouseY - GRID_OFFSET_Y) / CELL_SIZE;

        // Check if targeted cell is occupied, if not move character to new position
        if (!isXYInObjects(gridX, gridY)) {
            //characterPositionX = gridX;
            //characterPositionY = gridY;

            HumanPlayerStrategy hps;
            character->setStrategy(&hps);
            character->performMoveGUI(*map, gridX, gridY, *this);

        }
        else if (XYPositionIsChest(gridX, gridY)) {
            cout << "opening chest..." << endl;
            character->interactWithChest(*map, gridX, gridY);

            removeObject(objects, gridX, gridY);
            drawObjects(objects);
        }
        else if (XYPositionIsDoor(gridX, gridY)) {
            currentMapIndex += 1;

            HumanPlayerStrategy hps;
            character->setStrategy(&hps);
            character->performMoveGUI(*map, gridX, gridY, *this);

            // Check if its the last map
            if (currentMapIndex >= listOfMaps.size()) {
                wonTheGame = true;
            }
            else {
                mapName = listOfMaps[currentMapIndex];
                characterPositionX = 0;
                characterPositionY = 0;

                Editor* editor = new Editor();
                map = editor->selectMapGUI(mapName);
                character->setStrategy(&hps);
                map->placeCharacter(0, 0, character);
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

    //window.draw(worldBackground);
    //window.draw(backButton);
    //window.draw(campaignLabel);
    //window.draw(campaignNameLabel);
    //window.draw(mapNameLabel);

    //drawGrid(window);

    //drawSelectedMapGrid(mapName);
    drawSelectedMapGridStatic(mapName);


    if (showSuccessfulAlert) {
        window.draw(alertText);
    }

    if (wonTheGame) {
        window.draw(winLabel);
    }
}

void PlayGame::drawObjects(std::vector<Object> objects2) {
    window.clear();

    window.draw(worldBackground);
    window.draw(backButton);
    window.draw(campaignLabel);
    window.draw(campaignNameLabel);
    window.draw(mapNameLabel);
    drawGrid(window);

    for (const auto& obj : objects2) {
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
    window.display();
}

void PlayGame::drawObjectsStatic(std::vector<Object> objects2) {
    window.draw(worldBackground);
    window.draw(backButton);
    window.draw(campaignLabel);
    window.draw(campaignNameLabel);
    window.draw(mapNameLabel);
    drawGrid(window);

    for (const auto& obj : objects2) {
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

void PlayGame::removeObject(std::vector<Object>& objects, int x, int y) {
    auto it = std::remove_if(objects.begin(), objects.end(), [x, y](const Object& obj) {
        return obj.x == x && obj.y == y;
        });

    if (it != objects.end()) {
        objects.erase(it, objects.end());
        std::cout << "Object removed successfully." << std::endl;
    }
    else {
        std::cout << "Object not found." << std::endl;
    }
}

