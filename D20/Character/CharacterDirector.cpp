#include "CharacterDirector.h"

CharacterDirector::CharacterDirector() : builder(nullptr) {}

CharacterDirector::~CharacterDirector() {
    delete builder;
}

void CharacterDirector::setBuilder(CharacterBuilder* newBuilder) {
    builder = newBuilder;
}

Character* CharacterDirector::buildCharacter(int level, string name) {
    if (builder) {
        builder->assignFighterType();
        builder->assignLevel(level);
        builder->assignName(name);
        builder->buildAbilityScores();
        builder->saveToFile("./data/characters/" + name + ".txt");
        return builder->getCharacter();
    }
    notify();
    return nullptr;
}
