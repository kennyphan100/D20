//! @file 
//! @brief Implementation file for Character.h
//!

#include "Character.h"
#include <iostream>
#include <cmath>
#include "CharacterUtils.h"
#include <fstream>
#include <sstream>
#include <ctime>
#include <filesystem>
#include "CharacterBuilder.h"
#include "CharacterDirector.h"
#include "HumanPlayerStrategy.h"

using namespace std;

Character::Character() : level(1), fighterType(FighterType::TANK), armor(nullptr)
{

}

/**
 * @brief Constructs a new Character with a specified level and character type.
 * @param level The starting level of the character.
 * @param fighterType The class type of the character.* / "
 * @return character object
 */
Character::Character(int level, FighterType fighterType) : level(level), fighterType(fighterType), armor(nullptr) {
    generateAbilityScores();
    calculateAbilityModifiers();
    calculateHitPoints();
    calculateArmorClass();
    calculateAttackBonus();
    calculateDamageBonus();
}

Character::Character(int level, FighterType fighterType, string name) : level(level), fighterType(fighterType), name(name), armor(nullptr)
{
    generateAbilityScores();
    calculateAbilityModifiers();
    calculateHitPoints();
    calculateArmorClass();
    calculateAttackBonus();
    calculateDamageBonus();
}

Character::Character(Character& other) {
    // Copy primitive member variables
    this->level = other.level;
    this->fighterType = other.fighterType;
    this->abilityScores = other.abilityScores;
    this->abilityModifiers = other.abilityModifiers;
    this->hitPoints = other.hitPoints;
    this->armorClass = other.armorClass;
    this->attackBonus = other.attackBonus;
    this->damageBonus = other.damageBonus;
    this->nbOfAttacksPerRound = other.nbOfAttacksPerRound;
    this->dice = other.dice;

    //// Deep copy of equipped items
    //this->armor = (other.armor != nullptr) ? new Armor(*other.armor) : nullptr;
    //this->shield = (other.shield != nullptr) ? new Shield(*other.shield) : nullptr;
    //this->weapon = (other.weapon != nullptr) ? new Weapon(*other.weapon) : nullptr;
    //this->boots = (other.boots != nullptr) ? new Boots(*other.boots) : nullptr;
    //this->ring = (other.ring != nullptr) ? new Ring(*other.ring) : nullptr;
    //this->helmet = (other.helmet != nullptr) ? new Helmet(*other.helmet) : nullptr;

    //// Deep copy of backpack items
    //this->backpack = (other.backpack != nullptr) ? new Backpack(*other.backpack) : nullptr;
}


Character::Character(int level, FighterType fighterType, CharacterStrategy* strategy) : level(level), fighterType(fighterType), actionStrategy(strategy), armor(nullptr)
{
    generateAbilityScores();
    calculateAbilityModifiers();
    calculateHitPoints();
    calculateArmorClass();
    calculateAttackBonus();
    calculateDamageBonus();
}

void Character::setStrategy(CharacterStrategy* strategy) {
    actionStrategy = strategy;
}

void Character::performMove(Map& map) {
    actionStrategy->move(*this, map);
}

void Character::performMoveGUI(Map& map, int targetX, int targetY) {
    actionStrategy->moveGUI(*this, map, targetX, targetY);
}

void Character::performAttack(Map& map) {
    actionStrategy->attack(*this, map);
}

void Character::performFreeActions() {
    actionStrategy->freeAction(*this);
}

//! Generates ability scores for the character by rolling 3d6 for each score.
void Character::generateAbilityScores() {
    for (int& score : abilityScores) {
        score = dice.rollDice("3d6");
    }
}

//! Calculates ability modifiers based on the ability scores.
void Character::calculateAbilityModifiers() {
    for (int i = 0; i < 6; ++i) {
        abilityModifiers[i] = (abilityScores[i] - 10) / 2;
    }
}

//! Calculates hit points for the character based on level and constitution modifier.
void Character::calculateHitPoints() {
    int conMod = getAbilityModifier(2);
    hitPoints = 10 + conMod + (level - 1) * (5 + conMod);
}

//! Calculates armor class for the character based on dexterity modifier.
void Character::calculateArmorClass() {
    int dexMod = getAbilityModifier(1);
    armorClass = 10 + dexMod;
    //if (armor) armorClass += armor->armorBonus;
}

//! Calculates attack bonus for the character based on level and strength modifier.
void Character::calculateAttackBonus() {
    int strMod = getAbilityModifier(0);
    attackBonus = level + strMod;
}

//! Calculates damage bonus for the character based on strength modifier.
void Character::calculateDamageBonus() {
    int strMod = getAbilityModifier(0);
    damageBonus = strMod;
}

//! Equips armor to the character.
//! @param a Pointer to the armor object to be equipped.
void Character::equipArmor(Armor* a) {
    armor = a;
    calculateArmorClass();
    notify();
}

//! Equips a shield to the character.
//! @param s Pointer to the shield object to be equipped.
void Character::equipShield(Shield* s) {
    shield = s;
    notify();
}

//! Equips a weapon to the character.
//! @param w Pointer to the weapon object to be equipped.
void Character::equipWeapon(Weapon* w) {
    weapon = w;
    calculateAttackBonus();
    calculateDamageBonus();
    notify();
}

//! Equips boots to the character.
//! @param b Pointer to the boots object to be equipped.
void Character::equipBoots(Boots* b) {
    boots = b;
    notify();
}

//! Equips a ring to the character.
//! @param r Pointer to the ring object to be equipped.
void Character::equipRing(Ring* r) {
    ring = r;
    notify();
}

//! Equips a helmet to the character.
//! @param h Pointer to the helmet object to be equipped.
void Character::equipHelmet(Helmet* h) {
    helmet = h;
    notify();
}

Armor* Character::getArmor() const
{
    if (armor != nullptr) {
        return armor; 
    }
    else {
        return NULL;
    }
}

Shield* Character::getShield() const
{
    if (shield != nullptr) {
        return shield;
    }
    else {
        return NULL;
    }
}

Weapon* Character::getWeapon() const
{
    if (weapon != nullptr) {
        return weapon;
    }
    else {
        return NULL;
    }
}

Boots* Character::getBoots() const
{
    if (boots != nullptr) {
        return boots;
    }
    else {
        return NULL;
    }
}

Ring* Character::getRing() const
{
    if (ring != nullptr) {
        return ring;
    }
    else {
        return NULL;
    }
}

Helmet* Character::getHelmet() const
{
    if (helmet != nullptr) {
        return helmet;
    }
    else {
        return NULL;
    }
}

void Character::removeArmor() {
    if (armor) {
        armor = nullptr;
        calculateArmorClass();
        notify();
    }
}

//! Unequips the shield from the character.
void Character::removeShield() {
    if (shield) {
        shield = nullptr;
        // Update any stats if necessary
        notify();
    }
}

//! Unequips the weapon from the character.
void Character::removeWeapon() {
    if (weapon) {
        weapon = nullptr;
        delete weapon;
        calculateAttackBonus();
        calculateDamageBonus();  
        notify();
    }
}

//! Unequips the boots from the character.
void Character::removeBoots() {
    if (boots) {
        boots = nullptr;
        delete boots;
        notify();
    }
}

//! Unequips the ring from the character.
void Character::removeRing() {
    if (ring) {
        ring = nullptr;
        delete ring;
        notify();
    }
}

//! Unequips the helmet from the character.
void Character::removeHelmet() {
    if (helmet) {
        helmet = nullptr;
        delete helmet;
        notify();
    }
}

/* Unequips the belt from the character(assuming there's a belt field).
void Character::removeBelt() {
    if (belt) {
        belt = nullptr;
         Update any stats if necessary
        notify();
    }
}
*/



//! Retrieves the level of the character.
//! @return The level of the character.
int Character::getLevel() const {
    return level;
}

string Character::getName() const
{
    return name;
}

void Character::setName(string newName)
{
    name = newName;
}

//! Retrieves the character type of the character.
//! @return The character type of the character.
FighterType Character::getFighterType() const {
    return fighterType;
}

//! Retrieves the ability score at the specified index.
//! @param index The index of the ability score to retrieve.
//! @return The ability score at the specified index.
int Character::getAbilityScore(int index) const {
    return abilityScores[index];
}

//! Retrieves the ability modifier at the specified index.
//! @param index The index of the ability modifier to retrieve.
//! @return The ability modifier at the specified index.
int Character::getAbilityModifier(int index) const {
    return abilityModifiers[index];
}

//! Retrieves the hit points of the character.
//! @return The hit points of the character.
int Character::getHitPoints() const {
    return hitPoints;
}

//! Retrieves the armor class of the character.
//! @return The armor class of the character.
int Character::getArmorClass() const {
    return armorClass;
}

//! Retrieves the attack bonus of the character.
//! @return The attack bonus of the character.
int Character::getAttackBonus() const {
    return attackBonus;
}

//! Retrieves the damage bonus of the character.
//! @return The damage bonus of the character.
int Character::getDamageBonus() const {
    return damageBonus;
}



void Character::levelUp()
{
    this->level += 1;

    int diceValue = dice.rollDice("1d10");
    this->hitPoints += diceValue;

    int constitutionModifier = abilityScores[2];
    this->hitPoints += constitutionModifier;

    this->attackBonus += 1;

    int numberOfAttacksPerRound = floor(getLevel() / 5);

    this->nbOfAttacksPerRound = numberOfAttacksPerRound;
}

//! Prints information about the character.
void Character::printCharacter() const {
    cout << "Name: " << name << "\n"
        << "Class: " << fighterTypeToString(getFighterType()) << "\n"
        << "Level: " << level << "\n"
        << "HP: " << hitPoints << ", AC: " << armorClass << ", AttackBonus: " << attackBonus << ", DamageBonus: " << damageBonus << "\n"
        << "STR: " << abilityScores[0] << " (" << abilityModifiers[0] << "), "
        << "DEX: " << abilityScores[1] << " (" << abilityModifiers[1] << "), "
        << "CON: " << abilityScores[2] << " (" << abilityModifiers[2] << "), "
        << "INT: " << abilityScores[3] << " (" << abilityModifiers[3] << "), "
        << "WIS: " << abilityScores[4] << " (" << abilityModifiers[4] << "), "
        << "CHA: " << abilityScores[5] << " (" << abilityModifiers[5] << ")\n";

    cout << "Equipped Armor: " << (getArmor() ? getArmor()->getName() : "---") << endl;
    cout << "Equipped Shield: " << (getShield() ? getShield()->getName() : "---") << endl;
    cout << "Equipped Weapon: " << (getWeapon() ? getWeapon()->getName() : "---") << endl;
    cout << "Equipped Boots: " << (getBoots() ? getBoots()->getName() : "---") << endl;
    cout << "Equipped Ring: " << (getRing() ? getRing()->getName() : "---") << endl;
    cout << "Equipped Helmet: " << (getHelmet() ? getHelmet()->getName() : "---") << endl;

}

void Character::logCharacter(ostream& out) const {
    out << "Name: " << name << "\n"
        << "Class: " << fighterTypeToString(getFighterType()) << "\n"
        << "Level: " << level << "\n"
        << "HP: " << hitPoints << ", AC: " << armorClass << ", AttackBonus: " << attackBonus << ", DamageBonus: " << damageBonus << "\n"
        << "STR: " << abilityScores[0] << " (" << abilityModifiers[0] << "), "
        << "DEX: " << abilityScores[1] << " (" << abilityModifiers[1] << "), "
        << "CON: " << abilityScores[2] << " (" << abilityModifiers[2] << "), "
        << "INT: " << abilityScores[3] << " (" << abilityModifiers[3] << "), "
        << "WIS: " << abilityScores[4] << " (" << abilityModifiers[4] << "), "
        << "CHA: " << abilityScores[5] << " (" << abilityModifiers[5] << ")\n";

    out << "Equipped Armor: " << (getArmor() ? getArmor()->getName() : "---") << std::endl
        << "Equipped Shield: " << (getShield() ? getShield()->getName() : "---") << std::endl
        << "Equipped Weapon: " << (getWeapon() ? getWeapon()->getName() : "---") << std::endl
        << "Equipped Boots: " << (getBoots() ? getBoots()->getName() : "---") << std::endl
        << "Equipped Ring: " << (getRing() ? getRing()->getName() : "---") << std::endl
        << "Equipped Helmet: " << (getHelmet() ? getHelmet()->getName() : "---") << std::endl;
}
void Character::display() {
    cout << "Name: " << name << "\n"
        << "Class: " << fighterTypeToString(getFighterType()) << "\n"
        << "Level: " << level << "\n"
        << "HP: " << hitPoints << ", AC: " << armorClass << ", AttackBonus: " << attackBonus << ", DamageBonus: " << damageBonus << "\n"
        << "STR: " << abilityScores[0] << " (" << abilityModifiers[0] << "), "
        << "DEX: " << abilityScores[1] << " (" << abilityModifiers[1] << "), "
        << "CON: " << abilityScores[2] << " (" << abilityModifiers[2] << "), "
        << "INT: " << abilityScores[3] << " (" << abilityModifiers[3] << "), "
        << "WIS: " << abilityScores[4] << " (" << abilityModifiers[4] << "), "
        << "CHA: " << abilityScores[5] << " (" << abilityModifiers[5] << ")\n";
        
    cout << "Equipped Helmet: " << (CharacterUtils::getHelmet(this) ? CharacterUtils::getHelmet(this)->getName() : "---") << endl;
    cout << "Equipped Armor: " << (CharacterUtils::getArmor(this) ? CharacterUtils::getArmor(this)->getName() : "---") << endl;
    cout << "Equipped Shield: " << (CharacterUtils::getShield(this) ? CharacterUtils::getShield(this)->getName() : "---") << endl;
    cout << "Equipped Ring: " << (CharacterUtils::getRing(this) ? CharacterUtils::getRing(this)->getName() : "---") << endl;
    cout << "Equipped Belt: " << (CharacterUtils::getBelt(this) ? CharacterUtils::getBelt(this)->getName() : "---") << endl;
    cout << "Equipped Boots: " << (CharacterUtils::getBoots(this) ? CharacterUtils::getBoots(this)->getName() : "---") << endl;
    cout << "Equipped Weapon: " << (CharacterUtils::getWeapon(this) ? CharacterUtils::getWeapon(this)->getName() : "---") << endl;

    ofstream logFile("./game_log.txt", ios::app);
    if (logFile.is_open()) {
        time_t t = time(nullptr);
        tm tm;
        localtime_s(&tm, &t);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);
        string timestamp(buffer);
        logFile << "============ Equipping Item ============" << endl;
        logFile << "Timestamp: " << timestamp << endl;
        logFile << "Equipped Helmet: " << (CharacterUtils::getHelmet(this) ? CharacterUtils::getHelmet(this)->getName() : "---") << endl;
        logFile << "Equipped Armor: " << (CharacterUtils::getArmor(this) ? CharacterUtils::getArmor(this)->getName() : "---") << endl;
        logFile << "Equipped Shield: " << (CharacterUtils::getShield(this) ? CharacterUtils::getShield(this)->getName() : "---") << endl;
        logFile << "Equipped Ring: " << (CharacterUtils::getRing(this) ? CharacterUtils::getRing(this)->getName() : "---") << endl;
        logFile << "Equipped Belt: " << (CharacterUtils::getBelt(this) ? CharacterUtils::getBelt(this)->getName() : "---") << endl;
        logFile << "Equipped Boots: " << (CharacterUtils::getBoots(this) ? CharacterUtils::getBoots(this)->getName() : "---") << endl;
        logFile << "Equipped Weapon: " << (CharacterUtils::getWeapon(this) ? CharacterUtils::getWeapon(this)->getName() : "---") << endl;
        logFile << "\n";
        logFile.close();
    }
}

void Character::applyEnhancement(CharacterStat stat, int bonus) {
    // Implementation of applyEnhancement method goes here

}

//! Converts a character type enum value to its string representation.
//! @param characterType The character type enum value.
//! @return The string representation of the character type.
string characterTypeToString(CharacterType characterType) {
    switch (characterType) {
    case CharacterType::FIGHTER: return "FIGHTER";
    case CharacterType::SORCERER: return "SORCERER";
    case CharacterType::MONK: return "MONK";
    case CharacterType::PALADIN: return"PALADIN";
    case CharacterType::BARD: return "BARD";
    case CharacterType::BARBARIAN: return "BARBARIAN";
    default: return "Unknown CharacterType";
    }
}

//! Converts a fighter type enum value to its string representation.
//! @param fighterType The character type enum value.
//! @return The string representation of the fighter type.
string fighterTypeToString(FighterType fighterType) {
    switch (fighterType) {
    case FighterType::BULLY: return "BULLY";
    case FighterType::NIMBLE: return "NIMBLE";
    case FighterType::TANK: return "TANK";
    default: return "Unknown FighterType";
    }
}

void Character::takeDamage(int damage) {
    hitPoints -= damage;

    if (hitPoints <= 0) {
        std::cout << name << " has been defeated.\n";
    }
    else {
        std::cout << name << " now has " << hitPoints << " hit points remaining.\n";
    }

    notify();
}

StrategyType Character::getStrategyType() const {
    if (actionStrategy) {
        return actionStrategy->getStrategyType();
    }
    return StrategyType::Player;
}

bool Character::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return false;
    }

    HumanPlayerStrategy hps;
    this->setStrategy(&hps);

    string line;
    string name;
    FighterType fighterType;
    int level;
    int hitPoints, armorClass, attackBonus, damageBonus;
    array<int, 6> abilityScores; // STR, DEX, CON, INT, WIS, CHA
    array<int, 6> abilityModifiers;

    string armor;

    // Read character data from the file
    while (getline(file, line)) {
        istringstream iss(line);
        string key;
        if (iss >> key) {
            if (key == "Name:") {
                getline(iss, name);
                name = name.substr(1); // Remove leading space
            }
            else if (key == "Class:") {
                std::string classStr;
                std::getline(iss, classStr);
                if (classStr == " TANK") {
                    fighterType = FighterType::TANK;
                }
                else if (classStr == " BULLY") {
                    fighterType = FighterType::BULLY;
                }
                else if (classStr == " NIMBLE") {
                    fighterType = FighterType::NIMBLE;
                }
            }
            else if (key == "Level:") {
                iss >> level;
            }
            else if (key == "HP:") {
                char comma;
                iss >> hitPoints >> comma >> key >> armorClass >> comma >> key >> attackBonus >> comma >> key >> damageBonus;
            }
            else if (key == "STR:") {
                char comma;
                char paren;
                iss >> abilityScores[0] >> paren >> abilityModifiers[0] >> paren >> comma >> key >> abilityScores[1] >> paren >> abilityModifiers[1] >> paren >> comma >> key >> abilityScores[2] >> paren >> abilityModifiers[2] >> paren >> comma >> key >> abilityScores[3] >> paren >> abilityModifiers[3] >> paren >> comma >> key >> abilityScores[4] >> paren >> abilityModifiers[4] >> paren >> comma >> key >> abilityScores[5] >> paren >> abilityModifiers[5] >> paren;
            }
            else if (key == "Equipped Armor:") {
                iss >> armor;
            }
            else if (key == "Equipped Shield:") {
                iss >> armor;
            }
            else if (key == "Equipped Weapon:") {
                iss >> armor;
            }
            else if (key == "Equipped Boots:") {
                iss >> armor;
            }
            else if (key == "Equipped Ring:") {
                iss >> armor;
            }
            else if (key == "Equipped Helmet:") {
                iss >> armor;
            }
        }
    }

    this->name = name;
    this->fighterType = fighterType;
    this->level = level;
    this->hitPoints = hitPoints;
    this->armorClass = armorClass;
    this->attackBonus = attackBonus;
    this->damageBonus = damageBonus;

    for (int i = 0; i < 6; ++i) {
        this->abilityScores[i] = abilityScores[i];
        this->abilityModifiers[i] = abilityModifiers[i];
    }

    return true;
}

void Character::addToInventory(Item* item) {
    if (!backpack) {
        backpack = new Backpack("Character Backpack");
    }
    backpack->addItem(item);
}
