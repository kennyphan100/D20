#include "Item.h"
#include <iostream>

using namespace std;

Item::Item(string name): name(move(name)) {}

ItemContainer::ItemContainer(string name): name(move(name)) {}

Backpack::Backpack(string name): ItemContainer(name) {}

Helmet::Helmet(string name) : Item(move(name)) {
}

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

Armor::Armor(string name): Item(move(name)) {
}

pair<Enhancements, int> Armor::getEnhancement() const {
    int armorBonus = rand() %5+1;
    return {Enhancements::armorClass, armorBonus};
}

Shield::Shield(string name): Item(move(name)) {
}

pair<Enhancements, int> Shield::getEnhancement() const {
    int armorBonus = rand() %5+1;
    return {Enhancements::armorClass, armorBonus};
}

Ring::Ring(string name) : Item(move(name)) {
}

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

Belt::Belt(string name) : Item(move(name)) {
}

pair<Enhancements, int> Belt::getEnhancement() const {
    int bonus = rand() % 5 + 1;
    Enhancements enhance;

    if (rand() % 2 == 0)
        enhance = Enhancements::constitution;
    else
        enhance = Enhancements::strength;

    return { enhance, bonus };
}

Boots::Boots(string name): Item(move(name)) {
}

pair<Enhancements, int> Boots::getEnhancement() const {
    int bonus = rand() %5+1;
    Enhancements enhance;
    
    if (rand() % 2 == 0)
        enhance = Enhancements::dexterity;
    else
        enhance = Enhancements::armorClass;

    return { enhance, bonus };
}

Weapon::Weapon(string name) : Item(move(name)) {
}

pair<Enhancements, int> Weapon::getEnhancement() const {
    int bonus = rand() % 5 + 1;
    Enhancements enhance;

    if (rand() % 2 == 0)
        enhance = Enhancements::attackBonus;
    else
        enhance = Enhancements::damageBonus;

    return { enhance, bonus };
}

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

void ItemContainer::addItem(Item* item){
    items.push_back(item);
}

void ItemContainer::removeItem(const string& label){

    for(auto element = items.begin(); element != items.end(); ++element){
        if ((*element)->name == label){
            delete *element;
            items.erase(element);
            break;
        }
    }
}

Item* ItemContainer::getItemByName(const string& itemName) const {
    for (const auto& item : items) {
        if (item->name == itemName) {
            return item;
        }
    }
    return nullptr; 
}

void Item::displayItem() const {
    cout << name << endl;
    cout << "Enhancement: " << enhancementToString(getEnhancement().first) << ", Enhancement Bonus: " << getEnhancement().second << endl << endl;

}

void ItemContainer::displayItems() const {
    cout << " ===== Items in " << name << ": =====" << endl;
    for (const auto& item : items) {
        item->displayItem();
    }
}