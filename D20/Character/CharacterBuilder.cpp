#include "CharacterBuilder.h"

CharacterBuilder::CharacterBuilder() : character(new Character(1, FighterType::TANK)) {}

CharacterBuilder::~CharacterBuilder() {
    delete character;
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
}

