#include <SFML/Graphics.hpp>
#include <iostream>
#include "Character/CharacterDirector.h"
#include "GUI/CharacterCreation.h"
#include "GUI/MapCreation.h"
#include "GUI/CampaignCreation.h"
#include "GUI/MapEdit.h"
#include "GUI/ItemCreation.h"
#include "GUI/PlayGameMenu.h"


using namespace std;

enum MenuState {
    MAIN_MENU,
    EDITOR,
    CHARACTER_CREATION,
    MAP_CREATION,
    MAP_EDIT,
    CAMPAIGN_CREATION,
    EDIT_MAP,
    EDIT_CAMPAIGN,
    PLAY_GAME_MENU,
    ITEM_MENU
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
    
    const int NUMBER_OF_ITEMS_IN_MENU = 4;
    sf::Text menuOptions[NUMBER_OF_ITEMS_IN_MENU];

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

    menuOptions[2].setFont(font);
    menuOptions[2].setString("Start Game");
    menuOptions[2].setCharacterSize(38);
    menuOptions[2].setStyle(sf::Text::Bold);
    menuOptions[2].setFillColor(sf::Color(153, 0, 0));
    menuOptions[2].setPosition((window.getSize().x / 2 - menuOptions[2].getLocalBounds().width / 2), 500);

    menuOptions[3].setFont(font);
    menuOptions[3].setString("Create Item");
    menuOptions[3].setCharacterSize(34);
    menuOptions[3].setFillColor(sf::Color::Black);
    menuOptions[3].setPosition(100, 500); // Position the button appropriately

    sf::RectangleShape startGameInputBackground;
    startGameInputBackground.setSize(sf::Vector2f(245, 50));
    startGameInputBackground.setFillColor(sf::Color::Black);
    startGameInputBackground.setPosition((window.getSize().x / 2 - menuOptions[2].getLocalBounds().width / 2) - 10, 500);

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
    MapEdit mapEdit(window);
    CampaignCreation campaignCreation(window);
    PlayGameMenu PlayGameMenu(window);
    ItemCreation itemCreation(window);

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
                        for (int i = 0; i < NUMBER_OF_ITEMS_IN_MENU; ++i) {
                            if (menuOptions[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                if (i == 0) {
                                    currentState = CHARACTER_CREATION;
                                }
                                else if (i == 1) {
                                    currentState = EDITOR;
                                }
                                else if (i == 2) {
                                    currentState = PLAY_GAME_MENU;
                                }
                                else if (i == 3) {
                                    currentState = ITEM_MENU;
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

                    else if (currentState == ITEM_MENU) {
                        if (backButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                            currentState = MAIN_MENU;
                        }
                        itemCreation.handleItemCreationClick(mousePos.x, mousePos.y);
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
                        mapEdit.handleMapEditClick(mousePos.x, mousePos.y);
                    }
                    else if (currentState == CAMPAIGN_CREATION) {
                        if (backButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                            currentState = EDITOR;
                        }
                        campaignCreation.handleCampaignCreationClick(mousePos.x, mousePos.y);
                    }
                    else if (currentState == EDIT_CAMPAIGN) {
                        if (backButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                            currentState = EDITOR;
                        }
                        mapCreation.handleMapCreationClick(mousePos.x, mousePos.y);
                    }
                    else if (currentState == PLAY_GAME_MENU) {
                        if (backButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                            currentState = MAIN_MENU;
                        }
                        PlayGameMenu.handlePlayGameMenuClick(mousePos.x, mousePos.y);
                    }
                }
                else if (event.mouseButton.button == sf::Mouse::Right) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    if (currentState == EDIT_MAP) {
                        if (backButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                            currentState = EDITOR;
                        }
                        mapEdit.handleRemoveObject(mousePos.x, mousePos.y);
                    }
                }
                break;
            case sf::Event::TextEntered:
                if (currentState == CHARACTER_CREATION) {
                    characterCreation.handleTextInput(event.text.unicode);
                }
                else if (currentState == ITEM_MENU) {
                    itemCreation.handleTextInput(event.text.unicode);
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
                    if (campaignCreation.getActiveField() == CampaignCreation::NAME) {
                        campaignCreation.handleTextInput(event.text.unicode);
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
            window.draw(startGameInputBackground);
            for (int i = 0; i < NUMBER_OF_ITEMS_IN_MENU; ++i) {
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
        else if (currentState == ITEM_MENU) {
            itemCreation.drawItemCreation();
        }

        else if (currentState == MAP_CREATION) {
            mapCreation.drawMapCreation();
        }
        else if (currentState == EDIT_MAP) {
            mapEdit.drawMapEdit();
        }
        else if (currentState == CAMPAIGN_CREATION) {
            campaignCreation.drawCampaignCreation();
        }
        else if (currentState == EDIT_CAMPAIGN) {
            mapCreation.drawMapCreation();
        }
        else if (currentState == PLAY_GAME_MENU) {
            PlayGameMenu.drawPlayGameMenu();
        }
        window.display();
    }

    return 0;
}