#pragma once
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "Dice.h"

class TestDice : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TestDice);
    CPPUNIT_TEST(testRollDiceInvalidFormat);
    CPPUNIT_TEST(testRollDiceInvalidDiceType);
    CPPUNIT_TEST(testRollDiceValid);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp(void);
    void tearDown(void);

protected:
    void testRollDiceInvalidFormat(void);
    void testRollDiceInvalidDiceType(void);
    void testRollDiceValid(void);
private:
    Dice* DiceObject;
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestDice);