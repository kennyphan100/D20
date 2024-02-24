#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <vector>

using namespace std;

enum class Enhancements {
    damageBonus,
    attackBonus, 
    armorClass, 
    strength, 
    dexterity, 
    wisdom, 
    intelligence, 
    constitution,
    charisma
};

class Item {
public:
    string name;
    Item(string name);
    virtual ~Item() = default;
    virtual pair<Enhancements, int> getEnhancement() const = 0;
    void displayItem() const;
};

class Helmet : public Item {
public:
    Helmet(string name);
    pair<Enhancements, int> getEnhancement() const override;
};

class Armor : public Item {
public:
    Armor(string name);
    pair<Enhancements, int> getEnhancement() const override;
};

class Shield : public Item {
public:
    Shield(string name);
    pair<Enhancements, int> getEnhancement() const override;
};

class Ring : public Item {
public:
    Ring(string name);
    pair<Enhancements, int> getEnhancement() const override;
};

class Belt : public Item {
public:
    Belt(string name);
    pair<Enhancements, int> getEnhancement() const override;
};

class Boots : public Item {
public:
    Boots(string name);
    pair<Enhancements, int> getEnhancement() const override;
};

class Weapon : public Item {
public:
    Weapon(string name);
    pair<Enhancements, int> getEnhancement() const override;
};


class ItemContainer {
public:
    vector<Item*> items;
    string name;
    ItemContainer(string name);
    virtual ~ItemContainer() = default;
    virtual void addItem(Item* item);
    virtual void removeItem(const string& label);
    Item* getItemByName(const string& itemName) const;
    void displayItems() const;
};

class Backpack : public ItemContainer {
public:
    Backpack(string name);
};

class WornItems : public ItemContainer {
};

class TreasureChest : public ItemContainer {
};

string enhancementToString(Enhancements enhancement);

#endif
