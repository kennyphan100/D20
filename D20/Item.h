//! @file 
//! @brief Header file for Item.cpp
//!

#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <vector>

using namespace std;

enum class Enhancements {
    damageBonus,    //!< Additional damage bonus.
    attackBonus,    //!< Additional attack bonus.
    armorClass,     //!< Bonus to armor class.
    strength,       //!< Increase in strength.
    dexterity,      //!< Increase in dexterity.
    wisdom,         //!< Increase in wisdom.
    intelligence,   //!< Increase in intelligence.
    constitution,   //!< Increase in constitution.
    charisma        //!< Increase in charisma.
};

/**
 * @class Item
 * @brief This class represents an item that can be worn by a character.
 *
 * Game Rules:
 * Each item can have one or more enhancements associated with it, such as damage bonus, attack bonus, or increased attributes.
 * Different types of items (Helmet, Armor, Shield, etc.) provide different sets of enhancements.
 * Item containers (Backpack, WornItems, TreasureChest) allow players to manage and store their items.
 *
 * Design:
 * The design follows a hierarchical structure with base class Item representing all items in the game.
 * Derived classes like Helmet, Armor, Shield, etc., represent specific types of items with specialized functionalities.
 * ItemContainer is a base class representing containers for items, allowing addition, removal, and display of items. Derived classes like Backpack, WornItems, etc., specialize the container behavior.
 * The code uses polymorphism to handle different item types uniformly through base class pointers.
 * Utility function enhancementToString converts enhancement enum values to their string representations.
 *
 * Libraries:
 * <vector> for storing the map grid due to its flexibility in handling dynamic 2D arrays.
 * <string> from the C++ Standard Library for managing and manipulating string data
 */
class Item {
public:
    string name;
    Item(string name);
    virtual ~Item() = default;
    virtual pair<Enhancements, int> getEnhancement() const = 0;
    void displayItem() const;
};

//! Class representing a helmet item.
class Helmet : public Item {
public:
    //! Constructor for Helmet class.
    //! @param name The name of the helmet.
    Helmet(string name);

    //! Overridden function to get the enhancement provided by the helmet.
    //! @return A pair containing the enhancement type and its value.
    pair<Enhancements, int> getEnhancement() const override;
};

//! Class representing an armor item.
class Armor : public Item {
public:
    Armor(string name);
    pair<Enhancements, int> getEnhancement() const override;
};

//! Class representing a shield item.
class Shield : public Item {
public:
    Shield(string name);
    pair<Enhancements, int> getEnhancement() const override;
};

//! Class representing a ring item.
class Ring : public Item {
public:
    Ring(string name);
    pair<Enhancements, int> getEnhancement() const override;
};

//! Class representing a belt item.
class Belt : public Item {
public:
    Belt(string name);
    pair<Enhancements, int> getEnhancement() const override;
};

//! Class representing a boots item.
class Boots : public Item {
public:
    Boots(string name);
    pair<Enhancements, int> getEnhancement() const override;
};

//! Class representing a weapon item.
class Weapon : public Item {
public:
    Weapon(string name);
    pair<Enhancements, int> getEnhancement() const override;
};

//! Class representing a container for items.
class ItemContainer {
public:
    vector<Item*> items; //!< Vector containing pointers to items in the container.
    string name; //!< The name of the container.
    ItemContainer(string name);
    virtual ~ItemContainer() = default;
    virtual void addItem(Item* item);
    virtual void removeItem(const string& label);
    Item* getItemByName(const string& itemName) const;
    void displayItems() const;
    int getSize() const;
};

//! Class representing a backpack item container
class Backpack : public ItemContainer {
public:
    Backpack(string name);
};

//! Class representing worn items container.
class WornItems : public ItemContainer {
};

//! Class representing a treasure chest item container.
class TreasureChest : public ItemContainer {
};

//! Function to convert an enhancement type enum value to its string representation.
//! @param enhancement The enhancement type enum value.
//! @return The string representation of the enhancement type.
string enhancementToString(Enhancements enhancement);

#endif
