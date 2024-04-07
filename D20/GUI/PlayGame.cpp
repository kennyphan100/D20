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

    backButton.setFont(font);
    backButton.setString("Go Back");
    backButton.setCharacterSize(24);
    backButton.setFillColor(sf::Color::Black);
    backButton.setPosition(25, 25);

    titleLabel.setFont(font);
    titleLabel.setString("Game Play");
    titleLabel.setCharacterSize(36);
    titleLabel.setFillColor(sf::Color::Black);
    titleLabel.setStyle(sf::Text::Bold | sf::Text::Underlined);
    titleLabel.setPosition((window.getSize().x / 2 - titleLabel.getLocalBounds().width / 2), 70);

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

void PlayGame::handlePlayGameClick(int mouseX, int mouseY, Character* character) {
    // Handle clicks on main menu


    if (startGameButtonBackground.getGlobalBounds().contains(mouseX, mouseY))
    {
        cout << "test123" << endl;

        character->display();
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

void PlayGame::drawPlayGame() {
    window.draw(worldBackground);
    window.draw(backButton);
    window.draw(titleLabel);

    window.draw(startGameButtonBackground);
    window.draw(startGameButtonText);


    if (showSuccessfulAlert) {
        window.draw(alertText);
    }
    

}
