#include "characterutils.h"

Helmet2* CharacterUtils::getHelmet(Character* character) {
    // Implementation of findHelmet function
     // Check if the character is wearing an item
    Item2* item = dynamic_cast<Item2*>(character);
    if (item) {
        // If it's a helmet, return it
        Helmet2* helmet = dynamic_cast<Helmet2*>(item);
        if (helmet) {
            return helmet;
        }
        // Otherwise, recursively search for a helmet in the decorated character
        else {
            return getHelmet(item->character);
        }
    }
    // If the character is not wearing an item or it's not a helmet, return nullptr
    return nullptr;
}

Armor2* CharacterUtils::getArmor(Character* character) {
    Item2* item = dynamic_cast<Item2*>(character);
    if (item) {
        Armor2* armor = dynamic_cast<Armor2*>(item);
        if (armor) {
            return armor;
        }
        else {
            return getArmor(item->character);
        }
    }
    return nullptr;
}

Shield2* CharacterUtils::getShield(Character* character)
{
    Item2* item = dynamic_cast<Item2*>(character);
    if (item) {
        Shield2* shield = dynamic_cast<Shield2*>(item);
        if (shield) {
            return shield;
        }
        else {
            return getShield(item->character);
        }
    }
    return nullptr;
}

Ring2* CharacterUtils::getRing(Character* character)
{
    Item2* item = dynamic_cast<Item2*>(character);
    if (item) {
        Ring2* ring = dynamic_cast<Ring2*>(item);
        if (ring) {
            return ring;
        }
        else {
            return getRing(item->character);
        }
    }
    return nullptr;
}

Belt2* CharacterUtils::getBelt(Character* character)
{
    Item2* item = dynamic_cast<Item2*>(character);
    if (item) {
        Belt2* belt = dynamic_cast<Belt2*>(item);
        if (belt) {
            return belt;
        }
        else {
            return getBelt(item->character);
        }
    }
    return nullptr;
}

Boots2* CharacterUtils::getBoots(Character* character)
{
    Item2* item = dynamic_cast<Item2*>(character);
    if (item) {
        Boots2* boots = dynamic_cast<Boots2*>(item);
        if (boots) {
            return boots;
        }
        else {
            return getBoots(item->character);
        }
    }
    return nullptr;
}

Weapon2* CharacterUtils::getWeapon(Character* character)
{
    Item2* item = dynamic_cast<Item2*>(character);
    if (item) {
        Weapon2* weapon = dynamic_cast<Weapon2*>(item);
        if (weapon) {
            return weapon;
        }
        else {
            return getWeapon(item->character);
        }
    }
    return nullptr;
}
