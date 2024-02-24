#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <vector>

enum class Enhancements {
    damageBonus, attackBonus, armorClass, strength, dexterity, wisdom, intelligence, constitution,
    charisma
};

class Item {
public:
    std::string name;
    Item(std::string name);
    virtual ~Item() = default;
    virtual std::pair<Enhancements, int> getEnhancement() const = 0;
};

class Armor : public Item {
public:
    Armor(std::string name);
    std::pair <Enhancements, int>getEnhancement() const override;
};

class Shield : public Item {
public:
    Shield(std::string name);
    std::pair<Enhancements,int>getEnhancement() const override;
};

class Weapon : public Item {
public:
    Weapon(std::string name);
    std::pair<Enhancements,int>getEnhancement() const override;
};

class Boots : public Item {
public:
    Boots(std::string name);
    std::pair<Enhancements,int>getEnhancement() const override;
};

class Ring : public Item {
public:
    Ring(std::string name);
    std::pair<Enhancements, int>getEnhancement() const override;
};

class Helmet : public Item {
public:
    Helmet(std::string name);
    std::pair<Enhancements, int>getEnhancement() const override;
};


class ItemContainer{
public:
    std::vector<Item*> items;
    std::string name;
    virtual ~ItemContainer() = default;
    virtual void addItem(Item* item);
    virtual void removeItem(const std::string& label);
    Item* getItemByName(const std::string& itemName) const;
};



class ItemBackpack : public ItemContainer {
};

class WornItems : public ItemContainer {
};

class TreasureChest : public ItemContainer {
};

std::string enhancementToString(Enhancements enhancement);

#endif
