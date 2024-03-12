//! @file
//! @brief File containing the Test Class declaration for Dice
//!

#pragma once
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../Dice/Dice.h"

/**
 * @class TestDice
 * @brief Test suite for the Dice class.
 *
 * This class tests the functionality of the Dice class, ensuring that dice rolls
 * are handled correctly according to various input scenarios.
 */
class TestDice : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TestDice);
    CPPUNIT_TEST(testRollDiceInvalidFormat);
    CPPUNIT_TEST(testRollDiceInvalidDiceType);
    CPPUNIT_TEST(testRollDiceValid);
    CPPUNIT_TEST_SUITE_END();

public:
    /**
     * @brief Sets up the test environment before each test.
     */
    void setUp(void);

    /**
     * @brief Cleans up the test environment after each test.
     */
    void tearDown(void);

protected:
    /**
     * @brief Tests the Dice class with invalid format strings.
     */
    void testRollDiceInvalidFormat(void);

    /**
     * @brief Tests the Dice class with invalid dice types.
     */
    void testRollDiceInvalidDiceType(void);

    /**
     * @brief Tests the Dice class with valid roll expressions.
     */
    void testRollDiceValid(void);

private:
    Dice* DiceObject; ///< Pointer to the Dice instance used for testing.
};

//! @brief Register the test suite.
CPPUNIT_TEST_SUITE_REGISTRATION(TestDice);