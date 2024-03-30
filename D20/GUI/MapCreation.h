#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class MapCreation {
public:
    enum ActiveInputField { CREATE, NAME, WIDTH, HEIGHT };
    MapCreation(sf::RenderWindow& window);

    void handleMainMenuClick(int mouseX, int mouseY);
    void handleMapCreationClick(int mouseX, int mouseY);
    void handleTextInput(sf::Uint32 unicode);
    void drawMainMenu(sf::RenderWindow& window);
    void drawMapCreation();
    bool isPrintableAscii(sf::Uint32 unicode);
    ActiveInputField getActiveField() const;

    sf::Text titleLabel;
    sf::Text nameLabel;
    sf::Text nameValue;
    sf::RectangleShape nameInputBackground;
    sf::Text widthLabel;
    sf::Text widthValue;
    sf::RectangleShape widthInputBackground;
    sf::Text heightLabel;
    sf::Text heightValue;
    sf::RectangleShape heightInputBackground;
    sf::RectangleShape createMapButton;
    sf::Text createMapButtonText;
    sf::Text alertTextSuccess;
    sf::Text alertTextFailure;

private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Texture worldBackgroundTex;
    sf::Sprite worldBackground;
    sf::Text backButton;

    bool showSuccessfulAlert;
    bool showFailureAlert;
    string inputName;
    string inputWidth;
    string inputHeight;
    ActiveInputField activeField;
};

