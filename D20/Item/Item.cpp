//! @file 
//! @brief Implementation file for Item.h
//!

#include "Item.h"
#include <iostream>

using namespace std;

//! Constructor for Item class.
//! @param name The name of the item.
//! @return new Item object
Item::Item(string name): name(move(name)) {}

//! Constructor for ItemContainer class.
//! @param name The name of the item container.
//! @return new ItemContainer object
ItemContainer::ItemContainer(string name): name(move(name)) {}

//! Constructor for Backpack class.
//! @param name The name of the backpack.
//! @return new Backpack object
Backpack::Backpack(string name): ItemContainer(name) {}

//! Constructor for Helmet class.
//! @param name The name of the helmet.
//! @return new Helmet object
Helmet::Helmet(string name) : Item(move(name)) {
}

//! Retrieves an enhancement and its bonus for the helmet.
//! @return A pair containing the enhancement and its bonus.
pair<Enhancements, int> Helmet::getEnhancement() const {
    int bonus = rand() % 5 + 1;
    Enhancements enhance;

    if (rand() % 3 == 0)
        enhance = Enhancements::wisdom;
    else if (rand() % 3 == 1)
        enhance = Enhancements::intelligence;
    else
        enhance = Enhancements::armorClass;

    return { enhance, bonus };
}

//! Constructor for Armor class.
//! @param name The name of the armor.
//! @return new Armor object
Armor::Armor(string name): Item(move(name)) {
}

//! Retrieves the enhancement and its bonus for the armor.
//! @return A pair containing the enhancement and its bonus.
pair<Enhancements, int> Armor::getEnhancement() const {
    int armorBonus = rand() %5+1;
    return {Enhancements::armorClass, armorBonus};
}

//! Constructor for Shield class.
//! @param name The name of the shield.
//! @return new Shield object
Shield::Shield(string name): Item(move(name)) {
}

//! Retrieves the enhancement and its bonus for the shield.
//! @return A pair containing the enhancement and its bonus.
pair<Enhancements, int> Shield::getEnhancement() const {
    int armorBonus = rand() %5+1;
    return {Enhancements::armorClass, armorBonus};
}

//! Constructor for Ring class.
//! @param name The name of the ring.
//! @return new Ring object
Ring::Ring(string name) : Item(move(name)) {
}

//! Retrieves a random enhancement and its bonus for the ring.
//! @return A pair containing the enhancement and its bonus.
pair<Enhancements, int> Ring::getEnhancement() const {
    int bonus = rand() % 5 + 1;
    Enhancements enhance;

    if (rand() % 5 == 0)
        enhance = Enhancements::strength;
    else if (rand() % 5 == 1)
        enhance = Enhancements::constitution;
    else if (rand() % 5 == 2)
        enhance = Enhancements::armorClass;
    else if (rand() % 5 == 3)
        enhance = Enhancements::wisdom;
    else
        enhance = Enhancements::charisma;

    return { enhance, bonus };
}

//! Constructor for Belt class.
//! @param name The name of the belt.
//! @return new Belt object
Belt::Belt(string name) : Item(move(name)) {
}

//! Retrieves a random enhancement and its bonus for the belt.
//! @return A pair containing the enhancement and its bonus.
pair<Enhancements, int> Belt::getEnhancement() const {
    int bonus = rand() % 5 + 1;
    Enhancements enhance;

    if (rand() % 2 == 0)
        enhance = Enhancements::constitution;
    else
        enhance = Enhancements::strength;

    return { enhance, bonus };
}

//! Constructor for Boots class.
//! @param name The name of the boots.
//! @return new Boots object
Boots::Boots(string name): Item(move(name)) {
}

//! Retrieves a random enhancement and its bonus for the boots.
//! @return A pair containing the enhancement and its bonus.
pair<Enhancements, int> Boots::getEnhancement() const {
    int bonus = rand() %5+1;
    Enhancements enhance;
    
    if (rand() % 2 == 0)
        enhance = Enhancements::dexterity;
    else
        enhance = Enhancements::armorClass;

    return { enhance, bonus };
}

//! Constructor for Weapon class.
//! @param name The name of the weapon.
//! @return new Weapon object
Weapon::Weapon(string name) : Item(move(name)) {
}

//! Retrieves a random enhancement and its bonus for the weapon.
//! @return A pair containing the enhancement and its bonus.
pair<Enhancements, int> Weapon::getEnhancement() const {
    int bonus = rand() % 5 + 1;
    Enhancements enhance;

    if (rand() % 2 == 0)
        enhance = Enhancements::attackBonus;
    else
        enhance = Enhancements::damageBonus;

    return { enhance, bonus };
}

//! Converts an enhancement enum value to its string representation.
//! @param enhancement The enhancement enum value.
//! @return The string representation of the enhancement.
string enhancementToString(Enhancements enhancement) {
    switch (enhancement) {
        case Enhancements::damageBonus:
            return "Damage Bonus";
        case Enhancements::attackBonus:
            return "Attack Bonus";
        case Enhancements::armorClass:
            return "Armor Class";
        case Enhancements::strength:
            return "Strength";
        case Enhancements::dexterity:
            return "Dexterity";
        case Enhancements::wisdom:
            return "Wisdom";
        case Enhancements::intelligence:
            return "Intelligence";
        case Enhancements::constitution:
            return "Constitution";
        case Enhancements::charisma:
            return "Charisma";
        default:
            return "Unknown Enhancement";
    }
}

//! Adds an item to the item container.
//! @param item Pointer to the item to be added.
void ItemContainer::addItem(Item* item){
    items.push_back(item);
}

//! Removes an item from the item container.
//! @param label The name of the item to be removed.
void ItemContainer::removeItem(const string& label){

    for(auto element = items.begin(); element != items.end(); ++element){
        if ((*element)->name == label){
            delete *element;
            items.erase(element);
            break;
        }
    }
}

//! Retrieves an item from the item container by name.
//! @param itemName The name of the item to be retrieved.
//! @return Pointer to the item if found, nullptr otherwise.
Item* ItemContainer::getItemByName(const string& itemName) const {
    for (const auto& item : items) {
        if (item->name == itemName) {
            return item;
        }
    }
    return nullptr; 
}

//! Displays name and enhancement and bonus information about an item.
void Item::displayItem() const {
    cout << name << endl;
    cout << "Enhancement: " << enhancementToString(getEnhancement().first) << ", Enhancement Bonus: " << getEnhancement().second << endl << endl;
}

//! Displays all items' information from the item container.
void ItemContainer::displayItems() const {
    cout << " ====== Items in " << name << ": ======" << endl;
    for (const auto& item : items) {
        item->displayItem();
    }
}

int ItemContainer::getSize() const {
    return items.size();
}