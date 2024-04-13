//! @file 
//! @brief Implementation file for Item.h
//!

#include "Item.h"
#include <iostream>
#include <fstream> 
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <vector>

using namespace std;

//! Constructor for Item class.
//! @param name The name of the item.
//! @return new Item object
Item::Item(string name): name(move(name)) {}

Item::Item(string name, EnhancementType enhancementType, int enhancementBonus) : name(name), enhancementType(enhancementType), enhancementBonus(enhancementBonus)
{
}

std::string Item::getItemType(const Item* item) {
    if (dynamic_cast<const Armor*>(item)) return "Armor";
    if (dynamic_cast<const Weapon*>(item)) return "Weapon";
    if (dynamic_cast<const Ring*>(item)) return "Ring";
    if (dynamic_cast<const Helmet*>(item)) return "Helmet";
    if (dynamic_cast<const Shield*>(item)) return "Shield";
    if (dynamic_cast<const Belt*>(item)) return "Belt";
    if (dynamic_cast<const Boots*>(item)) return "Boots";

    return "Unknown";
}

//! Constructor for ItemContainer class.
//! @param name The name of the item container.
//! @return new ItemContainer object
ItemContainer::ItemContainer(string name): name(move(name)) {}

const vector<Item*>& ItemContainer::getItems() const{
    return items;
}

//! Constructor for Backpack class.
//! @param name The name of the backpack.
//! @return new Backpack object
Backpack::Backpack(string name): ItemContainer(name) {}

//! Constructor for Helmet class.
//! @param name The name of the helmet.
//! @return new Helmet object
Helmet::Helmet(string name) : Item(move(name)) {
}

Helmet::Helmet(string name, EnhancementType enhancementType, int enhancementBonus) : Item(name, enhancementType, enhancementBonus)
{
}

//! Retrieves an enhancement and its bonus for the helmet.
//! @return A pair containing the enhancement and its bonus.
pair<EnhancementType, int> Helmet::getEnhancement() const {
    int bonus = rand() % 5 + 1;
    EnhancementType enhance;

    if (rand() % 3 == 0)
        enhance = EnhancementType::Wisdom;
    else if (rand() % 3 == 1)
        enhance = EnhancementType::Intelligence;
    else
        enhance = EnhancementType::ArmorClass;

    return { enhance, bonus };
}

//! Constructor for Armor class.
//! @param name The name of the armor.
//! @return new Armor object
Armor::Armor(string name): Item(move(name)) {
}

Armor::Armor(string name, EnhancementType enhancementType, int enhancementBonus) : Item(name, enhancementType, enhancementBonus)
{
}

//! Retrieves the enhancement and its bonus for the armor.
//! @return A pair containing the enhancement and its bonus.
pair<EnhancementType, int> Armor::getEnhancement() const {
    int armorBonus = rand() %5+1;
    return { EnhancementType::ArmorClass, armorBonus};
}

//! Constructor for Shield class.
//! @param name The name of the shield.
//! @return new Shield object
Shield::Shield(string name): Item(move(name)) {
}

Shield::Shield(string name, EnhancementType enhancementType, int enhancementBonus) : Item(name, enhancementType, enhancementBonus)
{
}

//! Retrieves the enhancement and its bonus for the shield.
//! @return A pair containing the enhancement and its bonus.
pair<EnhancementType, int> Shield::getEnhancement() const {
    int armorBonus = rand() %5+1;
    return { EnhancementType::ArmorClass, armorBonus};
}

//! Constructor for Ring class.
//! @param name The name of the ring.
//! @return new Ring object
Ring::Ring(string name) : Item(move(name)) {
}

Ring::Ring(string name, EnhancementType enhancementType, int enhancementBonus) : Item(name, enhancementType, enhancementBonus)
{
}

//! Retrieves a random enhancement and its bonus for the ring.
//! @return A pair containing the enhancement and its bonus.
pair<EnhancementType, int> Ring::getEnhancement() const {
    int bonus = rand() % 5 + 1;
    EnhancementType enhance;

    if (rand() % 5 == 0)
        enhance = EnhancementType::Strength;
    else if (rand() % 5 == 1)
        enhance = EnhancementType::Constitution;
    else if (rand() % 5 == 2)
        enhance = EnhancementType::ArmorClass;
    else if (rand() % 5 == 3)
        enhance = EnhancementType::Wisdom;
    else
        enhance = EnhancementType::Charisma;

    return { enhance, bonus };
}

//! Constructor for Belt class.
//! @param name The name of the belt.
//! @return new Belt object
Belt::Belt(string name) : Item(move(name)) {
}

Belt::Belt(string name, EnhancementType enhancementType, int enhancementBonus) : Item(name, enhancementType, enhancementBonus)
{
}

//! Retrieves a random enhancement and its bonus for the belt.
//! @return A pair containing the enhancement and its bonus.
pair<EnhancementType, int> Belt::getEnhancement() const {
    int bonus = rand() % 5 + 1;
    EnhancementType enhance;

    if (rand() % 2 == 0)
        enhance = EnhancementType::Constitution;
    else
        enhance = EnhancementType::Strength;

    return { enhance, bonus };
}

//! Constructor for Boots class.
//! @param name The name of the boots.
//! @return new Boots object
Boots::Boots(string name): Item(move(name)) {
}

Boots::Boots(string name, EnhancementType enhancementType, int enhancementBonus) : Item(name, enhancementType, enhancementBonus)
{
}

//! Retrieves a random enhancement and its bonus for the boots.
//! @return A pair containing the enhancement and its bonus.
pair<EnhancementType, int> Boots::getEnhancement() const {
    int bonus = rand() %5+1;
    EnhancementType enhance;
    
    if (rand() % 2 == 0)
        enhance = EnhancementType::Dexterity;
    else
        enhance = EnhancementType::ArmorClass;

    return { enhance, bonus };
}

//! Constructor for Weapon class.
//! @param name The name of the weapon.
//! @return new Weapon object
Weapon::Weapon(string name) : Item(move(name)) {
}

Weapon::Weapon(string name, EnhancementType enhancementType, int enhancementBonus) : Item(name, enhancementType, enhancementBonus)
{
}

//! Retrieves a random enhancement and its bonus for the weapon.
//! @return A pair containing the enhancement and its bonus.
pair<EnhancementType, int> Weapon::getEnhancement() const {
    int bonus = rand() % 5 + 1;
    EnhancementType enhance;

    if (rand() % 2 == 0)
        enhance = EnhancementType::AttackBonus;
    else
        enhance = EnhancementType::DamageBonus;

    return { enhance, bonus };
}

//! Converts an enhancement enum value to its string representation.
//! @param enhancement The enhancement enum value.
//! @return The string representation of the enhancement.
string enhancementToString(EnhancementType enhancement) {
    switch (enhancement) {
        case EnhancementType::DamageBonus:
            return "Damage Bonus";
        case EnhancementType::AttackBonus:
            return "Attack Bonus";
        case EnhancementType::ArmorClass:
            return "Armor Class";
        case EnhancementType::Strength:
            return "Strength";
        case EnhancementType::Dexterity:
            return "Dexterity";
        case EnhancementType::Wisdom:
            return "Wisdom";
        case EnhancementType::Intelligence:
            return "Intelligence";
        case EnhancementType::Constitution:
            return "Constitution";
        case EnhancementType::Charisma:
            return "Charisma";
        default:
            return "Unknown Enhancement";
    }
}

EnhancementType stringToEnhancementType(const string& enhancementStr) {
    if (enhancementStr == "Damage Bonus" or enhancementStr == "DamageBonus")
        return EnhancementType::DamageBonus;
    if (enhancementStr == "Attack Bonus" or enhancementStr == "AttackBonus")
        return EnhancementType::AttackBonus;
    if (enhancementStr == "Armor Class" or enhancementStr == "ArmorClass")
        return EnhancementType::ArmorClass;
    if (enhancementStr == "Strength")
        return EnhancementType::Strength;
    if (enhancementStr == "Dexterity")
        return EnhancementType::Dexterity;
    if (enhancementStr == "Wisdom")
        return EnhancementType::Wisdom;
    if (enhancementStr == "Intelligence")
        return EnhancementType::Intelligence;
    if (enhancementStr == "Constitution")
        return EnhancementType::Constitution;
    if (enhancementStr == "Charisma")
        return EnhancementType::Charisma;
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
        if ((*element)->getName() == label) {
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
        if (item->getName() == itemName) {
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

bool Item::saveToFile(const string& filename, const string& itemType)
{
    ofstream out(filename);
    if (!out.is_open()) {
        cerr << "Failed to open file '" << filename << "' for writing.\n";
        return false;
    }

    out << "Armor Type: " << itemType << "\n"
        << "Name: " << name << "\n"
        << "Enhancement Type: " << enhancementToString(enhancementType) << "\n"
        << "Enhancement Bonus: " << enhancementBonus << "\n";

    out.close();
    return true;
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

string Item::getName() const
{
    return name;
}

void Item::setName(string newName)
{
    name = newName;
}

EnhancementType Item::getEnhancementType() const
{
    return enhancementType;
}

void Item::setEnhancementType(EnhancementType newEnhancementType)
{
    enhancementType = newEnhancementType;
}

int Item::getEnhancementBonus() const
{
    return enhancementBonus;
}

void Item::setEnhancementBonus(int newEnhancementBonus)
{
    enhancementBonus = newEnhancementBonus;
}

Item* Item::spawnRandomItem() {
    srand(static_cast<unsigned int>(time(nullptr)));

    int itemType = rand() % 6;
    EnhancementType enhancementType = static_cast<EnhancementType>(rand() % 9);
    int enhancementBonus = rand() % 5 + 1;
    string itemName;

    std::vector<string> armorNames = { "Armor of Aegis", "Breastplate of Protection", "Chainmail of Fortitude" };
    std::vector<string> weaponNames = { "Butcher's Cleaver", "Sword of Valor", "Axe of the Minotaur" };
    std::vector<string> ringNames = { "Ring of Power", "Band of Insight", "Circle of Mystique" };
    std::vector<string> helmetNames = { "Helm of Wisdom", "Cap of the Fox", "Crown of Kings" };
    std::vector<string> shieldNames = { "Barrier Buckler", "Shield of the Guardian", "Defender's Wall" };
    //std::vector<string> beltNames = { "Belt of Vigor", "Girdle of Giants", "Waistband of Stamina" };
    std::vector<string> bootsNames = { "Boots of Speed", "Greaves of Grounding", "Footwear of the Fleet" };

    switch (itemType) {
    case 0:
        itemName = armorNames[rand() % armorNames.size()];
        return new Armor(itemName, enhancementType, enhancementBonus);
    case 1:
        itemName = weaponNames[rand() % weaponNames.size()];
        return new Weapon(itemName, enhancementType, enhancementBonus);
    case 2:
        itemName = ringNames[rand() % ringNames.size()];
        return new Ring(itemName, enhancementType, enhancementBonus);
    case 3:
        itemName = helmetNames[rand() % helmetNames.size()];
        return new Helmet(itemName, enhancementType, enhancementBonus);
    case 4:
        itemName = shieldNames[rand() % shieldNames.size()];
        return new Shield(itemName, enhancementType, enhancementBonus);
    //case 5:
    //    itemName = beltNames[rand() % beltNames.size()];
    //    return new Belt(itemName, enhancementType, enhancementBonus);
    case 5:
        itemName = bootsNames[rand() % bootsNames.size()];
        return new Boots(itemName, enhancementType, enhancementBonus);
    }
}
