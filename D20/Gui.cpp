#include <SFML/Graphics.hpp>
#include <iostream>
#include "Character/CharacterDirector.h"
#include "GUI/CharacterCreation.h"
#include "GUI/MapCreation.h"
using namespace std;

enum MenuState {
    MAIN_MENU,
    EDITOR,
    CHARACTER_CREATION,
    MAP_CREATION,
    CAMPAIGN_CREATION,
    EDIT_MAP,
    EDIT_CAMPAIGN
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

    if (!worldBackgroundTex.loadFromFile("./Images/d20.jpg")) {
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

    sf::Text menuOptions[2];
    menuOptions[0].setFont(font);
    menuOptions[0].setString("Create Character");
    menuOptions[0].setCharacterSize(34);
    menuOptions[0].setFillColor(sf::Color::Black);
    menuOptions[0].setPosition(100, 300);

    menuOptions[1].setFont(font);
    menuOptions[1].setString("Editor");
    menuOptions[1].setCharacterSize(34);
    menuOptions[1].setFillColor(sf::Color::Black);
    menuOptions[1].setPosition(100, 400);

    sf::Text editorOptions[4];
    editorOptions[0].setFont(font);
    editorOptions[0].setString("Create Map");
    editorOptions[0].setCharacterSize(34);
    editorOptions[0].setFillColor(sf::Color::Black);
    editorOptions[0].setPosition(100, 200);

    editorOptions[1].setFont(font);
    editorOptions[1].setString("Edit Map");
    editorOptions[1].setCharacterSize(34);
    editorOptions[1].setFillColor(sf::Color::Black);
    editorOptions[1].setPosition(100, 300);

    editorOptions[2].setFont(font);
    editorOptions[2].setString("Create Campaign");
    editorOptions[2].setCharacterSize(34);
    editorOptions[2].setFillColor(sf::Color::Black);
    editorOptions[2].setPosition(100, 400);

    editorOptions[3].setFont(font);
    editorOptions[3].setString("Edit Campaign");
    editorOptions[3].setCharacterSize(34);
    editorOptions[3].setFillColor(sf::Color::Black);
    editorOptions[3].setPosition(100, 500);

    MenuState currentState = MAIN_MENU;

    CharacterCreation characterCreation(window);
    MapCreation mapCreation(window);

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
                        for (int i = 0; i < 2; ++i) {
                            if (menuOptions[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                if (i == 0) {
                                    currentState = CHARACTER_CREATION;
                                }
                                else if (i == 1) {
                                    currentState = EDITOR;
                                }
                                // Add handling for other menu options here
                            }
                        }
                    }
                    else if (currentState == EDITOR) {
                        if (backButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                            currentState = MAIN_MENU;
                        }
                        for (int i = 0; i < 4; ++i) {
                            if (editorOptions[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                if (i == 0) {
                                    currentState = MAP_CREATION;
                                }
                                else if (i == 1) {
                                    currentState = EDIT_MAP;
                                }
                                else if (i == 2) {
                                    currentState = CAMPAIGN_CREATION;
                                }
                                else if (i == 3) {
                                    currentState = EDIT_CAMPAIGN;
                                }
                                // Add handling for other menu options here
                            }
                        }
                    }
                    else if (currentState == CHARACTER_CREATION) {
                        if (backButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                            currentState = MAIN_MENU;
                        }
                        characterCreation.handleCharacterCreationClick(mousePos.x, mousePos.y);
                    }
                    else if (currentState == MAP_CREATION) {
                        if (backButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                            currentState = EDITOR;
                        }
                        mapCreation.handleMapCreationClick(mousePos.x, mousePos.y);
                    }
                    else if (currentState == EDIT_MAP) {
                        if (backButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                            currentState = EDITOR;
                        }
                        mapCreation.handleMapCreationClick(mousePos.x, mousePos.y);
                    }
                    else if (currentState == CAMPAIGN_CREATION) {
                        if (backButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                            currentState = EDITOR;
                        }
                        mapCreation.handleMapCreationClick(mousePos.x, mousePos.y);
                    }
                    else if (currentState == EDIT_CAMPAIGN) {
                        if (backButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                            currentState = EDITOR;
                        }
                        mapCreation.handleMapCreationClick(mousePos.x, mousePos.y);
                    }
                }
                break;
            case sf::Event::TextEntered:
                if (currentState == CHARACTER_CREATION) {
                    characterCreation.handleTextInput(event.text.unicode);
                }
                else if (currentState == MAP_CREATION) {
                    if (mapCreation.getActiveField() == MapCreation::NAME) {
                        mapCreation.handleTextInput(event.text.unicode);
                    }
                    else if (mapCreation.getActiveField() == MapCreation::WIDTH) {
                        mapCreation.handleTextInput(event.text.unicode);
                    }
                    else if (mapCreation.getActiveField() == MapCreation::HEIGHT) {
                        mapCreation.handleTextInput(event.text.unicode);
                    }
                }
                else if (currentState == EDIT_MAP) {
                    if (mapCreation.getActiveField() == MapCreation::NAME) {
                        mapCreation.handleTextInput(event.text.unicode);
                    }
                    else if (mapCreation.getActiveField() == MapCreation::WIDTH) {
                        mapCreation.handleTextInput(event.text.unicode);
                    }
                    else if (mapCreation.getActiveField() == MapCreation::HEIGHT) {
                        mapCreation.handleTextInput(event.text.unicode);
                    }
                }
                else if (currentState == CAMPAIGN_CREATION) {
                    if (mapCreation.getActiveField() == MapCreation::NAME) {
                        mapCreation.handleTextInput(event.text.unicode);
                    }
                    else if (mapCreation.getActiveField() == MapCreation::WIDTH) {
                        mapCreation.handleTextInput(event.text.unicode);
                    }
                    else if (mapCreation.getActiveField() == MapCreation::HEIGHT) {
                        mapCreation.handleTextInput(event.text.unicode);
                    }
                }
                else if (currentState == EDIT_CAMPAIGN) {
                    if (mapCreation.getActiveField() == MapCreation::NAME) {
                        mapCreation.handleTextInput(event.text.unicode);
                    }
                    else if (mapCreation.getActiveField() == MapCreation::WIDTH) {
                        mapCreation.handleTextInput(event.text.unicode);
                    }
                    else if (mapCreation.getActiveField() == MapCreation::HEIGHT) {
                        mapCreation.handleTextInput(event.text.unicode);
                    }
                }
                break;
            }
        }

        window.clear();

        window.draw(worldBackground);

        if (currentState == MAIN_MENU) {
            for (int i = 0; i < 2; ++i) {
                window.draw(menuOptions[i]);
            }
        }
        else if (currentState == EDITOR) {
            window.draw(backButton);
            for (int i = 0; i < 4; ++i) {
                window.draw(editorOptions[i]);
            }
        }
        else if (currentState == CHARACTER_CREATION) {
            characterCreation.drawCharacterCreation();
        }
        else if (currentState == MAP_CREATION) {
            mapCreation.drawMapCreation();
        }
        else if (currentState == EDIT_MAP) {
            mapCreation.drawMapCreation();
        }
        else if (currentState == CAMPAIGN_CREATION) {
            mapCreation.drawMapCreation();
        }
        else if (currentState == EDIT_CAMPAIGN) {
            mapCreation.drawMapCreation();
        }
        window.display();
    }

    return 0;
}