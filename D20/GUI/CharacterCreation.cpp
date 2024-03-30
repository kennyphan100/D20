#include "CharacterCreation.h"
#include "../Character/CharacterDirector.h"
#include "../Character/CharacterBuilder.h"

CharacterCreation::CharacterCreation(sf::RenderWindow& window) : window(window), dropdownOpen(false), showSuccessfulAlert(false) {
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }

    if (!worldBackgroundTex.loadFromFile("./Images/background1.jpg")) {
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
    titleLabel.setString("Character Creation: ");
    titleLabel.setCharacterSize(40);
    titleLabel.setFillColor(sf::Color::Black);
    titleLabel.setStyle(sf::Text::Bold | sf::Text::Underlined);
    titleLabel.setPosition((window.getSize().x / 2 - levelLabel.getLocalBounds().width / 2) - 200, 25);

    levelLabel.setFont(font);
    levelLabel.setString("Level: ");
    levelLabel.setCharacterSize(24);
    levelLabel.setFillColor(sf::Color::Black);
    levelLabel.setPosition((window.getSize().x / 2 - levelLabel.getLocalBounds().width / 2) - 200, 125);

    levelValue.setFont(font);
    levelValue.setString("");
    levelValue.setCharacterSize(24);
    levelValue.setFillColor(sf::Color::Black);
    levelValue.setPosition((window.getSize().x / 2 - levelValue.getLocalBounds().width / 2) - 140, 125);

    levelInputBackground.setSize(sf::Vector2f(150, 40));
    levelInputBackground.setFillColor(sf::Color::White);
    levelInputBackground.setPosition((window.getSize().x / 2 - levelInputBackground.getLocalBounds().width / 2) - 80, 120);

    nameLabel.setFont(font);
    nameLabel.setString("Name:");
    nameLabel.setCharacterSize(24);
    nameLabel.setFillColor(sf::Color::Black);
    nameLabel.setPosition((window.getSize().x / 2 - nameLabel.getLocalBounds().width / 2) - 200, 200);

    nameValue.setFont(font);
    nameValue.setString("");
    nameValue.setCharacterSize(24);
    nameValue.setFillColor(sf::Color::Black);
    nameValue.setPosition((window.getSize().x / 2 - nameValue.getLocalBounds().width / 2) - 140, 205);

    nameInputBackground.setSize(sf::Vector2f(200, 40));
    nameInputBackground.setFillColor(sf::Color::White);
    nameInputBackground.setPosition((window.getSize().x / 2 - nameInputBackground.getLocalBounds().width / 2) - 50, 200);

    dropdownButton.setSize(sf::Vector2f(250, 50));
    dropdownButton.setFillColor(sf::Color::Transparent);
    dropdownButton.setPosition((window.getSize().x / 2 - dropdownButton.getLocalBounds().width / 2) - 110, 280);

    dropdownText.setFont(font);
    dropdownText.setString("Select Fighter Type: ");
    dropdownText.setCharacterSize(24);
    dropdownText.setFillColor(sf::Color::Black);
    dropdownText.setPosition((window.getSize().x / 2 - dropdownText.getLocalBounds().width / 2) - 110, 280);

    fighterOptions[static_cast<int>(FighterType::NIMBLE)].setFont(font);
    fighterOptions[static_cast<int>(FighterType::NIMBLE)].setString("Nimble");
    fighterOptions[static_cast<int>(FighterType::NIMBLE)].setCharacterSize(24);
    fighterOptions[static_cast<int>(FighterType::NIMBLE)].setFillColor(sf::Color::Black);
    fighterOptions[static_cast<int>(FighterType::NIMBLE)].setPosition((window.getSize().x / 2 - levelLabel.getLocalBounds().width / 2) - 200, 330);

    fighterOptions[static_cast<int>(FighterType::TANK)].setFont(font);
    fighterOptions[static_cast<int>(FighterType::TANK)].setString("Tank");
    fighterOptions[static_cast<int>(FighterType::TANK)].setCharacterSize(24);
    fighterOptions[static_cast<int>(FighterType::TANK)].setFillColor(sf::Color::Black);
    fighterOptions[static_cast<int>(FighterType::TANK)].setPosition((window.getSize().x / 2 - levelLabel.getLocalBounds().width / 2) - 200, 380);

    fighterOptions[static_cast<int>(FighterType::BULLY)].setFont(font);
    fighterOptions[static_cast<int>(FighterType::BULLY)].setString("Bully");
    fighterOptions[static_cast<int>(FighterType::BULLY)].setCharacterSize(24);
    fighterOptions[static_cast<int>(FighterType::BULLY)].setFillColor(sf::Color::Black);
    fighterOptions[static_cast<int>(FighterType::BULLY)].setPosition((window.getSize().x / 2 - levelLabel.getLocalBounds().width / 2) - 200, 430);

    createCharacterButton.setSize(sf::Vector2f(250, 50));
    createCharacterButton.setFillColor(sf::Color::Black);
    createCharacterButton.setPosition((window.getSize().x / 2 - createCharacterButtonText.getLocalBounds().width / 2) - 125, 500);

    createCharacterButtonText.setFont(font);
    createCharacterButtonText.setString("Create Character");
    createCharacterButtonText.setCharacterSize(24);
    createCharacterButtonText.setFillColor(sf::Color::White);
    createCharacterButtonText.setPosition((window.getSize().x / 2 - createCharacterButtonText.getLocalBounds().width / 2), 510);

    alertText.setFont(font);
    alertText.setString("Successfully created character!");
    alertText.setCharacterSize(24);
    alertText.setFillColor(sf::Color::Green); // Text color
    alertText.setPosition(window.getSize().x / 2 - alertText.getLocalBounds().width / 2, 570); // Adjust position as needed
}

void CharacterCreation::handleMainMenuClick(int mouseX, int mouseY) {
    // Handle clicks on main menu
}

void CharacterCreation::handleCharacterCreationClick(int mouseX, int mouseY) {
    // Handle clicks on character creation screen
    for (int i = 0; i < 3; ++i) {
        if (fighterOptions[i].getGlobalBounds().contains(mouseX, mouseY)) {
            dropdownText.setString(fighterOptions[i].getString());
            fighterType = fighterOptions[i].getString();
            dropdownOpen = false;
        }
    }

    if (nameInputBackground.getGlobalBounds().contains(mouseX, mouseY)) {
        activeField = NAME;
    }
    else if (levelInputBackground.getGlobalBounds().contains(mouseX, mouseY)) {
        activeField = LEVEL;
    }
    else if (dropdownButton.getGlobalBounds().contains(mouseX, mouseY)) {
        dropdownOpen = !dropdownOpen;
    }
    else if (createCharacterButton.getGlobalBounds().contains(mouseX, mouseY)) {
        // add logic for creating character here
        std::cout << "creating character..." << std::endl;
        cout << fighterType << endl;

        CharacterDirector director;
        Character* newCharacter;
        CharacterBuilder* characterBuilder;

        if (fighterType._Equal("Bully")) {
            characterBuilder = new BullyFighterBuilder;
        }
        else if (fighterType._Equal("Nimble")) {
            characterBuilder = new NimbleFighterBuilder;
        }
        else {
            characterBuilder = new TankFighterBuilder;
        }

        director.setBuilder(characterBuilder);
        newCharacter = director.buildCharacter(stoi(inputLevel), inputName);

        newCharacter->printCharacter();
        showSuccessfulAlert = true;
    }
}

void CharacterCreation::handleTextInput(sf::Uint32 unicode) {
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
    else if (activeField == LEVEL) {
        // Handle width and height input (numeric input)
        if (unicode >= '0' && unicode <= '9') {
            inputLevel += static_cast<char>(unicode);
            levelValue.setString(inputLevel);
        }
        else if (unicode == 8) { // Backspace logic
            if (inputLevel.size() > 0) {
                inputLevel.pop_back();
                levelValue.setString(inputLevel);
            }
        }
    }
}

void CharacterCreation::drawMainMenu(sf::RenderWindow& window) {
    // Draw main menu
}

void CharacterCreation::drawCharacterCreation() {
    // Draw character creation screen
    window.draw(worldBackground);

    window.draw(dropdownButton);
    window.draw(dropdownText);
    if (dropdownOpen) {
        for (int i = 0; i < 3; ++i) {
            window.draw(fighterOptions[i]);
        }
    }
    window.draw(titleLabel);

    window.draw(levelInputBackground);
    window.draw(levelLabel);
    window.draw(levelValue);

    window.draw(nameInputBackground);
    window.draw(nameValue);
    window.draw(nameLabel);

    window.draw(createCharacterButton);
    window.draw(createCharacterButtonText);
    window.draw(backButton);

    if (showSuccessfulAlert) {
        window.draw(alertText);
    }
}

bool CharacterCreation::isPrintableAscii(sf::Uint32 unicode)
{
    return (unicode >= 32 && unicode <= 126) || unicode == 8;
}

CharacterCreation::ActiveInputField CharacterCreation::getActiveField() const
{
    return activeField;
}
