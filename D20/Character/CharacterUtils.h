#pragma once
#ifndef CHARACTER_UTILS_H
#define CHARACTER_UTILS_H

#include "../Item/Item2.h"

namespace CharacterUtils {
    Helmet2* getHelmet(Character* character);
    Armor2* getArmor(Character* character);
    Shield2* getShield(Character* character);
    Ring2* getRing(Character* character);
    Belt2* getBelt(Character* character);
    Boots2* getBoots(Character* character);
    Weapon2* getWeapon(Character* character);
}

#endif // CHARACTER_UTILS_H
