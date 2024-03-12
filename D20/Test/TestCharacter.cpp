//! @file
//! @brief Implementation file for TestCharacter - CppUnit test cases for the Character class.
//!

#include "TestCharacter.h"
#include <cppunit/config/SourcePrefix.h>
#include "../Character/Character.h"
#include <iostream>
#include <cassert>

//! setUp() method that is executed before each test case.
void TestCharacter::setUp() {
    // Example setup: Initialize a Level 1 Fighter for testing
    character = new Character(1, CharacterType::FIGHTER);
}

//! tearDown() method that is executed after each test case. Typically used for deallocation.
void TestCharacter::tearDown() {
    delete character;
    character = nullptr;
}

//! Test Case: Testing constructor for correct initialization of attributes.
void TestCharacter::testConstructor() {
    CPPUNIT_ASSERT(character != nullptr);
    CPPUNIT_ASSERT_EQUAL(1, character->getLevel());
    CPPUNIT_ASSERT_EQUAL(CharacterType::FIGHTER, character->getCharacterType());
}

//! Test Case: Testing ability score generation within expected range.
void TestCharacter::testGenerateAbilityScores() {
    character->generateAbilityScores();
    for (int i = 0; i < 6; ++i) {
        CPPUNIT_ASSERT(character->getAbilityScore(i) >= 3 && character->getAbilityScore(i) <= 18);
    }
}

//! Test Case: Testing calculation of ability modifiers based on ability scores.
void TestCharacter::testCalculateAbilityModifiers() {
    character->generateAbilityScores();
    character->calculateAbilityModifiers();
    for (int i = 0; i < 6; ++i) {
        int expectedMod = (character->getAbilityScore(i) - 10) / 2;
        CPPUNIT_ASSERT_EQUAL(expectedMod, character->getAbilityModifier(i));
    }
}

//! Test Case: Testing calculation of hit points based on level and constitution modifier.
void TestCharacter::testCalculateHitPoints() {
    character->generateAbilityScores();
    character->calculateAbilityModifiers();
    character->calculateHitPoints();
    int expectedHP = 10 + character->getAbilityModifier(2);
    CPPUNIT_ASSERT_EQUAL(expectedHP, character->getHitPoints());
}

//! Test Case: Testing calculation of armor class based on dexterity modifier and equipped armor.
void TestCharacter::testCalculateArmorClass() {
    character->generateAbilityScores();
    character->calculateAbilityModifiers();
    character->calculateArmorClass();
    int expectedAC = 10 + character->getAbilityModifier(1);
    CPPUNIT_ASSERT_EQUAL(expectedAC, character->getArmorClass());
}

//! Test Case: Testing calculation of attack bonus based on level and strength/dexterity modifiers.
void TestCharacter::testCalculateAttackBonus() {
    character->generateAbilityScores();
    character->calculateAbilityModifiers();
    character->calculateAttackBonus();
    int expectedAB = 1 + character->getAbilityModifier(0);
    CPPUNIT_ASSERT_EQUAL(expectedAB, character->getAttackBonus());
}

//! Test Case: Testing calculation of damage bonus based on strength modifier.
void TestCharacter::testCalculateDamageBonus() {
    character->generateAbilityScores();
    character->calculateAbilityModifiers();
    character->calculateDamageBonus();
    int expectedDB = character->getAbilityModifier(0);
    CPPUNIT_ASSERT_EQUAL(expectedDB, character->getDamageBonus());
}
