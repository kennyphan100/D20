#ifndef ITEM_CREATION_H
#define ITEM_CREATION_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class ItemCreation {
public:
    explicit ItemCreation(sf::RenderWindow& window);
    void drawItemCreation();
    void handleItemCreationClick(int mouseX, int mouseY);
    bool isPrintableAscii(sf::Uint32 unicode);
    void handleTextInput(sf::Uint32 unicode);

private:
    enum ActiveInputField {
        ARMOR_NAME
    };

    struct DropdownMenu {
        sf::RectangleShape box;
        sf::Text title;
        std::vector<sf::Text> options;
        bool expanded = false;
        int selectedIndex = -1;
    };

    sf::RenderWindow& window;
    sf::Texture worldBackgroundTex;
    sf::Sprite worldBackground;
    sf::Font font;
    sf::Text backButton;
    sf::Text titleLabel;
    sf::Text createItemButtonText;
    sf::RectangleShape createItemButton;
    sf::Text alertText;
    DropdownMenu armorTypeMenu;
    DropdownMenu enhancementMenu;
    DropdownMenu bonusMenu;

    bool showSuccessfulAlert;
    bool showFailureAlert;

    sf::RectangleShape armorNameInputBox;
    sf::Text armorNameText;
    sf::Text armorNameLabel;
    std::string armorName;
 
 
    ActiveInputField activeField;

    void drawDropdown(DropdownMenu& menu, sf::RenderWindow& window);
    void toggleDropdown(DropdownMenu& menu, int mouseX, int mouseY);
    void createItem();
    ActiveInputField getActiveField() const;
};

#endif // ITEM_CREATION_H