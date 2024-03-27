#include <SFML/Graphics.hpp>
#include <iostream>
#include "Character/CharacterDirector.h"
using namespace std;

enum MenuState {
    MAIN_MENU,
    CHARACTER_CREATION,
    CREATE_MAP,
    CREATE_CAMPAIGN
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "D20 Game", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return 1;
    }

    sf::Texture worldBackgroundTex;
    sf::Sprite worldBackground;

    if (!worldBackgroundTex.loadFromFile("d20.jpg")) {
        cout << "ERROR: Game could not load background image" << "\n";
    }
    worldBackground.setScale(static_cast<float>(window.getSize().x) / worldBackgroundTex.getSize().x,
        static_cast<float>(window.getSize().y) / worldBackgroundTex.getSize().y);
    
    worldBackground.setTexture(worldBackgroundTex);

    sf::Text backButton;
    backButton.setFont(font);
    backButton.setString("Go Back");
    backButton.setCharacterSize(24);
    backButton.setFillColor(sf::Color::Black);
    backButton.setPosition(25, 25);

    sf::Text menuOptions[3];
    menuOptions[0].setFont(font);
    menuOptions[0].setString("Create Character");
    menuOptions[0].setCharacterSize(34);
    menuOptions[0].setFillColor(sf::Color::Black);
    menuOptions[0].setPosition(100, 300);

    menuOptions[1].setFont(font);
    menuOptions[1].setString("Create Map");
    menuOptions[1].setCharacterSize(34);
    menuOptions[1].setFillColor(sf::Color::Black);
    menuOptions[1].setPosition(100, 400);

    menuOptions[2].setFont(font);
    menuOptions[2].setString("Create Campaign");
    menuOptions[2].setCharacterSize(34);
    menuOptions[2].setFillColor(sf::Color::Black);
    menuOptions[2].setPosition(100, 500);

    sf::Text nameLabel;
    nameLabel.setFont(font);
    nameLabel.setString("Name:");
    nameLabel.setCharacterSize(24);
    nameLabel.setFillColor(sf::Color::Black);
    nameLabel.setPosition(100, 350);

    sf::Text nameValue;
    nameValue.setFont(font);
    nameValue.setString("");
    nameValue.setCharacterSize(24);
    nameValue.setFillColor(sf::Color::Black);
    nameValue.setPosition(210, 350);

    sf::RectangleShape nameInputBackground(sf::Vector2f(200, 40)); // Background for name input
    nameInputBackground.setFillColor(sf::Color::White);
    nameInputBackground.setPosition(200, 345);

    sf::Text levelLabel;
    levelLabel.setFont(font);
    levelLabel.setString("Level: ");
    levelLabel.setCharacterSize(24);
    levelLabel.setFillColor(sf::Color::Black);
    levelLabel.setPosition(115, 70);

    sf::Text levelValue;
    levelValue.setFont(font);
    levelValue.setString("");
    levelValue.setCharacterSize(24);
    levelValue.setFillColor(sf::Color::Black);
    levelValue.setPosition(210, 75);

    sf::RectangleShape levelInputBackground(sf::Vector2f(150, 40)); // Background for level input
    levelInputBackground.setFillColor(sf::Color::White);
    levelInputBackground.setPosition(200, 70);

    sf::RectangleShape createCharacterButton(sf::Vector2f(250, 50));
    createCharacterButton.setFillColor(sf::Color::Green);
    createCharacterButton.setPosition(100, 500);

    sf::Text createCharacterButtonText;
    createCharacterButtonText.setFont(font);
    createCharacterButtonText.setString("Create Character");
    createCharacterButtonText.setCharacterSize(24);
    createCharacterButtonText.setFillColor(sf::Color::White);
    createCharacterButtonText.setPosition(115, 510);

    sf::RectangleShape dropdownButton(sf::Vector2f(250, 50));
    dropdownButton.setFillColor(sf::Color::Transparent);
    dropdownButton.setPosition(110, 140);

    sf::Text dropdownText;
    dropdownText.setFont(font);
    dropdownText.setString("Select Fighter Type: ");
    dropdownText.setCharacterSize(24);
    dropdownText.setFillColor(sf::Color::Black);
    dropdownText.setPosition(115, 150);

    sf::Text fighterOptions[3];
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

    MenuState currentState = MAIN_MENU;

    Character* playerCharacter;

    bool dropdownOpen = false;
    string inputLevel;
    string inputName;
    bool showAlert = false;

    sf::Text alertText;
    alertText.setFont(font);
    alertText.setString("Successfully created character!");
    alertText.setCharacterSize(24);
    alertText.setFillColor(sf::Color::Black); // Text color
    alertText.setPosition(window.getSize().x / 2 - alertText.getLocalBounds().width / 2, 500); // Adjust position as needed

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (currentState == MAIN_MENU) {
                        for (int i = 0; i < 3; ++i) {
                            if (menuOptions[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                if (i == 0) {
                                    currentState = CHARACTER_CREATION;
                                }
                                // Add handling for other menu options here
                            }
                        }
                    }
                    else if (currentState == CHARACTER_CREATION) {
                        if (backButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                            currentState = MAIN_MENU;
                        }
                        if (dropdownButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            dropdownOpen = !dropdownOpen;
                        }
                        string fighterType = "";
                        for (int i = 0; i < 3; ++i) {
                            if (fighterOptions[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                //playerCharacter.fighterType = static_cast<FighterType>(i);
                                dropdownText.setString(fighterOptions[i].getString());
                                fighterType = fighterOptions[i].getString();
                                dropdownOpen = false;
                            }
                        }
                        if (createCharacterButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            // Add logic for creating character here
                            std::cout << "Creating character..." << std::endl;

                            CharacterDirector director;
                            Character* newCharacter;
                            CharacterBuilder* characterBuilder;

                            if (fighterType._Equal("bully")) {
                                characterBuilder = new BullyFighterBuilder;
                            }
                            else if (fighterType._Equal("nimble")) {
                                characterBuilder = new NimbleFighterBuilder;
                            }
                            else {
                                characterBuilder = new TankFighterBuilder;
                            }

                            director.setBuilder(characterBuilder);
                            newCharacter = director.buildCharacter(stoi(inputLevel), inputName);

                            newCharacter->printCharacter();
                            showAlert = true;
                        }
                    }
                }
                break;
            case sf::Event::TextEntered:
                if (currentState == CHARACTER_CREATION) {
                    if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                        inputLevel += static_cast<char>(event.text.unicode);
                        levelValue.setString(inputLevel);
                    }
                    else if ((event.text.unicode >= 32 && event.text.unicode <= 126) || event.text.unicode == 8) {
                        if (event.text.unicode == 8 && inputName.size() > 0) {
                            inputName.pop_back();
                            nameValue.setString(inputName);
                        }
                        else if (event.text.unicode != 8) {
                            inputName += static_cast<char>(event.text.unicode);
                            nameValue.setString(inputName);
                        }
                    }
                }
                break;
            }
        }

        window.clear();

        window.draw(worldBackground);

        if (currentState == MAIN_MENU) {
            for (int i = 0; i < 3; ++i) {
                window.draw(menuOptions[i]);
            }
        }
        else if (currentState == CHARACTER_CREATION) {
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

            if (showAlert) {
                window.draw(alertText);
            }
        }
        window.display();
    }

    return 0;
}