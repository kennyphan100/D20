#pragma once
#ifndef CHARACTER_DIRECTOR_H
#define CHARACTER_DIRECTOR_H

#include "CharacterBuilder.h"

class CharacterDirector : public Observable {
    CharacterBuilder* builder;

public:
    CharacterDirector();
    ~CharacterDirector();
    void setBuilder(CharacterBuilder* newBuilder);
    Character* buildCharacter(int level, string name);
};

#endif
