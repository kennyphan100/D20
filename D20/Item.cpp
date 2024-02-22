#include <string>
#include <vector>
#include <iostream>

enum class Enhancements {
    damageBonus, attackBonus, armorClass, strength, dexterity, wisdom, intelligence, constitution,
    charisma
};

class Item {
public:
    std::string name;
    Item(std::string name) : name(name) {}
    virtual ~Item() = default;
    virtual std::pair<Enhancements, int>getEnhancement() const = 0;
};

class Armor : public Item {
public:


    Armor(std::string name) : Item(name) {}

    int armorBonus = rand() %5+1;
    std::pair <Enhancements, int>getEnhancement() const override{
        return {Enhancements::armorClass, armorBonus};
    }
};

class Shield : public Item {
public:

    Shield(std::string name) : Item(name){}

    int armorBonus = rand() %5+1;

    std::pair<Enhancements,int>getEnhancement() const override{
        return {Enhancements::armorClass, armorBonus};
    }
};

class Weapon : public Item {
public:
    int bonus = rand() % 5+1;
    Weapon(std::string name) : Item(name){}
    
    std::pair<Enhancements,int>getEnhancement() const override{
    Enhancements enhance;

    if (rand() % 2 == 0)
        enhance = Enhancements::attackBonus;
    else
        enhance = Enhancements::damageBonus;

    return {enhance, bonus};
    }
};

class Boots : public Item {
public:
    int dexBonus = rand() % 5+1;
    Boots(std::string name) : Item(name){}

    std::pair<Enhancements,int>getEnhancement() const override{
        Enhancements enhance;

         if (rand() % 2 == 0)
            enhance = Enhancements::dexterity;
        else
            enhance = Enhancements::armorClass;

    return {enhance, dexBonus};
    }
};

class Ring : public Item {
public:
    int bonus = rand() % 5+1;
    Ring(std::string name) : Item(name) {}

     std::pair<Enhancements, int>getEnhancement() const override{
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
        
    return {enhance, bonus};
    }
};

class Helmet : public Item {
public:
    int bonus = rand() % 5+1;

    Helmet(std::string name) : Item(name){}
    std::pair<Enhancements, int>getEnhancement() const override{
        Enhancements enhance;

        if (rand() % 3 == 0)
            enhance = Enhancements::wisdom;
        else if (rand() % 3 == 1)
            enhance = Enhancements::intelligence;
        else
            enhance = Enhancements::armorClass;

    return {enhance, bonus};
    }
};


class ItemContainer{
public:
     std::vector<Item*> items;
     std::string name;
     virtual ~ItemContainer() = default;

virtual void addItem(Item* item){
    items.push_back(item);
}

virtual void removeItem(const std::string& label){

    for(auto element = items.begin(); element != items.end(); ++element){
        if ((*element)->name == label){
            delete *element;
            items.erase(element);
            break;
        }
    }
}

Item* getItemByName(const std::string& itemName) const {
    for (const auto& item : items) {
        if (item->name == itemName) {
            return item;
        }
    }
    return nullptr; 
}
};

class ItemBackpack : public ItemContainer {
    public:
};

class WornItems : public ItemContainer {
    public:
};

class TreasureChest : public ItemContainer {
    public:
};

   std::string enhancementToString(Enhancements enhancement) {
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

int main() {
   
    Armor armor("Plate Armor");
    Shield shield("Wooden Shield");
    Weapon weapon("Long Sword");
    Boots boots("Leather Boots");
    Ring ring("Diamond Ring");
    Helmet helmet("Steel Helmet");

    std::cout << "Armor: " << armor.name << std::endl;
    auto armorEnhancement = armor.getEnhancement();
    std::cout << "Enhancement: " << enhancementToString(armorEnhancement.first) << ", Enhancement Number: " << armorEnhancement.second << std::endl << std::endl;

    std::cout << "Shield: " << shield.name << std::endl;
    auto shieldEnhancement = shield.getEnhancement();
    std::cout << "Enhancement: " << enhancementToString(shieldEnhancement.first) << ", Enhancement Number: " << shieldEnhancement.second << std::endl << std::endl;

    std::cout << "Weapon: " << weapon.name << std::endl;
    auto weaponEnhancement = weapon.getEnhancement();
    std::cout << "Enhancement: " << enhancementToString(weaponEnhancement.first) << ", Enhancement Number: " << weaponEnhancement.second << std::endl << std::endl;

    std::cout << "Ring: " << ring.name << std::endl;
    auto ringEnhancement = ring.getEnhancement();
    std::cout << "Enhancement: " << enhancementToString(ringEnhancement.first) << ", Enhancement Number: " << ringEnhancement.second << std::endl << std::endl;

   return 0;
}

