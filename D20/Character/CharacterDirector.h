#pragma once
#ifndef CHARACTER_DIRECTOR_H
#define CHARACTER_DIRECTOR_H

#include "CharacterBuilder.h"

class CharacterDirector {
    CharacterBuilder* builder;

public:
    CharacterDirector();
    ~CharacterDirector();
    void setBuilder(CharacterBuilder* newBuilder);
    Character* buildCharacter(int level);
};

#endif
