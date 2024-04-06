#include "MapCreation.h"
#include "../Map/Map.h"
#include "../Map/Editor.h"

MapCreation::MapCreation(sf::RenderWindow& window) : window(window), showSuccessfulAlert(false), showFailureAlert(false) {
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
    titleLabel.setString("Map Creation");
    titleLabel.setCharacterSize(40);
    titleLabel.setFillColor(sf::Color::Black);
    titleLabel.setStyle(sf::Text::Bold | sf::Text::Underlined);
    titleLabel.setPosition((window.getSize().x / 2 - titleLabel.getLocalBounds().width / 2), 25);

    nameLabel.setFont(font);
    nameLabel.setString("Name:");
    nameLabel.setCharacterSize(24);
    nameLabel.setFillColor(sf::Color::Black);
    nameLabel.setPosition((window.getSize().x / 2 - nameLabel.getLocalBounds().width / 2) - 200, 100);

    nameValue.setFont(font);
    nameValue.setString("");
    nameValue.setCharacterSize(24);
    nameValue.setFillColor(sf::Color::Black);
    nameValue.setPosition((window.getSize().x / 2 - nameValue.getLocalBounds().width / 2) - 140, 100);

    nameInputBackground.setSize(sf::Vector2f(400, 40));
    nameInputBackground.setFillColor(sf::Color::White);
    nameInputBackground.setPosition((window.getSize().x / 2 - nameInputBackground.getLocalBounds().width / 2) + 50, 95);

    widthLabel.setFont(font);
    widthLabel.setString("Width: ");
    widthLabel.setCharacterSize(24);
    widthLabel.setFillColor(sf::Color::Black);
    widthLabel.setPosition((window.getSize().x / 2 - widthLabel.getLocalBounds().width / 2) - 200, 150);

    widthValue.setFont(font);
    widthValue.setString("");
    widthValue.setCharacterSize(24);
    widthValue.setFillColor(sf::Color::Black);
    widthValue.setPosition((window.getSize().x / 2 - widthValue.getLocalBounds().width / 2) - 140, 150);

    widthInputBackground.setSize(sf::Vector2f(100, 40));
    widthInputBackground.setFillColor(sf::Color::White);
    widthInputBackground.setPosition((window.getSize().x / 2 - widthInputBackground.getLocalBounds().width / 2) - 100, 145);

    heightLabel.setFont(font);
    heightLabel.setString("Height: ");
    heightLabel.setCharacterSize(24);
    heightLabel.setFillColor(sf::Color::Black);
    heightLabel.setPosition((window.getSize().x / 2 - heightLabel.getLocalBounds().width / 2) - 200, 200);

    heightValue.setFont(font);
    heightValue.setString("");
    heightValue.setCharacterSize(24);
    heightValue.setFillColor(sf::Color::Black);
    heightValue.setPosition((window.getSize().x / 2 - heightValue.getLocalBounds().width / 2) - 140, 200);

    heightInputBackground.setSize(sf::Vector2f(100, 40));
    heightInputBackground.setFillColor(sf::Color::White);
    heightInputBackground.setPosition((window.getSize().x / 2 - heightInputBackground.getLocalBounds().width / 2) - 100, 195);

    createMapButton.setSize(sf::Vector2f(175, 50));
    createMapButton.setFillColor(sf::Color::Black);
    createMapButton.setPosition((window.getSize().x / 2 - createMapButton.getLocalBounds().width / 2), 300);

    createMapButtonText.setFont(font);
    createMapButtonText.setString("Create Map");
    createMapButtonText.setCharacterSize(24);
    createMapButtonText.setFillColor(sf::Color::White);
    createMapButtonText.setPosition((window.getSize().x / 2 - createMapButtonText.getLocalBounds().width / 2), 310);

    alertTextSuccess.setFont(font);
    alertTextSuccess.setString("Successfully created map " + inputName + " !");
    alertTextSuccess.setCharacterSize(24);
    alertTextSuccess.setStyle(sf::Text::Bold);
    alertTextSuccess.setFillColor(sf::Color::White); // Text color
    alertTextSuccess.setPosition(window.getSize().x / 2 - alertTextSuccess.getLocalBounds().width / 2, 500); // Adjust position as needed

    alertTextFailure.setFont(font);
    alertTextFailure.setString("The map with the name " + inputName + " already exists!");
    alertTextFailure.setCharacterSize(24);
    alertTextFailure.setFillColor(sf::Color::Black); // Text color
    alertTextFailure.setPosition(window.getSize().x / 2 - alertTextFailure.getLocalBounds().width / 2, 500); // Adjust position as needed

}

void MapCreation::handleMainMenuClick(int mouseX, int mouseY) {
    // Handle clicks on main menu
}

void MapCreation::handleMapCreationClick(int mouseX, int mouseY) {
    try {
        showSuccessfulAlert, showFailureAlert = false, false;
        sf::Vector2f mousePosF(static_cast<float>(mouseX), static_cast<float>(mouseY));
        if (nameInputBackground.getGlobalBounds().contains(mousePosF)) {
            activeField = NAME;
        }
        else if (widthInputBackground.getGlobalBounds().contains(mousePosF)) {
            activeField = WIDTH;
        }
        else if (heightInputBackground.getGlobalBounds().contains(mousePosF)) {
            activeField = HEIGHT;
        }
        else if (createMapButton.getGlobalBounds().contains(mouseX, mouseY)) {
            std::cout << "creating map..." << std::endl;
            cout << inputName << endl;

            Editor* editor = new Editor();
            editor->createMapGUI(inputName, stoi(inputWidth), stoi(inputHeight));
            showSuccessfulAlert = true;
        }
    }
    catch (const exception& e) {
        showFailureAlert = true;
        cerr << "A map with this name already exists. Please choose a different name." << endl;
    }
}

void MapCreation::handleTextInput(sf::Uint32 unicode) {
    if (activeField == NAME) {
        // Handle name input (similar to character creation)
        if (isPrintableAscii(unicode)) {
            if (unicode == 8 && inputName.size() > 0) { // Backspace pressed
                inputName.pop_back();
            }
            else if (unicode != 8) {
                inputName += static_cast<char>(unicode);
            }
            nameValue.setString(inputName);
        }
    }
    else if (activeField == WIDTH || activeField == HEIGHT) {
        // Handle width and height input (numeric input)
        if (unicode >= '0' && unicode <= '9') {
            if (activeField == WIDTH) {
                inputWidth += static_cast<char>(unicode);
                widthValue.setString(inputWidth);
            }
            else {
                inputHeight += static_cast<char>(unicode);
                heightValue.setString(inputHeight);
            }
        }
        else if (unicode == 8) { // Backspace logic
            if (activeField == WIDTH && inputWidth.size() > 0) {
                inputWidth.pop_back();
                widthValue.setString(inputWidth);
            }
            else if (activeField == HEIGHT && inputHeight.size() > 0) {
                inputHeight.pop_back();
                heightValue.setString(inputHeight);
            }
        }
    }
}

void MapCreation::drawMainMenu(sf::RenderWindow& window) {
    // Draw main menu
}

void MapCreation::drawMapCreation() {
    // Draw character creation screen
    window.draw(worldBackground);
    window.draw(titleLabel);

    if (activeField == NAME) {
        nameInputBackground.setOutlineThickness(2);
        nameInputBackground.setOutlineColor(sf::Color::Black);
    }
    else {
        nameInputBackground.setOutlineThickness(0);
    }

    if (activeField == WIDTH) {
        widthInputBackground.setOutlineThickness(2);
        widthInputBackground.setOutlineColor(sf::Color::Black);
    }
    else {
        widthInputBackground.setOutlineThickness(0);
    }

    if (activeField == HEIGHT) {
        heightInputBackground.setOutlineThickness(2);
        heightInputBackground.setOutlineColor(sf::Color::Black);
    }
    else {
        heightInputBackground.setOutlineThickness(0);
    }

    window.draw(widthInputBackground);
    window.draw(widthLabel);
    window.draw(widthValue);

    window.draw(heightInputBackground);
    window.draw(heightLabel);
    window.draw(heightValue);

    window.draw(nameInputBackground);
    window.draw(nameValue);
    window.draw(nameLabel);

    window.draw(createMapButton);
    window.draw(createMapButtonText);
    window.draw(backButton);

    if (showFailureAlert) {
        window.draw(alertTextFailure);
    }
    else if (showSuccessfulAlert) {
        window.draw(alertTextSuccess);
    }
}

bool MapCreation::isPrintableAscii(sf::Uint32 unicode) {
    // Function to check if the unicode is a printable ASCII character
    return (unicode >= 32 && unicode <= 126) || unicode == 8;
}

MapCreation::ActiveInputField MapCreation::getActiveField() const
{
    return activeField;
}
