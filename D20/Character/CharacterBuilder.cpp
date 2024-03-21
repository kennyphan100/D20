#include "CharacterBuilder.h"
#include <iostream>
#include <fstream> 
#include <sstream>

using namespace std;

CharacterBuilder::CharacterBuilder() : character(new Character(1, FighterType::TANK)) {}

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

    out << "Name: " << getCharacter()->getName() << "\n"
        << "Class: " << fighterTypeToString(getCharacter()->getFighterType()) << "\n"
        << "Level: " << getCharacter()->getLevel() << "\n"
        << "HP: " << getCharacter()->getHitPoints() << ", AC: " << getCharacter()->getArmorClass() << ", Attack Bonus: " << getCharacter()->getAttackBonus() << ", Damage Bonus: " << getCharacter()->getDamageBonus() << "\n"
        << "STR: " << getCharacter()->abilityScores[0] << " (" << getCharacter()->abilityModifiers[0] << "), "
        << "DEX: " << getCharacter()->abilityScores[1] << " (" << getCharacter()->abilityModifiers[1] << "), "
        << "CON: " << getCharacter()->abilityScores[2] << " (" << getCharacter()->abilityModifiers[2] << "), "
        << "INT: " << getCharacter()->abilityScores[3] << " (" << getCharacter()->abilityModifiers[3] << "), "
        << "WIS: " << getCharacter()->abilityScores[4] << " (" << getCharacter()->abilityModifiers[4] << "), "
        << "CHA: " << getCharacter()->abilityScores[5] << " (" << getCharacter()->abilityModifiers[5] << ")\n";

    out << "Equipped Armor: " << (getCharacter()->getArmor() ? getCharacter()->getArmor()->name : "---") << "\n"
        << "Equipped Shield: " << (getCharacter()->getShield() ? getCharacter()->getShield()->name : "---") << "\n"
        << "Equipped Weapon: " << (getCharacter()->getWeapon() ? getCharacter()->getWeapon()->name : "---") << "\n"
        << "Equipped Boots: " << (getCharacter()->getBoots() ? getCharacter()->getBoots()->name : "---") << "\n"
        << "Equipped Ring: " << (getCharacter()->getRing() ? getCharacter()->getRing()->name : "---") << "\n"
        << "Equipped Helmet: " << (getCharacter()->getHelmet() ? getCharacter()->getHelmet()->name : "---") << "\n";

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
        << "HP: " << getCharacter()->getHitPoints() << ", AC: " << getCharacter()->getArmorClass() << ", Attack Bonus: " << getCharacter()->getAttackBonus() << ", Damage Bonus: " << getCharacter()->getDamageBonus() << "\n" 
        << "STR: " << getCharacter()->abilityScores[0] << " (" << getCharacter()->abilityModifiers[0] << "), "
        << "DEX: " << getCharacter()->abilityScores[1] << " (" << getCharacter()->abilityModifiers[1] << "), "
        << "CON: " << getCharacter()->abilityScores[2] << " (" << getCharacter()->abilityModifiers[2] << "), "
        << "INT: " << getCharacter()->abilityScores[3] << " (" << getCharacter()->abilityModifiers[3] << "), "
        << "WIS: " << getCharacter()->abilityScores[4] << " (" << getCharacter()->abilityModifiers[4] << "), "
        << "CHA: " << getCharacter()->abilityScores[5] << " (" << getCharacter()->abilityModifiers[5] << ")\n";

    out << "Equipped Armor: " << (getCharacter()->getArmor() ? getCharacter()->getArmor()->name : "---") << std::endl
        << "Equipped Shield: " << (getCharacter()->getShield() ? getCharacter()->getShield()->name : "---") << std::endl
        << "Equipped Weapon: " << (getCharacter()->getWeapon() ? getCharacter()->getWeapon()->name : "---") << std::endl
        << "Equipped Boots: " << (getCharacter()->getBoots() ? getCharacter()->getBoots()->name : "---") << std::endl
        << "Equipped Ring: " << (getCharacter()->getRing() ? getCharacter()->getRing()->name : "---") << std::endl
        << "Equipped Helmet: " << (getCharacter()->getHelmet() ? getCharacter()->getHelmet()->name : "---") << std::endl;
}

void NimbleFighterBuilder::logCharacter(ostream& out) {
    out << "Name: " << getCharacter()->getName() << "\n"
        << "Class: " << fighterTypeToString(getCharacter()->getFighterType()) << "\n"
        << "Level: " << getCharacter()->getLevel() << "\n"
        << "HP: " << getCharacter()->getHitPoints() << ", AC: " << getCharacter()->getArmorClass() << ", Attack Bonus: " << getCharacter()->getAttackBonus() << ", Damage Bonus: " << getCharacter()->getDamageBonus() << "\n"
        << "STR: " << getCharacter()->abilityScores[0] << " (" << getCharacter()->abilityModifiers[0] << "), "
        << "DEX: " << getCharacter()->abilityScores[1] << " (" << getCharacter()->abilityModifiers[1] << "), "
        << "CON: " << getCharacter()->abilityScores[2] << " (" << getCharacter()->abilityModifiers[2] << "), "
        << "INT: " << getCharacter()->abilityScores[3] << " (" << getCharacter()->abilityModifiers[3] << "), "
        << "WIS: " << getCharacter()->abilityScores[4] << " (" << getCharacter()->abilityModifiers[4] << "), "
        << "CHA: " << getCharacter()->abilityScores[5] << " (" << getCharacter()->abilityModifiers[5] << ")\n";

    out << "Equipped Armor: " << (getCharacter()->getArmor() ? getCharacter()->getArmor()->name : "---") << std::endl
        << "Equipped Shield: " << (getCharacter()->getShield() ? getCharacter()->getShield()->name : "---") << std::endl
        << "Equipped Weapon: " << (getCharacter()->getWeapon() ? getCharacter()->getWeapon()->name : "---") << std::endl
        << "Equipped Boots: " << (getCharacter()->getBoots() ? getCharacter()->getBoots()->name : "---") << std::endl
        << "Equipped Ring: " << (getCharacter()->getRing() ? getCharacter()->getRing()->name : "---") << std::endl
        << "Equipped Helmet: " << (getCharacter()->getHelmet() ? getCharacter()->getHelmet()->name : "---") << std::endl;
}

void TankFighterBuilder::logCharacter(ostream& out) {
    out << "Name: " << getCharacter()->getName() << "\n"
        << "Class: " << fighterTypeToString(getCharacter()->getFighterType()) << "\n"
        << "Level: " << getCharacter()->getLevel() << "\n"
        << "HP: " << getCharacter()->getHitPoints() << ", AC: " << getCharacter()->getArmorClass() << ", Attack Bonus: " << getCharacter()->getAttackBonus() << ", Damage Bonus: " << getCharacter()->getDamageBonus() << "\n"
        << "STR: " << getCharacter()->abilityScores[0] << " (" << getCharacter()->abilityModifiers[0] << "), "
        << "DEX: " << getCharacter()->abilityScores[1] << " (" << getCharacter()->abilityModifiers[1] << "), "
        << "CON: " << getCharacter()->abilityScores[2] << " (" << getCharacter()->abilityModifiers[2] << "), "
        << "INT: " << getCharacter()->abilityScores[3] << " (" << getCharacter()->abilityModifiers[3] << "), "
        << "WIS: " << getCharacter()->abilityScores[4] << " (" << getCharacter()->abilityModifiers[4] << "), "
        << "CHA: " << getCharacter()->abilityScores[5] << " (" << getCharacter()->abilityModifiers[5] << ")\n";

    out << "Equipped Armor: " << (getCharacter()->getArmor() ? getCharacter()->getArmor()->name : "---") << std::endl
        << "Equipped Shield: " << (getCharacter()->getShield() ? getCharacter()->getShield()->name : "---") << std::endl
        << "Equipped Weapon: " << (getCharacter()->getWeapon() ? getCharacter()->getWeapon()->name : "---") << std::endl
        << "Equipped Boots: " << (getCharacter()->getBoots() ? getCharacter()->getBoots()->name : "---") << std::endl
        << "Equipped Ring: " << (getCharacter()->getRing() ? getCharacter()->getRing()->name : "---") << std::endl
        << "Equipped Helmet: " << (getCharacter()->getHelmet() ? getCharacter()->getHelmet()->name : "---") << std::endl;
}

