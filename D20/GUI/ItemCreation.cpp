#include "ItemCreation.h"
#include "../Item/Item.h"
#include "../Character/Character.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

using namespace std;

ItemCreation::ItemCreation(sf::RenderWindow& window) : window(window), showSuccessfulAlert(false), showFailureAlert(false) {
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Failed to load font" << endl;
    }

    if (!worldBackgroundTex.loadFromFile("./Images/background2.jpg")) {
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

 
    createItemButton.setSize(sf::Vector2f(200, 50));
    createItemButton.setFillColor(sf::Color::Black);
    createItemButton.setPosition((window.getSize().x / 2) - (createItemButton.getLocalBounds().width / 2), 450);

    createItemButtonText.setFont(font);
    createItemButtonText.setString("Create Item");
    createItemButtonText.setCharacterSize(24);
    createItemButtonText.setFillColor(sf::Color::White);
    createItemButtonText.setPosition((window.getSize().x / 2) - (createItemButtonText.getLocalBounds().width / 2), 460);

    alertText.setFont(font);
    alertText.setCharacterSize(24);
    alertText.setFillColor(sf::Color::Red); 
    alertText.setStyle(sf::Text::Bold);
    alertText.setPosition(window.getSize().x / 2 - alertText.getLocalBounds().width / 2 -160, 510);

    
    armorTypeMenu.box.setSize(sf::Vector2f(220, 60));
    armorTypeMenu.box.setFillColor(sf::Color::Black);
    armorTypeMenu.box.setPosition(50, 150); 

    armorTypeMenu.title.setFont(font);
    armorTypeMenu.title.setCharacterSize(24);
    armorTypeMenu.title.setString("Select Armor Type");
    armorTypeMenu.title.setPosition(armorTypeMenu.box.getPosition().x, armorTypeMenu.box.getPosition().y - 30);

  
    enhancementMenu.box.setSize(sf::Vector2f(220, 60));
    enhancementMenu.box.setFillColor(sf::Color::Black);
    enhancementMenu.box.setPosition(armorTypeMenu.box.getPosition().x + armorTypeMenu.box.getSize().x + 60, armorTypeMenu.box.getPosition().y);

    enhancementMenu.title.setFont(font);
    enhancementMenu.title.setCharacterSize(24);
    enhancementMenu.title.setString("Select Enhancement");
    enhancementMenu.title.setPosition(enhancementMenu.box.getPosition().x, enhancementMenu.box.getPosition().y - 30);

    bonusMenu.box.setSize(sf::Vector2f(220, 60));
    bonusMenu.box.setFillColor(sf::Color::Black);
    bonusMenu.box.setPosition(enhancementMenu.box.getPosition().x + enhancementMenu.box.getSize().x + 60, enhancementMenu.box.getPosition().y);

    bonusMenu.title.setFont(font);
    bonusMenu.title.setCharacterSize(24);
    bonusMenu.title.setString("Select Bonus");
    bonusMenu.title.setPosition(bonusMenu.box.getPosition().x, bonusMenu.box.getPosition().y - 30);

    armorNameInputBox.setSize(sf::Vector2f(300, 60));
    armorNameInputBox.setFillColor(sf::Color::Black);
    armorNameInputBox.setOutlineColor(sf::Color::Black);
    armorNameInputBox.setOutlineThickness(1);
    armorNameInputBox.setPosition(bonusMenu.box.getPosition().x + bonusMenu.box.getSize().x + 60, bonusMenu.box.getPosition().y);  // Adjust as needed

    armorNameText.setFont(font);
    armorNameText.setCharacterSize(24);
    armorNameText.setFillColor(sf::Color::White);
    armorNameText.setPosition(armorNameInputBox.getPosition() + sf::Vector2f(10, 10));

    armorNameLabel.setFont(font);
    armorNameLabel.setString("Armor Name");
    armorNameLabel.setCharacterSize(24);
    armorNameLabel.setFillColor(sf::Color::White);
    armorNameLabel.setPosition(armorNameInputBox.getPosition().x, armorNameInputBox.getPosition().y - 35);

    
    sf::Text bonusOption;
    bonusOption.setFont(font);
    bonusOption.setCharacterSize(24);
    std::vector<std::string> bonus = { "1","2","3","4","5"};
    for (const auto& item : bonus) {
        bonusOption.setString(item);
        bonusOption.setPosition(bonusMenu.box.getPosition().x, bonusMenu.box.getPosition().y + bonusMenu.box.getSize().y);
        bonusMenu.options.push_back(bonusOption);

    }

    sf::Text enhancementOption;
    enhancementOption.setFont(font);
    enhancementOption.setCharacterSize(24);

    float optionHeight2 = enhancementOption.getLocalBounds().height + 5;


    std::vector<std::string> armorItems = {"Intelligence", "Wisdom", "Armor class", "Strength", "Constitution", "Wisdom", "Charisma", "Dexterity", "Attack Bonus", "Damage Bonus"};
    for (const auto& item : armorItems) {
        enhancementOption.setString(item);
        enhancementOption.setPosition(enhancementMenu.box.getPosition().x, enhancementMenu.box.getPosition().y + enhancementMenu.box.getSize().y + armorItems.size() * optionHeight2);
        enhancementMenu.options.push_back(enhancementOption);
    }


    sf::Text armorTypeOption;
    armorTypeOption.setFont(font);
    armorTypeOption.setCharacterSize(24);

    float optionHeight = armorTypeOption.getLocalBounds().height + 5;

    std::vector<std::string> items = { "Helmet", "Armor", "Shield", "Ring", "Belt", "Boots" };
    for (const auto& item : items) {
        armorTypeOption.setString(item);
        armorTypeOption.setPosition(armorTypeMenu.box.getPosition().x, armorTypeMenu.box.getPosition().y + armorTypeMenu.box.getSize().y + items.size() * optionHeight);
        armorTypeMenu.options.push_back(armorTypeOption);
    }
}


void ItemCreation::handleTextInput(sf::Uint32 unicode) {
    if (activeField == ARMOR_NAME) { // Assume ARMOR_NAME is an enum value for the active input field
        if (isPrintableAscii(unicode)) {
            if (unicode == 8 && armorName.size() > 0) { // Backspace pressed
                armorName.pop_back();
            }
            else if (unicode != 8) {
                armorName += static_cast<char>(unicode);
            }
            armorNameText.setString(armorName);
        }
    }
}

void ItemCreation::handleItemCreationClick(int mouseX, int mouseY) {
    sf::Vector2f mousePos(mouseX, mouseY);
    if (armorTypeMenu.box.getGlobalBounds().contains(mousePos)) {
        armorTypeMenu.expanded = !armorTypeMenu.expanded;
    }

    if (armorNameInputBox.getGlobalBounds().contains(mousePos)) {
        activeField = ARMOR_NAME; 
        armorNameInputBox.setOutlineColor(sf::Color::White);
    }

    else if (armorTypeMenu.expanded) {
        float offsetY = armorTypeMenu.box.getSize().y;
        for (int i = 0; i < armorTypeMenu.options.size(); ++i) {
            sf::FloatRect optionBounds = armorTypeMenu.options[i].getGlobalBounds();
            optionBounds.top = armorTypeMenu.box.getPosition().y + offsetY;
            if (optionBounds.contains(mousePos)) {
                armorTypeMenu.selectedIndex = i;
                armorTypeMenu.expanded = false;
                break;
            }
            offsetY += armorTypeMenu.options[i].getLocalBounds().height + 5;  // Add some padding
        }
    }

    if (enhancementMenu.box.getGlobalBounds().contains(mousePos)) {
        enhancementMenu.expanded = !enhancementMenu.expanded;
    }
    else if (enhancementMenu.expanded) {
        float offsetY = enhancementMenu.box.getSize().y;
        for (int i = 0; i < enhancementMenu.options.size(); ++i) {
            sf::FloatRect optionBounds = enhancementMenu.options[i].getGlobalBounds();
            optionBounds.top = enhancementMenu.box.getPosition().y + offsetY;
            if (optionBounds.contains(mousePos)) {
                enhancementMenu.selectedIndex = i;
                enhancementMenu.expanded = false;
                break;
            }
            offsetY += enhancementMenu.options[i].getLocalBounds().height + 5;
        }
    }

    if (bonusMenu.box.getGlobalBounds().contains(mousePos)) {
        bonusMenu.expanded = !bonusMenu.expanded;
    }
    else if (bonusMenu.expanded) {
        float offsetY = bonusMenu.box.getSize().y;
        for (int i = 0; i < bonusMenu.options.size(); ++i) {
            sf::FloatRect optionBounds = bonusMenu.options[i].getGlobalBounds();
            optionBounds.top = bonusMenu.box.getPosition().y + offsetY;
            if (optionBounds.contains(mousePos)) {
                bonusMenu.selectedIndex = i;
                bonusMenu.expanded = false;
                break;
            }
            offsetY += bonusMenu.options[i].getLocalBounds().height + 5;
        }
    }
    if (createItemButton.getGlobalBounds().contains(mousePos)) {
        createItem();  
    }
    
}


void ItemCreation::drawItemCreation() {
    window.draw(worldBackground);
    window.draw(titleLabel);
    window.draw(createItemButton);
    window.draw(createItemButtonText);
    window.draw(backButton);
    drawDropdown(armorTypeMenu, window);
    drawDropdown(enhancementMenu, window);
    drawDropdown(bonusMenu, window);

    window.draw(armorNameLabel);
    window.draw(armorNameInputBox);
    window.draw(armorNameText);
  
    if (showSuccessfulAlert) {
        alertText.setString("Item successfully created!");
        window.draw(alertText);
    }
    else if (showFailureAlert) {
        alertText.setString("Failed to create item. Please try again.");
        window.draw(alertText);
    }
}

void ItemCreation::drawDropdown(DropdownMenu& menu, sf::RenderWindow& window) {
    window.draw(menu.box);
    window.draw(menu.title);

    if (menu.expanded) {
        float offsetY = menu.box.getSize().y;
        for (auto& option : menu.options) {
            option.setPosition(menu.box.getPosition().x, menu.box.getPosition().y + offsetY);
            window.draw(option);
            offsetY += option.getLocalBounds().height + 5;  // Add some padding
        }
    }
    else if (menu.selectedIndex >= 0) {
        sf::Text selectedOption = menu.options[menu.selectedIndex];
        selectedOption.setPosition(menu.box.getPosition());
        window.draw(selectedOption);
    }
}

bool ItemCreation::isPrintableAscii(sf::Uint32 unicode) {
    return (unicode >= 32 && unicode <= 126) || unicode == 8;
}

ItemCreation::ActiveInputField ItemCreation::getActiveField() const {
    return activeField;
}

void ItemCreation::createItem() {
    if (armorTypeMenu.selectedIndex < 0 || enhancementMenu.selectedIndex < 0 || bonusMenu.selectedIndex < 0) {
        showFailureAlert = true;
        return;
    }

    // Gather the selected options
    std::string armorType = armorTypeMenu.options[armorTypeMenu.selectedIndex].getString();
    std::string enhancementTypeStr = enhancementMenu.options[enhancementMenu.selectedIndex].getString();
    std::string bonusStr = bonusMenu.options[bonusMenu.selectedIndex].getString();

    // Convert enhancementTypeStr and bonusStr to the proper types
    EnhancementType enhancementType = stringToEnhancementType(enhancementTypeStr);
    int bonus = std::stoi(bonusStr);

    // Create the item based on the armor type
    Item* item = nullptr;
    if (armorType == "Helmet") {
        item = new Helmet(armorName, enhancementType, bonus);
    }
    else if (armorType == "Armor") {
        item = new Armor(armorName, enhancementType, bonus);
    }
    else if (armorType == "Ring") {
        item = new Ring(armorName, enhancementType, bonus);
    }
    else if (armorType == "Boots") {
        item = new Boots(armorName, enhancementType, bonus);
    }
    else if (armorType == "Weapon") {
        item = new Weapon(armorName, enhancementType, bonus);
    }
    else if (armorType == "Shield") {
        item = new Ring(armorName, enhancementType, bonus);
    }

    if (item) {

        std::string filename = "./data/items/" + armorName + ".txt";;
        if (item->saveToFile(filename, armorType)) {
            std::cout << "Item details saved to file: " << filename << std::endl;
        }
        else {
            std::cerr << "Failed to save item details to file." << std::endl;
        }

        std::cout << "Creating item with the following details:" << std::endl;
        std::cout << "Armor Type: " << armorType << std::endl;
        std::cout << "Enhancement Type: " << enhancementTypeStr << std::endl;
        std::cout << "Bonus: " << bonus << std::endl;

 
        showSuccessfulAlert = true;
    }
    else {
        std::cerr << "Invalid armor type selected." << std::endl;
        showFailureAlert = true;
    }
}
