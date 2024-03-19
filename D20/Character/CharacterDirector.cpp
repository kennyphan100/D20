#include "CharacterDirector.h"

CharacterDirector::CharacterDirector() : builder(nullptr) {}

CharacterDirector::~CharacterDirector() {
    delete builder;
}

void CharacterDirector::setBuilder(CharacterBuilder* newBuilder) {
    builder = newBuilder;
}

Character* CharacterDirector::buildCharacter(int level) {
    if (builder) {
        builder->assignFighterType();
        builder->assignLevel(level);
        builder->buildAbilityScores();
        return builder->getCharacter();
    }
    return nullptr;
}
