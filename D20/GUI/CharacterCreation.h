#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class CharacterCreation {
public:
    CharacterCreation(sf::RenderWindow& window);

    void handleMainMenuClick(int mouseX, int mouseY);
    //void handleCharacterCreationClick(int mouseX, int mouseY);
    void handleCharacterCreationClick(int mouseX, int mouseY);
    void handleTextInput(sf::Uint32 unicode);
    void drawMainMenu(sf::RenderWindow& window);
    void drawCharacterCreation();

    sf::Text nameLabel;

    sf::Text nameValue;

    sf::RectangleShape nameInputBackground; // Background for name input

    sf::Text levelLabel;

    sf::Text levelValue;

    sf::RectangleShape levelInputBackground; // Background for level input

    sf::RectangleShape createCharacterButton;

    sf::Text createCharacterButtonText;

    sf::RectangleShape dropdownButton;

    sf::Text dropdownText;

    sf::Text fighterOptions[3];

    sf::Text alertText;

private:
    sf::RenderWindow& window;
    sf::Font font;
    //sf::Texture worldBackgroundTex;
    //sf::Sprite worldBackground;
    sf::Text backButton;

    bool dropdownOpen;
    bool showSuccessfulAlert;
    string inputLevel;
    string inputName;
    string fighterType;
};
