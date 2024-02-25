//! @file
//! @brief Header file for the TestCharacter class - CppUnit test cases for the Character class.
//!

#ifndef TESTCHARACTER_H
#define TESTCHARACTER_H

#pragma once
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "Character.h"

/**
 * @class TestCharacter
 * @brief Test class for Character, utilizing the CppUnit framework.
 *
 * This class is designed to implement test cases for testing the functionality of the Character class. It aims to verify the correctness
 * of the character initialization, ability score generation, ability modifiers calculation, hit points calculation, armor class calculation,
 * attack bonus calculation, damage bonus calculation, and the equipment functionality.
 */
class TestCharacter : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TestCharacter);
    CPPUNIT_TEST(testConstructor);
    CPPUNIT_TEST(testGenerateAbilityScores);
    CPPUNIT_TEST(testCalculateAbilityModifiers);
    CPPUNIT_TEST(testCalculateHitPoints);
    CPPUNIT_TEST(testCalculateArmorClass);
    CPPUNIT_TEST(testCalculateAttackBonus);
    CPPUNIT_TEST(testCalculateDamageBonus);
    CPPUNIT_TEST_SUITE_END();

public:
    /**
     * @brief Set up the test fixtures.
     *
     * This method is called before each test case method is executed. It is used to initialize the objects and data
     * structures required for the tests.
     */
    void setUp();

    /**
     * @brief Tear down the test fixtures.
     *
     * This method is called after each test case method has been executed. It is used to perform any necessary cleanup
     * operations, such as deallocating resources used during the test.
     */
    void tearDown();

    // Test methods documentation

    //! @brief Tests the Character constructor for correct initialization of attributes.
    void testConstructor();

    //! @brief Tests the generateAbilityScores method for generating ability scores within the expected range.
    void testGenerateAbilityScores();

    //! @brief Tests the calculateAbilityModifiers method for correct calculation of ability modifiers based on ability scores.
    void testCalculateAbilityModifiers();

    //! @brief Tests the calculateHitPoints method for correct calculation of hit points based on level and constitution modifier.
    void testCalculateHitPoints();

    //! @brief Tests the calculateArmorClass method for correct calculation of armor class based on dexterity modifier and equipped armor.
    void testCalculateArmorClass();

    //! @brief Tests the calculateAttackBonus method for correct calculation of attack bonus based on level and strength/dexterity modifiers.
    void testCalculateAttackBonus();

    //! @brief Tests the calculateDamageBonus method for correct calculation of damage bonus based on strength modifier.
    void testCalculateDamageBonus();

private:
    Character* character; ///< Pointer to a Character object used for testing.
};

#endif // TESTCHARACTER_H
