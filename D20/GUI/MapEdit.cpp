#include "MapEdit.h"
#include "../Map/Map.h"
#include "../Map/Editor.h"
#include <filesystem>

namespace fs = std::filesystem;

MapEdit::MapEdit(sf::RenderWindow& window) : window(window), showSuccessfulAlert(false), showFailureAlert(false) {
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }

    if (!worldBackgroundTex.loadFromFile("./Images/mapbackground.jpg")) {
        cout << "ERROR: Game could not load background image" << "\n";
    }
    worldBackground.setScale(static_cast<float>(window.getSize().x) / worldBackgroundTex.getSize().x,
        static_cast<float>(window.getSize().y) / worldBackgroundTex.getSize().y);

    worldBackground.setTexture(worldBackgroundTex);

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

    titleLabel.setFont(font);
    titleLabel.setString("Map Edit");
    titleLabel.setCharacterSize(40);
    titleLabel.setFillColor(sf::Color::Black);
    titleLabel.setStyle(sf::Text::Bold | sf::Text::Underlined);
    titleLabel.setPosition((window.getSize().x / 2 - titleLabel.getLocalBounds().width / 2), 25);

    editMapButton.setSize(sf::Vector2f(175, 50));
    editMapButton.setFillColor(sf::Color::Black);
    editMapButton.setPosition((window.getSize().x / 2 - editMapButton.getLocalBounds().width / 2), 550);

    editMapButtonText.setFont(font);
    editMapButtonText.setString("Save Map");
    editMapButtonText.setCharacterSize(24);
    editMapButtonText.setFillColor(sf::Color::White);
    editMapButtonText.setPosition((window.getSize().x / 2 - editMapButtonText.getLocalBounds().width / 2), 560);

    mapLabel.setFont(font);
    mapLabel.setString("Available Maps");
    mapLabel.setCharacterSize(24);
    mapLabel.setFillColor(sf::Color::Black);
    mapLabel.setStyle(sf::Text::Underlined);
    mapLabel.setPosition(60, 100);

    alertText.setFont(font);
    alertText.setString("Successfully edited map!");
    alertText.setCharacterSize(28);
    alertText.setFillColor(sf::Color::White); // Text color
    alertText.setPosition(window.getSize().x / 2 - alertText.getLocalBounds().width / 2, 620); // Adjust position as needed

}

void MapEdit::drawGrid(sf::RenderWindow& window) {
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

void MapEdit::drawSelectedMapGrid(string selectedMap)
{
    objects.clear();

    Editor* editor = new Editor();
    Map* loadedMap = editor->selectMapGUI(selectedMap);

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

void MapEdit::drawObjectMenu(sf::RenderWindow& window, ObjectType selectedObjectType) {
    // Draw Walls
    sf::Sprite wallSprite(wallTexture);
    wallSprite.setPosition(WINDOW_WIDTH - OBJECT_MENU_WIDTH + OBJECT_MENU_OFFSET, OBJECT_MENU_OFFSET + OBJECT_MENU_Y);
    wallSprite.setScale(static_cast<float>(CELL_SIZE) / wallTexture.getSize().x, static_cast<float>(CELL_SIZE) / wallTexture.getSize().y);
    window.draw(wallSprite);

    // Draw Chests
    sf::Sprite chestSprite(chestTexture);
    chestSprite.setPosition(WINDOW_WIDTH - OBJECT_MENU_WIDTH + OBJECT_MENU_OFFSET, OBJECT_MENU_OFFSET + CELL_SIZE + 10 + OBJECT_MENU_Y);
    chestSprite.setScale(static_cast<float>(CELL_SIZE) / chestTexture.getSize().x, static_cast<float>(CELL_SIZE) / chestTexture.getSize().y);
    window.draw(chestSprite);

    // Draw Doors
    sf::Sprite doorSprite(doorTexture);
    doorSprite.setPosition(WINDOW_WIDTH - OBJECT_MENU_WIDTH + OBJECT_MENU_OFFSET, OBJECT_MENU_OFFSET + 2 * (CELL_SIZE + 10) + OBJECT_MENU_Y);
    doorSprite.setScale(static_cast<float>(CELL_SIZE) / doorTexture.getSize().x, static_cast<float>(CELL_SIZE) / doorTexture.getSize().y);
    window.draw(doorSprite);

    // Draw labels next to the objects
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        // Handle error if font loading fails
        return;
    }

    sf::Text wallLabel("Wall", font, 18);
    wallLabel.setPosition(WINDOW_WIDTH - OBJECT_MENU_WIDTH + OBJECT_MENU_OFFSET + CELL_SIZE + 10, OBJECT_MENU_OFFSET + OBJECT_MENU_Y);

    sf::Text chestLabel("Chest", font, 18);
    chestLabel.setPosition(WINDOW_WIDTH - OBJECT_MENU_WIDTH + OBJECT_MENU_OFFSET + CELL_SIZE + 10, OBJECT_MENU_OFFSET + CELL_SIZE + 10 + OBJECT_MENU_Y);

    sf::Text doorLabel("Door", font, 18);
    doorLabel.setPosition(WINDOW_WIDTH - OBJECT_MENU_WIDTH + OBJECT_MENU_OFFSET + CELL_SIZE + 10, OBJECT_MENU_OFFSET + 2 * (CELL_SIZE + 10) + OBJECT_MENU_Y);

    // Highlight selected object type
    sf::RectangleShape selectionRect(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    switch (selectedObjectType) {
        case ObjectType::Wall:
            wallLabel.setFillColor(sf::Color(128, 128, 128, 128)); // Transparent red
            selectionRect.setFillColor(sf::Color(128, 128, 128, 128)); // Transparent red
            selectionRect.setPosition(WINDOW_WIDTH - OBJECT_MENU_WIDTH + OBJECT_MENU_OFFSET, OBJECT_MENU_OFFSET + OBJECT_MENU_Y);
            break;
        case ObjectType::Chest:
            chestLabel.setFillColor(sf::Color(128, 128, 128, 128)); // Transparent blue
            selectionRect.setFillColor(sf::Color(128, 128, 128, 128)); // Transparent blue
            selectionRect.setPosition(WINDOW_WIDTH - OBJECT_MENU_WIDTH + OBJECT_MENU_OFFSET, OBJECT_MENU_OFFSET + CELL_SIZE + 10 + OBJECT_MENU_Y);
            break;
        case ObjectType::Door:
            doorLabel.setFillColor(sf::Color(128, 128, 128, 128)); // Transparent green
            selectionRect.setFillColor(sf::Color(128, 128, 128, 128)); // Transparent green
            selectionRect.setPosition(WINDOW_WIDTH - OBJECT_MENU_WIDTH + OBJECT_MENU_OFFSET, OBJECT_MENU_OFFSET + 2 * (CELL_SIZE + 10) + OBJECT_MENU_Y);
            break;
        default:
            break;
    }
    if (selectedObjectType != ObjectType::None) {
        window.draw(selectionRect);
    }
    window.draw(wallLabel);
    window.draw(chestLabel);
    window.draw(doorLabel);
}

vector<vector<ObjectType>> MapEdit::createMap(const vector<Object>& objects) {

    vector<vector<ObjectType>> map(GRID_HEIGHT, vector<ObjectType>(GRID_WIDTH, ObjectType::None));

    // Populate map with placed objects
    for (const auto& obj : objects) {
        map[obj.y][obj.x] = obj.type;
    }

    return map;
}

void MapEdit::handleMapEditClick(int mouseX, int mouseY) {
    if (mouseX >= GRID_OFFSET_X && mouseX < GRID_OFFSET_X + GRID_WIDTH * CELL_SIZE &&
        mouseY >= GRID_OFFSET_Y && mouseY < GRID_OFFSET_Y + GRID_HEIGHT * CELL_SIZE) {
        // Inside the grid
        int gridX = (mouseX - GRID_OFFSET_X) / CELL_SIZE;
        int gridY = (mouseY - GRID_OFFSET_Y) / CELL_SIZE;

        // Add object to the grid
        if (selectedObjectType != ObjectType::None) {
            objects.push_back({ gridX, gridY, selectedObjectType });
        }
    }
    else if (mouseX >= WINDOW_WIDTH - OBJECT_MENU_WIDTH) {
        // Inside the object menu
        if (mouseY >= OBJECT_MENU_OFFSET && mouseY < OBJECT_MENU_OFFSET + CELL_SIZE + OBJECT_MENU_Y) {
            selectedObjectType = ObjectType::Wall;
        }
        else if (mouseY >= OBJECT_MENU_OFFSET + CELL_SIZE + 10 && mouseY < OBJECT_MENU_OFFSET + 2 * CELL_SIZE + 10 + OBJECT_MENU_Y) {
            selectedObjectType = ObjectType::Chest;
        }
        else if (mouseY >= OBJECT_MENU_OFFSET + 2 * (CELL_SIZE + 10) && mouseY < OBJECT_MENU_OFFSET + 3 * CELL_SIZE + 20 + OBJECT_MENU_Y) {
            selectedObjectType = ObjectType::Door;
        }
    }
    else if (isClickOnMapList(mouseX, mouseY)) {
        // Determine which map was clicked
        int mapIndex = static_cast<int>((mouseY - mapListStartPosition.y) / mapListItemSpacing);
        if (mapIndex >= 0 && static_cast<size_t>(mapIndex) < mapFiles.size()) {
            std::fill(mapSelections.begin(), mapSelections.end(), false);
            mapSelections[mapIndex] = true;

            //std::vector<std::string> selectedMaps;
            for (size_t i = 0; i < mapSelections.size(); ++i) {
                if (mapSelections[i]) {
                    //selectedMaps.push_back(mapFiles[i]);
                    selectedMap = mapFiles[i];
                }
            }

            drawSelectedMapGrid(selectedMap);
        }
    }
    else if (editMapButton.getGlobalBounds().contains(mouseX, mouseY)) {
        cout << "Editing map..." << endl;

        vector<vector<ObjectType>> newMap = createMap(objects);

        // Print the map (for demonstration)
        //for (int y = 0; y < GRID_HEIGHT; ++y) {
        //    for (int x = 0; x < GRID_WIDTH; ++x) {
        //        switch (map[y][x]) {
        //        case ObjectType::Wall:
        //            std::cout << "W ";
        //            break;
        //        case ObjectType::Chest:
        //            std::cout << "C ";
        //            break;
        //        case ObjectType::Door:
        //            std::cout << "D ";
        //            break;
        //        default:
        //            std::cout << "_ ";
        //            break;
        //        }
        //    }
        //    std::cout << std::endl;
        //}

        Editor* editor = new Editor();
        Map* mapObject = editor->selectMapGUI(selectedMap);

        for (int y = 0; y < GRID_HEIGHT; ++y) {
            for (int x = 0; x < GRID_WIDTH; ++x) {
                switch (newMap[y][x]) {
                    case ObjectType::Wall:
                        mapObject->setCell(x, y, Cell::WALL);
                        break;
                    case ObjectType::Chest:
                        mapObject->setCell(x, y, Cell::CHEST);
                        break;
                    case ObjectType::Door:
                        mapObject->setCell(x, y, Cell::DOOR);
                        break;
                    case ObjectType::None:
                        mapObject->setCell(x, y, Cell::EMPTY);
                        break;
                }
            }
        }

        editor->editMapGUI(mapObject);

        showSuccessfulAlert = true;

    }
}

void MapEdit::handleRemoveObject(int mouseX, int mouseY) {
    for (auto it = objects.begin(); it != objects.end(); ++it) {
        if (mouseX >= GRID_OFFSET_X + it->x * CELL_SIZE &&
            mouseX < GRID_OFFSET_X + (it->x + 1) * CELL_SIZE &&
            mouseY >= GRID_OFFSET_Y + it->y * CELL_SIZE &&
            mouseY < GRID_OFFSET_Y + (it->y + 1) * CELL_SIZE) {
            objects.erase(it);
            break; // Only remove one object if multiple overlap
        }
    }
}

void MapEdit::drawMapEdit() {
    window.draw(worldBackground);
    window.draw(titleLabel);
    window.draw(backButton);
    window.draw(editMapButton);
    window.draw(editMapButtonText);
    window.draw(mapLabel);

    drawGrid(window);
    drawObjectMenu(window, selectedObjectType);

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
            default:
                break;
        }
        window.draw(objectSprite);
    }

    float currentYPosition = mapListStartPosition.y;

    loadMapFiles("./data/maps");
    mapSelections.resize(mapFiles.size(), false);

    for (size_t i = 0; i < mapFiles.size(); ++i) {
        sf::Text mapNameText;
        mapNameText.setFont(font);
        mapNameText.setString(mapFiles[i]);
        mapNameText.setCharacterSize(20);
        mapNameText.setFillColor(mapSelections[i] ? sf::Color::White : sf::Color::Black); // Highlight if selected
        mapNameText.setPosition(mapListStartPosition.x, currentYPosition);

        window.draw(mapNameText);

        currentYPosition += mapListItemSpacing;
    }

    if (showSuccessfulAlert) {
        window.draw(alertText);
    }

}

void MapEdit::loadMapFiles(const string& directoryPath) {
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

bool MapEdit::isClickOnMapList(int mouseX, int mouseY) {
    // Assuming you have a defined area for the map list
    sf::FloatRect mapListArea(mapListStartPosition.x, mapListStartPosition.y, 300, mapFiles.size() * mapListItemSpacing); // Example dimensions
    return mapListArea.contains(static_cast<float>(mouseX), static_cast<float>(mouseY));
}


bool MapEdit::isPrintableAscii(sf::Uint32 unicode) {
    // Function to check if the unicode is a printable ASCII character
    return (unicode >= 32 && unicode <= 126) || unicode == 8;
}

MapEdit::ActiveInputField MapEdit::getActiveField() const
{
    return activeField;
}
