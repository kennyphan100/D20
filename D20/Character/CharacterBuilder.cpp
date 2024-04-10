#include "CharacterBuilder.h"
#include <iostream>
#include <fstream> 
#include <sstream>

using namespace std;

CharacterBuilder::CharacterBuilder() : character(new FighterCharacter(1, FighterType::TANK)) {}

CharacterBuilder::~CharacterBuilder() {
    delete character;
}

void CharacterBuilder::assignName(string name)
{
    character->setName(name);
    notify();
}

bool CharacterBuilder::saveToFile(const string& filename) {
    ofstream out(filename);
    if (!out.is_open()) {
        cerr << "Failed to open file '" << filename << "' for writing.\n";
        return false;
    }

    Character* character = getCharacter();
    if (!character) {
        cerr << "No character to save.\n";
        return false;
    }

    out << "Name: " << character->getName() << "\n"
        << "Class: " << fighterTypeToString(character->getFighterType()) << "\n"
        << "Level: " << character->getLevel() << "\n"
        << "HP: " << character->getHitPoints() << ", AC: " << character->getArmorClass() << ", AttackBonus: " << character->getAttackBonus() << ", DamageBonus: " << character->getDamageBonus() << "\n"
        << "STR: " << character->getAbilityScore(0) << " (" << character->getAbilityModifier(0) << "), "
        << "DEX: " << character->getAbilityScore(1) << " (" << character->getAbilityModifier(1) << "), "
        << "CON: " << character->getAbilityScore(2) << " (" << character->getAbilityModifier(2) << "), "
        << "INT: " << character->getAbilityScore(3) << " (" << character->getAbilityModifier(3) << "), "
        << "WIS: " << character->getAbilityScore(4) << " (" << character->getAbilityModifier(4) << "), "
        << "CHA: " << character->getAbilityScore(5) << " (" << character->getAbilityModifier(5) << ")\n";

    out << "Equipped Armor: " << (character->getArmor() ? character->getArmor()->getName() + ", " + enhancementToString(character->getArmor()->getEnhancementType()) + ", " + to_string(character->getArmor()->getEnhancementBonus()) : "None") << "\n"
        << "Equipped Shield: " << (character->getShield() ? character->getShield()->getName() + ", " + enhancementToString(character->getShield()->getEnhancementType()) + ", " + to_string(character->getShield()->getEnhancementBonus()) : "None") << "\n"
        << "Equipped Weapon: " << (character->getWeapon() ? character->getWeapon()->getName() + ", " + enhancementToString(character->getWeapon()->getEnhancementType()) + ", " + to_string(character->getWeapon()->getEnhancementBonus()) : "None") << "\n"
        << "Equipped Boots: " << (character->getBoots() ? character->getBoots()->getName() + ", " + enhancementToString(character->getBoots()->getEnhancementType()) + ", " + to_string(character->getBoots()->getEnhancementBonus()) : "None") << "\n"
        << "Equipped Ring: " << (character->getRing() ? character->getRing()->getName() + ", " + enhancementToString(character->getRing()->getEnhancementType()) + ", " + to_string(character->getRing()->getEnhancementBonus()) : "None") << "\n"
        << "Equipped Helmet: " << (character->getHelmet() ? character->getHelmet()->getName() + ", " + enhancementToString(character->getHelmet()->getEnhancementType()) + ", " + to_string(character->getHelmet()->getEnhancementBonus()) : "None") << "\n";

    Backpack* backpack = character->backpack;
    if (backpack && !backpack->getItems().empty()) {
        out << "Inventory: \n";
        for (const auto& item : backpack->getItems()) {
            out << "Item Name: " << item->getName() << ", "
                << "Item Type: " << item->getItemType(item) << ", "
                << "Enhancement Type: " << enhancementToString(item->getEnhancementType()) << ", "
                << "Enhancement Bonus: " << item->getEnhancementBonus() << "\n";
        }
    }
    else {
        out << "Inventory: None\n";
    }

    out.close();
    return true;
}

Character* CharacterBuilder::getCharacter() {
    return character;
}

int CharacterBuilder::roll4d6DropLowest()
{
    vector<int> fourDiceRolls(4);

    for (int i = 0; i < 4; ++i) {
        fourDiceRolls[i] = dice.rollDice("1d6");
    }

    sort(fourDiceRolls.begin(), fourDiceRolls.end());

    return fourDiceRolls[1] + fourDiceRolls[2] + fourDiceRolls[3];
}

vector<int> CharacterBuilder::generateAbilityScores()
{
    vector<int> abilityScores(6);

    for (int i = 0; i < 6; ++i) {
        abilityScores[i] = roll4d6DropLowest();
    }

    sort(abilityScores.begin(), abilityScores.end(), std::greater<int>()); // Sorted from highest to lowest

    return abilityScores; 
}

void BullyFighterBuilder::buildAbilityScores() {
    vector<int> abilityScores = generateAbilityScores();

    character->abilityScores[0] = abilityScores[0]; // Strength
    character->abilityScores[2] = abilityScores[1]; // Constitution
    character->abilityScores[1] = abilityScores[2]; // Dexterity
    character->abilityScores[3] = abilityScores[3]; // Intelligence
    character->abilityScores[5] = abilityScores[4]; // Charisma
    character->abilityScores[4] = abilityScores[5]; // Wisdom
}

void BullyFighterBuilder::assignFighterType() {
    character->fighterType = FighterType::BULLY;
}

void BullyFighterBuilder::assignLevel(int level)
{
    for (int i = 1; i < level; i++) {
        character->levelUp();
    }
    //notify();
}

void NimbleFighterBuilder::buildAbilityScores() {
    vector<int> abilityScores = generateAbilityScores();

    character->abilityScores[1] = abilityScores[0]; // Dexterity
    character->abilityScores[2] = abilityScores[1]; // Constitution
    character->abilityScores[0] = abilityScores[2]; // Strength
    character->abilityScores[3] = abilityScores[3]; // Intelligence
    character->abilityScores[5] = abilityScores[4]; // Charisma
    character->abilityScores[4] = abilityScores[5]; // Wisdom
}

void NimbleFighterBuilder::assignFighterType() {
    character->fighterType = FighterType::NIMBLE;
}

void NimbleFighterBuilder::assignLevel(int level)
{
    for (int i = 1; i < level; i++) {
        character->levelUp();
    }
    //notify();
}

void TankFighterBuilder::buildAbilityScores() {
    vector<int> abilityScores = generateAbilityScores();

    character->abilityScores[2] = abilityScores[0]; // Constitution
    character->abilityScores[1] = abilityScores[1]; // Dexterity
    character->abilityScores[0] = abilityScores[2]; // Strength
    character->abilityScores[3] = abilityScores[3]; // Intelligence
    character->abilityScores[5] = abilityScores[4]; // Charisma
    character->abilityScores[4] = abilityScores[5]; // Wisdom
}

void TankFighterBuilder::assignFighterType() {
    character->fighterType = FighterType::TANK;
}

void TankFighterBuilder::assignLevel(int level)
{
    for (int i = 1; i < level; i++) {
        character->levelUp();
    }
    //notify();
}

void BullyFighterBuilder::logCharacter(ostream& out) {
    out << "Name: " << getCharacter()->getName() << "\n"
        << "Class: " << fighterTypeToString(getCharacter()->getFighterType()) << "\n"
        << "Level: " << getCharacter()->getLevel() << "\n"
        << "HP: " << getCharacter()->getHitPoints() << ", AC: " << getCharacter()->getArmorClass() << ", AttackBonus: " << getCharacter()->getAttackBonus() << ", DamageBonus: " << getCharacter()->getDamageBonus() << "\n" 
        << "STR: " << getCharacter()->abilityScores[0] << " (" << getCharacter()->abilityModifiers[0] << "), "
        << "DEX: " << getCharacter()->abilityScores[1] << " (" << getCharacter()->abilityModifiers[1] << "), "
        << "CON: " << getCharacter()->abilityScores[2] << " (" << getCharacter()->abilityModifiers[2] << "), "
        << "INT: " << getCharacter()->abilityScores[3] << " (" << getCharacter()->abilityModifiers[3] << "), "
        << "WIS: " << getCharacter()->abilityScores[4] << " (" << getCharacter()->abilityModifiers[4] << "), "
        << "CHA: " << getCharacter()->abilityScores[5] << " (" << getCharacter()->abilityModifiers[5] << ")\n";

    out << "Equipped Armor: " << (getCharacter()->getArmor() ? getCharacter()->getArmor()->getName() : "---") << std::endl
        << "Equipped Shield: " << (getCharacter()->getShield() ? getCharacter()->getShield()->getName() : "---") << std::endl
        << "Equipped Weapon: " << (getCharacter()->getWeapon() ? getCharacter()->getWeapon()->getName() : "---") << std::endl
        << "Equipped Boots: " << (getCharacter()->getBoots() ? getCharacter()->getBoots()->getName() : "---") << std::endl
        << "Equipped Ring: " << (getCharacter()->getRing() ? getCharacter()->getRing()->getName() : "---") << std::endl
        << "Equipped Helmet: " << (getCharacter()->getHelmet() ? getCharacter()->getHelmet()->getName() : "---") << std::endl;
}

void NimbleFighterBuilder::logCharacter(ostream& out) {
    out << "Name: " << getCharacter()->getName() << "\n"
        << "Class: " << fighterTypeToString(getCharacter()->getFighterType()) << "\n"
        << "Level: " << getCharacter()->getLevel() << "\n"
        << "HP: " << getCharacter()->getHitPoints() << ", AC: " << getCharacter()->getArmorClass() << ", AttackBonus: " << getCharacter()->getAttackBonus() << ", DamageBonus: " << getCharacter()->getDamageBonus() << "\n"
        << "STR: " << getCharacter()->abilityScores[0] << " (" << getCharacter()->abilityModifiers[0] << "), "
        << "DEX: " << getCharacter()->abilityScores[1] << " (" << getCharacter()->abilityModifiers[1] << "), "
        << "CON: " << getCharacter()->abilityScores[2] << " (" << getCharacter()->abilityModifiers[2] << "), "
        << "INT: " << getCharacter()->abilityScores[3] << " (" << getCharacter()->abilityModifiers[3] << "), "
        << "WIS: " << getCharacter()->abilityScores[4] << " (" << getCharacter()->abilityModifiers[4] << "), "
        << "CHA: " << getCharacter()->abilityScores[5] << " (" << getCharacter()->abilityModifiers[5] << ")\n";

    out << "Equipped Armor: " << (getCharacter()->getArmor() ? getCharacter()->getArmor()->getName() : "---") << std::endl
        << "Equipped Shield: " << (getCharacter()->getShield() ? getCharacter()->getShield()->getName() : "---") << std::endl
        << "Equipped Weapon: " << (getCharacter()->getWeapon() ? getCharacter()->getWeapon()->getName() : "---") << std::endl
        << "Equipped Boots: " << (getCharacter()->getBoots() ? getCharacter()->getBoots()->getName() : "---") << std::endl
        << "Equipped Ring: " << (getCharacter()->getRing() ? getCharacter()->getRing()->getName() : "---") << std::endl
        << "Equipped Helmet: " << (getCharacter()->getHelmet() ? getCharacter()->getHelmet()->getName() : "---") << std::endl;
}

void TankFighterBuilder::logCharacter(ostream& out) {
    out << "Name: " << getCharacter()->getName() << "\n"
        << "Class: " << fighterTypeToString(getCharacter()->getFighterType()) << "\n"
        << "Level: " << getCharacter()->getLevel() << "\n"
        << "HP: " << getCharacter()->getHitPoints() << ", AC: " << getCharacter()->getArmorClass() << ", AttackBonus: " << getCharacter()->getAttackBonus() << ", DamageBonus: " << getCharacter()->getDamageBonus() << "\n"
        << "STR: " << getCharacter()->abilityScores[0] << " (" << getCharacter()->abilityModifiers[0] << "), "
        << "DEX: " << getCharacter()->abilityScores[1] << " (" << getCharacter()->abilityModifiers[1] << "), "
        << "CON: " << getCharacter()->abilityScores[2] << " (" << getCharacter()->abilityModifiers[2] << "), "
        << "INT: " << getCharacter()->abilityScores[3] << " (" << getCharacter()->abilityModifiers[3] << "), "
        << "WIS: " << getCharacter()->abilityScores[4] << " (" << getCharacter()->abilityModifiers[4] << "), "
        << "CHA: " << getCharacter()->abilityScores[5] << " (" << getCharacter()->abilityModifiers[5] << ")\n";

    out << "Equipped Armor: " << (getCharacter()->getArmor() ? getCharacter()->getArmor()->getName() : "---") << std::endl
        << "Equipped Shield: " << (getCharacter()->getShield() ? getCharacter()->getShield()->getName() : "---") << std::endl
        << "Equipped Weapon: " << (getCharacter()->getWeapon() ? getCharacter()->getWeapon()->getName() : "---") << std::endl
        << "Equipped Boots: " << (getCharacter()->getBoots() ? getCharacter()->getBoots()->getName() : "---") << std::endl
        << "Equipped Ring: " << (getCharacter()->getRing() ? getCharacter()->getRing()->getName() : "---") << std::endl
        << "Equipped Helmet: " << (getCharacter()->getHelmet() ? getCharacter()->getHelmet()->getName() : "---") << std::endl;
}

