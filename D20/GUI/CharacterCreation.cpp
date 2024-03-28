#include "CharacterCreation.h"
#include "../Character/CharacterDirector.h"
#include "../Character/CharacterBuilder.h"

CharacterCreation::CharacterCreation(sf::RenderWindow& window) : window(window), dropdownOpen(false), showSuccessfulAlert(false) {
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }

    backButton.setFont(font);
    backButton.setString("Go Back");
    backButton.setCharacterSize(24);
    backButton.setFillColor(sf::Color::Black);
    backButton.setPosition(25, 25);

    nameLabel.setFont(font);
    nameLabel.setString("Name:");
    nameLabel.setCharacterSize(24);
    nameLabel.setFillColor(sf::Color::Black);
    nameLabel.setPosition(100, 350);

    nameValue.setFont(font);
    nameValue.setString("");
    nameValue.setCharacterSize(24);
    nameValue.setFillColor(sf::Color::Black);
    nameValue.setPosition(210, 350);

    nameInputBackground.setSize(sf::Vector2f(200, 40));
    nameInputBackground.setFillColor(sf::Color::White);
    nameInputBackground.setPosition(200, 345);

    levelLabel.setFont(font);
    levelLabel.setString("Level: ");
    levelLabel.setCharacterSize(24);
    levelLabel.setFillColor(sf::Color::Black);
    levelLabel.setPosition(115, 70);

    levelValue.setFont(font);
    levelValue.setString("");
    levelValue.setCharacterSize(24);
    levelValue.setFillColor(sf::Color::Black);
    levelValue.setPosition(210, 75);

    levelInputBackground.setSize(sf::Vector2f(150, 40));
    levelInputBackground.setFillColor(sf::Color::White);
    levelInputBackground.setPosition(200, 70);

    createCharacterButton.setSize(sf::Vector2f(250, 50));
    createCharacterButton.setFillColor(sf::Color::Green);
    createCharacterButton.setPosition(100, 500);

    createCharacterButtonText.setFont(font);
    createCharacterButtonText.setString("Create Character");
    createCharacterButtonText.setCharacterSize(24);
    createCharacterButtonText.setFillColor(sf::Color::White);
    createCharacterButtonText.setPosition(115, 510);

    dropdownButton.setSize(sf::Vector2f(250, 50));
    dropdownButton.setFillColor(sf::Color::Transparent);
    dropdownButton.setPosition(110, 140);

    dropdownText.setFont(font);
    dropdownText.setString("Select Fighter Type: ");
    dropdownText.setCharacterSize(24);
    dropdownText.setFillColor(sf::Color::Black);
    dropdownText.setPosition(115, 150);

    fighterOptions[static_cast<int>(FighterType::NIMBLE)].setFont(font);
    fighterOptions[static_cast<int>(FighterType::NIMBLE)].setString("Nimble");
    fighterOptions[static_cast<int>(FighterType::NIMBLE)].setCharacterSize(24);
    fighterOptions[static_cast<int>(FighterType::NIMBLE)].setFillColor(sf::Color::Black);
    fighterOptions[static_cast<int>(FighterType::NIMBLE)].setPosition(110, 200);

    fighterOptions[static_cast<int>(FighterType::TANK)].setFont(font);
    fighterOptions[static_cast<int>(FighterType::TANK)].setString("Tank");
    fighterOptions[static_cast<int>(FighterType::TANK)].setCharacterSize(24);
    fighterOptions[static_cast<int>(FighterType::TANK)].setFillColor(sf::Color::Black);
    fighterOptions[static_cast<int>(FighterType::TANK)].setPosition(110, 250);

    fighterOptions[static_cast<int>(FighterType::BULLY)].setFont(font);
    fighterOptions[static_cast<int>(FighterType::BULLY)].setString("Bully");
    fighterOptions[static_cast<int>(FighterType::BULLY)].setCharacterSize(24);
    fighterOptions[static_cast<int>(FighterType::BULLY)].setFillColor(sf::Color::Black);
    fighterOptions[static_cast<int>(FighterType::BULLY)].setPosition(110, 300);

    alertText.setFont(font);
    alertText.setString("Successfully created character!");
    alertText.setCharacterSize(24);
    alertText.setFillColor(sf::Color::Black); // Text color
    alertText.setPosition(window.getSize().x / 2 - alertText.getLocalBounds().width / 2, 500); // Adjust position as needed
}

void CharacterCreation::handleMainMenuClick(int mouseX, int mouseY) {
    // Handle clicks on main menu
}

void CharacterCreation::handleCharacterCreationClick(int mouseX, int mouseY) {
    // Handle clicks on character creation screen
    if (dropdownButton.getGlobalBounds().contains(mouseX, mouseY)) {
        dropdownOpen = !dropdownOpen;
    }

    for (int i = 0; i < 3; ++i) {
        if (fighterOptions[i].getGlobalBounds().contains(mouseX, mouseY)) {
            dropdownText.setString(fighterOptions[i].getString());
            fighterType = fighterOptions[i].getString();
            dropdownOpen = false;
        }
    }

    if (createCharacterButton.getGlobalBounds().contains(mouseX, mouseY)) {
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
    // Handle text input for character creation
    if (unicode >= '0' && unicode <= '9') {
        inputLevel += static_cast<char>(unicode);
        levelValue.setString(inputLevel);
    }
    else if ((unicode >= 32 && unicode <= 126) || unicode == 8) {
        if (unicode == 8 && inputName.size() > 0) {
            inputName.pop_back();
            nameValue.setString(inputName);
        }
        else if (unicode != 8) {
            inputName += static_cast<char>(unicode);
            nameValue.setString(inputName);
        }
    }

}

void CharacterCreation::drawMainMenu(sf::RenderWindow& window) {
    // Draw main menu
}

void CharacterCreation::drawCharacterCreation() {
    // Draw character creation screen
    window.draw(dropdownButton);
    window.draw(dropdownText);
    if (dropdownOpen) {
        for (int i = 0; i < 3; ++i) {
            window.draw(fighterOptions[i]);
        }
    }
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
