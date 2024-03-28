#include <SFML/Graphics.hpp>
#include <iostream>
#include "Character/CharacterDirector.h"
#include "GUI/CharacterCreation.h"
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

    MenuState currentState = MAIN_MENU;

    CharacterCreation characterCreation(window);

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
                        characterCreation.handleCharacterCreationClick(mousePos.x, mousePos.y);
                    }
                }
                break;
            case sf::Event::TextEntered:
                if (currentState == CHARACTER_CREATION) {
                    characterCreation.handleTextInput(event.text.unicode);
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
            characterCreation.drawCharacterCreation();
        }
        window.display();
    }

    return 0;
}