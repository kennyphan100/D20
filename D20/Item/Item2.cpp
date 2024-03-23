#include "Item2.h"

//CharacterDecorator::CharacterDecorator(Character* character) : character(character) {}

//CharacterDecorator::CharacterDecorator(Character* character) : Character(*character) {}

CharacterDecorator::CharacterDecorator(Character* newCharacter) : Character(newCharacter->level, newCharacter->fighterType, newCharacter->name) {
    this->character = newCharacter;
}

//CharacterDecorator::CharacterDecorator(Character* newCharacter) {
//    this->character = newCharacter;
//}

//CharacterDecorator::CharacterDecorator(Character* character) {
//    this->character = character;
//}

CharacterDecorator::~CharacterDecorator() {
    delete character;
}

//void CharacterDecorator::display() {
//    character->display();
//}

void CharacterDecorator::applyEnhancement(CharacterStat stat, int bonus) {
    character->applyEnhancement(stat, bonus);
}

Item2::Item2(Character* character, string name, CharacterStat type, int bonus)
    : CharacterDecorator(character), name(name), enhancementType(type), enhancementBonus(bonus) {}

string Item2::getDescription() const {
    return "Item";
}

string Item2::getName() const {
    return name;
}

int Item2::getEnhancementBonus() const {
    return enhancementBonus;
}

CharacterStat Item2::getEnhancementType() const {
    return enhancementType;
}

Helmet2::Helmet2(Character* character, string name, CharacterStat type, int bonus)
    : Item2(character, name, type, bonus) {}

string Helmet2::getDescription() const {
    return "Helmet";
}

Armor2::Armor2(Character* character, string name, CharacterStat type, int bonus)
    : Item2(character, name, type, bonus) {}

string Armor2::getDescription() const {
    return "Chestpiece";
}

Shield2::Shield2(Character* character, string name, CharacterStat type, int bonus)
    : Item2(character, name, type, bonus) {}

string Shield2::getDescription() const {
    return "Pants";
}

Ring2::Ring2(Character* character, string name, CharacterStat type, int bonus)
    : Item2(character, name, type, bonus) {}

string Ring2::getDescription() const {
    return "Pants";
}

Belt2::Belt2(Character* character, string name, CharacterStat type, int bonus)
    : Item2(character, name, type, bonus) {}

string Belt2::getDescription() const {
    return "Pants";
}

Boots2::Boots2(Character* character, string name, CharacterStat type, int bonus)
    : Item2(character, name, type, bonus) {}

string Boots2::getDescription() const {
    return "Boots";
}

Weapon2::Weapon2(Character* character, string name, CharacterStat type, int bonus)
    : Item2(character, name, type, bonus) {}

string Weapon2::getDescription() const {
    return "Boots";
}
